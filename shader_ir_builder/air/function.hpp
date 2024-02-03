#ifndef LLVM_AIR_FUNCTION_H
#define LLVM_AIR_FUNCTION_H

#include "../function.hpp"

#include "block.hpp"

namespace irb {

class AIRBuilder;

class AIRFunction : public Function {
public:
    AIRFunction(Context& aContext, IRBuilder* aBuilder, FunctionType* aFunctionType, Value* aValue);

    void end() override;

    void addArgument(Value* argument);

    //Getters
    llvm::Function* getHandle() {
        return static_cast<llvm::Function*>(value->getHandle());
    }

    //Setters
    void setInsertBlock(Block* aInsertBlock) override;

private:
    AIRBuilder* builder;

    uint32_t argumentIndex = 0;
};

} //namespace irb

#endif
