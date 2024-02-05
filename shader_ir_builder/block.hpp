#ifndef LVSLANG_BLOCK_H
#define LVSLANG_BLOCK_H

#include "value.hpp"

namespace irb {

class Function;
class IRBuilder;

class BlockType : public Type {
public:
    BlockType(Context& aContext) : Type(aContext, TypeID::Block) {}

    ~BlockType() = default;

    Type* copy() override {
        return new BlockType(*this);
    }

    std::string getTemplateName() const override {
        return "";
    }

    std::string getDebugName() const override {
        return "block";
    }
};

class Block : public Value {
public:
    Block(Context& aContext, Function* aFunction, std::string aName = "");

    //Getters
    bool hasReturned() {
        return returned;
    }

protected:
    Function* function;
    bool returned = false;
};

} //namespace irb

#endif
