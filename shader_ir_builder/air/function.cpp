#include "function.hpp"

#include "ir.hpp"

namespace irb {

AIRFunction::AIRFunction(Context& aContext, IRBuilder* aBuilder, FunctionType* aFunctionType, Value* aValue) : Function(aContext, aFunctionType), builder(static_cast<AIRBuilder*>(aBuilder)) {
    value = aValue;

    AIRBlock* block = new AIRBlock(context, this);
    setInsertBlock(block);
}

void AIRFunction::end() {
    llvm::verifyFunction(*static_cast<llvm::Function*>(value->getHandle()));
}

void AIRFunction::addArgument(Value* argument) {
    llvm::Argument* llvmArgument = static_cast<llvm::Function*>(value->getHandle())->getArg(argumentIndex++);
    llvmArgument->setName(argument->getRawName());
    argument->setHandle(llvmArgument);
}

void AIRFunction::setInsertBlock(Block* aInsertBlock) {
    insertBlock = aInsertBlock;
    if (!std::count(blocks.begin(), blocks.end(), insertBlock))
        blocks.push_back(insertBlock);
    builder->getHandle()->SetInsertPoint(static_cast<AIRBlock*>(insertBlock)->getHandle());
}

} //namespace irb
