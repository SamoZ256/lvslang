#ifndef LVSLANG_AIR_IR_H
#define LVSLANG_AIR_IR_H

#include "../ir.hpp"

#include "function.hpp"

namespace irb {

struct AIRInterfaceVariable {

};

struct AIREntryPoint {
    Value* value;
    FunctionRole functionRole;
    Type* returnType;
    std::vector<Argument> arguments;
};

class AIRBuilder : public IRBuilder {
private:
    std::vector<AIREntryPoint> entryPoints;

public:
    AIRBuilder(Context& aContext, const std::string& aCompilerName, bool aIncludeDebugInformation = false) : IRBuilder(aContext, aCompilerName, aIncludeDebugInformation) {}

    void opExtension(const std::string& extensionName) override {}

    void opImportSTD_EXT(const std::string& stdName) override {}

    void opMemoryModel() override {}

    void opEntryPoint(Value* entryPoint, FunctionRole functionRole, const std::string& name, Type* returnType, const std::vector<Argument>& arguments) override;

    void opName(Value* value, const std::string& name) override {
        //TODO: put something here?
    }

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

    void opBlockMerge(Block* block) override {}

    void opLoopMerge(Block* block1, Block* block2) override {}

    Value* opConstruct(Type* type, const std::vector<Value*>& components) override;

    Value* opVectorExtract(Value* vec, ConstantInt* index) override;

    Value* opVectorInsert(Value* vec, Value* val, ConstantInt* index) override;

    Value* opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes) override;

    void opUnreachable() override;

    Value* opCast(Value* val, Type* type) override;

    Value* opSample(Value* funcV, Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) override;

    Value* opVariable(PointerType* type, Value* initializer = nullptr) override;

    void createMetadata(const std::string& languageName, uint32_t languageVersionMajor, uint32_t languageVersionMinor, uint32_t languageVersionPatch, const std::string& sourceFilenameStr);

    //Getters
    std::string getCode() override {
        return code;
    }

private:
    std::string code;

    std::map<std::string, Value*> functionDeclarations;

    Value* opFunctionDeclaration(FunctionType* functionType, const std::string& name, const std::string& attributes = "");

    inline AIRBlock* getAIRInsertBlock() {
        return static_cast<AIRBlock*>(getInsertBlock());
    }

    inline AIRBlock* getAIRFunctionBlock() {
        return static_cast<AIRBlock*>(getFunctionBlock());
    }

    inline AIRBlock* getAIRFirstFunctionBlock() {
        return static_cast<AIRBlock*>(getFirstFunctionBlock());
    }
};

} //namespace irb

#endif
