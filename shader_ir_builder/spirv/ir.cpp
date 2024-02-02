#include "ir.hpp"

namespace irb {

SPIRVBuilder::SPIRVBuilder(Context& aContext, const std::string& aCompilerName, bool aIncludeDebugInformation) : IRBuilder(aContext, aCompilerName, aIncludeDebugInformation) {
    blockHeader = new SPIRVBlock(context);
    blockDebug = new SPIRVBlock(context);
    blockAnnotations = new SPIRVBlock(context);
    blockTypesVariablesConstants = new SPIRVBlock(context);
    blockMain = new SPIRVBlock(context);

    //TODO: do not hardcode these values
    blockHeader->addCodeRawToBeginning(
"; SPIR-V\n" \
"; Version:   " + spirvVersionMap[spirvVersion] + "\n" \
"; Generator: " + compilerName + "; 11\n" \
"; Bound:     385\n" \
"; Schema:    0\n" \
"\n");

    blockHeader->addCodeToBeginning("OpCapability Shader");
    //TODO: make these optional
    blockHeader->addCodeToBeginning("OpCapability Float16");
    blockHeader->addCodeToBeginning("OpCapability Int8");
    blockHeader->addCodeToBeginning("OpCapability Int16");

    blockDebug->addCodeRawToBeginning("; Debug information\n");
    blockAnnotations->addCodeRawToBeginning("; Annotations (non-debug)\n");
    blockTypesVariablesConstants->addCodeRawToBeginning("; All types, variables, and constants\n");
    blockMain->addCodeRawToBeginning("; All functions\n");
}

void SPIRVBuilder::opExtension(const std::string& extensionName)  {
    blockHeader->addCodeToBeginning("OpExtension \"" + extensionName + "\"");
}

void SPIRVBuilder::opImportSTD_EXT(const std::string& stdName)  {
    importV = new Value(context, nullptr, "import");
    blockHeader->addCodeToBeginning("OpExtInstImport \"" + stdName + "\"", importV);
}

void SPIRVBuilder::opMemoryModel()  {
    blockHeader->addCodeToBeginning("OpMemoryModel Logical GLSL450");
}

void SPIRVBuilder::opEntryPoint(Value* entryPoint, FunctionRole functionRole, const std::string& name, Type* returnType, const std::vector<Argument>& arguments)  {
    Function* oldFunction = function;
    Value* entryPointFunction = opFunction(new FunctionType(context, new ScalarType(context, TypeID::Void, 0, true), {}));

    GET_FUNCTION_ROLE_NAME(functionRole);
    std::string code = "OpEntryPoint " + functionRoleStr + " " + entryPointFunction->getName() + " \"" + name + "\"";
    //TODO: support other origins as well
    if (functionRole == FunctionRole::Fragment)
        blockHeader->addCode("OpExecutionMode " + entryPointFunction->getName() + " OriginUpperLeft");
    //blockHeader->addCode("OpSource GLSL 450");
    //blockHeader->addCode("OpSourceExtension \"GL_GOOGLE_cpp_style_line_directive\"");
    //blockHeader->addCode("OpSourceExtension \"GL_GOOGLE_include_directive\"");

    //Body
    Block* block = opBlock();
    setInsertBlock(block);

    // -------- Input --------
    std::vector<Value*> argValues;
    argValues.reserve(arguments.size());
    for (const auto& argument : arguments) {
        Type* type = argument.type;
        const auto& attr = argument.attributes;

        StorageClass storageClass = StorageClass::MaxEnum;
        //TODO: do not hardcode the storage classes
        if (attr.isBuffer)
            storageClass = StorageClass::Uniform;
        else if (attr.isTexture)
            storageClass = StorageClass::UniformConstant;
        else if (attr.isSampler)
            storageClass = StorageClass::UniformConstant;
        else if (attr.isInput)
            storageClass = StorageClass::Input;
            
        Value* argValue = opVariable(new PointerType(context, type, storageClass));
    
        //TODO: check if these decorations are correct
        //TODO: support other storage classes as well
        Structure* structure;
        switch (storageClass) {
        case StorageClass::Uniform:
        case StorageClass::UniformConstant:
            opDecorate(argValue, Decoration::DescriptorSet, {std::to_string(attr.bindings.set)});
            opDecorate(argValue, Decoration::Binding, {std::to_string(attr.bindings.binding)});
            break;
        case StorageClass::Input:
            switch (functionRole) {
            case FunctionRole::Vertex:
                //TODO: do this somewhere else
                //TODO: don't throw this error
                if (!type->isStructure()) {
                    IRB_ERROR("Entry point argument declared with the 'input' attribute must have a structure type");
                    return;
                }
                structure = static_cast<StructureType*>(type)->getStructure();
                for (uint32_t i = 0; i < structure->members.size(); i++)
                    opMemberDecorate(type->getValue(this), i, Decoration::Location, {std::to_string(structure->members[i].attributes.locationIndex)});
                break;
            case FunctionRole::Fragment:
                opDecorate(argValue, Decoration::Location, {"0"});
                break;
            default:
                IRB_ERROR("kernel functions cannot have 'input' attribute");
            }
            break;
        default:
            break;
        }
        if (attr.isBuffer || (functionRole == FunctionRole::Vertex && attr.isInput))
            opDecorate(type->getValue(this, true), Decoration::Block);
        
        //Add to interface
        if (spirvVersionIsGreaterThanOrEqual(SPIRVVersion::_1_4) || (storageClass == StorageClass::Input || storageClass == StorageClass::Output))
            code += " " + argValue->getName();
        
        //HACK: create a new variable, since we need to have the 'Function' storage class
        Value* loadedAndStoredArgValue = opVariable(new PointerType(context, type, StorageClass::Function));
        opStore(loadedAndStoredArgValue, opLoad(argValue));
        argValues.push_back(loadedAndStoredArgValue);
    }

    // -------- Call to entry point --------
    Value* returnValue = opFunctionCall(entryPoint, argValues);

    // -------- Output --------
    opDecorate(returnType->getValue(this), Decoration::Block);
    context.pushRegisterName(name + "_output");
    Value* returnVariable = opVariable(new PointerType(context, returnType, StorageClass::Output));
    opStore(returnVariable, returnValue);
    Value* positionVariable = nullptr;
    if (functionRole == FunctionRole::Vertex) {
        opDecorate(returnVariable, Decoration::Location, {"0"});
    
        context.pushRegisterName("position");
        positionVariable = opVariable(new PointerType(context, new VectorType(context, new ScalarType(context, TypeID::Float, 32, true), 4), StorageClass::Output));
        opDecorate(positionVariable, Decoration::Position);
    }
    
    if (functionRole == FunctionRole::Vertex) {
        //TODO: don't throw this error
        if (!returnType->isStructure()) {
            IRB_ERROR("Entry point argument declared with the 'output' attribute must have a structure type");
            return;
        }
        Structure* structure = static_cast<StructureType*>(returnType)->getStructure();
        Value* positionV = nullptr;
        for (uint32_t i = 0; i < structure->members.size(); i++) {
            if (structure->members[i].attributes.isPosition) {
                Value* indexV = opConstant(new ConstantInt(context, i, 32, true));

                positionV = opGetElementPtr(new PointerType(context, structure->members[i].type, StorageClass::Output), returnVariable, {indexV});
                positionV = opLoad(positionV);
                break;
            }
        }
        if (positionV)
            opStore(positionVariable, positionV);
    } else if (functionRole == FunctionRole::Fragment) {
        //TODO: do this error check for every backend?
        if (!returnType->isStructure()) {
            IRB_ERROR("Entry point argument declared with the 'output' attribute must have a structure type");
            return;
        }
        //TODO: do this decoration somewhere else
        irb::Structure* structure = static_cast<StructureType*>(returnType)->getStructure();
        for (uint32_t i = 0; i < structure->members.size(); i++)
            opMemberDecorate(returnType->getValue(this), i, Decoration::Location, {std::to_string(structure->members[i].attributes.colorIndex)});
    }

    //Add to interface
    code += " " + returnVariable->getName();
    if (positionVariable)
        code += " " + positionVariable->getName();

    opReturn();

    opFunctionEnd();

    blockHeader->addCodeToBeginning(code);

    //Set the active function to be the old active funciton
    function = oldFunction;
}

void SPIRVBuilder::opName(Value* value, const std::string& name)  {
    if (includeDebugInformation && !dynamic_cast<StandardFunctionValue*>(value))
        blockDebug->addCode("OpName " + value->getName() + " \"" + name + "\"");
}

Value* SPIRVBuilder::opConstant(ConstantValue* val)  {
    Value* typeV = val->getType()->getValue(this);

    std::string str;
    if (val->getType()->getTypeID() == TypeID::Bool)
        str = "OpConstant" + std::string(val->getName() == "1" ? "True " : "False ") + typeV->getName();
    else
        str = "OpConstant " + typeV->getName() + " " + val->getName();

    return _addCodeToTypesVariablesConstantsBlock(typeV->getType(), str, context.popRegisterName());
}

Value* SPIRVBuilder::opStructureDefinition(StructureType* structureType)  {
    return new Value(context, structureType, context.popRegisterName());
}

Value* SPIRVBuilder::opRegisterFunction(FunctionType* functionType)  {
    return new Value(context, functionType, context.popRegisterName() + functionType->getTemplateName(), "%", false);
}

Value* SPIRVBuilder::opStandardFunctionDeclaration(FunctionType* functionType, const std::string& name)  {
    const auto& standardFunctionInfo = standardFunctionLUT[name];

    Value* returnV = functionType->getReturnType()->getValue(this);

    std::string fullName;
    if (standardFunctionInfo.spirv.requiresOpExtInst)
        fullName = "OpExtInst " + returnV->getName() + " " + importV->getName() + " ";
    else
        fullName = "Op";

    //TODO: only add template name if there is at least one argument
    if (standardFunctionInfo.spirv.argumentIndexForSpecialization != -1)
        fullName += functionType->getArguments()[standardFunctionInfo.spirv.argumentIndexForSpecialization]->getOpPrefix(true, false);
    fullName += standardFunctionInfo.spirv.name;
    if (!standardFunctionInfo.spirv.requiresOpExtInst)
        fullName += " " + returnV->getName();

    Value* value = new StandardFunctionValue(context, functionType, fullName, "", false);

    return value;
}

Value* SPIRVBuilder::opFunction(FunctionType* functionType, Value* value)  {
    if (!value)
        value = opRegisterFunction(functionType);
    function = new SPIRVFunction(context, this, functionType, blockTypesVariablesConstants, value);
    value = function->getValue();
    //TODO: uncomment?
    //if (includeDebugInformation && name.size() != 0)
    //    opName(name, value);

    return value;
}

Value* SPIRVBuilder::opFunctionParameter(Type* type)  {
    type = new PointerType(context, type, StorageClass::Function);
    Value* value = new Value(context, type, context.popRegisterName());
    getSPIRVInsertBlock()->addCode("OpFunctionParameter " + type->getValue(this)->getName(), value);

    return value;
}

void SPIRVBuilder::opFunctionEnd()  {
    function->end();
    blockMain->addCodeRaw(static_cast<SPIRVFunction*>(function)->getCode() + "\n");
}

Block* SPIRVBuilder::opBlock()  {
    SPIRVBlock* block = new SPIRVBlock(context, context.popRegisterName());
    block->addCodeToBeginning("OpLabel", block);

    return block;
}

Value* SPIRVBuilder::opOperation(Value* l, Value* r, Type* type, Operation operation)  {
    if (!type->isOperatorFriendly()) {
        IRB_INVALID_ARGUMENT_WITH_REASON("type", "type is not operator friendly (e.g. is not one of: scalar, pointer, vector)");
        return nullptr;
    }

    if (r->getType()->isVector() && l->getType()->isScalar())
        std::swap(l, r);
    Value* value = new Value(context, (type->getTypeID() == TypeID::Bool && l->getType()->isVector() ? new VectorType(context, type, static_cast<VectorType*>(l->getType())->getComponentCount()) : type), context.popRegisterName());
    Value* typeV = value->getType()->getValue(this);
    if (l->getType()->isVector() && r->getType()->isScalar()) {
        if (operation == Operation::Multiply && type->getBaseType()->getTypeID() == TypeID::Float) {
            getSPIRVInsertBlock()->addCode("OpVectorTimesScalar " + typeV->getName() + " " + l->getName() + " " + r->getName(), value);
            return value;
        } else {
            VectorType* vectorType = static_cast<VectorType*>(l->getType());
            r = opConstruct(vectorType, std::vector<Value*>(vectorType->getComponentCount(), opCast(r, vectorType->getBaseType()))); //TODO: check if the type is vector
        }
    }
    
    bool needsOrd = (operation == Operation::GreaterThan || operation == Operation::GreaterThanEqual || operation == Operation::LessThan || operation == Operation::LessThanEqual || operation == Operation::Equal || operation == Operation::NotEqual);
    bool signSensitive = (operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || operation == Operation::GreaterThan || operation == Operation::GreaterThanEqual || operation == Operation::LessThan || operation == Operation::LessThanEqual);
    bool needsPrefix = (operation == Operation::Add || operation == Operation::Subtract || operation == Operation::Multiply || operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || needsOrd);

    GET_OPERATION_NAME(operation);

    //TODO: do not use l for getting op prefix?
    getSPIRVInsertBlock()->addCode("Op" + (needsPrefix ? l->getType()->getOpPrefix(signSensitive, needsOrd) : "") + operationStr + " " + typeV->getName() + " " + l->getName() + " " + r->getName(), value);

    //"Unpack" the vector
    if (type->getTypeID() == TypeID::Bool && value->getType()->isVector()) {
        std::vector<Value*> resultComponents(static_cast<VectorType*>(value->getType())->getComponentCount());
        for (uint8_t i = 0; i < resultComponents.size(); i++) {
            context.pushRegisterName("vec_op_unpack");
            resultComponents[i] = opVectorExtract(value, new ConstantInt(context, i, 32, true));
        }
        value = resultComponents[0];
        for (uint8_t i = 1; i < resultComponents.size(); i++)
            value = opOperation(value, resultComponents[i], type, operation);
    }

    return value;
}

Value* SPIRVBuilder::opLoad(Value* v)  {
    if (!v->getType()->isPointer()) {
        std::cout << v->getType()->getNameForRegister() << " : " << v->getName() << std::endl;
        IRB_INVALID_ARGUMENT_WITH_REASON("v", "type of 'v' is not a pointer");
        return nullptr;
    }

    Type* elementType = v->getType()->getElementType();
    Value* elementTypeV = elementType->getValue(this);
    Value* value = new Value(context, elementType, context.popRegisterName());
    getSPIRVInsertBlock()->addCode("OpLoad " + elementTypeV->getName() + " " + v->getName(), value);

    return value;
}

void SPIRVBuilder::opStore(Value* ptr, Value* v)  {
    getSPIRVInsertBlock()->addCode("OpStore " + ptr->getName() + " " + v->getName());
}

void SPIRVBuilder::opReturn(Value* v)  {
    SPIRVBlock* block = getSPIRVInsertBlock();
    if (block->hasReturned()) {
        IRB_ERROR("cannot have more than 1 return instructions in a single block");
        return;
    }

    if (v)
        block->addCode("OpReturnValue " + v->getName());
    else
        block->addCode("OpReturn");
    
    block->setReturned();
}

//TODO: what should be returned when type is void?
Value* SPIRVBuilder::opFunctionCall(Value* funcV, const std::vector<Value*>& arguments)  {
    FunctionType* type = dynamic_cast<FunctionType*>(funcV->getType());
    if (!type) {
        IRB_INVALID_ARGUMENT_WITH_REASON("funcV", "type of 'funcV' is not a function");
        return nullptr;
    }
    //TODO: check if this is necessary
    type->getValue(this); //HACK: the standard library functions still don't have their returnV initialized at this point
    Value* returnV = type->getReturnV();
    Value* value = new Value(context, returnV->getType(), context.popRegisterName());
    std::string code;
    if (dynamic_cast<StandardFunctionValue*>(funcV))
        code = funcV->getName();
    else
        code = "OpFunctionCall " + returnV->getName() + " " + funcV->getName();
    for (auto* arg : arguments)
        code += " " + arg->getName();
    getSPIRVInsertBlock()->addCode(code, value);

    return value;
}

void SPIRVBuilder::opBranch(Block* block)  {
    if (!getSPIRVInsertBlock()->hasReturned())
        getSPIRVInsertBlock()->addCode("OpBranch " + block->getName());
}

void SPIRVBuilder::opBranchCond(Value* cond, Block* blockTrue, Block* blockFalse)  {
    getSPIRVInsertBlock()->addCode("OpBranchConditional " + cond->getName() + " " + blockTrue->getName() + " " + blockFalse->getName());
}

void SPIRVBuilder::opBlockMerge(Block* block)  {
    //TODO: support other stuff besides 'None'
    getSPIRVInsertBlock()->addCode("OpSelectionMerge " + block->getName() + " None");
}

void SPIRVBuilder::opLoopMerge(Block* block1, Block* block2)  {
    //TODO: support other stuff besides 'None'
    getSPIRVInsertBlock()->addCode("OpLoopMerge " + block1->getName() + " " + block2->getName() + " None");
}

Value* SPIRVBuilder::opConstruct(Type* type, const std::vector<Value*>& components)  {
    if (type->isVector()) {
        if (components.size() != static_cast<VectorType*>(type)->getComponentCount()) {
            IRB_INVALID_ARGUMENT_WITH_REASON("components", "the number of components must match the number of components of the vector type");
            return nullptr;
        }
    } else if (type->isMatrix()) {
        if (components.size() != static_cast<MatrixType*>(type)->getColumnCount()) {
            IRB_INVALID_ARGUMENT_WITH_REASON("components", "the number of components must match the number of columns of the matrix type");
            return nullptr;
        }
    }
    Value* typeV = type->getValue(this);
    Value* value = new Value(context, type, context.popRegisterName());
    bool isAllConstants = true;
    for (auto* component : components) {
        if (!component->isConstant()) {
            isAllConstants = false;
            break;
        }
    }
    std::string code = (isAllConstants ? "OpConstantComposite " : "OpCompositeConstruct ") + typeV->getName();
    for (auto* component : components)
        code += " " + component->getName();
    (isAllConstants ? blockTypesVariablesConstants : getSPIRVInsertBlock())->addCode(code, value);
    if (isAllConstants)
        value->setIsConstant(true);

    return value;
}

Value* SPIRVBuilder::opVectorExtract(Value* vec, ConstantInt* index)  {
    if (!vec->getType()->isVector()) {
        IRB_ERROR("cannot extract value from a non-vector type");
        return nullptr;
    }
    //VectorType* vecType = static_cast<VectorType*>(vec->getType());
    /*
    if (index->getInt() >= vecType->getComponentCount()) {
        error("trying to get element at index " + std::to_string(index->getInt()) + ", but vector has only " +  + " elements", "SPIRVBuilder::opVectorExtract");
        return nullptr;
    }
    */
    Type* type = vec->getType()->getBaseType();

    Value* value = new Value(context, type, context.popRegisterName());
    getSPIRVInsertBlock()->addCode("OpCompositeExtract " + type->getValue(this)->getName() + " " + vec->getName() + " " + index->getName(), value);

    return value;
}

Value* SPIRVBuilder::opVectorInsert(Value* vec, Value* val, ConstantInt* index)  {
    Value* value = new Value(context, vec->getType(), context.popRegisterName());
    getSPIRVInsertBlock()->addCode("OpCompositeInsert " + vec->getType()->getValue(this)->getName() + " " + val->getName() + " " + vec->getName() + " " + index->getName(), value);

    return value;
}

Value* SPIRVBuilder::opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes)  {
    if (!ptr->getType()->isPointer()) {
        IRB_INVALID_ARGUMENT_WITH_REASON("ptr", "type of 'ptr' is not pointer type");
        return nullptr;
    }
    Value* elementTypeV = elementType->getValue(this);
    Value* value = new Value(context, elementType, context.popRegisterName());
    std::string code = "OpAccessChain " + elementTypeV->getName() + " " + ptr->getName();
    for (auto* index : indexes)
        code += " " + index->getName();
    getSPIRVInsertBlock()->addCode(code, value);

    return value;
}

