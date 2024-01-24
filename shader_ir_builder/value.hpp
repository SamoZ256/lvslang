#ifndef LVSLANG_VALUE_H
#define LVSLANG_VALUE_H

#include "context.hpp"

#include "common.hpp"

namespace irb {

//Forward declarations
class IRBuilder;

inline Target target = Target::None;

enum class TypeID {
    None = 0x0,

    //Scalar
    Void      = 0x1,
    Bool      = 0x2,
    Integer   = 0x4,
    Float     = 0x8,

    //Container
    Pointer   = 0x10,
    Array     = 0x20,

    //User-defined
    Structure = 0x40,

    //Vector
    Vector    = 0x80,

    //Function
    Function  = 0x100,

    //Builtin
    Texture   = 0x200,
    Sampler   = 0x400,

    //Misc
    Block     = 0x800,

    Scalar    = Void | Bool | Integer | Float,
    All       = Scalar | Pointer | Array | Structure | Vector | Function | Texture | Sampler,

    MaxEnum
};

inline uint32_t operator&(TypeID l, TypeID r) {
    return (uint32_t)l & (uint32_t)r;
}

inline TypeID operator|(TypeID l, TypeID r) {
    return TypeID((uint32_t)l | (uint32_t)r);
}

class Type {
protected:
    Context& context;
    TypeID typeID;

    std::string attributesStr;

public:
    Type(Context& aContext, TypeID aTypeID = TypeID::None) : context(aContext), typeID(aTypeID) {}

    virtual ~Type() {}

    virtual Type* copy() = 0;

    bool equals(Type* other) {
        if (other->isTemplate() && (typeID & other->getTypeID()))
            return true;

        return _equals(other);
    }

    virtual bool _equals(Type* other) {
        return false;
    }

    virtual Value* getValue(IRBuilder* builder, bool decorate = false) = 0;

    virtual std::string getNameForRegister() = 0;

    virtual uint32_t getBitCount(bool align = false) {
        return 0;
    }

    virtual uint16_t pointerCount() {
        return 0;
    }

    virtual Type* getElementType() {
        IRB_ERROR("This type does not have an element type");
        return nullptr;
    }

    virtual Type* getBaseType() {
        return this;
    }

    virtual std::string getOpPrefix(bool signSensitive, bool needsOrd) {
        return "";
    }

    virtual std::string getTemplateName() {
        return "none.none";
    }

    virtual std::string getCastOpName(Type* castFrom) {
        return "";
    }

    virtual Type* getSpecializedType(Type* other) {
        return nullptr;
    }

    virtual Type* specialize(Type* specializedType) {
        return specializedType;
    }

    inline std::string getAttributes() const {
        return attributesStr;
    }

    inline void addAttribute(const std::string& attr) {
        if (target == Target::AIR)
            attributesStr += attr;
    }

    inline bool isScalar() const {
        return typeID & TypeID::Scalar;
    }

    inline bool isPointer() const {
        return typeID & TypeID::Pointer;
    }

    inline bool isArray() const {
        return typeID & TypeID::Array;
    }

    inline bool isStructure() const {
        return typeID & TypeID::Structure;
    }

    inline bool isFunctionType() const {
        return typeID & TypeID::Function;
    }

    inline bool isVector() const {
        return typeID & TypeID::Vector;
    }

    inline bool isTexture() const {
        return typeID & TypeID::Texture;
    }

    inline bool isSampler() const {
        return typeID & TypeID::Sampler;
    }

    virtual bool isTemplate() const {
        return false;
    }

    virtual bool isOperatorFriendly() {
        return false;
    }

    virtual bool getIsSigned() {
        return false;
    }

    TypeID getTypeID() {
        return typeID;
    }

    std::string getName() const {
        return getNameBegin() + getNameEnd();
    }

    virtual std::string getNameBegin() const = 0;

    virtual std::string getNameEnd() const {
        return "";
    }
};

class Value {
protected:
    Context& context;

