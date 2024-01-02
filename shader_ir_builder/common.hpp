#ifndef IRB_COMMON_H
#define IRB_COMMON_H

#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>

namespace irb {

//Errors and warnings
#define _IRB_MSG(type, msg) fprintf(stderr, "[IRB:" type "]::%s: %s\n", __FUNCTION__, msg)

#define IRB_ERROR(msg) \
{ \
_IRB_MSG("error", msg); \
abort(); \
}

#define IRB_WARN(msg) _IRB_MSG("warning", msg)

#define IRB_INVALID_ARGUMENT(argName) IRB_ERROR("Invalid argument '" argName "'")

#define IRB_INVALID_ARGUMENT_WITH_REASON(argName, reason) IRB_ERROR("Invalid argument '" argName "', reason: " reason)

#define IRB_CHECK_ARGUMENT(type, arg) \
if (arg < (type)0 || arg >= type::MaxEnum) \
    IRB_INVALID_ARGUMENT(#arg)

#define IRB_ERROR_UNSUPPORTED_TARGET(targetName) IRB_ERROR("'" targetName "' is not a supported target");

#define IRB_ERROR_UNSUPPORTED_TARGET_VERSIONS(versions, targetName) IRB_ERROR("Version/s '" versions "' is/are not a supported version for " targetName);

#define IRB_WARN_UNSUPPORTED(featureName) IRB_WARN("'" featureName "' is unsupported")

#define IRB_WARN_UNSUPPORTED_FUNCTION IRB_WARN("This function is unsupported")

#define IRB_VALIDATE_ENUM_ARGUMENT(enumName, arg) \
{ \
    if (arg < (enumName)0 || arg >= enumName::MaxEnum) \
        IRB_INVALID_ARGUMENT(#arg); \
}

inline void error(const std::string& msg, const std::string& funcName) {
    std::cout << "[IRB:error]::" << funcName << ": " << msg << std::endl;
}

//Enums
enum class StorageClass {
    UniformConstant,
    Input,
    Uniform,
    Output,
    Workgroup,
    //CrossWorkgroup,
    Private,
    Function,
    //Generic,
    PushConstant,
    AtomicCounter,
    Image,
    StorageBuffer,

    MaxEnum
};

const std::string storageClassLUT[] = {
    "UniformConstant",
    "Input",
    "Uniform",
    "Output",
    "Workgroup",
    //"CrossWorkgroup",
    "Private",
    "Function",
    //"Generic",
    "PushConstant",
    "AtomicCounter",
    "Image",
    "StorageBuffer"
};

#define GET_STORAGE_CLASS_NAME(storageClass) \
IRB_VALIDATE_ENUM_ARGUMENT(StorageClass, storageClass); \
const std::string& storageClass##Str = storageClassLUT[(int)storageClass];

enum class Decoration {
    Block,
    ArrayStride,
    NoPerspective,
    Flat,
    Patch,
    Sample,
    Invariant,
    Restrict,
    Aliased,
    Volatile,
    Constant,
    Coherent,
    NonWritable,
    NonReadable,
    Uniform,
    Location,
    DescriptorSet,
    Binding,
    Offset,
    Alignment,

    Position,

    MaxEnum
};

const std::string decorationLUT[] = {
    "Block",
    "ArrayStride",
    "NoPerspective",
    "Flat",
    "Patch",
    "Sample",
    "Invariant",
    "Restrict",
    "Aliased",
    "Volatile",
    "Constant",
    "Coherent",
    "NonWritable",
    "NonReadable",
    "Uniform",
    "Location",
    "DescriptorSet",
    "Binding",
    "Offset",
    "Alignment",

    "BuiltIn Position"
};

#define GET_DECORATION_NAME(decoration) \
IRB_VALIDATE_ENUM_ARGUMENT(Decoration, decoration); \
const std::string& decoration##Str = decorationLUT[(int)decoration];

enum class TextureViewType {
    _1D,
    _2D,
    _3D,
    _1DArray,
    _2DArray,
    Cube,
    CubeArray,
    Buffer, //For future use

    MaxEnum
};

enum class Target {
    None,
    Metal,
    HLSL,
    GLSL,
    SPIRV,
    AIR,

    MaxEnum
};

#define CASE_TARGET_CODE Target::Metal ... Target::GLSL
#define CASE_TARGET_IR Target::SPIRV ... Target::SPIRV

#define TARGET_IS_CODE(target) ((int)target >= (int)irb::Target::Metal && (int)target <= (int)irb::Target::GLSL)
#define TARGET_IS_IR(target) ((int)target >= (int)irb::Target::SPIRV && (int)target <= (int)irb::Target::AIR)

enum class GLSLVersion {
    None,

    //1.x
    _1_10,
    _1_20,
    _1_30,
    _1_40,
    _1_50,

    //3.x
    _3_30,

    //4.x
    _4_00,
    _4_10,
    _4_20,
    _4_30,
    _4_40,
    _4_50,

    MaxEnum
};

extern std::map<GLSLVersion, std::string> glslVersionMap;

enum class Extension {
    _8bit_storage,
    _16bit_storage,
    explicit_arithmetic_types,

    MaxEnum
};

//is enabled, glsl name, spirv name
extern std::tuple<bool, std::string, std::string> extensions[(int)Extension::MaxEnum];

enum class Operation {
    //Binary
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo,
    Remainder,

    //Bitwise
    BitwiseAnd,
    BitwiseOr,

    //Logical
    LogicalEqual,
    LogicalNotEqual,
    LogicalAnd,
    LogicalOr,
    GreaterThan,
    LessThan,
    GreaterThanEqual,
    LessThanEqual,

    MaxEnum
};

const std::string operationLUT_SPIRV[] = {
    "Add",
    "Sub",
    "Mul",
    "Div",
    "Mod",
    "Rem",
    "BitwiseAnd",
    "BitwiseOr",
    "LogicalEqual",
    "LogicalNotEqual",
    "LogicalAnd",
    "LogicalOr",
    "GreaterThan",
    "LessThan",
    "GreaterThanEqual",
    "LessThanEqual"
};

const std::string operationLUT_AIR[] = {
    "add",
    "sub",
    "mul",
    "div",
    "mod",
    "rem",
    "BitwiseAnd???",
    "BitwiseOr???",
    "cmp",
    "cmp",
    "and",
    "or",
    "cmp",
    "cmp",
    "cmp",
    "cmp"
};

const std::string operationKindLUT_AIR[] = {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "eq",
    "ne",
    "",
    "",
    "gt",
    "lt",
    "ge",
    "le"
};

#define GET_OPERATION_NAME(operation) \
IRB_VALIDATE_ENUM_ARGUMENT(Operation, operation); \
std::string operation##Str; \
std::string operationKind##Str; \
switch (target) { \
case Target::SPIRV: \
    operation##Str = operationLUT_SPIRV[(int)operation]; \
    break; \
case Target::AIR: \
    operation##Str = operationLUT_AIR[(int)operation]; \
    operationKind##Str = operationKindLUT_AIR[(int)operation]; \
    break; \
default: \
    break; \
}

//TODO: rename?
enum class FunctionRole {
    Normal,
    Vertex,
    Fragment,
    Kernel,

    MaxEnum
};

const std::string functionRoleLUT_SPIRV[] = {
    "None",
    "Vertex",
    "Fragment",
    "Kernel"
};

#define GET_FUNCTION_ROLE_NAME(functionRole) \
IRB_VALIDATE_ENUM_ARGUMENT(FunctionRole, functionRole); \
std::string functionRole##Str; \
switch (target) { \
case Target::SPIRV: \
    functionRole##Str = functionRoleLUT_SPIRV[(int)functionRole]; \
    break; \
case Target::AIR: \
    throw std::runtime_error("OOOPPPSSSS"); \
    break; \
default: \
    break; \
}

//Utility functions
union DoubleToUint64 {
    double d;
    uint64_t u;
};

inline std::string doubleToHEX(float d) {
    DoubleToUint64 doubleToUint64;
    doubleToUint64.d = d;

    std::stringstream stream;
    stream << std::hex << doubleToUint64.u;
    
    return "0x" + stream.str();
}

} //namespace irb

#endif
