#ifndef LVSLANG_COMMON_H
#define LVSLANG_COMMON_H

#include "../shader_ir_builder/common.hpp"

//Errors and warnings
#define _LVSLANG_MSG(type, msg) fprintf(stderr, "[LVSLANG:" type "]::%s: %s\n", __FUNCTION__, msg)

#define LVSLANG_ERROR(msg) \
{ \
_LVSLANG_MSG("error", msg); \
abort(); \
}

#define LVSLANG_WARN(msg) _LVSLANG_MSG("warning", msg)

#define LVSLANG_INVALID_ARGUMENT(argName) LVSLANG_ERROR("Invalid argument '" argName "'")

#define LVSLANG_INVALID_ARGUMENT_WITH_REASON(argName, reason) LVSLANG_ERROR("Invalid argument '" argName "', reason: " reason)

#define LVSLANG_CHECK_ARGUMENT(type, arg) \
if (arg < (type)0 || arg >= type::MaxEnum) \
    LVSLANG_INVALID_ARGUMENT(#arg)

#define LVSLANG_ERROR_UNSUPPORTED_TARGET(targetName) LVSLANG_ERROR("'" targetName "' is not a supported target");

#define LVSLANG_ERROR_UNSUPPORTED_TARGET_VERSIONS(versions, targetName) LVSLANG_ERROR("Version/s '" versions "' is/are not a supported version for " targetName);

#define LVSLANG_WARN_UNSUPPORTED(featureName) LVSLANG_WARN("'" featureName "' is unsupported")

#define LVSLANG_WARN_UNSUPPORTED_FUNCTION LVSLANG_WARN("This function is unsupported")

#define LVSLANG_VALIDATE_ENUM_ARGUMENT(enumName, arg) \
{ \
    if (arg < (enumName)0 || arg >= enumName::MaxEnum) \
        LVSLANG_INVALID_ARGUMENT(#arg); \
}

static uint32_t crntDebugLine = 1;
static uint32_t crntDebugChar = 1;

static std::vector<std::string> source;

inline void logError(const char* msg) {
    std::cerr << crntDebugLine + 1 << ":" << crntDebugChar + 1 << ": error: " << msg << std::endl;
    std::cout << source[crntDebugLine] << std::endl;
    std::string pointLine;
    for (uint32_t i = 0; i < crntDebugChar; i++)
        pointLine += " ";
    std::cout << pointLine << "^" << std::endl;
}

inline void logError(std::string msg) {
    logError(msg.c_str());
}

#endif
