#ifndef LVSLANG_SPIRV_IR_H
#define LVSLANG_SPIRV_IR_H

#include "../ir.hpp"

#include "function.hpp"

namespace irb {

class StandardFunctionValue : public Value {
public:
    using Value::Value;
};

class SPIRVBuilder : public IRBuilder {
public:
    SPIRVBuilder(Context& aContext, const std::string& aCompilerName, bool aIncludeDebugInformation = false);

    void opExtension(const std::string& extensionName) override;

    void opImportSTD_EXT(const std::string& stdName) override;

    void opMemoryModel() override;

    void opEntryPoint(Value* entryPoint, FunctionRole functionRole, const std::string& name, Type* returnType, const std::vector<Argument>& arguments) override;

    void opName(Value* value, const std::string& name) override;

    Value* opConstant(ConstantValue* val) override;

    Value* opStructureDefinition(StructureType* structureType) override;

    Value* opRegisterFunction(FunctionType* functionType) override;

    Value* opStandardFunctionDeclaration(FunctionType* functionType, const std::string& name) override;

    Value* opFunction(FunctionType* functionType, Value* value = nullptr) override;

    Value* opFunctionParameter(Type* type) override;

    void opFunctionEnd() override;

    Block* opBlock() override;

    Value* opOperation(Value* l, Value* r, Type* type, Operation operation) override;

    Value* opLoad(Value* v) override;

    void opStore(Value* ptr, Value* v) override;

    void opReturn(Value* v = nullptr) override;

    Value* opFunctionCall(Value* funcV, const std::vector<Value*>& arguments) override;

    void opBranch(Block* block) override;

    void opBranchCond(Value* cond, Block* blockTrue, Block* blockFalse) override;

    void opBlockMerge(Block* block) override;

    void opLoopMerge(Block* block1, Block* block2) override;

    Value* opConstruct(Type* type, const std::vector<Value*>& components) override;

    Value* opVectorExtract(Value* vec, ConstantInt* index) override;

    Value* opVectorInsert(Value* vec, Value* val, ConstantInt* index) override;

    Value* opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes) override;

    void opUnreachable() override;

    Value* opCast(Value* val, Type* type) override;

    Value* opSample(Value* funcV, Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) override;

    Value* opVariable(PointerType* type, Value* initializer = nullptr) override;

    Value* _addCodeToTypesVariablesConstantsBlock(Type* type, const std::string& code, const std::string& registerName, const std::string& comment = "", const std::string& userDefinedName = "");

    void opDecorate(Value* value, Decoration decoration, const std::vector<std::string>& values = {});

    void opMemberDecorate(Value* value, uint32_t memberIndex, Decoration decoration, const std::vector<std::string>& values = {});

    //Getters
    std::string getCode() override {
        return blockHeader->getCode() + blockDebug->getCode() + blockAnnotations->getCode() + blockTypesVariablesConstants->getCode() + blockMain->getCode();
    }

private:
    std::map<std::string, Value*> typesVariablesConstantsDefinitions;

    //Blocks
    SPIRVBlock* blockHeader;
    SPIRVBlock* blockDebug;
    SPIRVBlock* blockAnnotations;
    SPIRVBlock* blockTypesVariablesConstants;
    SPIRVBlock* blockMain;

    void _opDecorate(std::string begin, Decoration decoration, const std::vector<std::string>& values = {});

    inline SPIRVBlock* getSPIRVInsertBlock() {
        return static_cast<SPIRVBlock*>(getInsertBlock());
    }

    inline SPIRVBlock* getSPIRVFunctionBlock() {
        return static_cast<SPIRVBlock*>(getFunctionBlock());
    }

    inline SPIRVBlock* getSPIRVFirstFunctionBlock() {
        return static_cast<SPIRVBlock*>(getFirstFunctionBlock());
    }
};

} //namespace irn

#endif
