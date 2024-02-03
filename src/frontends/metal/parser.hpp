#ifndef LVSLANG_METAL_PARSER_H
#define LVSLANG_METAL_PARSER_H

#include <string>

namespace lvslang {

namespace metal {

bool compileStandardLibrary();

bool compile(const std::string& source);

} //namespace lvsl

} //namespace lvslang

#endif
