#ifndef LLVM_AIR_BLOCK_H
#define LLVM_AIR_BLOCK_H

#include "../block.hpp"

namespace irb {

class AIRBuilder;
class Function;

class AIRBlock : public Block {
public:
    AIRBlock(Context& aContext, Function* aFunction, const std::string& aName = "");

    void addCodeToBeginning(const std::string& instruction, Value* registerToAssign = nullptr, const std::string& comment = "") {
        codeBegin += _addCode(instruction, registerToAssign, comment);
    }

    void addCode(const std::string& instruction, Value* registerToAssign = nullptr, const std::string& comment = "") {
        code += _addCode(instruction, registerToAssign, comment);
    }

    //Getters
    llvm::BasicBlock* getHandle() {
        return handle;
    }

    std::string getCode() {
        return codeBegin + (codeBegin.size() == 0 ? "" : "\n") + code + "\n";
    }

    //Setters
    void setReturned() {
        returned = true;
    }

protected:
    llvm::BasicBlock* handle;

    std::string codeBegin;
    std::string code;

    virtual std::string _addCode(const std::string& instruction, Value* registerToAssign, const std::string& comment) {
        std::string inst = "\n\t";
        if (registerToAssign != nullptr)
            inst += registerToAssign->getName() + " = ";

        inst += instruction;

        if (comment.size() != 0)
            inst += " ; " + comment;

        return inst;
    }
};

} //namespace irb

#endif