void SPIRVBuilder::opUnreachable()  {
    getSPIRVInsertBlock()->addCode("OpUnreachable");
}

Value* SPIRVBuilder::opCast(Value* val, Type* type)  {
    if (val->getType()->equals(type))
        return val;

    std::string opName = type->getCastOpName(val->getType());
    if (opName == "NP") { //Not possible
        //TODO: warn?
        return val;
    } if (opName == "NR") { //Not required
        return val;
    } else if (opName == "VC") { //Vector construct //TODO: I am actually not sure if I want this
        VectorType* srcVec = static_cast<VectorType*>(val->getType());
        VectorType* dstVec = static_cast<VectorType*>(type);
        if (srcVec->getComponentCount() < dstVec->getComponentCount()) {
            error("cannot cast from a vector with component count of " + std::to_string(srcVec->getComponentCount()) + " to a vector with component count of " + std::to_string(dstVec->getComponentCount()), "SPIRVBuilder::opCast");
            return nullptr;
        }
        std::vector<Value*> components(dstVec->getComponentCount());
        for (uint8_t i = 0; i < components.size(); i++)
            components[i] = opVectorExtract(val, new ConstantInt(context, i, 32, false));
        
        return opConstruct(dstVec, components);
    } else if (opName == "VCS") { //Vector construct from scalar
        VectorType* dstVec = static_cast<VectorType*>(type);

        return opConstruct(dstVec, std::vector<Value*>(dstVec->getComponentCount(), val));
    }

    Value* typeV = type->getValue(this);
    Value* value = new Value(context, type, context.popRegisterName());
    getSPIRVInsertBlock()->addCode("Op" + opName + " " + typeV->getName() + " " + val->getName(), value);

    return value;
}

