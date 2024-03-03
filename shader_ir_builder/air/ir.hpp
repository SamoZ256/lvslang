#ifndef LVSLANG_AIR_IR_H
#define LVSLANG_AIR_IR_H

#include "../ir.hpp"

#include "function.hpp"

namespace irb {

struct AIREntryPoint {
    Value* value;
    std::string name;
    FunctionRole functionRole;
    Type* returnType;
    std::vector<Argument> arguments;
};

class AIRBuilder : public IRBuilder {
public:
    AIRBuilder(Context& aContext, const std::string& aCompilerName, const std::string& aSourceFilenameStr, bool aIncludeDebugInformation = false) : IRBuilder(aContext, aIncludeDebugInformation), compilerName(aCompilerName), sourceFilenameStr(aSourceFilenameStr) {
        // TODO: set this to filename
        llvmModule = std::make_unique<llvm::Module>((includeDebugInformation ? sourceFilenameStr : ""), *context.handle);

        // Set the 'target triple' and 'target datalayout'
        llvmModule->setTargetTriple("air64-apple-macosx14.0.0");
        // TODO: support other datalayouts as well?
        llvm::DataLayout dataLayout("e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32");
        llvmModule->setDataLayout(dataLayout);

        handle = new llvm::IRBuilder<>(*context.handle);
    }

    void opExtension(irb::Extension extension) override {}

    void opImportSTD_EXT(const std::string& stdName) override {}

    void opMemoryModel() override {}

    void opEntryPoint(Value* entryPoint, FunctionRole functionRole, const std::string& name, Type* returnType, const std::vector<Argument>& arguments) override;

    void opName(Value* value, const std::string& name) override {
        // TODO: put something here?
    }

    Value* opConstant(ConstantValue* val) override;

    Value* opStructureDefinition(StructureType* structureType) override;

    Function* opStandardFunctionDeclaration(FunctionType* functionType, const std::string& name) override;

    Function* opFunction(FunctionType* functionType, const std::string& name) override;

    Value* opFunctionParameter(Function* function, Type* type) override;

    void opFunctionEnd(Function* function) override;

    Block* opBlock(Function* function) override;

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

    Value* opExtract(Value* val, ConstantInt* index) override;

    Value* opInsert(Value* val1, Value* val2, ConstantInt* index) override;

    Value* opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes) override;

    void opUnreachable() override;

    Value* opCast(Value* val, Type* type) override;

    Value* opSample(Value* funcV, Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) override;

    Value* opVariable(PointerType* type, Value* initializer = nullptr) override;

    std::string createMetadata(const std::string& languageName, uint32_t languageVersionMajor, uint32_t languageVersionMinor, uint32_t languageVersionPatch);

    // Getters
    bool getCode(std::string& outputCode, OptimizationLevel optimizationLevel, bool outputAssembly, SPIRVVersion spirvVersion) override;

    std::unique_ptr<llvm::Module>& getLLVMModule() {
        return llvmModule;
    }

    llvm::IRBuilder<>* getHandle() {
        return handle;
    }

    // Setters
    void setInsertBlock(Block* block) override {
        insertBlock = block;
        handle->SetInsertPoint(static_cast<llvm::BasicBlock*>(insertBlock->getHandle()));
    }

private:
    std::unique_ptr<llvm::Module> llvmModule;
    // TODO: make this a unique_ptr
    llvm::IRBuilder<>* handle;

    std::string code;

    std::vector<AIREntryPoint> entryPoints;
    std::map<std::string, Function*> functionDeclarations;

    // Debug
    std::string compilerName;
    std::string sourceFilenameStr;

    Function* opFunctionDeclaration(FunctionType* functionType, const std::string& name, const std::vector<std::pair<llvm::Attribute::AttrKind, uint64_t> >& attributes = {});

    // Matrix operations (column-major)
    Value* _opMatrixTimesScalar(Value* matrix, Value* scalar);

    Value* _opMatrixTimesVector(Value* matrix, Value* vector);

    Value* _opMatrixTimesMatrix(Value* matrix1, Value* matrix2);

    inline AIRBlock* getAIRInsertBlock() {
        return static_cast<AIRBlock*>(getInsertBlock());
    }
};

} // namespace irb

#endif
