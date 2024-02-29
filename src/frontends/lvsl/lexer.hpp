#ifndef LVSLANG_LVSL_LEXER_H
#define LVSLANG_LVSL_LEXER_H

#include <string>

#include "token.hpp"

namespace lvslang {

namespace lvsl {

int getTypeFromString(const std::string& strType);

int getOperatorFromString(const std::string& operatorStr);

void resetLastChar();

int getNextToken();

} // namespace lvsl

} // namespace lvslang

#endif
