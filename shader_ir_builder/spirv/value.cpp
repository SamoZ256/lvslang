#include "../value.hpp"

#include "ir.hpp"

namespace irb {

Value* ScalarType::getValue(IRBuilder* builder, bool decorate) {
    std::string code;
    switch (typeID) {
    case TypeID::Void:
        code = "OpTypeVoid";
        break;
    case TypeID::Bool:
        code = "OpTypeBool";
        break;
    case TypeID::Integer:
        code = "OpTypeInt " + std::to_string(bitCount) + " " + (isSigned ? "1" : "0");
        break;
    case TypeID::Float:
        code = "OpTypeFloat " + std::to_string(bitCount);
        break;
    default:
        code = "OpUnknownType";
        break;
    }
    
    //std::string comment = registerName;
    //if (!isSigned)
    //    comment += ", sign-less";
    
    //TODO: add comment?
    return static_cast<SPIRVBuilder*>(builder)->_addCodeToTypesVariablesConstantsBlock(this, code, getNameForRegister());
}

Value* PointerType::getValue(IRBuilder* builder, bool decorate) {
    Value* baseValue = _baseType->getValue(builder, decorate);
    GET_STORAGE_CLASS_NAME(storageClass);
    std::string code = "OpTypePointer " + storageClassStr + " " + baseValue->getName();

    return static_cast<SPIRVBuilder*>(builder)->_addCodeToTypesVariablesConstantsBlock(this, code, getNameForRegister(), _baseType->getNameForRegister() + "*");
}

Value* ArrayType::getValue(IRBuilder* builder, bool decorate) {
    Value* arrayValue = arrayType->getValue(builder);
    Type* sizeType = new ScalarType(context, TypeID::Integer, 32, false);
    Value* sizeTypeValue = sizeType->getValue(builder);
    Value* sizeValue = builder->opConstant(new ConstantInt(context, size->getValue(), 32, false));
    std::string code = "OpTypeArray " + arrayValue->getName() + " " + sizeValue->getName();

    return static_cast<SPIRVBuilder*>(builder)->_addCodeToTypesVariablesConstantsBlock(this, code, getNameForRegister(), arrayType->getNameForRegister() + "[" + std::to_string(size->getValue()) + "]");
}

Value* StructureType::getValue(IRBuilder* builder, bool decorate) {
    std::vector<Value*> memberValues(structure->members.size());
    for (uint16_t i = 0; i < memberValues.size(); i++)
        memberValues[i] = structure->members[i].type->getValue(builder, decorate);
    std::string code = "OpTypeStruct";
    for (auto* memberValue : memberValues)
        code += " " + memberValue->getName();

    Value* value = static_cast<SPIRVBuilder*>(builder)->_addCodeToTypesVariablesConstantsBlock(this, code, getNameForRegister(), name, name);

    if (decorate && !structure->decorated) {
        //We need to set @ref decorated to 'true' at the beginning, since @ref opMemberDecorate is going to call this function and we want to avoid endless loop
        structure->decorated = true;
        uint32_t offset = 0;
        for (uint32_t i = 0; i < structure->members.size(); i++) {
            //Offset
            static_cast<SPIRVBuilder*>(builder)->opMemberDecorate(value, i, Decoration::Offset, {std::to_string(offset)});
            offset += memberValues[i]->getType()->getBitCount(true) / 8; //To bytes
            //TODO: uncomment?
            //Location
            /*
            const auto& attributes = structure->members[i].attributes;
            if (attributes.locationIndex != -1)
                static_cast<SPIRVBuilder*>(builder)->opMemberDecorate(value-, i, Decoration::Location, {std::to_string(attributes.locationIndex)});
            //Color
            if (attributes.colorIndex != -1)
                static_cast<SPIRVBuilder*>(builder)->opMemberDecorate(value, i, Decoration::Location, {std::to_string(attributes.colorIndex)});
            */
        }
    }
    
    return value;
}

Value* FunctionType::getValue(IRBuilder* builder, bool decorate) {
    returnV = returnType->getValue(builder);
    std::vector<Value*> argumentVs(arguments.size());
    for (uint16_t i = 0; i < argumentVs.size(); i++)
        argumentVs[i] = PointerType(context, arguments[i], StorageClass::Function).getValue(builder);
    Value* value = new Value(context, this);
    std::string code = "OpTypeFunction " + returnV->getName();
    for (auto* argV : argumentVs)
        code += " " + argV->getName();
    
    std::string comment = returnType->getNameForRegister() + " (";
    for (uint32_t i = 0; i < arguments.size(); i++) {
        if (i != 0)
            comment += ", ";
        comment += arguments[i]->getNameForRegister();
    }
    comment += ")";
    
    return static_cast<SPIRVBuilder*>(builder)->_addCodeToTypesVariablesConstantsBlock(this, code, getNameForRegister(), comment);
}

Value* VectorType::getValue(IRBuilder* builder, bool decorate) {
    Value* componentValue = componentType->getValue(builder);
    std::string code = "OpTypeVector " + componentValue->getName() + " " + std::to_string(componentCount->getValue());
    
    return static_cast<SPIRVBuilder*>(builder)->_addCodeToTypesVariablesConstantsBlock(this, code, getNameForRegister(), "vector(" + std::to_string(componentCount->getValue()) + ") of " + componentType->getNameForRegister());
}

Value* TextureType::getValue(IRBuilder* builder, bool decorate) {
    GET_TEXTURE_NAME(viewType);

    Value* scalarValue = type->getValue(builder);
    std::string code = "OpTypeImage " + scalarValue->getName() + " " + viewTypeStr + " 0 0 0 1 Unknown";
    
    return static_cast<SPIRVBuilder*>(builder)->_addCodeToTypesVariablesConstantsBlock(this, code, getNameForRegister(), "image"); //TODO: use different comment
}

Value* SamplerType::getValue(IRBuilder* builder, bool decorate) {
    return static_cast<SPIRVBuilder*>(builder)->_addCodeToTypesVariablesConstantsBlock(this, "OpTypeSampler", getNameForRegister(), "sampler"); //TODO: use different comment
}

} //namespace irb
