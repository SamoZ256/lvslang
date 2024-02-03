#include "block.hpp"

#include "ir.hpp"

namespace irb {

AIRBlock::AIRBlock(Context& aContext, Function* function, const std::string& aName) : Block(aContext, new BlockType(aContext), aName) {
    handle = llvm::BasicBlock::Create(*context.handle, "entry", static_cast<AIRFunction*>(function)->getHandle());
}

} //namespace irb