    Type* type;
    bool _isConstant = false; //TODO: rename to isConstant?
    std::string name;
    std::string prefix;

public:
    Value(Context& aContext, Type* aType, std::string aName = "", const std::string aPrefix = "%", bool checkIfNameIsAlreadyUsed = true) : context(aContext), type(aType), prefix(aPrefix) {
        name = aName;
        if (aName == "") {
            if (target == Target::SPIRV)
                name = std::to_string(context.crntRegisterNumber++);
            else if (target == Target::AIR)
                name = (prefix == "%" ? "_" : "") + std::to_string(context.crntRegisterNumber++);
        } else {
            std::string baseName = name;

            //Check if the name isn't already used
            if (TARGET_IS_IR(target) && checkIfNameIsAlreadyUsed) {
                uint32_t nb = 0;
                while (std::find(context.registerNames.begin(), context.registerNames.end(), getName()) != context.registerNames.end())
                    name = baseName + std::to_string(nb++);
                context.registerNames.insert(getName());
            }
        }
    }

    //Getters
    Type* getType() {
        return type;
    }

    inline virtual std::string getName() {
        return prefix + name;
    }

    inline std::string getNameWithType() {
        return type->getName() + " " + getName();
    }

    inline std::string getNameWithTypeAndAttributes() {
        return type->getName() + type->getAttributes() + " " + getName();
    }

    inline bool isConstant() const {
        return _isConstant;
    }

    //HACK: just for the "non-ir" backends
    virtual std::string getRawName() {
        return name;
    }

    //Setters
    void setIsConstant(bool aIsConstant) {
        _isConstant = aIsConstant;
    }
};

class UndefinedValue : public Value {
public:
    UndefinedValue(Context& aContext, Type* aType) : Value(aContext, aType, "undef", "", false) {}
};

class ScalarType : public Type {
private:
    uint32_t bitCount;
    bool isSigned;

public:
    ScalarType(Context& aContext, TypeID aTypeID, uint32_t aBitCount, bool aIsSigned = true) : Type(aContext, aTypeID), bitCount(aBitCount), isSigned(aIsSigned) {}

    ~ScalarType() = default;

    Type* copy() override {
        return new ScalarType(*this);
    }

    bool _equals(Type* other) override {
        if (!other->isScalar() || other->getTypeID() != typeID)
            return false;
        ScalarType* otherScalar = static_cast<ScalarType*>(other);

        return (otherScalar->getBitCount() == bitCount && otherScalar->getIsSigned() == isSigned);
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        switch (typeID) {
        case TypeID::Void:
            return "void";
        case TypeID::Bool:
            return "bool";
        case TypeID::Integer:
            return (isSigned ? "int" : "uint") + std::to_string(bitCount);
        case TypeID::Float:
            return "float" + std::to_string(bitCount);
        default:
            return "unknown";
        }
    }

    uint32_t getBitCount(bool align = false) override {
        return bitCount;
    }

    //TODO: support unordered?
    std::string getOpPrefix(bool signSensitive, bool needsOrd) override {
        switch (target) {
        case Target::SPIRV:
            switch (typeID) {
            case TypeID::Bool: //TODO: return "Logical" in some cases?
            case TypeID::Integer:
                if (signSensitive)
                    return (isSigned ? "S" : "U");
                else
                    return "I";
            case TypeID::Float:
                if (needsOrd)
                    return "FOrd";
                else
                    return "F";
            case TypeID::Void:
                return "";
            default:
                return "Unknown";
            }
        case Target::AIR:
            switch (typeID) {
            case TypeID::Bool:
            case TypeID::Integer:
                if (signSensitive)
                    return (isSigned ? "s" : "u");
                else
                    return "";
            case TypeID::Float:
                return "f";
            case TypeID::Void:
                return "";
            default:
                return "Unknown";
            }
        default:
            return "Unknown";
        }
    }

    std::string getTemplateName() override {
        switch (typeID) {
        case TypeID::Bool:
        case TypeID::Integer:
            return getNameBegin();
        case TypeID::Float:
            return "f" + std::to_string(bitCount);
        default:
            return "none_scalar.none_scalar";
        }
    }