Value* SPIRVBuilder::opSample(Value* funcV, Value* texture, Value* sampler, Value* coords, Value* lod)  {
    Value* sampledImageTypeV = new Value(context, nullptr, "sampledImageType");
    blockTypesVariablesConstants->addCode("OpTypeSampledImage " + texture->getType()->getValue(this)->getName(), sampledImageTypeV);

    Value* sampledImage = new Value(context, nullptr, "samplerTexTmp");
    getSPIRVInsertBlock()->addCode("OpSampledImage " + sampledImageTypeV->getName() + " " + texture->getName() + " " + sampler->getName(), sampledImage);

    if (!lod)
        lod = opConstant(new ConstantFloat(context, 0.0f, 32));
    Value* value = new Value(context, new VectorType(context, texture->getType()->getBaseType(), 4), context.popRegisterName());
    getSPIRVInsertBlock()->addCode("OpImageSampleExplicitLod " + value->getType()->getValue(this)->getName() + " " + sampledImage->getName() + " " + coords->getName() + " Lod " + lod->getName(), value);

    return value;
}

Value* SPIRVBuilder::opVariable(PointerType* type, Value* initializer)  {
    Value* typeV = type->getValue(this);
    Value* value = new Value(context, type, context.popRegisterName());
    StorageClass storageClass = type->getStorageClass();
    GET_STORAGE_CLASS_NAME(storageClass);
    std::string code = "OpVariable " + typeV->getName() + " " + storageClassStr;
    if (initializer) {
        if (initializer->isConstant())
            code += " " + initializer->getName();
        else
            opStore(value, initializer);
    }
    if (storageClass == StorageClass::Function)
        getSPIRVFirstFunctionBlock()->addCodeToBeginning(code, value);
    else
        blockTypesVariablesConstants->addCode(code, value);

    return value;
}

