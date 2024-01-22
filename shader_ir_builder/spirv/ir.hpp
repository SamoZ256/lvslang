#ifndef LVSLANG_SPIRV_IR_H
#define LVSLANG_SPIRV_IR_H

#include "../ir.hpp"

#include "function.hpp"

namespace irb {

class SPIRVBuilder : public IRBuilder {
private:
    std::map<std::string, Value*> typesVariablesConstantsDefinitions;

    //Blocks
    SPIRVBlock* blockHeader;
    SPIRVBlock* blockDebug;
    SPIRVBlock* blockAnnotations;
    SPIRVBlock* blockTypesVariablesConstants;
    SPIRVBlock* blockMain;

    void _opDecorate(std::string begin, Decoration decoration, const std::vector<std::string>& values = {}) {
        GET_DECORATION_NAME(decoration);
        std::string code = begin + " " + decorationStr;
        for (auto& value : values)
            code += " " + value;
        blockAnnotations->addCode(code);
    }

    inline SPIRVBlock* getSPIRVInsertBlock() {
        return static_cast<SPIRVBlock*>(getInsertBlock());
    }

    inline SPIRVBlock* getSPIRVFunctionBlock() {
        return static_cast<SPIRVBlock*>(getFunctionBlock());
    }

    inline SPIRVBlock* getSPIRVFirstFunctionBlock() {
        return static_cast<SPIRVBlock*>(getFirstFunctionBlock());
    }

public:
    SPIRVBuilder(Context& aContext, bool aIncludeDebugInformation = false) : IRBuilder(aContext, aIncludeDebugInformation) {
        blockHeader = new SPIRVBlock(context);
        blockDebug = new SPIRVBlock(context);
        blockAnnotations = new SPIRVBlock(context);
        blockTypesVariablesConstants = new SPIRVBlock(context);
        blockMain = new SPIRVBlock(context);

        blockHeader->addCodeRawToBeginning(
"; SPIR-V\n" \
"; Version:   " + spirvVersionMap[spirvVersion] + "\n" \
"; Generator: Lvslang; 11\n" \
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

    void opExtension(const std::string& extensionName) override {
        blockHeader->addCodeToBeginning("OpExtension \"" + extensionName + "\"");
    }

    void opImportSTD_EXT(const std::string& stdName) override {
        importV = new Value(context, nullptr, "import");
        blockHeader->addCodeToBeginning("OpExtInstImport \"" + stdName + "\"", importV);
    }

    void opMemoryModel() override {
        blockHeader->addCodeToBeginning("OpMemoryModel Logical GLSL450");
    }

    void opEntryPoint(Value* entryPoint, FunctionRole functionRole, const std::string& name, Type* returnType, const std::vector<Argument>& arguments) override {
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

    void opName(Value* value, const std::string& name) override {
        blockDebug->addCode("OpName " + value->getName() + " \"" + name + "\"");
    }

    Value* opConstant(ConstantValue* val) override {
        Value* typeV = val->getType()->getValue(this);

        std::string str;
        if (val->getType()->getTypeID() == TypeID::Bool)
            str = "OpConstant" + std::string(val->getName() == "1" ? "True " : "False ") + typeV->getName();
        else
            str = "OpConstant " + typeV->getName() + " " + val->getName();

        return _addCodeToTypesVariablesConstantsBlock(typeV->getType(), str, context.popRegisterName());
    }

    Value* opStructureDefinition(StructureType* structureType) override {
        return new Value(context, structureType, context.popRegisterName());
    }

    Value* opRegisterFunction(FunctionType* functionType) override {
        return new Value(context, functionType, context.popRegisterName());
    }

    Value* opFunctionDeclaration(FunctionType* functionType, Value* value = nullptr) override {
        if (value)
            return value;
        
        return opRegisterFunction(functionType);
    }

    Value* opFunction(FunctionType* functionType, Value* value = nullptr) override {
        if (!value)
            value = opRegisterFunction(functionType);
        function = new SPIRVFunction(context, this, functionType, blockTypesVariablesConstants, value);
        value = function->getValue();
        //TODO: uncomment?
        //if (includeDebugInformation && name.size() != 0)
        //    opName(name, value);

        return value;
    }

    Value* opFunctionParameter(Type* type) override {
        type = new PointerType(context, type, StorageClass::Function);
        Value* value = new Value(context, type, context.popRegisterName());
        getSPIRVInsertBlock()->addCode("OpFunctionParameter " + type->getValue(this)->getName(), value);

        return value;
    }

    void opFunctionEnd() override {
        function->end();
        blockMain->addCodeRaw(static_cast<SPIRVFunction*>(function)->getCode() + "\n");
    }

    Block* opBlock() override {
        SPIRVBlock* block = new SPIRVBlock(context, context.popRegisterName());
        block->addCodeToBeginning("OpLabel", block);

        return block;
    }

    Value* opOperation(Value* l, Value* r, Type* type, Operation operation) override {
        if (!type->isOperatorFriendly()) {
            IRB_INVALID_ARGUMENT_WITH_REASON("type", "type is not operator friendly (e.g. is not one of: scalar, pointer, vector)");
            return nullptr;
        }

        Value* typeV = type->getValue(this);
        Value* value = new Value(context, type, context.popRegisterName());
        if (r->getType()->isVector() && l->getType()->isScalar())
            std::swap(l, r);
        if (l->getType()->isVector() && r->getType()->isScalar()) {
            if (operation == Operation::Multiply && type->getBaseType()->getTypeID() == TypeID::Float) {
                getSPIRVInsertBlock()->addCode("OpVectorTimesScalar " + typeV->getName() + " " + l->getName() + " " + r->getName(), value);
                return value;
            } else {
                r = opVectorConstruct(static_cast<VectorType*>(type), std::vector<Value*>(static_cast<VectorType*>(type)->getComponentCount(), r)); //TODO: check if the type is vector
            }
        }
        
        bool needsOrd = (operation == Operation::GreaterThan || operation == Operation::GreaterThanEqual || operation == Operation::LessThan || operation == Operation::LessThanEqual);
        bool signSensitive = (operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || needsOrd);
        bool needsPrefix = (operation == Operation::Add || operation == Operation::Subtract || operation == Operation::Multiply || operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || needsOrd);

        GET_OPERATION_NAME(operation);

        //TODO: do not use l for getting op prefix?
        getSPIRVInsertBlock()->addCode("Op" + (needsPrefix ? l->getType()->getOpPrefix(signSensitive, needsOrd) : "") + operationStr + " " + typeV->getName() + " " + l->getName() + " " + r->getName(), value);

        return value;
    }

    Value* opLoad(Value* v) override {
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

    void opStore(Value* ptr, Value* v) override {
        getSPIRVInsertBlock()->addCode("OpStore " + ptr->getName() + " " + v->getName());
    }

    void opReturn(Value* v = nullptr) override {
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

    //TODO: don't return anything if type is void?
    Value* opFunctionCall(Value* funcV, const std::vector<Value*>& arguments) override {
        FunctionType* type = dynamic_cast<FunctionType*>(funcV->getType());
        if (!type) {
            IRB_INVALID_ARGUMENT_WITH_REASON("funcV", "type of 'funcV' is not a function");
            return nullptr;
        }
        //TODO: check if this is necessary
        type->getValue(this); //HACK: the standard library functions still don't have their returnV initialized at this point
        Value* returnV = type->getReturnV();
        Value* value = new Value(context, returnV->getType(), context.popRegisterName());
        std::string code = "OpFunctionCall " + returnV->getName() + " " + funcV->getName();
        for (auto* arg : arguments)
            code += " " + arg->getName();
        getSPIRVInsertBlock()->addCode(code, value);

        return value;
    }

    Value* opSTDFunctionCall_EXT(std::string funcName, FunctionType* type, const std::vector<Value*>& arguments, Type* specializedType) override {
        type->getValue(this); //HACK: the standard library functions still don't have their returnV initialized at this point
        Value* returnV = type->getReturnV();
        Value* value = new Value(context, returnV->getType(), context.popRegisterName());
        std::string code;
        if (funcName == "isinf") {
            if (arguments.size() != 1) {
                IRB_INVALID_ARGUMENT_WITH_REASON("arguments", "the number of arguments of 'isinf' function must be 1");
                return nullptr;
            }
            code = "OpIsInf " + returnV->getName() + " " + arguments[0]->getName();
        } else if (funcName == "isnan") {
            if (arguments.size() != 1) {
                IRB_INVALID_ARGUMENT_WITH_REASON("arguments", "the number of arguments of 'isnan' function must be 1");
                return nullptr;
            }
            code = "OpIsNan " + returnV->getName() + " " + arguments[0]->getName();
        } else {
            std::vector<std::string> needOpFunctions = {
                "abs",
                "clamp",
                "max",
                "min",
                "mix",
                "sign"
            };

            std::string opPrefix;
            if (std::find(needOpFunctions.begin(), needOpFunctions.end(), funcName) != needOpFunctions.end())
                opPrefix = specializedType->getOpPrefix(true, false);
            funcName[0] = toupper(funcName[0]);
            if (funcName == "Smoothstep")
                funcName = "SmoothStep";
            code = "OpExtInst " + returnV->getName() + " " + importV->getName() + " " + opPrefix + funcName;
            for (auto* arg : arguments)
                code += " " + arg->getName();
        }
        getSPIRVInsertBlock()->addCode(code, value);

        return value;
    }

    void opBranch(Block* block) override {
        if (!getSPIRVInsertBlock()->hasReturned())
            getSPIRVInsertBlock()->addCode("OpBranch " + block->getName());
    }

    void opBranchCond(Value* cond, Block* blockTrue, Block* blockFalse) override {
        getSPIRVInsertBlock()->addCode("OpBranchConditional " + cond->getName() + " " + blockTrue->getName() + " " + blockFalse->getName());
    }

    void opBlockMerge(Block* block) override {
        //TODO: support other stuff besides 'None'
        getSPIRVInsertBlock()->addCode("OpSelectionMerge " + block->getName() + " None");
    }

    void opLoopMerge(Block* block1, Block* block2) override {
        //TODO: support other stuff besides 'None'
        getSPIRVInsertBlock()->addCode("OpLoopMerge " + block1->getName() + " " + block2->getName() + " None");
    }

    Value* opVectorConstruct(VectorType* type, const std::vector<Value*>& components) override {
        if (components.size() != type->getComponentCount()) {
            IRB_INVALID_ARGUMENT_WITH_REASON("components", "the number of components must match the number of components of the vector type");
            return nullptr;
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

        return value;
    }

    Value* opVectorExtract(Value* vec, ConstantInt* index) override {
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

    Value* opVectorInsert(Value* vec, Value* val, ConstantInt* index) override {
        Value* value = new Value(context, vec->getType(), context.popRegisterName());
        getSPIRVInsertBlock()->addCode("OpCompositeInsert " + vec->getType()->getValue(this)->getName() + " " + val->getName() + " " + vec->getName() + " " + index->getName(), value);

        return value;
    }

    Value* opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes) override {
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

    void opUnreachable() override {
        getSPIRVInsertBlock()->addCode("OpUnreachable");
    }

    Value* opCast(Value* val, Type* type) override {
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
            
            return opVectorConstruct(dstVec, components);
        } else if (opName == "VCS") { //Vector construct from scalar
            VectorType* dstVec = static_cast<VectorType*>(type);

            return opVectorConstruct(dstVec, std::vector<Value*>(dstVec->getComponentCount(), val));
        }

        Value* typeV = type->getValue(this);
        Value* value = new Value(context, type, context.popRegisterName());
        getSPIRVInsertBlock()->addCode("Op" + opName + " " + typeV->getName() + " " + val->getName(), value);

        return value;
    }

    Value* opDot(Value* a, Value* b) override {
        if (!a->getType()->isVector() || !b->getType()->isVector()) {
            IRB_ERROR("cannot dot non-vector types");
            return nullptr;
        }
        VectorType* aType = static_cast<VectorType*>(a->getType());
        VectorType* bType = static_cast<VectorType*>(b->getType());
        if (aType->getComponentCount() != bType->getComponentCount()) {
            IRB_ERROR("cannot dot vectors with different component counts");
            return nullptr;
        }
        //TODO: check if this is correct
        Value* typeV = (new ScalarType(context, TypeID::Float, 32, true))->getValue(this);//aType->getBaseType()->getValue(this);
        Value* value = new Value(context, aType->getBaseType(), context.popRegisterName());
        getSPIRVInsertBlock()->addCode("OpDot " + typeV->getName() + " " + a->getName() + " " + b->getName(), value);

        return value;
    }

    Value* opSample(Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) override {
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

    Value* opVariable(PointerType* type, Value* initializer = nullptr) override {
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

    Value* _addCodeToTypesVariablesConstantsBlock(Type* type, const std::string& code, const std::string& registerName, const std::string& comment = "", const std::string& userDefinedName = "") {
        //HACK: use @ref userDefinedName to prevent structures with same members to end up as the same value
        auto& mappedValue = typesVariablesConstantsDefinitions[code + userDefinedName];
        if (!mappedValue) {
            mappedValue = new Value(context, type, registerName);
            mappedValue->setIsConstant(true);
            blockTypesVariablesConstants->addCode(code, mappedValue, comment);
        }

        return mappedValue;
    }

    void opDecorate(Value* value, Decoration decoration, const std::vector<std::string>& values = {}) {
        _opDecorate("OpDecorate " + value->getName(), decoration, values);
    }

    void opMemberDecorate(Value* value, uint32_t memberIndex, Decoration decoration, const std::vector<std::string>& values = {}) {
        _opDecorate("OpMemberDecorate " + value->getName() + " " + std::to_string(memberIndex), decoration, values);
    }

    //Getters
    std::string getCode() override {
        return blockHeader->getCode() + blockDebug->getCode() + blockAnnotations->getCode() + blockTypesVariablesConstants->getCode() + blockMain->getCode();
    }
};

} //namespace irn

#endif
