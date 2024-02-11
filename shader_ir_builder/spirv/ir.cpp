#include "ir.hpp"

#include "spirv-tools/libspirv.hpp"
#include "spirv-tools/optimizer.hpp"

#include "type_value.hpp"

namespace irb {

//TODO: support unordered?
static std::string getTypeOpPrefix(Type* type, bool signSensitive, bool needsOrd) {
    switch (type->getTypeID()) {
    case TypeID::Void:
        return "";
    case TypeID::Bool:
        return "Logical";
    case TypeID::Integer:
        if (signSensitive)
            return (type->getIsSigned() ? "S" : "U");
        else
            return "I";
    case TypeID::Float:
        if (needsOrd)
            return "FOrd";
        else
            return "F";
    case TypeID::Pointer:
        return ""; //TODO: implement this
    case TypeID::Vector:
    case TypeID::Matrix:
        return getTypeOpPrefix(type->getBaseType(), signSensitive, needsOrd);
    default:
        return "";
    }
}

//TODO: support matrices?
static std::string getTypeCastOpName(Type* castFrom, Type* castTo) {
    if (castTo->isScalar()) {
        if (castFrom->isVector())
            return "NP"; //Not possible
        switch (castFrom->getTypeID()) {
        case TypeID::Bool:
        case TypeID::Integer:
            if (castFrom->getIsSigned()) {
                switch (castTo->getTypeID()) {
                case TypeID::Bool:
                case TypeID::Integer:
                    if (castTo->getIsSigned())
                        return "SConvert";
                    else
                        return "NR"; //SatConvertSToU
                case TypeID::Float:
                    return "ConvertSToF";
                default:
                    break;
                }
            } else {
                switch (castTo->getTypeID()) {
                case TypeID::Bool:
                case TypeID::Integer:
                    if (castTo->getIsSigned())
                        return "NR"; //SatConvertUToS
                    else
                        return "UConvert";
                case TypeID::Float:
                    return "ConvertUToF";
                default:
                    break;
                }
            }
            break;
        case TypeID::Float:
            switch (castTo->getTypeID()) {
            case TypeID::Bool:
            case TypeID::Integer:
                if (castTo->getIsSigned())
                    return "ConvertFToS";
                else
                    return "ConvertFToU";
            case TypeID::Float:
                return "FConvert";
            default:
                break;
            }
            break;
        default:
            break;
        }
    } else if (castTo->isVector()) {
        if (castFrom->isScalar()) {
            if (castFrom->equals(castTo->getBaseType()))
                return "VCS";
            //TODO: cast twice in other cases
        }
    }

    return "Unknown";
}

struct StandardFunctionInfo {
    std::string name;
    bool requiresOpExtInst = true;
    int32_t argumentIndexForSpecialization = -1;
};

static std::map<std::string, StandardFunctionInfo> standardFunctionLUT = {
    {"abs", {"Abs", true, 0}},
    {"acos", {"Acos"}},
    {"acosh", {"Acosh"}},
    {"asin", {"Asin"}},
    {"asinh", {"Asinh"}},
    {"atan", {"Atan"}},
    {"atanh", {"Atanh"}},
    {"ceil", {"Ceil"}},
    {"clamp", {"Clamp", true, 0}},
    {"cos", {"Cos"}},
    {"cosh", {"Cosh"}},
    {"cross", {"Cross"}},
    {"distance", {"Distance"}},
    {"dot", {"Dot", false}},
    {"exp", {"Exp"}},
    {"exp2", {"Exp2"}},
    {"floor", {"Floor"}},
    {"fract", {"Fract"}},
    //TODO: add image functions
    //TODO: add transpose
    {"isinf", {"IsInf", false}},
    {"isnan", {"IsNan", false}},
    {"length", {"Length"}},
    {"log", {"Log"}},
    {"log2", {"Log2"}},
    {"max", {"Max", true, 0}},
    {"min", {"Min", true, 0}},
    {"mix", {"Mix", true, 0}},
    {"normalize", {"Normalize"}},
    {"pow", {"Pow"}},
    {"reflect", {"Reflect"}},
    {"refract", {"Refract"}},
    {"round", {"Round"}},
    {"sample", {"ImageSampleExplicitLod", false}},
    {"sign", {"Sign", true, 0}},
    {"sin", {"Sin"}},
    {"sinh", {"Sinh"}},
    {"smoothstep", {"SmoothStep"}},
    {"sqrt", {"Sqrt"}},
    {"step", {"Step"}},
    {"tan", {"Tan"}},
    {"tanh", {"Tanh"}}
    //TODO: add transpose function
};

class StandardFunctionValue : public SPIRVFunction {
public:
    using SPIRVFunction::SPIRVFunction;
};

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
    Function* oldFunction = activeFunction;