    std::string getCastOpName(Type* castFrom) override {
        if (castFrom->isVector())
            return "NP"; //Not possible
        switch (castFrom->getTypeID()) {
        case TypeID::Bool:
        case TypeID::Integer:
            if (castFrom->getIsSigned()) {
                switch (typeID) {
                case TypeID::Bool:
                case TypeID::Integer:
                    if (isSigned)
                        return "SConvert";
                    else
                        return "NR"; //SatConvertSToU
                case TypeID::Float:
                    return "ConvertSToF";
                default:
                    break;
                }
            } else {
                switch (typeID) {
                case TypeID::Bool:
                case TypeID::Integer:
                    if (isSigned)
                        return "NR"; //SatConvertUToS
                    else
                        return "UConvert";
                case TypeID::Float:
                    return "ConvertUToF";
                default:
                    break;
                }
            }
            break;
        case TypeID::Float:
            switch (typeID) {
            case TypeID::Bool:
            case TypeID::Integer:
                if (isSigned)
                    return "ConvertFToS";
                else
                    return "ConvertFToU";
            case TypeID::Float:
                return "FConvert";
            default:
                break;
            }
            break;
        default:
            break;
        }

        return "Unknown";
    }

    bool isOperatorFriendly() override {
        return true;
    }

    bool getIsSigned() override {
        return isSigned;
    }

    //TODO: add "noundef" attribute by default?
    std::string getNameBegin() const override {
        std::string strTmp;
        switch (target) {
        case Target::Metal:
            switch (typeID) {
            case TypeID::Void:
                return "void";
            case TypeID::Bool:
                return "bool";
            case TypeID::Integer:
                switch (bitCount) {
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
                    return nullptr;
                }
                if (!isSigned)
                    strTmp = "u" + strTmp;
                
                return strTmp;
            case TypeID::Float:
                switch (bitCount) {
                case 16:
                    return "half";
                case 32:
                    return "float";
                default:
                    IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of float can only be 16 or 32");
                    return nullptr;
                }
            default:
                break;
            }
            return "";
        case Target::HLSL:
            switch (typeID) {
            case TypeID::Void:
                return "void";
            case TypeID::Bool:
                return "bool";
            case TypeID::Integer:
                switch (bitCount) {
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
                if (!isSigned)
                    strTmp = "u" + strTmp;
                
                return strTmp;
            case TypeID::Float:
                switch (bitCount) {
                case 16:
                    return "min16float";
                case 32:
                    return "float";
                default:
                    IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of float can only be 16 or 32");
                    return nullptr;
                }
            default:
                break;
            }
            return "";
        case Target::GLSL:
            switch (typeID) {
            case TypeID::Void:
                return "void";
            case TypeID::Bool:
                return "bool";
            case TypeID::Integer:
                //TODO: uncomment
                strTmp = "int"/* + std::to_string(bitCount)*/;
                if (!isSigned)
                    strTmp = "u" + strTmp;
                
                return strTmp;
            case TypeID::Float:
                switch (bitCount) {
                case 16:
                    return "float16_t";
                case 32:
                    return "float";
                default:
                    IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of float can only be 16 or 32");
                    return nullptr;
                }
            default:
                break;
            }
            return "";
        case Target::AIR:
            switch (typeID) {
            case TypeID::Void:
                return "void";
            case TypeID::Bool:
                return "i1";
            case TypeID::Integer:
                return "i" + std::to_string(bitCount);
            case TypeID::Float:
                switch (bitCount) {
                case 16:
                    return "half";
                case 32:
                    return "float";
                default:
                    IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of float can only be 16 or 32");
                    return nullptr;
                }
            default:
                break;
            }
            return "";
        default:
            return "";
        }
    }
};

class ConstantValue : public Value {
protected:
    std::string valueStr;

public:
    ConstantValue(Context& aContext, Type* aType, std::string aValueStr) : Value(aContext, aType, "const"), valueStr(aValueStr) {
        _isConstant = true;
    }

    std::string getName() override {
        return valueStr;
    }

