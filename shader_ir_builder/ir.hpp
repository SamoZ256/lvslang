#ifndef LVSLANG_IR_H
#define LVSLANG_IR_H

#include "function.hpp"

namespace irb {

enum class OptimizationLevel {
    O0,
    O1,
    O2,
    O3,
    Os
};

class IRBuilder {
public:
    IRBuilder(Context& aContext, bool aIncludeDebugInformation) : context(aContext), includeDebugInformation(aIncludeDebugInformation) {}

    // Header
    /**
     * Enables extension.
     * 
     * USELESS FOR AIR
     * 
     * @param[in] extensionName the name of the extension, the list of all available extensions can be found at https:// github.com/KhronosGroup/SPIRV-Registry
     */
    virtual void opExtension(irb::Extension extension) = 0;
    
    /**
     * Imports standard library.
     * 
     * USELESS FOR AIR
     * 
     * @param[in] stdName the name of the standard library (e.g. GLSL.std.450)
     */
    virtual void opImportSTD_EXT(const std::string& stdName) = 0;

    /**
     * Defines the memory model of the application. Only "Logical GLSL450" is allowed for now.
     * 
     * USELESS FOR AIR
     */
    virtual void opMemoryModel() = 0;

    /**
     * Defines an entry point.
     * 
     * @param[in] entryPoint the id of the entry point function
     * @param[in] functionRole the shader stage of the entry point. Can be either "Vertex", "Fragment" or "Kernel"
     * @param[in] name the name of the entry point in the original code, only for debugging purposes
     * @param[in] returnType return type of the entry point
     * @param[in] arguments entry point arguments
     */
    virtual void opEntryPoint(Value* entryPoint, FunctionRole functionRole, const std::string& name, Type* returnType, const std::vector<Argument>& arguments) = 0;

    // Debug
    /**
     * Name an id.
     * 
     * USELESS FOR AIR
     * 
     * @param[in] value the id to name
     * @param[in] name the name to use
     */
    virtual void opName(Value* value, const std::string& name) = 0;

    // Types, variables and constants
    /**
     * Create a constant value.
     * 
     * @param[in] val the value that will be used to initialize the id
     * 
     * @returns an id containing the constant value
     */
    virtual Value* opConstant(ConstantValue* val) = 0;

    // Main
    // TODO: create operation for structure declaration

    virtual Value* opStructureDefinition(StructureType* structureType) = 0;
    
    virtual Function* opStandardFunctionDeclaration(FunctionType* functionType, const std::string& name) = 0;

    virtual Function* opFunction(FunctionType* functionType, const std::string& name) = 0;

    virtual Value* opFunctionParameter(Function* function, Type* type) = 0;

    virtual void opFunctionEnd(Function* function) = 0;

    virtual Block* opBlock(Function* function) = 0;

    virtual Value* opOperation(Value* l, Value* r, Type* type, Operation operation) = 0;

    virtual Value* opLoad(Value* v) = 0;

    virtual void opStore(Value* ptr, Value* v) = 0;

    virtual void opReturn(Value* v = nullptr) = 0;

    virtual Value* opFunctionCall(Value* funcV, const std::vector<Value*>& arguments) = 0;

    virtual void opBranch(Block* block) = 0;

    virtual void opBranchCond(Value* cond, Block* blockTrue, Block* blockFalse) = 0;

    virtual void opBlockMerge(Block* block) = 0;

    virtual void opLoopMerge(Block* block1, Block* block2) = 0;

    virtual Value* opConstruct(Type* type, const std::vector<Value*>& components) = 0;

    virtual Value* opExtract(Value* vec, ConstantInt* index) = 0;

    virtual Value* opInsert(Value* vec, Value* val, ConstantInt* index) = 0;

    virtual Value* opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes) = 0;

    virtual void opUnreachable() = 0;

    virtual Value* opCast(Value* val, Type* type) = 0;

    // TODO: merge into @ref opSTDFunctionCall_EXT
    virtual Value* opSample(Value* funcV, Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) = 0;

    // Miscelanous
    virtual Value* opVariable(PointerType* type, Value* initializer = nullptr) = 0;

    // Getters
    virtual bool getCode(std::string& outputCode, OptimizationLevel optimizationLevel, bool outputAssembly, SPIRVVersion spirvVersion) = 0;

    // Blocks
    Function* getActiveFunction() {
        return activeFunction;
    }

    Block* getInsertBlock() {
        if (!insertBlock) {
            IRB_ERROR("there is currently no active block");
            return nullptr;
        }

        return insertBlock;
    }

    Block* getFunctionBlock() {
        if (!activeFunction) {
            IRB_ERROR("there is currently no active function");
            return nullptr;
        }

        return activeFunction->getFunctionBlock();
    }

    Block* getFirstFunctionBlock() {
        if (!activeFunction) {
            IRB_ERROR("there is currently no active function");
            return nullptr;
        }

        return activeFunction->getFirstBlock();
    }

    // Setters
    void setActiveFunction(Function* function) {
        activeFunction = function;
    }

    virtual void setInsertBlock(Block* block) {
        insertBlock = block;
    }

protected:
    Context& context;
    Function* activeFunction = nullptr;
    Value* importV;

    bool includeDebugInformation;

    Block* insertBlock = nullptr;
};

} // namespace irb

#endif
