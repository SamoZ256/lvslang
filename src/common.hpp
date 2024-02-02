#ifndef LVSLANG_COMMON_H
#define LVSLANG_COMMON_H

#include "../shader_ir_builder/common.hpp"

namespace lvslang {

//Errors and warnings
#define _LVSLANG_MSG(type, msg) fprintf(stderr, "[LVSLANG:" type "]::%s: %s\n", __FUNCTION__, msg)

#define LVSLANG_ERROR(msg) _LVSLANG_MSG("error", msg);

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

enum class GLSLVersion {
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

static std::map<GLSLVersion, std::string> glslVersionMap = {
    {GLSLVersion::_1_10, "110"},
    {GLSLVersion::_1_20, "120"},
    {GLSLVersion::_1_30, "130"},
    {GLSLVersion::_1_40, "140"},
    {GLSLVersion::_1_50, "150"},

    {GLSLVersion::_3_30, "330"},

    {GLSLVersion::_4_00, "400"},
    {GLSLVersion::_4_10, "410"},
    {GLSLVersion::_4_20, "420"},
    {GLSLVersion::_4_30, "430"},
    {GLSLVersion::_4_40, "440"},
    {GLSLVersion::_4_50, "450"}
};

struct Source {
    uint32_t stringPos = 0;

    uint32_t crntLine = 0;
    uint32_t crntChar = 0;

    uint32_t crntDebugLine = 1;
    uint32_t crntDebugChar = 1;

    std::vector<std::string> source;
};

extern Source source;

inline void setSource(const std::string& aSource) {
    uint32_t lineStart = 0;
    for (uint32_t i = 0; i < aSource.size(); i++) {
        if (aSource[i] == '\n' || aSource[i] == '\r') {
            source.source.push_back(aSource.substr(lineStart, i - lineStart));
            lineStart = i + 1;
        }
    }
}

extern int crntToken;

extern std::string identifierStr;
extern std::string operatorStr;

extern uint8_t componentCount;
extern uint8_t columnCount;
extern uint8_t rowCount;

extern double numValueD;
extern long numValueL;
extern unsigned long numValueU;
extern char numTypeStr;

//TODO: support custom error callbacks
inline void logError(const char* msg) {
    std::cerr << source.crntDebugLine + 1 << ":" << source.crntDebugChar + 1 << ": " << SET_TEXT_COLOR("31") << "error:" << RESET_TEXT_COLOR() " " << msg << std::endl;
    std::cout << source.source[source.crntDebugLine] << std::endl;
    std::string pointLine;
    for (uint32_t i = 0; i < source.crntDebugChar; i++)
        pointLine += " ";
    std::cout << pointLine << "^" << std::endl;
}

inline void logError(std::string msg) {
    logError(msg.c_str());
}

inline char getEscapedVersionOfChar(char src) {
    static char escChar[]= { '\a','\b','\f','\n','\r','\t','\v', '\\', '\0'};
    static char esscStr[]= {  'a', 'b', 'f', 'n', 'r', 't', 'v', '\\',  '0'};
    for (uint8_t i = 0; i < sizeof(escChar) / sizeof(char); i++) {
        if (src == esscStr[i])
            return escChar[i];
    }

    return src;
}

inline bool charIsOperator(char c) {
    static char operators[] = {
        '&', '|', '!', '<', '>',
        '+', '-', '*', '/',
        '=',
        '.'
    };
    for (uint8_t i = 0; i < sizeof(operators) / sizeof(char); i++) {
        if (c == operators[i])
            return true;
    }

    return false;
}

inline char getNextChar() {
    if (source.crntLine >= source.source.size())
        return 0; //EOF
    if (source.stringPos == source.source[source.crntLine].size()) {
        source.stringPos = 0;
        source.crntChar = 0;
        source.crntDebugChar = 0;
        source.crntLine++;
        source.crntDebugLine = source.crntLine;

        return '\n';
    }
    source.crntChar++;
    source.crntDebugChar = source.crntChar;

    return source.source[source.crntLine][source.stringPos++];
}

} //namespace lvslang

#endif