    Function* entryPointFunction = opFunction(new FunctionType(context, new ScalarType(context, TypeID::Void, 0, true), {}), name);
    setActiveFunction(entryPointFunction);

    GET_FUNCTION_ROLE_NAME(functionRole);
    std::string code = "OpEntryPoint " + functionRoleStr + " " + entryPointFunction->getName() + " \"" + name + "\"";
    //TODO: support other origins as well
    if (functionRole == FunctionRole::Fragment)
        blockHeader->addCode("OpExecutionMode " + entryPointFunction->getName() + " OriginUpperLeft");
    //blockHeader->addCode("OpSource GLSL 450");
    //blockHeader->addCode("OpSourceExtension \"GL_GOOGLE_cpp_style_line_directive\"");
    //blockHeader->addCode("OpSourceExtension \"GL_GOOGLE_include_directive\"");

    //Body
    Block* block = opBlock(entryPointFunction);
    setInsertBlock(block);

    // -------- Input --------
    std::vector<Value*> argValues;
    argValues.reserve(arguments.size());
    for (const auto& argument : arguments) {
        Type* type = argument.type;
        const auto& attr = argument.attributes;
        //Get element type in case of buffer
        if (attr.isBuffer)
            type = type->getElementType();

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
                    opMemberDecorate(getTypeValue(this, type), i, Decoration::Location, {std::to_string(structure->members[i].attributes.locationIndex)});
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
            opDecorate(getTypeValue(this, type, true), Decoration::Block);
        
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
    opDecorate(getTypeValue(this, returnType), Decoration::Block);
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
    
    //TODO: don't throw this error
    if (!returnType->isStructure()) {
        IRB_ERROR(("Entry point argument declared with the 'output' attribute must have a structure type, found '" + returnType->getDebugName() + "' instead").c_str());
        return;
    }
    if (functionRole == FunctionRole::Vertex) {
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
        //TODO: do this decoration somewhere else
        irb::Structure* structure = static_cast<StructureType*>(returnType)->getStructure();
        for (uint32_t i = 0; i < structure->members.size(); i++)
            opMemberDecorate(getTypeValue(this, returnType), i, Decoration::Location, {std::to_string(structure->members[i].attributes.colorIndex)});
    }

    //Add to interface
    code += " " + returnVariable->getName();
    if (positionVariable)
        code += " " + positionVariable->getName();

    opReturn();

    opFunctionEnd(entryPointFunction);

    blockHeader->addCodeToBeginning(code);

    //Set the active function to be the old active funciton
    activeFunction = oldFunction;
}

void SPIRVBuilder::opName(Value* value, const std::string& name) {
    if (includeDebugInformation)
        blockDebug->addCode("OpName " + value->getName() + " \"" + name + "\"");
}

Value* SPIRVBuilder::opConstant(ConstantValue* val)  {
    Value* typeV = getTypeValue(this, val->getType());

    std::string str;
    if (val->getType()->getTypeID() == TypeID::Bool)
        str = "OpConstant" + std::string(val->getName() == "1" ? "True " : "False ") + typeV->getName();
    else
        str = "OpConstant " + typeV->getName() + " " + val->getName();

    return _addCodeToTypesVariablesConstantsBlock(typeV->getType(), str, context.popRegisterName());
}

Value* SPIRVBuilder::opStructureDefinition(StructureType* structureType) {
    return new Value(context, structureType, context.popRegisterName());
}

Function* SPIRVBuilder::opStandardFunctionDeclaration(FunctionType* functionType, const std::string& name) {
    const auto& standardFunctionInfo = standardFunctionLUT[name];

    Value* returnV = getTypeValue(this, functionType->getReturnType());

    std::string fullName;
    if (standardFunctionInfo.requiresOpExtInst)
        fullName = "OpExtInst " + returnV->getName() + " " + importV->getName() + " ";
    else
        fullName = "Op";

    if (standardFunctionInfo.argumentIndexForSpecialization != -1)
        fullName += getTypeOpPrefix(functionType->getArguments()[standardFunctionInfo.argumentIndexForSpecialization], true, false);
    fullName += standardFunctionInfo.name;
    if (!standardFunctionInfo.requiresOpExtInst)
        fullName += " " + returnV->getName();

    return new StandardFunctionValue(context, functionType, fullName, "", false);
}

Function* SPIRVBuilder::opFunction(FunctionType* functionType, const std::string& name) {
    SPIRVFunction* function = new SPIRVFunction(context, functionType, name);
    new SPIRVBlock(context, function);

    return function;
}

Value* SPIRVBuilder::opFunctionParameter(Function* function, Type* type) {
    //HACK: only get pointer if its not a pointer already (buffers need this)
    if (!type->isPointer())
        type = new PointerType(context, type, StorageClass::Function);
    Value* value = new Value(context, type, context.popRegisterName());
    static_cast<SPIRVBlock*>(function->getFunctionBlock())->addCode("OpFunctionParameter " + getTypeValue(this, type)->getName(), value);

    return value;
}

void SPIRVBuilder::opFunctionEnd(Function* function) {
    function->end(this);
    blockMain->addCodeRaw(static_cast<SPIRVFunction*>(function)->getCode() + "\n");
}

Block* SPIRVBuilder::opBlock(Function* function) {
    SPIRVBlock* block = new SPIRVBlock(context, function, context.popRegisterName());
    block->addCodeToBeginning("OpLabel", block);

    return block;
}

Value* SPIRVBuilder::opOperation(Value* l, Value* r, Type* type, Operation operation) {
    if (!type->isOperatorFriendly()) {
        IRB_INVALID_ARGUMENT_WITH_REASON("type", "type is not operator friendly (e.g. is not one of: scalar, pointer, vector)");
        return nullptr;
    }

    if (r->getType()->isVector() && l->getType()->isScalar())
        std::swap(l, r);
    Value* value = new Value(context, (type->getTypeID() == TypeID::Bool && l->getType()->isVector() ? new VectorType(context, type, static_cast<VectorType*>(l->getType())->getComponentCount()) : type), context.popRegisterName());
    Value* typeV = getTypeValue(this, value->getType());
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
    getSPIRVInsertBlock()->addCode("Op" + (needsPrefix ? getTypeOpPrefix(l->getType(), signSensitive, needsOrd) : "") + operationStr + " " + typeV->getName() + " " + l->getName() + " " + r->getName(), value);

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
        IRB_INVALID_ARGUMENT_WITH_REASON("v", "type of 'v' is not a pointer");
        return nullptr;
    }

