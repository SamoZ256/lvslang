#include "common.hpp"

namespace irb {

std::map<SPIRVVersion, std::string> spirvVersionMap = {
    {SPIRVVersion::_1_0, "1.0"},
    {SPIRVVersion::_1_1, "1.1"},
    {SPIRVVersion::_1_2, "1.2"},
    {SPIRVVersion::_1_3, "1.3"},
    {SPIRVVersion::_1_4, "1.4"},
    {SPIRVVersion::_1_5, "1.5"}
};

std::map<GLSLVersion, std::string> glslVersionMap = {
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

std::tuple<bool, std::string, std::string> extensions[(int)Extension::MaxEnum] = {
    {false, "GL_EXT_shader_8bit_storage", "SPV_KHR_8bit_storage"},
    {false, "GL_EXT_shader_16bit_storage", "SPV_KHR_16bit_storage"},
    {false, "GL_EXT_shader_explicit_arithmetic_types", "SPV_AMD_gpu_shader_int16"}
};

} //namespace irb
