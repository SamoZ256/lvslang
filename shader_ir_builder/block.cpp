#include "block.hpp"

#include "function.hpp"

namespace irb {

Block::Block(Context& aContext, Function* aFunction, std::string aName) : Value(aContext, new BlockType(aContext), aName), function(aFunction) {
    // HACK: check if function is not nullptr
    if (function)
        function->_addBlock(this);
}

} // namespace irb
