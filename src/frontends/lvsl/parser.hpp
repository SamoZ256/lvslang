#ifndef LVSLANG_LVSL_PARSER_H
#define LVSLANG_LVSL_PARSER_H

#include <string>

namespace lvslang {

namespace lvsl {

bool compileStandardLibrary();

bool compile(const std::string& source);

} //namespace lvsl

} //namespace lvslang

#endif