Value* SPIRVBuilder::_addCodeToTypesVariablesConstantsBlock(Type* type, const std::string& code, const std::string& registerName, const std::string& comment, const std::string& userDefinedName) {
    //HACK: use @ref userDefinedName to prevent structures with same members to end up as the same value
    auto& mappedValue = typesVariablesConstantsDefinitions[code + userDefinedName];
    if (!mappedValue) {
        mappedValue = new Value(context, type, registerName);
        mappedValue->setIsConstant(true);
        blockTypesVariablesConstants->addCode(code, mappedValue, comment);
    }

    return mappedValue;
}

void SPIRVBuilder::opDecorate(Value* value, Decoration decoration, const std::vector<std::string>& values) {
    _opDecorate("OpDecorate " + value->getName(), decoration, values);
}

void SPIRVBuilder::opMemberDecorate(Value* value, uint32_t memberIndex, Decoration decoration, const std::vector<std::string>& values) {
    _opDecorate("OpMemberDecorate " + value->getName() + " " + std::to_string(memberIndex), decoration, values);
}

void SPIRVBuilder::_opDecorate(std::string begin, Decoration decoration, const std::vector<std::string>& values) {
    GET_DECORATION_NAME(decoration);
    std::string code = begin + " " + decorationStr;
    for (auto& value : values)
        code += " " + value;
    blockAnnotations->addCode(code);
}

} //namespace irb
