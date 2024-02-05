#include "function.hpp"

#include "ir.hpp"

namespace irb {

void SPIRVFunction::end(IRBuilder* builder) {
    Value* functionV = getTypeValue(static_cast<SPIRVBuilder*>(builder), type);
    Value* returnV = getTypeValue(static_cast<SPIRVBuilder*>(builder), static_cast<FunctionType*>(type)->getReturnType());
    static_cast<SPIRVBlock*>(getFunctionBlock())->addCodeToBeginning("OpFunction " + returnV->getName() + " " + property + " " + functionV->getName(), this, getName());
    SPIRVBlock* endB = new SPIRVBlock(context, this);
    endB->addCode("OpFunctionEnd");
    for (uint32_t i = 0; i < blocks.size(); i++)
        code += static_cast<SPIRVBlock*>(blocks[i])->getCode();
}

} //namespace irb
