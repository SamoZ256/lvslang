#include "common.hpp"

namespace lvslang {

Source source = {};

int crntToken;

std::string identifierStr;
std::string operatorStr;

uint8_t componentCount = 0;
uint8_t columnCount = 0;
uint8_t rowCount = 0;

double numValueD;
long numValueL;
unsigned long numValueU;
char numTypeStr;

} // namespace lvslang
