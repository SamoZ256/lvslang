#include "common.hpp"

namespace irb {

std::map<SPIRVVersion, std::string> spirvVersionMap = {
    {SPIRVVersion::_1_0, "1.0"},
    {SPIRVVersion::_1_1, "1.1"},
    {SPIRVVersion::_1_2, "1.2"},
    {SPIRVVersion::_1_3, "1.3"},
    {SPIRVVersion::_1_4, "1.4"},
    {SPIRVVersion::_1_5, "1.5"},
    {SPIRVVersion::_1_6, "1.6"}
};

} // namespace irb
