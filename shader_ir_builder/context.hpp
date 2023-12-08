#ifndef LVSLANG_CONTEXT_H
#define LVSLANG_CONTEXT_H

#include "common.hpp"

namespace irb {

//Forward declarations
class Type;
class Value;
class SPIRVBlock;

struct Attribute {
    enum class Enum {
        Constant,
        Device,
        Buffer,

        Position,
        Input,
        Output,
        DescriptorSet,

        NoAlias,
        ReadOnly,
        ReadNone,

        MaxEnum
    } attrib;
    std::vector<int> values;
};

struct StructureMember {
    std::string name;
    Type* type;
    std::vector<Attribute> attributes;
};

struct Structure {
    std::vector<StructureMember> members;
};

class Context {
public:
    std::set<std::string> registerNames;

    std::string registerName = "";

    std::map<std::string, Structure*> structures;

    //Code
    std::string codeHeader;
    std::string codeMain;

    uint32_t crntRegisterNumber = 2;

    Context() {}

    void pushRegisterName(const std::string& name) {
        registerName = name;
    }

    std::string popRegisterName() {
        const std::string prevRegisterName = registerName;
        registerName = "";

        return prevRegisterName;
    }

    bool pushedRegisterName() {
        return registerName != "";
    }
};

} //namespace irb

#endif
