#ifndef LVSLANG_LVSL_PARSER_H
#define LVSLANG_LVSL_PARSER_H

#include <string>

namespace lvslang {

class AST;

namespace lvsl {

bool compileStandardLibrary(AST& ast);

bool compile(AST& ast, const std::string& source);

} //namespace lvsl

} //namespace lvslang

#endif
