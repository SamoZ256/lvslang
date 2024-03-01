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

#define SET_TEXT_COLOR(color) "\x1b[" color "m"

#define RESET_TEXT_COLOR() SET_TEXT_COLOR("0")

// Errors and warnings
#define _IRB_MSG(type, msg) fprintf(stderr, "[IRB:" type "]::%s: %s\n", __FUNCTION__, msg)

#define IRB_ERROR(msg) _IRB_MSG("error", msg);

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

enum class SPIRVVersion {
    // 1.x
    _1_0,
    _1_1,
    _1_2,
    _1_3,
    _1_4,
    _1_5,
    _1_6,

    MaxEnum
};

// TODO: make this static?
extern std::map<SPIRVVersion, std::string> spirvVersionMap;

inline bool spirvVersionIsLessThanOrEqual(SPIRVVersion spirvVersion, SPIRVVersion lessThanOrEqual) {
    return ((int)spirvVersion <= (int)lessThanOrEqual);
}

inline bool spirvVersionIsGreaterThanOrEqual(SPIRVVersion spirvVersion, SPIRVVersion greaterThanOrEqual) {
    return ((int)spirvVersion >= (int)greaterThanOrEqual);
}

enum class Extension {
    _8bit_storage,
    _16bit_storage,
    explicit_arithmetic_types,

    MaxEnum
};

// Enums
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

enum class TextureViewType {
    _1D,
    _2D,
    _3D,
    _1DArray,
    _2DArray,
    Cube,
    CubeArray,
    Buffer, // For future use

    MaxEnum
};

enum class Operation {
    // Binary
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo,
    Remainder,

    // Bitwise
    BitwiseAnd,
    BitwiseOr,

    // Logical
    Equal,
    NotEqual,
    And,
    Or,
    GreaterThan,
    LessThan,
    GreaterThanEqual,
    LessThanEqual,

    MaxEnum
};

// TODO: rename?
enum class FunctionRole {
    Normal,
    Vertex,
    Fragment,
    Kernel,

    MaxEnum
};

// Utility functions
/*
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
*/

} // namespace irb

#endif
