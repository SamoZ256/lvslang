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
        AddressSpace,
        DescriptorSet,
        Position,
        Input,
        Location,
        Color,

        //NoAlias,
        //ReadOnly,
        //ReadNone,

        MaxEnum
    } attrib;
    std::vector<int> values;
};

struct Attributes {
    uint8_t addressSpace = 0;
    int8_t locationIndex = -1;
    int8_t colorIndex = -1;
    bool isBuffer = false;
    bool isTexture = false;
    bool isSampler = false;
    bool isPosition = false;
    bool isInput = false;
    bool isOutput = false;
    struct {
        uint32_t set = 0, binding = 0;
        uint32_t buffer = 0;
        uint32_t texture = 0;
        uint32_t sampler = 0;
    } bindings;
};

struct Argument {
    std::string name;
    Type* type;
    Attributes attributes;
};

struct StructureMember {
    std::string name;
    Type* type;
    Attributes attributes;
};

struct Structure {
    std::vector<StructureMember> members;
    bool decorated = false; //For SPIRV backend
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
