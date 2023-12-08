#ifndef LLVM_AIR_FUNCTION_H
#define LLVM_AIR_FUNCTION_H

#include "../function.hpp"

#include "block.hpp"

namespace irb {

class AIRBuilder;

class AIRFunction : public Function {
public:
    AIRFunction(Context& aContext, IRBuilder* builder, FunctionType* aFunctionType, Value* aValue) : Function(aContext, aFunctionType) {
        value = aValue;
        AIRBlock* block = new AIRBlock(context);
        setInsertBlock(block);

        code = "define " + functionType->getReturnType()->getName() + " " + value->getName() + "(";
        //block->addCode("OpFunction " + returnV->getName() + " " + property + " " + functionV->getName(), value->getName(), name);
    }

    void end() override {
        code += ") {";
        for (uint32_t i = 0; i < blocks.size(); i++) {
            if (i >= 2)
                code += "\n_" + blocks[i]->getRawName() + ":"; //HACK: add the "_"
            code += static_cast<AIRBlock*>(blocks[i])->getCode();
        }
        code += "}";
    }

    //TODO: support attributes as well
    void addArgument(Value* argument) {
        if (addedArgument)
            code += ", ";
        code += argument->getType()->getName() + " " + argument->getName();
        addedArgument = true;
    }

    //Getters
    const std::string& getCode() override {
        return code;
    }

private:
    std::string code;
    bool addedArgument = false;
};

} //namespace irb

#endif
