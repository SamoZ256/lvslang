#ifndef LVSLANG_SPIRV_BLOCK_H
#define LVSLANG_SPIRV_BLOCK_H

#include "../block.hpp"

namespace irb {

class SPIRVBlock : public Block {
private:
    std::string codeBegin;
    std::string code;

    //TODO: support comments
    std::string _addCode(const std::string& instruction, Value* registerToAssign, const std::string& comment) {
        std::string inst;
        uint8_t beginSpaceCount = 22;
        if (registerToAssign != nullptr)
            beginSpaceCount = std::max((int)beginSpaceCount - (int)registerToAssign->getName().size(), 0);

        for (uint8_t i = 0; i < beginSpaceCount; i++)
            inst += " ";
        if (registerToAssign != nullptr)
            inst += registerToAssign->getName() + " = ";
        inst += instruction;

        if (comment.size() != 0) {
            uint8_t endSpaceCount = (uint8_t)std::max(int(54 - inst.size()), 0);
            for (uint8_t i = 0; i < endSpaceCount; i++)
                inst += " ";
            inst += "; " + comment;
        }
        inst += "\n";

        return inst;
    }

public:
    SPIRVBlock(Context& aContext, const std::string& aName = "") : Block(aContext, new BlockType(aContext), aName) {}

    void addCodeToBeginning(const std::string& instruction, Value* registerToAssign = nullptr, const std::string& comment = "") {
        codeBegin += _addCode(instruction, registerToAssign, comment);
    }

    void addCode(const std::string& instruction, Value* registerToAssign = nullptr, const std::string& comment = "") {
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
        return codeBegin + code + "\n";
    }

    void setReturned() {
        returned = true;
    }
};

} //namespace irb

#endif
