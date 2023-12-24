#ifndef LVSLANG_SPIRV_IR_H
#define LVSLANG_SPIRV_IR_H

#include "../ir.hpp"

#include "function.hpp"

namespace irb {

class SPIRVBuilder : public IRBuilder {
private:
    std::string entryPointCode;
    std::string interfaceCode;

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
"; Magic:     0x07230203 (SPIR-V)\n" \
"; Version:   0x00010000 (Version: 1.0.0)\n" \
"; Generator: 0x00080001 (Lvslang Front End; 1)\n" \
"; Bound:     63\n" \
"; Schema:    0\n" \
"\n");
        blockHeader->addCode("OpCapability Shader");
        blockHeader->addCode("OpCapability Float16");
        blockHeader->addCode("OpCapability Int8");
        blockHeader->addCode("OpCapability Int16");

        blockDebug->addCodeRawToBeginning("; Debug information\n");
        blockAnnotations->addCodeRawToBeginning("; Annotations (non-debug)\n");
        blockTypesVariablesConstants->addCodeRawToBeginning("; All types, variables, and constants\n");
        blockMain->addCodeRawToBeginning("; All functions\n");
    }

    void opExtension(const std::string& extensionName) override {
        blockHeader->addCode("OpExtension \"" + extensionName + "\"");
    }

    void opImportSTD_EXT(const std::string& stdName) override {
        importV = new Value(context, nullptr, "import");
        blockHeader->addCode("OpExtInstImport \"" + stdName + "\"", importV->getName());
    }

    void opMemoryModel() override {
        blockHeader->addCode("OpMemoryModel Logical GLSL450");
    }

    void opEntryPoint(Value* entryPoint, const std::string& executionModel, const std::string& name = "main") override {
        entryPointCode = "OpEntryPoint " + executionModel + " " + entryPoint->getName() + " \"" + name + "\"";
    }

    void opExecutionMode(Value* entryPoint, const std::string& origin = "OriginLowerLeft") override {
        blockHeader->addCode("OpExecutionMode " + entryPoint->getName() + " " + origin);
    }

    void opName(Value* value, const std::string& name) override {
        blockDebug->addCode("OpName " + value->getName() + " \"" + name + "\"");
    }

    void opDecorate(Value* val, Decoration decoration, const std::vector<std::string>& values = {}) override {
        return _opDecorate("OpDecorate " + val->getName(), decoration, values);
    }

    void opMemberDecorate(Value* val, uint32_t memberIndex, Decoration decoration, const std::vector<std::string>& values = {}) override {
        return _opDecorate("OpMemberDecorate " + val->getName() + " " + std::to_string(memberIndex), decoration, values);
    }

    Value* opConstant(ConstantValue* val) override {
        Value* typeV = val->getType()->getValue(this);

        return _addCodeToTypesVariablesConstantsBlock(typeV->getType(), "OpConstant " + typeV->getName() + " " + val->getName(), context.popRegisterName());
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
        getSPIRVInsertBlock()->addCode("OpFunctionParameter " + type->getValue(this)->getName(), value->getName());

        return value;
    }

    void opFunctionEnd() override {
        function->end();
        blockMain->addCodeRaw(static_cast<SPIRVFunction*>(function)->getCode() + "\n");
    }

    Block* opBlock() override {
        SPIRVBlock* block = new SPIRVBlock(context, context.popRegisterName());
        block->addCodeToBeginning("OpLabel", block->getName());

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
                getSPIRVInsertBlock()->addCode("OpVectorTimesScalar " + typeV->getName() + " " + l->getName() + " " + r->getName(), value->getName());
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
        getSPIRVInsertBlock()->addCode("Op" + (needsPrefix ? l->getType()->getOpPrefix(signSensitive, needsOrd) : "") + operationStr + " " + typeV->getName() + " " + l->getName() + " " + r->getName(), value->getName());

        return value;
    }

    Value* opLoad(Value* v) override {
        if (!v->getType()->isPointer()) {
            IRB_INVALID_ARGUMENT_WITH_REASON("v", "type of 'v' is not a pointer");
            return nullptr;
        }

        Type* elementType = v->getType()->getElementType();
        Value* elementTypeV = elementType->getValue(this);
        Value* value = new Value(context, elementType, context.popRegisterName());
        getSPIRVInsertBlock()->addCode("OpLoad " + elementTypeV->getName() + " " + v->getName(), value->getName());

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
        getSPIRVInsertBlock()->addCode(code, value->getName());

        return value;
    }

    Value* opSTDFunctionCall_EXT(std::string funcName, FunctionType* type, const std::vector<Value*>& arguments) override {
        type->getValue(this); //HACK: the standard library functions still don't have their returnV initialized at this point
        Value* returnV = type->getReturnV();
        Value* value = new Value(context, returnV->getType(), context.popRegisterName());
        funcName[0] = toupper(funcName[0]);
        std::string code = "OpExtInst " + returnV->getName() + " " + importV->getName() + " " + funcName;
        for (auto* arg : arguments)
            code += " " + arg->getName();
        getSPIRVInsertBlock()->addCode(code, value->getName());

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
        std::string code = "OpCompositeConstruct " + typeV->getName();
        for (auto* component : components)
            code += " " + component->getName();
        getSPIRVInsertBlock()->addCode(code, value->getName());

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
        getSPIRVInsertBlock()->addCode("OpCompositeExtract " + type->getValue(this)->getName() + " " + vec->getName() + " " + index->getName(), value->getName());

        return value;
    }

    Value* opVectorInsert(Value* vec, Value* val, ConstantInt* index) override {
        Value* value = new Value(context, vec->getType(), context.popRegisterName());
        //TODO: implement this

        return value;
    }

    Value* opGetElementPtr(Type* elementType, Value* ptr, const std::vector<Value*>& indexes) override {
        Value* elementTypeV = elementType->getValue(this);
        Value* value = new Value(context, elementType, context.popRegisterName());
        std::string code = "OpAccessChain " + elementTypeV->getName() + " " + ptr->getName();
        for (auto* index : indexes)
            code += " " + index->getName();
        getSPIRVInsertBlock()->addCode(code, value->getName());

        return value;
    }

    void opUnreachable() override {
        getSPIRVInsertBlock()->addCode("OpUnreachable");
    }

    Value* opCast(Value* val, Type* type) override {
        if (val->getType()->equals(type))
            return val;

        std::string opName = type->getCastOpName(val->getType());
        if (opName == "NR") { //Not required
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
        getSPIRVInsertBlock()->addCode("Op" + opName + " " + typeV->getName() + " " + val->getName(), value->getName());

        return value;
    }

    Value* opSample(Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) override {
        Value* sampledImageTypeV = new Value(context, nullptr, "sampledImageType");
        blockTypesVariablesConstants->addCode("OpTypeSampledImage " + texture->getType()->getValue(this)->getName(), sampledImageTypeV->getName());

        Value* sampledImage = new Value(context, nullptr, "samplerTexTmp");
        getSPIRVInsertBlock()->addCode("OpSampledImage " + sampledImageTypeV->getName() + " " + texture->getName() + " " + sampler->getName(), sampledImage->getName());

        if (!lod)
            lod = opConstant(new ConstantFloat(context, 0.0f, 32));
        Value* value = new Value(context, new VectorType(context, texture->getType()->getBaseType(), 4), context.popRegisterName());
        getSPIRVInsertBlock()->addCode("OpImageSampleExplicitLod " + value->getType()->getValue(this)->getName() + " " + sampledImage->getName() + " " + coords->getName() + " Lod " + lod->getName(), value->getName());

        return value;
    }

    Value* opVariable(PointerType* type, StorageClass storageClass, Value* initializer = nullptr) override {
        Value* typeV = type->getValue(this);
        Value* value = new Value(context, type, context.popRegisterName());
        GET_STORAGE_CLASS_NAME(storageClass);
        std::string code = "OpVariable " + typeV->getName() + " " + storageClassStr;
        if (initializer)
            code += " " + initializer->getName();
        if (storageClass == StorageClass::Function)
            getSPIRVFirstFunctionBlock()->addCodeToBeginning(code, value->getName());
        else
            blockTypesVariablesConstants->addCode(code, value->getName());

        return value;
    }

    void addInterfaceVariable(Value* val) {
        interfaceCode += " " + val->getName();
    }

    Value* _addCodeToTypesVariablesConstantsBlock(Type* type, const std::string& code, const std::string& registerName, const std::string& comment = "") {
        auto& mappedValue = typesVariablesConstantsDefinitions[code];
        if (!mappedValue) {
            mappedValue = new Value(context, type, registerName);
            blockTypesVariablesConstants->addCode(code, mappedValue->getName(), comment);
        }

        return mappedValue;
    }

    //Getters
    std::string getCode() override {
        blockHeader->addCode(entryPointCode + interfaceCode);

        return blockHeader->getCode() + blockDebug->getCode() + blockAnnotations->getCode() + blockTypesVariablesConstants->getCode() + blockMain->getCode();
    }
};

} //namespace irn

#endif
