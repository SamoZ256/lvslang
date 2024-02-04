#ifndef LVSLANG_SPIRV_FUNCTION_H
#define LVSLANG_SPIRV_FUNCTION_H

#include "../function.hpp"

#include "block.hpp"

namespace irb {

class SPIRVFunction : public Function {
private:
    std::string property = "None"; //TODO: support other as well (for instance "DontInline")

    std::string code;

public:
    using Function::Function;

    void end(IRBuilder* builder) override {
        Value* functionV = type->getValue(builder);
        Value* returnV = static_cast<FunctionType*>(type)->getReturnV();
        static_cast<SPIRVBlock*>(getFunctionBlock())->addCodeToBeginning("OpFunction " + returnV->getName() + " " + property + " " + functionV->getName(), this, getName());
        SPIRVBlock* endB = new SPIRVBlock(context, this);
        endB->addCode("OpFunctionEnd");
        for (uint32_t i = 0; i < blocks.size(); i++)
            code += static_cast<SPIRVBlock*>(blocks[i])->getCode();
    }

    //Getters
    const std::string& getCode() {
        return code;
    }
};

} //namespace irb

#endif
