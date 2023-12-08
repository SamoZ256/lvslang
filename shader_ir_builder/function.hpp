#ifndef LVSLANG_FUNCTION_H
#define LVSLANG_FUNCTION_H

#include "block.hpp"

namespace irb {

class Function {
protected:
    Context& context;

    FunctionType* functionType;
    Value* value;

    std::vector<Block*> blocks;
    Block* insertBlock = nullptr;

public:
    Function(Context& aContext, FunctionType* aFunctionType) : context(aContext), functionType(aFunctionType) {}

    virtual void end() = 0;

    //Getters
    Value* getValue() {
        return value;
    }

    FunctionType* getType() {
        return functionType;
    }

    virtual const std::string& getCode() = 0;

    //Blocks
    Block* getInsertBlock() {
        return insertBlock;
    }

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
            return nullptr;
        }

        return blocks[1];
    }

    void setInsertBlock(Block* aInsertBlock) {
        insertBlock = aInsertBlock;
        if (!std::count(blocks.begin(), blocks.end(), insertBlock))
            blocks.push_back(insertBlock);
    }

    void popLastBlock() {
        if (blocks.size() <= 1) {
            IRB_ERROR("there is currently no active block");
            return;
        }
        blocks.pop_back();
    }
};

} //namespace irb

#endif
