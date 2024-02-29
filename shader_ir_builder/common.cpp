#include "common.hpp"

namespace irb {

SPIRVVersion spirvVersion;

std::map<SPIRVVersion, std::string> spirvVersionMap = {
    {SPIRVVersion::_1_0, "1.0"},
    {SPIRVVersion::_1_1, "1.1"},
    {SPIRVVersion::_1_2, "1.2"},
    {SPIRVVersion::_1_3, "1.3"},
    {SPIRVVersion::_1_4, "1.4"},
    {SPIRVVersion::_1_5, "1.5"},
    {SPIRVVersion::_1_6, "1.6"}
};

std::tuple<bool, std::string, std::string> extensions[(int)Extension::MaxEnum] = {
    {false, "GL_EXT_shader_8bit_storage", "SPV_KHR_8bit_storage"},
    {false, "GL_EXT_shader_16bit_storage", "SPV_KHR_16bit_storage"},
    {false, "GL_EXT_shader_explicit_arithmetic_types", "SPV_AMD_gpu_shader_int16"}
};

} // namespace irb
