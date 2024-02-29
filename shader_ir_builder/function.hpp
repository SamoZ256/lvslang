#ifndef LVSLANG_FUNCTION_H
#define LVSLANG_FUNCTION_H

#include "block.hpp"

namespace irb {

class Function : public Value {
protected:
    std::vector<Block*> blocks;

public:
    Function(Context& aContext, FunctionType* type, const std::string& aName, const std::string& prefix = "%", bool checkIfNameIsAlreadyUsed = true) : Value(aContext, type, aName, prefix, checkIfNameIsAlreadyUsed) {}

    virtual void end(IRBuilder* builder) = 0;

    // Blocks
    Block* getFunctionBlock() {
        if (blocks.size() == 0) {
            IRB_ERROR("there is currently no active block");
            return nullptr;
        }

        return blocks[0];
    }

    Block* getFirstBlock() {
        if (blocks.size() <= 1) {
            IRB_ERROR("there is currently no active block");
            std::cout << name << " : " << blocks.size() << std::endl;
            return nullptr;
        }

        return blocks[1];
    }

    void _addBlock(Block* block) {
        blocks.push_back(block);
    }
};

} // namespace irb

#endif
