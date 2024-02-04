#ifndef LLVM_AIR_FUNCTION_H
#define LLVM_AIR_FUNCTION_H

#include "../function.hpp"

#include "block.hpp"

namespace irb {

class AIRBuilder;

class AIRFunction : public Function {
public:
    AIRFunction(Context& aContext, IRBuilder* builder, FunctionType* type, const std::string& aName = "");

    void end(IRBuilder* builder) override;

    void addArgument(Value* argument);

private:
    uint32_t argumentIndex = 0;
};

} //namespace irb

#endif
