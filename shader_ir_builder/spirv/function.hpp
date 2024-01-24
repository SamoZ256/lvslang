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
    SPIRVFunction(Context& aContext, IRBuilder* builder, FunctionType* aFunctionType, Block* blockTypesVariablesConstants, Value* aValue) : Function(aContext, aFunctionType) {
        value = aValue;
        Value* functionV = functionType->getValue(builder);
        Value* returnV = functionType->getReturnV();
        SPIRVBlock* block = new SPIRVBlock(context);
        setInsertBlock(block);
        block->addCode("OpFunction " + returnV->getName() + " " + property + " " + functionV->getName(), value, value->getName());
    }

    void end() override {
        SPIRVBlock* endB = new SPIRVBlock(context);
        endB->addCode("OpFunctionEnd");
        for (uint32_t i = 0; i < blocks.size(); i++)
            code += static_cast<SPIRVBlock*>(blocks[i])->getCode();
        code += endB->getCode();
    }

    //Getters
    const std::string& getCode() override {
        return code;
    }
};

} //namespace irb

#endif