    Type* elementType = v->getType()->getElementType();
    Value* elementTypeV = getTypeValue(this, elementType);
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
        IRB_ERROR("cannot have more than 1 return instruction in a single block");
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
    Value* returnV = getTypeValue(this, type->getReturnType());
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
    Value* typeV = getTypeValue(this, type);
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
    getSPIRVInsertBlock()->addCode("OpCompositeExtract " + getTypeValue(this, type)->getName() + " " + vec->getName() + " " + index->getName(), value);

    return value;
}

Value* SPIRVBuilder::opVectorInsert(Value* vec, Value* val, ConstantInt* index)  {
    Value* value = new Value(context, vec->getType(), context.popRegisterName());
    getSPIRVInsertBlock()->addCode("OpCompositeInsert " + getTypeValue(this, vec->getType())->getName() + " " + val->getName() + " " + vec->getName() + " " + index->getName(), value);

    return value;
}

Value* SPIRVBuilder::opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes)  {
    if (!ptr->getType()->isPointer()) {
        IRB_INVALID_ARGUMENT_WITH_REASON("ptr", "type of 'ptr' is not pointer type");
        return nullptr;
    }
    Value* elementTypeV = getTypeValue(this, elementType);
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

    std::string opName = getTypeCastOpName(val->getType(), type);
    if (opName == "NP") { //Not possible
        //TODO: warn?
        return val;
    } else if (opName == "NR") { //Not required
        return val;
    } else if (opName == "VCS") { //Vector construct from scalar
        VectorType* dstVec = static_cast<VectorType*>(type);

        return opConstruct(dstVec, std::vector<Value*>(dstVec->getComponentCount(), val));
    }

    Value* typeV = getTypeValue(this, type);
    Value* value = new Value(context, type, context.popRegisterName());
    getSPIRVInsertBlock()->addCode("Op" + opName + " " + typeV->getName() + " " + val->getName(), value);

    return value;
}

Value* SPIRVBuilder::opSample(Value* funcV, Value* texture, Value* sampler, Value* coords, Value* lod)  {
    Value* sampledImageTypeV = new Value(context, nullptr, "sampledImageType");
    blockTypesVariablesConstants->addCode("OpTypeSampledImage " + getTypeValue(this, texture->getType())->getName(), sampledImageTypeV);

    Value* sampledImage = new Value(context, nullptr, "samplerTexTmp");
    getSPIRVInsertBlock()->addCode("OpSampledImage " + sampledImageTypeV->getName() + " " + texture->getName() + " " + sampler->getName(), sampledImage);

    if (!lod)
        lod = opConstant(new ConstantFloat(context, 0.0f, 32));
    Value* value = new Value(context, new VectorType(context, texture->getType()->getBaseType(), 4), context.popRegisterName());
    getSPIRVInsertBlock()->addCode("OpImageSampleExplicitLod " + getTypeValue(this, value->getType())->getName() + " " + sampledImage->getName() + " " + coords->getName() + " Lod " + lod->getName(), value);

    return value;
}