    std::string getRawName() override {
        return valueStr;
    }
};

class ConstantBool : public ConstantValue {
public:
    ConstantBool(Context& aContext, bool value) : ConstantValue(aContext, new ScalarType(aContext, TypeID::Bool, 8, false), TARGET_IS_IR(target) ? std::to_string(value) : (value ? "true" : "false")) {}
};

class ConstantInt : public ConstantValue {
public:
    ConstantInt(Context& aContext, long value, uint8_t bitCount, bool isSigned) : ConstantValue(aContext, new ScalarType(aContext, TypeID::Integer, bitCount, isSigned), std::to_string(value)) {}
};

class ConstantFloat : public ConstantValue {
public:
    ConstantFloat(Context& aContext, float value, uint8_t bitCount) : ConstantValue(aContext, new ScalarType(aContext, TypeID::Float, bitCount, true), target == Target::AIR ? doubleToHEX(value) : std::to_string(value)) {}
};

class PointerType : public Type {
private:
    Type* _baseType;
    StorageClass storageClass;
    int addressSpace = -1;

    std::string attributesStr;

public:
    PointerType(Context& aContext, Type* aBaseType, StorageClass aStorageClass) : Type(aContext, TypeID::Pointer), _baseType(aBaseType), storageClass(aStorageClass) {}

    ~PointerType() = default;

    Type* copy() override {
        return new PointerType(*this);
    }

    bool _equals(Type* other) override {
        return (other->isPointer() && _baseType == other->getElementType());
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        GET_STORAGE_CLASS_NAME(storageClass);
        return "ptr_" + storageClassStr + "_" + _baseType->getNameForRegister();
    }

    uint32_t getBitCount(bool align = false) override {
        return 64;
    }

    uint16_t pointerCount() override {
        return 1;
    }

    //TODO: override @ref getOpPrefix

    Type* getSpecializedType(Type* other) override {
        return _baseType->getSpecializedType(other->getElementType());
    }

    Type* specialize(Type* specializedType) override {
        return new PointerType(context, _baseType->specialize(specializedType), storageClass);
    }

    Type* getElementType() override {
        return _baseType->copy();
    }

    bool isOperatorFriendly() override {
        return true;
    }

    std::string getNameBegin() const override {
        if (TARGET_IS_CODE(target)) {
            return _baseType->getName() + "*";
        } else if (target == Target::AIR) {
            if (target == Target::AIR && addressSpace != -1)
                return "ptr addrspace(" + std::to_string(addressSpace) + ")";
            else
                return "ptr";
        } else {
            return "unknown";
        }
    }

    //Getters
    inline StorageClass getStorageClass() const {
        return storageClass;
    }

    inline int getAddressSpace() const {
        return addressSpace;
    }

    //Setters
    inline void setAddressSpace(int aAddressSpace) {
        addressSpace = aAddressSpace;
    }
};

class Size {
public:
    virtual uint32_t getValue() const = 0;

    inline bool equals(Size* other) const {
        return (getValue() == 0 || other->getValue() == 0 || getValue() == other->getValue());
    }
};

class NumberSize : public Size {
private:
    uint32_t value;

public:
    NumberSize(uint32_t aValue) : value(aValue) {
        if (value == 0)
            error("value cannot be 0", "NumerSize::NumberSize");
    }

    uint32_t getValue() const override {
        return value;
    }
};

class TemplateSize : public Size {
public:
    uint32_t getValue() const override {
        return 0;
    }
};

class ArrayType : public Type {
private:
    Type* arrayType;
    Size* size;

public:
    ArrayType(Context& aContext, Type* aArrayType, Size* aSize) : Type(aContext, TypeID::Array), arrayType(aArrayType), size(aSize) {}

    ~ArrayType() = default;

    Type* copy() override {
        return new ArrayType(*this);
    }

    bool _equals(Type* other) override {
        if (!other->isArray())
            return false;
        ArrayType* otherArray = static_cast<ArrayType*>(other);

        return (size->equals(otherArray->getSize()) && arrayType->equals(other->getElementType()));
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "array_" + arrayType->getNameForRegister() + "_" + std::to_string(size->getValue());
    }

    uint32_t getBitCount(bool align = false) override {
        return arrayType->getBitCount(align) * size->getValue();
    }

    uint16_t pointerCount() override {
        return arrayType->pointerCount() + 1;
    }

    Type* getBaseType() override {
        return arrayType;
    }

