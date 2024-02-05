#ifndef LVSLANG_TYPE_NAME_H
#define LVSLANG_TYPE_NAME_H

#include "../shader_ir_builder/value.hpp"

#include "common.hpp"

namespace lvslang {

std::string getTypeNameBegin_Metal(irb::Type* type);

std::string getTypeNameBegin_HLSL(irb::Type* type);

std::string getTypeNameBegin_GLSL(irb::Type* type);

inline std::string getTypeNameBegin(irb::Type* type) {
    switch (irb::target) {
    case irb::Target::Metal:
        return getTypeNameBegin_Metal(type);
    case irb::Target::HLSL:
        return getTypeNameBegin_HLSL(type);
    case irb::Target::GLSL:
        return getTypeNameBegin_GLSL(type);
    default:
        return "";
    }
}

std::string getTypeNameEnd(irb::Type* type);

inline std::string getTypeName(irb::Type* type) {
    return getTypeNameBegin(type) + getTypeNameEnd(type);
}

} //namespace lvslang

#endif
