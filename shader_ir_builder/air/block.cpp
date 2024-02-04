#include "block.hpp"

#include "ir.hpp"

namespace irb {

AIRBlock::AIRBlock(Context& aContext, Function* aFunction, const std::string& aName) : Block(aContext, aFunction, aName) {
    handle = llvm::BasicBlock::Create(*context.handle, name, static_cast<llvm::Function*>(function->getHandle()));
}

} //namespace irb