    Type* getSpecializedType(Type* other) override {
        Type* specializedBaseType = arrayType->getSpecializedType(other->getBaseType());
        if (size->getValue() == 0)
            return new ArrayType(context, specializedBaseType, static_cast<ArrayType*>(other)->getSize());

        return specializedBaseType;
    }

    Type* specialize(Type* specializedType) override {
        if (size->getValue() == 0)
            return specializedType;
        
        return new ArrayType(context, arrayType->specialize(specializedType), size);
    }

    std::string getNameBegin() const override {
        if (TARGET_IS_IR(target))
            return "[" + std::to_string(size->getValue()) + " x " + arrayType->getName() + "]";
        else
            return arrayType->getNameBegin();
    }

    std::string getNameEnd() const override {
        if (TARGET_IS_CODE(target))
            return "[" + std::to_string(size->getValue()) + "]" + arrayType->getNameEnd();
        
        return "unknown";
    }

    bool isTemplate() const override {
        return size->getValue() == 0;
    }
    
    //Getters
    inline Size* getSize() const {
        return size;
    }
};

class StructureType : public Type {
private:
    Structure* structure;

    std::string name;

public:
    StructureType(Context& aContext, const std::string& aName) : Type(aContext, TypeID::Structure), name(aName) {
        structure = context.structures[name];
        //if (target != Target::GLSL)
        //    nameBegin = "struct ";
        if (!structure)
            error("use of undeclared structure '" + name + "'", "StructureType::StructureType");
    }

    ~StructureType() = default;

    Type* copy() override {
        return new StructureType(*this);
    }

    bool _equals(Type* other) override {
        if (!other->isStructure())
            return false;
        StructureType* otherStruct = static_cast<StructureType*>(other);

        return (otherStruct->getStructure() == structure);
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "struct_" + name;
    }

    uint32_t getBitCount(bool align = false) override {
        uint32_t bitCount = 0;
        for (auto& member : structure->members)
            bitCount += member.type->getBitCount(align);
        
        return bitCount;
    }

    std::string getNameBegin() const override {
        if (target == Target::AIR)
            return "%" + name;
        else
            return name;
    }

    inline Structure* getStructure() {
        return structure;
    }
};

class FunctionType : public Type {
private:
    Type* returnType;
    std::vector<Type*> arguments;
    Value* returnV = nullptr;

public:
    FunctionType(Context& aContext, Type* aReturnType, const std::vector<Type*>& aArguments) : Type(aContext, TypeID::Function), returnType(aReturnType), arguments(aArguments) {}

    ~FunctionType() = default;

    Type* copy() override {
        return new FunctionType(*this);
    }

    bool _equals(Type* other) override {
        if (!other->isFunctionType())
            return false;

        FunctionType* otherFunctionType = static_cast<FunctionType*>(other);
        if (!returnType->equals(otherFunctionType->getReturnType()))
            return false;
        if (arguments.size() != otherFunctionType->getArguments().size())
            return false;
        for (uint32_t i = 0; i < arguments.size(); i++) {
            if (!arguments[i]->equals(otherFunctionType->getArguments()[i]))
                return false;
        }

        return true;
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        std::string registerName = "func_" + returnType->getNameForRegister();
        for (auto* arg : arguments)
            registerName += "_" + arg->getNameForRegister();
        
        return registerName;
    }

    Type* getSpecializedFunctionType(Type* other) {
        if (!equals(other)) {
            IRB_ERROR("types are not equal");
            return nullptr;
        }

        FunctionType* otherFunctionType = static_cast<FunctionType*>(other);

        Type* specializedType = nullptr;
        for (uint32_t i = 0; i < arguments.size(); i++) {
            Type* specializedArgType = arguments[i]->getSpecializedType(otherFunctionType->getArguments()[i]);
            if (specializedArgType) {
                if (!specializedType || specializedType->equals(specializedArgType))
                    specializedType = specializedArgType;
                else
                    return nullptr;
            }
        }
        Type* specializedReturnType = returnType->getSpecializedType(otherFunctionType->getReturnType());
        if (specializedReturnType) {
            if (specializedReturnType->isTemplate())
                otherFunctionType->setReturnType(otherFunctionType->getReturnType()->specialize(specializedType));
            else
                return specializedReturnType;
        }

        if (!specializedType)
            return new ScalarType(context, TypeID::Void, 0);
        
        return specializedType;
    }

