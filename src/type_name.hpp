#ifndef LVSLANG_TYPE_NAME_H
#define LVSLANG_TYPE_NAME_H

#include "../shader_ir_builder/value.hpp"

#include "common.hpp"

namespace lvslang {

std::string getTypeNameBegin_Metal(irb::Type* type);

std::string getTypeNameBegin_HLSL(irb::Type* type);

std::string getTypeNameBegin_GLSL(irb::Type* type);

inline std::string getTypeNameBegin(Target target, irb::Type* type) {
    switch (target) {
    case Target::Metal:
        return getTypeNameBegin_Metal(type);
    case Target::HLSL:
        return getTypeNameBegin_HLSL(type);
    case Target::GLSL:
        return getTypeNameBegin_GLSL(type);
    default:
        return "";
    }
}

std::string getTypeNameEnd(irb::Type* type);

inline std::string getTypeName(Target target, irb::Type* type) {
    return getTypeNameBegin(target, type) + getTypeNameEnd(type);
}

} // namespace lvslang

#endif
