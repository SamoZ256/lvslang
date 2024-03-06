#include "type_name.hpp"

namespace lvslang {

// TODO: support texture buffer?
const std::string textureViewTypeLUT_Metal[] = {
    "1d",
    "2d",
    "3d",
    "1d_array",
    "2d_array",
    "cube",
    "cube_array",
    "buffer"
};

std::string getTypeNameBegin_Metal(irb::Type* type) {
    std::string strTmp;
    switch (type->getTypeID()) {
    case irb::TypeID::Void:
        return "void";
    case irb::TypeID::Bool:
        return "bool";
    case irb::TypeID::Integer:
        switch (type->getBitCount()) {
        case 8:
            strTmp = "char";
            break;
        case 16:
            strTmp = "short";
            break;
        case 32:
            strTmp = "int";
            break;
        default:
            IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of integer can only be 8, 16 or 32");
            return "";
        }
        if (!type->getIsSigned())
            strTmp = "u" + strTmp;
        
        return strTmp;
    case irb::TypeID::Float:
        switch (type->getBitCount()) {
        case 16:
            return "half";
        case 32:
            return "float";
        default:
            IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of float can only be 16 or 32");
            return "";
        }
    case irb::TypeID::Pointer:
        return getTypeNameBegin_Metal(type->getElementType()) + "*";
    case irb::TypeID::Array:
        return getTypeNameBegin_Metal(type->getBaseType());
    case irb::TypeID::Structure:
        return static_cast<irb::StructureType*>(type)->getName();
    case irb::TypeID::Function:
        return "FUNCTION"; // TODO: implement this
    case irb::TypeID::Vector:
        return getTypeNameBegin_Metal(type->getBaseType()) + std::to_string(static_cast<irb::VectorType*>(type)->getComponentCount());
    case irb::TypeID::Matrix:
        return getTypeNameBegin_Metal(type->getBaseType()->getBaseType()) + std::to_string(static_cast<irb::MatrixType*>(type)->getColumnCount()) + "x" + std::to_string(static_cast<irb::VectorType*>(type->getBaseType())->getComponentCount());
    case irb::TypeID::Texture:
        return "texture" + textureViewTypeLUT_Metal[(int)static_cast<irb::TextureType*>(type)->getViewType()] + "<" + getTypeNameBegin_Metal(type->getBaseType()) + ">";
    case irb::TypeID::Sampler:
        return "sampler";
    default:
        return "";
    }
}

const std::string textureViewTypeLUT_HLSL[] = {
    "1D",
    "2D",
    "3D",
    "1DArray",
    "2DArray",
    "Cube",
    "CubeArray",
    "Buffer"
};

std::string getTypeNameBegin_HLSL(irb::Type* type) {
    std::string strTmp;
    switch (type->getTypeID()) {
    case irb::TypeID::Void:
        return "void";
    case irb::TypeID::Bool:
        return "bool";
    case irb::TypeID::Integer:
        switch (type->getBitCount()) {
        case 8:
        case 16:
            strTmp = "int16_t";
            break;
        case 32:
            strTmp = "int";
            break;
        default:
            IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of integer can only be 8, 16 or 32");
            return nullptr;
        }
        if (!type->getIsSigned())
            strTmp = "u" + strTmp;
        
        return strTmp;
    case irb::TypeID::Float:
        switch (type->getBitCount()) {
        case 16:
            return "half";
        case 32:
            return "float";
        default:
            IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of float can only be 16 or 32");
            return nullptr;
        }
    case irb::TypeID::Pointer:
        return getTypeNameBegin_HLSL(type->getElementType()) + "*";
    case irb::TypeID::Array:
        return getTypeNameBegin_HLSL(type->getBaseType());
    case irb::TypeID::Structure:
        return static_cast<irb::StructureType*>(type)->getName();
    case irb::TypeID::Function:
        return "FUNCTION"; // TODO: implement this
    case irb::TypeID::Vector:
        strTmp = getTypeNameBegin_HLSL(type->getBaseType());
        if (strTmp.substr(strTmp.size() - 2, 2) == "_t")
            return "vector<" + strTmp + ", " + std::to_string(static_cast<irb::VectorType*>(type)->getComponentCount()) + ">";
        else
            return strTmp + std::to_string(static_cast<irb::VectorType*>(type)->getComponentCount());
    case irb::TypeID::Matrix:
        return getTypeNameBegin_HLSL(type->getBaseType()->getBaseType()) + std::to_string(static_cast<irb::MatrixType*>(type)->getColumnCount()) + "x" + std::to_string(static_cast<irb::VectorType*>(type->getBaseType())->getComponentCount());
    case irb::TypeID::Texture:
        // HLSL requires the full type for the texture (e.g. float4 instead of 4)
        strTmp = "Texture" + textureViewTypeLUT_HLSL[(int)static_cast<irb::TextureType*>(type)->getViewType()];
        if (type->getBaseType()->getTypeID() != irb::TypeID::Float || type->getBaseType()->getBitCount() != 32)
            strTmp += "<" + getTypeNameBegin_HLSL(type->getBaseType()) + "4>";
        
        return strTmp;
    case irb::TypeID::Sampler:
        return "SamplerState";
    default:
        return "";
    }
}

const std::string textureViewTypeLUT_GLSL[] = {
    "1D",
    "2D",
    "3D",
    "1DArray",
    "2DArray",
    "Cube",
    "CubeArray",
    "Buffer"
};

std::string getTypeNameBegin_GLSL(irb::Type* type) {
    std::string strTmp;
    switch (type->getTypeID()) {
    case irb::TypeID::Void:
        return "void";
    case irb::TypeID::Bool:
        return "bool";
    case irb::TypeID::Integer:
        // TODO: uncomment
        strTmp = "int"/* + std::to_string(type->getBitCount())*/;
        if (!type->getIsSigned())
            strTmp = "u" + strTmp;
        
        return strTmp;
    case irb::TypeID::Float:
        switch (type->getBitCount()) {
        case 16:
            return "float16_t";
        case 32:
            return "float";
        default:
            IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of float can only be 16 or 32");
            return nullptr;
        }
    case irb::TypeID::Pointer:
        return getTypeNameBegin_GLSL(type->getElementType()) + "*";
    case irb::TypeID::Array:
        return getTypeNameBegin_GLSL(type->getBaseType());
    case irb::TypeID::Structure:
        return static_cast<irb::StructureType*>(type)->getName();
    case irb::TypeID::Function:
        return "FUNCTION"; // TODO: implement this
    case irb::TypeID::Vector:
        switch (type->getBaseType()->getTypeID()) {
        case irb::TypeID::Integer:
            strTmp = (type->getBaseType()->getIsSigned() ? "i" : "u");
            if (type->getBaseType()->getBitCount() != 32)
                strTmp += std::to_string(type->getBaseType()->getBitCount());
            break;
        case irb::TypeID::Float:
            if (type->getBaseType()->getBitCount() != 32)
                strTmp = "f" + std::to_string(type->getBaseType()->getBitCount());
            break;
        default:
            break;
        }
        strTmp += "vec" + std::to_string(static_cast<irb::VectorType*>(type)->getComponentCount());

        return strTmp;
    case irb::TypeID::Matrix:
        strTmp += "mat" + std::to_string(static_cast<irb::MatrixType*>(type)->getColumnCount());
        if (static_cast<irb::MatrixType*>(type)->getColumnCount() != static_cast<irb::VectorType*>(type->getBaseType())->getComponentCount())
            strTmp += "x" + std::to_string(static_cast<irb::VectorType*>(type->getBaseType())->getComponentCount());

        return strTmp;
    case irb::TypeID::Texture:
        return (static_cast<irb::TextureType*>(type)->getAccess() == irb::TextureAccess::Sample ? "texture" : "image") + textureViewTypeLUT_GLSL[(int)static_cast<irb::TextureType*>(type)->getViewType()]; // TODO: add type to the name
    case irb::TypeID::Sampler:
        return "sampler";
    default:
        return "";
    }
}

std::string getTypeNameEnd(irb::Type* type) {
    switch (type->getTypeID()) {
    case irb::TypeID::Array:
        return "[" + std::to_string(static_cast<irb::ArrayType*>(type)->getSize()) + "]" + getTypeNameEnd(type->getBaseType());
    default:
        return "";
    }
}

} // namespace lvslang