    Type* specialize(Type* specializedType) override {
        if (!specializedType->isTemplate()) {
            IRB_ERROR("type is not a template");
            return nullptr;
        }

        std::vector<irb::Type*> specializedArguments(arguments.size());
        for (uint32_t i = 0; i < arguments.size(); i++)
            specializedArguments[i] = arguments[i]->specialize(specializedType);

        FunctionType* specializedFunctionType = new FunctionType(context, returnType->specialize(specializedType), specializedArguments);

        return specializedFunctionType;
    }

    //TODO: make this different in case of code backends
    std::string getNameBegin() const override {
        return "ptr";
    }

    //Getters
    inline Type* getReturnType() const {
        return returnType;
    }

    inline Value* getReturnV() const {
        if (!returnV)
            IRB_ERROR("return value is null");
        
        return returnV;
    }

    inline const std::vector<Type*>& getArguments() const {
        return arguments;
    }

    //Setters
    inline void setReturnType(Type* aReturnType) {
        returnType = aReturnType;
    }
};

class VectorType : public Type {
private:
    Type* componentType;
    Size* componentCount;

public:
    VectorType(Context& aContext, Type* aComponentType, Size* aComponentCount) : Type(aContext, TypeID::Vector), componentType(aComponentType), componentCount(aComponentCount) {
        if (!componentType->isScalar()) {
            error("vectors cannot have non-scalar component type", "VectorType::VectorType");
            return;
        }
        if (componentCount->getValue() != 0 && (componentCount->getValue() < 2 || componentCount->getValue() > 4)) {
            error("vectors can only have component count of 2, 3 or 4", "VectorType::VectorType");
            return;
        }
    }

    ~VectorType() = default;

    Type* copy() override {
        return new VectorType(*this);
    }

    bool _equals(Type* other) override {
        if (!other->isVector())
            return false;
        VectorType* otherVector = static_cast<VectorType*>(other);

        return (componentCount->equals(otherVector->getComponentCount()) && componentType->equals(otherVector->getBaseType()));
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "vec_" + componentType->getNameForRegister() + "_" + std::to_string(componentCount->getValue());
    }

    uint32_t getBitCount(bool align = false) override {
        uint8_t alignComponentCount = componentCount->getValue();
        if (align && alignComponentCount == 3)
            alignComponentCount = 4;
        return componentType->getBitCount() * alignComponentCount;
    }

    std::string getOpPrefix(bool signSensitive, bool needsOrd) override {
        return componentType->getOpPrefix(signSensitive, needsOrd);
    }

    std::string getTemplateName() override {
        return componentType->getTemplateName();
    }

    std::string getCastOpName(Type* castFrom) override {
        if (castFrom->getTypeID() == TypeID::Vector) {
            if (componentType->equals(castFrom->getBaseType()))
                return "VC";
            //TODO: cast twice in other cases
        }
        if (castFrom->isScalar()) {
            if (castFrom->getTypeID() == componentType->getTypeID())
                return "VCS";
            //TODO: cast twice in other cases
        }

        return "Unknown";
    }

    Type* getSpecializedType(Type* other) override {
        Type* specializedComponentType = componentType->getSpecializedType(other->getBaseType());
        if (componentCount->getValue() == 0)
            return new VectorType(context, specializedComponentType, static_cast<VectorType*>(other)->getComponentCount());

        return specializedComponentType;
    }

    Type* specialize(Type* specializedType) override {
        if (componentCount->getValue() == 0)
            return specializedType;
        
        return new VectorType(context, componentType->specialize(specializedType), componentCount);
    }

    Type* getBaseType() override {
        return componentType->copy();
    }

    bool isOperatorFriendly() override {
        return true;
    }

