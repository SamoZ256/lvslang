#ifndef LLVM_AIR_BLOCK_H
#define LLVM_AIR_BLOCK_H

#include "../block.hpp"

namespace irb {

class AIRBlock : public Block {
protected:
    std::string codeBegin;
    std::string code;

    virtual std::string _addCode(const std::string& instruction, std::string registerToAssign, const std::string& comment) {
        if (registerToAssign.size() != 0)
            registerToAssign += " = ";

        std::string inst = "\n\t" + registerToAssign + instruction;

        if (comment.size() != 0)
            inst += " ; " + comment;

        return inst;
    }

public:
    AIRBlock(Context& aContext, const std::string& aName = "") : Block(aContext, new BlockType(aContext), aName) {}

    void addCodeToBeginning(const std::string& instruction, const std::string& registerToAssign = "", const std::string& comment = "") {
        codeBegin += _addCode(instruction, registerToAssign, comment);
    }

    void addCode(const std::string& instruction, const std::string& registerToAssign = "", const std::string& comment = "") {
        code += _addCode(instruction, registerToAssign, comment);
    }

    void addCodeRaw(const std::string& newCode) {
        code += newCode;
    }

    void addCodeRawToBeginning(const std::string& newCode) {
        codeBegin += newCode;
    }

    //Getters
    std::string getCode() {
        return codeBegin + (codeBegin.size() == 0 ? "" : "\n") + code + "\n";
    }

    void setReturned() {
        returned = true;
    }
};

} //namespace irb

#endif
