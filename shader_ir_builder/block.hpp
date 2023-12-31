#ifndef LVSLANG_BLOCK_H
#define LVSLANG_BLOCK_H

#include "value.hpp"

namespace irb {

class IRBuilder;

class BlockType : public Type {
public:
    BlockType(Context& aContext) : Type(aContext, TypeID::Block) {
        nameBegin = "label";
    }

    ~BlockType() = default;

    Type* copy() override {
        return new BlockType(*this);
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override {
        return nullptr;
    }

    std::string getNameForRegister() override {
        return "";
    }
};

class Block : public Value {
public:
    using Value::Value;

    //Getters
    bool hasReturned() {
        return returned;
    }

protected:
    bool returned = false;
};

} //namespace irb

#endif
