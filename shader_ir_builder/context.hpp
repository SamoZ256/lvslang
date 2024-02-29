#ifndef LVSLANG_CONTEXT_H
#define LVSLANG_CONTEXT_H

#include "common.hpp"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

namespace irb {

// Forward declarations
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

        // NoAlias,
        // ReadOnly,
        // ReadNone,

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
    llvm::StructType* handle = nullptr;
    std::vector<StructureMember> members;
    bool decorated = false; // For SPIRV backend
};

class Context {
public:
    // TODO: make this a void*?
    std::unique_ptr<llvm::LLVMContext> handle;

    std::set<std::string> registerNames;

    std::string registerName = "";

    std::map<std::string, Structure*> structures;

    uint32_t crntRegisterNumber = 2;

    Context() {}

    void reset() {
        handle = std::make_unique<llvm::LLVMContext>();
        crntRegisterNumber = 0;
        registerNames.clear();
        structures.clear();
    }

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

} // namespace irb

#endif
