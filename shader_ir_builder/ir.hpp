#ifndef LVSLANG_IR_H
#define LVSLANG_IR_H

#include "function.hpp"

namespace irb {

class IRBuilder {
protected:
    Context& context;
    Function* function = nullptr;
    Value* importV;

    bool includeDebugInformation;

public:
    IRBuilder(Context& aContext, bool aIncludeDebugInformation) : context(aContext), includeDebugInformation(aIncludeDebugInformation) {}

    //Header
    virtual void opExtension(const std::string& extensionName) = 0;
    
    virtual void opImportSTD_EXT(const std::string& stdName) = 0;

    virtual void opMemoryModel() = 0;

    virtual void opEntryPoint(Value* entryPoint, const std::string& executionModel, const std::string& name = "main") = 0;

    virtual void opExecutionMode(Value* entryPoint, const std::string& origin = "OriginLowerLeft") = 0;

    //Debug
    virtual void opName(Value* value, const std::string& name) = 0;

    //Annotations
    virtual void opDecorate(Value* val, Decoration decoration, const std::vector<std::string>& values = {}) = 0;

    virtual void opMemberDecorate(Value* val, uint32_t memberIndex, Decoration decoration, const std::vector<std::string>& values = {}) = 0;

    //Types, variables and constants
    virtual Value* opConstant(ConstantValue* val) = 0;

    //Main
    //TODO: create operation for structure declaration

    virtual Value* opStructureDefinition(StructureType* structureType) = 0;

    virtual Value* opRegisterFunction(FunctionType* functionType) = 0;
    
    virtual Value* opFunctionDeclaration(FunctionType* functionType, Value* value = nullptr) = 0;

    virtual Value* opFunction(FunctionType* functionType, Value* value = nullptr) = 0;

    virtual Value* opFunctionParameter(Type* type) = 0;

    virtual void opFunctionEnd() = 0;

    virtual Block* opBlock() = 0;

    virtual Value* opOperation(Value* l, Value* r, Type* type, Operation operation) = 0;

    virtual Value* opLoad(Value* v) = 0;

    virtual void opStore(Value* ptr, Value* v) = 0;

    virtual void opReturn(Value* v = nullptr) = 0;

    virtual Value* opFunctionCall(Value* funcV, const std::vector<Value*>& arguments) = 0;

    virtual Value* opSTDFunctionCall_EXT(std::string funcName, FunctionType* type, const std::vector<Value*>& arguments) = 0;

    virtual void opBranch(Block* block) = 0;

    virtual void opBranchCond(Value* cond, Block* blockTrue, Block* blockFalse) = 0;

    virtual void opBlockMerge(Block* block) = 0; //TODO: rename

    virtual void opLoopMerge(Block* block1, Block* block2) = 0;

    virtual Value* opVectorConstruct(VectorType* type, const std::vector<Value*>& components) = 0;

    virtual Value* opVectorExtract(Value* vec, ConstantInt* index) = 0;

    virtual Value* opVectorInsert(Value* vec, Value* val, ConstantInt* index) = 0;

    virtual Value* opGetElementPtr(Type* elementType, Value* ptr, const std::vector<Value*>& indexes) = 0;

    virtual void opUnreachable() = 0;

    virtual Value* opCast(Value* val, Type* type) = 0;

    //TODO: merge this into @ref opSTDFunctionCall_EXT?
    virtual Value* opSample(Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) = 0;

    //Miscelanous
    virtual Value* opVariable(PointerType* type, StorageClass storageClass, Value* initializer = nullptr) = 0;

    //Getters
    virtual std::string getCode() = 0;

    //Blocks
    Block* getInsertBlock() {
        if (!function) {
            IRB_ERROR("there is currently no active function");
            return nullptr;
        }
        Block* block = function->getInsertBlock();
        if (!block) {
            IRB_ERROR("there is currently no active block inside function");
            return nullptr;
        }

        return block;
    }

    Block* getFunctionBlock() {
        if (!function) {
            IRB_ERROR("there is currently no active function");
            return nullptr;
        }

        return function->getFunctionBlock();
    }

    Block* getFirstFunctionBlock() {
        if (!function) {
            IRB_ERROR("there is currently no active function");
            return nullptr;
        }

        return function->getFirstBlock();
    }

    void setInsertBlock(Block* block) {
        if (!function) {
            IRB_ERROR("there is currently no active function");
            return;
        }
        function->setInsertBlock(block);
    }

    void popLastBlock() {
        if (!function) {
            IRB_ERROR("there is currently no active function");
            return;
        }
        function->popLastBlock();
    }
};

} //namespace irb

#endif