    std::string getNameBegin() const override {
        std::string name;
        switch (target) {
        case Target::Metal:
        case Target::HLSL:
            return componentType->getName() + std::to_string(componentCount->getValue());
        case Target::GLSL:
            switch (componentType->getTypeID()) {
            case TypeID::Integer:
                name = (componentType->getIsSigned() ? "i" : "u");
                if (componentType->getBitCount() != 32)
                    name += std::to_string(componentType->getBitCount());
                break;
            case TypeID::Float:
                if (componentType->getBitCount() != 32)
                    name = "f" + std::to_string(componentType->getBitCount());
                break;
            default:
                break;
            }
            name += "vec";
            name += std::to_string(componentCount->getValue());

            return name;
        case Target::AIR:
            return "<" + std::to_string(componentCount->getValue()) + " x " + componentType->getName() + ">";
        default:
            return "unknown";
        }
    }

    bool isTemplate() const override {
        return componentCount->getValue() == 0;
    }

    //Getters
    Size* getComponentCount() {
        return componentCount;
    }
};

class TextureType : public Type {
private:
    TextureViewType viewType;
    Type* type;

public:
    TextureType(Context& aContext, TextureViewType aViewType, Type* aType) : Type(aContext, TypeID::Texture), viewType(aViewType), type(aType) {
        if (target == Target::AIR)
            attributesStr = " nocapture readonly";
    }

    ~TextureType() = default;

    Type* copy() override {
        return new TextureType(*this);
    }

    bool _equals(Type* other) override {
        if (!other->isTexture())
            return false;
        TextureType* otherTexture = static_cast<TextureType*>(other);

        return (otherTexture->getViewType() == viewType && type->equals(otherTexture->getBaseType()));
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "texture_" + std::to_string((int)viewType) + "_" + type->getNameForRegister(); //TODO: use view type name instead of plain enum
    }

    uint32_t getBitCount(bool align = false) override {
        return 64; //TODO: check if this is correct
    }

    Type* getBaseType() override {
        return type;
    }

    Type* getSpecializedType(Type* other) override {
        return type->getSpecializedType(other->getBaseType());
    }

    Type* specialize(Type* specializedType) override {
        return new TextureType(context, viewType, type->specialize(specializedType));
    }

    std::string getNameBegin() const override {
        GET_TEXTURE_NAME(viewType);
        std::string name = viewTypeStr;
        if (target == Target::Metal) {
            name += "<" + type->getName() + ">";
        } else if (target == Target::HLSL) {
            if (type->getTypeID() != TypeID::Float || type->getBitCount() != 32)
                name += "<" + type->getName() + ">"; //TODO: check if this is correct
        }

        return name;
    }

    //Getters
    inline TextureViewType getViewType() {
        return viewType;
    }
};

//TODO: support some template arguments
class SamplerType : public Type {
public:
    SamplerType(Context& aContext) : Type(aContext, TypeID::Sampler) {
        if (target == Target::AIR)
            attributesStr = " nocapture readonly";
    }

    ~SamplerType() = default;

    Type* copy() override {
        return new SamplerType(*this);
    }

    bool _equals(Type* other) override {
        if (!other->isSampler())
            return false;
        SamplerType* otherSampler = static_cast<SamplerType*>(other);

        return true;
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "sampler";
    }

    uint32_t getBitCount(bool align = false) override {
        return 64; //TODO: check if this is correct
    }

    Type* getSpecializedType(Type* other) override {
        return nullptr;
    }

    std::string getNameBegin() const override {
        //TODO: add template addguments
        if (TARGET_IS_IR(target))
            return "ptr addrspace(2)";//"%\"struct.metal::sampler\"";
        else if (target == Target::HLSL)
            return "SamplerState";
        else
            return "sampler";
    }
};

class TemplateType : public Type {
public:
    TemplateType(Context& aContext, TypeID aTypeID = TypeID::All) : Type(aContext, aTypeID) {}

    ~TemplateType() = default;

    Type* copy() override {
        return new TemplateType(*this);
    }

    bool _equals(Type* other) override {
        return true;
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override {
        return nullptr;
    }

    std::string getNameForRegister() override {
        return "none";
    }

    Type* getSpecializedType(Type* other) override {
        return other;
    }

    Type* specialize(Type* specializedType) override {
        return specializedType;
    }

    bool isTemplate() const override {
        return true;
    }

    //TODO: change this?
    std::string getNameBegin() const override {
        return "template<>";
    }
};

} //namespace irb

#endif
