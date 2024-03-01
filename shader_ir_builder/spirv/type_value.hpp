#ifndef IRB_SPIRV_TYPE_VALUE_H
#define IRB_SPIRV_TYPE_VALUE_H

#include "../value.hpp"

namespace irb {

class SPIRVBuilder;

static const std::string storageClassLUT[] = {
    "UniformConstant",
    "Input",
    "Uniform",
    "Output",
    "Workgroup",
    //"CrossWorkgroup",
    "Private",
    "Function",
    //"Generic",
    "PushConstant",
    "AtomicCounter",
    "Image",
    "StorageBuffer"
};

Value* getTypeValue(SPIRVBuilder* builder, Type* type, bool decorate = false);

} // namespace irb

#endif
