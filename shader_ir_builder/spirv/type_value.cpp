#include "type_value.hpp"

#include "ir.hpp"

namespace irb {

const std::string textureViewTypeLUT[] = {
    "1D",
    "2D",
    "3D",
    "1DArray",
    "2DArray",
    "Cube",
    "CubeArray",
    "Buffer"
};

std::string getNameForRegister(Type* type) {
    if (type->getTypeID() == TypeID::Void) {
        return "void";
    } else if (type->getTypeID() == TypeID::Bool) {
        return "bool";
    } else if (type->getTypeID() == TypeID::Integer) {
        return (type->getIsSigned() ? "int" : "uint") + std::to_string(type->getBitCount());
    } else if (type->getTypeID() == TypeID::Float) {
        return "float" + std::to_string(type->getBitCount());
    } else if (type->getTypeID() == TypeID::Pointer) {
        return "ptr_" + storageClassLUT[(int)static_cast<PointerType*>(type)->getStorageClass()] + "_" + getNameForRegister(type->getElementType());
    } else if (type->getTypeID() == TypeID::Array) {
        return "array_" + getNameForRegister(type->getBaseType()) + "_" + std::to_string(static_cast<ArrayType*>(type)->getSize());
    } else if (type->getTypeID() == TypeID::Structure) {
        return "struct_" + static_cast<StructureType*>(type)->getName();
    } else if (type->getTypeID() == TypeID::Function) {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        std::string registerName = "func_" + getNameForRegister(functionType->getReturnType());
        for (auto* arg : functionType->getArguments())
            registerName += "_" + getNameForRegister(arg);
        
        return registerName;
    } else if (type->getTypeID() == TypeID::Vector) {
        return "vec" + std::to_string(static_cast<VectorType*>(type)->getComponentCount()) + getNameForRegister(type->getBaseType());
    } else if (type->getTypeID() == TypeID::Matrix) {
        return "mat" + std::to_string(static_cast<MatrixType*>(type)->getColumnCount()) + getNameForRegister(type->getBaseType());
    } else if (type->getTypeID() == TypeID::Texture) {
        return "texture_" + textureViewTypeLUT[(int)static_cast<TextureType*>(type)->getViewType()] + "_" + getNameForRegister(type->getBaseType());
    } else if (type->getTypeID() == TypeID::Sampler) {
        return "sampler";
    }

    return "";
}

Value* getTypeValue(SPIRVBuilder* builder, Type* type, bool decorate) {
    std::string code;
    if (type->getTypeID() == TypeID::Void) {
        code = "OpTypeVoid";
    } else if (type->getTypeID() == TypeID::Bool) {
        code = "OpTypeBool";
    } else if (type->getTypeID() == TypeID::Integer) {
        code = "OpTypeInt " + std::to_string(type->getBitCount()) + " " + (type->getIsSigned() ? "1" : "0");
    } else if (type->getTypeID() == TypeID::Float) {
        code = "OpTypeFloat " + std::to_string(type->getBitCount());
    } else if (type->getTypeID() == TypeID::Pointer) {
        PointerType* pointerType = static_cast<PointerType*>(type);
        Value* elementTypeV = getTypeValue(builder, pointerType->getElementType(), decorate);
        code = "OpTypePointer " + storageClassLUT[(int)pointerType->getStorageClass()] + " " + elementTypeV->getName();
    } else if (type->getTypeID() == TypeID::Array) {
        ArrayType* arrayType = static_cast<ArrayType*>(type);
        Value* arrayV = getTypeValue(builder, arrayType->getBaseType(), decorate);
        Value* sizeV = builder->opConstant(new ConstantInt(type->getContext(), arrayType->getSize(), 32, false));
        code = "OpTypeArray " + arrayV->getName() + " " + sizeV->getName();
    } else if (type->getTypeID() == TypeID::Structure) {
        StructureType* structureType = static_cast<StructureType*>(type);
        Structure* structure = structureType->getStructure();
        std::vector<Value*> memberValues(structure->members.size());
        for (uint16_t i = 0; i < memberValues.size(); i++)
            memberValues[i] = getTypeValue(builder, structure->members[i].type, decorate);
        code = "OpTypeStruct";
        for (auto* memberValue : memberValues)
            code += " " + memberValue->getName();

        Value* value = builder->_addCodeToTypesVariablesConstantsBlock(type, code, getNameForRegister(structureType), structureType->getName());

        if (decorate && !structure->decorated) {
            //We need to set @ref decorated to 'true' at the beginning, since @ref opMemberDecorate is going to call this function and we want to avoid endless loop
            structure->decorated = true;
            uint32_t offset = 0;
            for (uint32_t i = 0; i < structure->members.size(); i++) {
                //Offset
                builder->opMemberDecorate(value, i, Decoration::Offset, {std::to_string(offset)});
                offset += memberValues[i]->getType()->getBitCount(true) / 8; //To bytes
            }
        }

        return value;
    } else if (type->getTypeID() == TypeID::Function) {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        Value* returnV = getTypeValue(builder, functionType->getReturnType(), decorate);
        std::vector<Value*> argumentVs(functionType->getArguments().size());
        for (uint16_t i = 0; i < argumentVs.size(); i++)
            argumentVs[i] = getTypeValue(builder, new PointerType(type->getContext(), functionType->getArguments()[i], StorageClass::Function), decorate);
        code = "OpTypeFunction " + returnV->getName();
        for (auto* argV : argumentVs)
            code += " " + argV->getName();
    } else if (type->getTypeID() == TypeID::Vector) {
        VectorType* vectorType = static_cast<VectorType*>(type);
        Value* componentV = getTypeValue(builder, vectorType->getBaseType(), decorate);
        code = "OpTypeVector " + componentV->getName() + " " + std::to_string(vectorType->getComponentCount());
    } else if (type->getTypeID() == TypeID::Matrix) {
        MatrixType* matrixType = static_cast<MatrixType*>(type);
        Value* componentV = getTypeValue(builder, matrixType->getBaseType(), decorate);
        code = "OpTypeMatrix " + componentV->getName() + " " + std::to_string(matrixType->getColumnCount());
    } else if (type->getTypeID() == TypeID::Texture) {
        TextureType* textureType = static_cast<TextureType*>(type);
        Value* scalarV = getTypeValue(builder, textureType->getBaseType(), decorate);
        code = "OpTypeImage " + scalarV->getName() + " " + textureViewTypeLUT[(int)textureType->getViewType()] + " 0 0 0 1 Unknown";
    } else if (type->getTypeID() == TypeID::Sampler) {
        code = "OpTypeSampler";
    }

    return builder->_addCodeToTypesVariablesConstantsBlock(type, code, getNameForRegister(type));
}

} //namespace irb