Value* SPIRVBuilder::opVariable(PointerType* type, Value* initializer)  {
    Value* typeV = getTypeValue(this, type);
    Value* value = new Value(context, type, context.popRegisterName());
    std::string code = "OpVariable " + typeV->getName() + " " + storageClassLUT[(int) type->getStorageClass()];
    if (initializer) {
        if (initializer->isConstant())
            code += " " + initializer->getName();
        else
            opStore(value, initializer);
    }
    if (type->getStorageClass() == StorageClass::Function)
        getSPIRVFirstFunctionBlock()->addCodeToBeginning(code, value);
    else
        blockTypesVariablesConstants->addCode(code, value);

    return value;
}

bool SPIRVBuilder::getCode(std::string& outputCode, OptimizationLevel optimizationLevel, bool outputAssembly, SPIRVVersion spirvVersion)  {
    std::string code = blockHeader->getCode() + blockDebug->getCode() + blockAnnotations->getCode() + blockTypesVariablesConstants->getCode() + blockMain->getCode();

    spv_target_env targetEnv;
    //TODO: use vulkan env?
    switch (spirvVersion) {
    case irb::SPIRVVersion::_1_0:
        targetEnv = SPV_ENV_UNIVERSAL_1_0;
        break;
    case irb::SPIRVVersion::_1_1:
        targetEnv = SPV_ENV_UNIVERSAL_1_1;
        break;
    case irb::SPIRVVersion::_1_2:
        targetEnv = SPV_ENV_UNIVERSAL_1_2;
        break;
    case irb::SPIRVVersion::_1_3:
        targetEnv = SPV_ENV_UNIVERSAL_1_3;
        break;
    case irb::SPIRVVersion::_1_4:
        targetEnv = SPV_ENV_UNIVERSAL_1_4;
        break;
    case irb::SPIRVVersion::_1_5:
        targetEnv = SPV_ENV_UNIVERSAL_1_5;
        break;
    case irb::SPIRVVersion::_1_6:
        targetEnv = SPV_ENV_UNIVERSAL_1_6;
        break;
    default:
        break;
    }

    spvtools::SpirvTools core(targetEnv);
    spvtools::Optimizer opt(targetEnv);

    auto printMsgToStderr = [](spv_message_level_t, const char* source, const spv_position_t& pos, const char* message) {
        std::cerr << pos.line << ":" << pos.column << ": " << SET_TEXT_COLOR("31") << "error" << RESET_TEXT_COLOR() << ": " << message << std::endl;
        //std::cout << source << std::endl;
        //std::cout << pos.column << std::endl;
        //for (uint32_t i = 0; i < pos.column - 1; i++)
        //    std::cout << " ";
        //std::cout << "^" << std::endl;
    };
    core.SetMessageConsumer(printMsgToStderr);
    opt.SetMessageConsumer(printMsgToStderr);

    std::vector<uint32_t> binary;
    if (!core.Assemble(code, &binary)) {
        IRB_ERROR("spirv assembler failed");
        return false;
    }
    if (!core.Validate(binary)) {
        IRB_ERROR("spirv validator failed");
        return false;
    }

    switch (optimizationLevel) {
    case OptimizationLevel::O0:
        break;
    //TODO: differentiate between these?
    case OptimizationLevel::O1:
    case OptimizationLevel::O2:
    case OptimizationLevel::O3:
        opt.RegisterPerformancePasses();
        break;
    case OptimizationLevel::Os:
        opt.RegisterSizePasses();
        break;
    }
    if (!opt.Run(binary.data(), binary.size(), &binary)) {
        IRB_ERROR("spirv optimizer failed");
        return false;
    }

    if (outputAssembly) {
        if (!core.Disassemble(binary, &outputCode, SPV_BINARY_TO_TEXT_OPTION_INDENT | SPV_BINARY_TO_TEXT_OPTION_FRIENDLY_NAMES | SPV_BINARY_TO_TEXT_OPTION_COMMENT)) {
            IRB_ERROR("spirv disassembler failed");
            return false;
        }
    } else {
        outputCode = std::string((const char*)binary.data(), binary.size() * sizeof(binary[0]) / sizeof(char));
    }

    return true;
}

Value* SPIRVBuilder::_addCodeToTypesVariablesConstantsBlock(Type* type, const std::string& code, const std::string& registerName, const std::string& userDefinedName) {
    //HACK: use @ref userDefinedName to prevent structures with same members to end up as the same value
    auto& mappedValue = typesVariablesConstantsDefinitions[code + userDefinedName];
    if (!mappedValue) {
        mappedValue = new Value(context, type, registerName);
        mappedValue->setIsConstant(true);
        blockTypesVariablesConstants->addCode(code, mappedValue);
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
