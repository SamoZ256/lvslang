#ifndef IRB_SPIRV_TYPE_VALUE_H
#define IRB_SPIRV_TYPE_VALUE_H

#include "../value.hpp"

namespace irb {

class SPIRVBuilder;

Value* getTypeValue(SPIRVBuilder* builder, Type* type, bool decorate = false);

} //namespace irb

#endif
