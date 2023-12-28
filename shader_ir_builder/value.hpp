#ifndef LVSLANG_VALUE_H
#define LVSLANG_VALUE_H

#include "context.hpp"

#include "common.hpp"

namespace irb {

//Forward declarations
class IRBuilder;

inline Target target = Target::None;

enum class TypeID {
    None,

    //Scalar
    Void,
    Bool,
    Integer,
    Float,

    //TODO: find a suitable name
    Pointer,
    Array,

    //User-defined
    Structure,

    //Vector
    Vector,

    //Function
    Function,

    //Builtin
    Texture,
    Sampler,

    //Misc
    Block,

    MaxEnum
};

inline std::string getTypeName(TypeID typeID, uint32_t bitCount, bool isSigned) {
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
};

class Type {
protected:
    Context& context;
    TypeID typeID;

    std::string nameBegin;
    std::string nameEnd = "";
    std::string code;

public:
    Type(Context& aContext, TypeID aTypeID = TypeID::None) : context(aContext), typeID(aTypeID) {}

    virtual ~Type() {}

    virtual Type* copy() = 0;

    virtual bool equals(Type* other) {
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
        return "Unknown";
    }

    virtual std::string getBuiltinFunctionTypeName() {
        return "none.none";
    }

    virtual std::string getCastOpName(Type* castFrom) {
        return "Unknown";
    }

    virtual std::string getAttributes() {
        return "noundef ";
    }

    virtual bool isScalar() {
        return false;
    }

    virtual bool isPointer() {
        return false;
    }

    virtual bool isArray() {
        return false;
    }

    virtual bool isStructure() {
        return false;
    }

    virtual bool isVector() {
        return false;
    }

    virtual bool isTexture() {
        return false;
    }

    virtual bool isSampler() {
        return false;
    }

    virtual bool isOperatorFriendly() { //TODO: rename?
        return false;
    }

    virtual bool getIsSigned() {
        return false;
    }

    TypeID getTypeID() {
        return typeID;
    }

    std::string getName() {
        return nameBegin + nameEnd;
    }

    const std::string& getNameBegin() {
        return nameBegin;
    }

    const std::string& getNameEnd() {
        return nameEnd;
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
    //HACK: add "_" before the name to prevent LLVM error "instruction expected to be numbered '%n'"
    Value(Context& aContext, Type* aType, std::string aName = "", const std::string aPrefix = "%_", bool checkIfNameIsAlreadyUsed = true) : context(aContext), type(aType), prefix(aPrefix) {
        std::string baseName;
        if (aName == "")
            baseName = std::to_string(context.crntRegisterNumber++);
        else
            baseName = aName;
        name = baseName;

        //Check if the name isn't already used
        if (TARGET_IS_IR(target) && checkIfNameIsAlreadyUsed) {
            uint32_t nb = 0;
            while (context.registerNames.contains(getName()))
                name = baseName + std::to_string(nb++);
            context.registerNames.insert(getName());
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
        return type->getName() + " " + type->getAttributes() + getName();
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

    std::string registerName;

public:
    ScalarType(Context& aContext, TypeID aTypeID, uint32_t aBitCount, bool aIsSigned) : Type(aContext, aTypeID), bitCount(aBitCount), isSigned(aIsSigned) {
        nameBegin = getTypeName(typeID, bitCount, isSigned);
        switch (typeID) {
        case TypeID::Void:
            code = "OpTypeVoid";
            registerName = "void";
            break;
        case TypeID::Bool:
            code = "OpTypeBool";
            registerName = "bool";
            break;
        case TypeID::Integer:
            code = "OpTypeInt " + std::to_string(bitCount) + " " + (isSigned ? "1" : "0");
            if (!isSigned)
                registerName = "u";
            registerName += "int" + std::to_string(bitCount);
            break;
        case TypeID::Float:
            code = "OpTypeFloat " + std::to_string(bitCount);
            registerName = "float" + std::to_string(bitCount);
            break;
        default:
            break;
        }
    }

    ~ScalarType() = default;

    Type* copy() override {
        return new ScalarType(*this);
    }

    bool equals(Type* other) override {
        if (!other->isScalar() || other->getTypeID() != typeID)
            return false;
        ScalarType* otherScalar = static_cast<ScalarType*>(other);

        return (otherScalar->getBitCount() == bitCount && otherScalar->getIsSigned() == isSigned);
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return registerName;
    }

    uint32_t getBitCount(bool align = false) override {
        return bitCount;
    }

    //TODO: support unordered?
    std::string getOpPrefix(bool signSensitive, bool needsOrd) override {
        switch (target) {
        case Target::SPIRV:
            switch (typeID) {
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
            default:
                return "Unknown";
            }
        case Target::AIR:
            switch (typeID) {
            case TypeID::Integer:
                if (signSensitive)
                    return (isSigned ? "s" : "u");
                else
                    return "";
            case TypeID::Float:
                return "f";
            default:
                return "Unknown";
            }
        default:
            return "Unknown";
        }
    }

    std::string getBuiltinFunctionTypeName() override {
        //TODO: check if all of this is correct
        switch (typeID) {
        case TypeID::Bool:
        case TypeID::Integer:
            return (isSigned ? "s." : "u.") + nameBegin;
        case TypeID::Float:
            return "f.f" + std::to_string(bitCount);
        default:
            return "none_scalar.none_scalar";
        }
    }

    std::string getCastOpName(Type* castFrom) override {
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

    bool isScalar() override {
        return true;
    }

    bool isOperatorFriendly() override {
        return true;
    }

    bool getIsSigned() override {
        return isSigned;
    }
};

class ConstantValue : public Value {
protected:
    std::string valueStr;

public:
    ConstantValue(Context& aContext, Type* aType, std::string aValueStr) : Value(aContext, aType), valueStr(aValueStr) {
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
    ConstantBool(Context& aContext, bool value) : ConstantValue(aContext, new ScalarType(aContext, TypeID::Bool, 8, false), std::to_string(value)) {}
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

public:
    PointerType(Context& aContext, Type* aBaseType, StorageClass aStorageClass) : Type(aContext, TypeID::Pointer), _baseType(aBaseType), storageClass(aStorageClass) {
        if (TARGET_IS_CODE(target))
            nameBegin = _baseType->getName() + "*";
        else if (target == Target::AIR)
            nameBegin = "ptr";
    }

    ~PointerType() = default;

    Type* copy() override {
        return new PointerType(*this);
    }

    bool equals(Type* other) override {
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

    std::string getAttributes() override {
        return _baseType->getAttributes();
    }

    bool isPointer() override {
        return true;
    }

    Type* getElementType() override {
        return _baseType->copy();
    }

    bool isOperatorFriendly() override {
        return true;
    }

    //Getters
    inline StorageClass getStorageClass() const {
        return storageClass;
    }

    //Setters
    inline void setAddressSpace(int aAddressSpace) {
        addressSpace = aAddressSpace;
        if (target == Target::AIR)
            nameBegin = "ptr addrspace(" + std::to_string(addressSpace) + ")";
    }
};

class ArrayType : public Type {
private:
    Type* arrayType;
    uint32_t size;

public:
    ArrayType(Context& aContext, Type* aArrayType, uint32_t aSize) : Type(aContext, TypeID::Array), arrayType(aArrayType), size(aSize) {
        if (TARGET_IS_IR(target)) {
            nameBegin = "[" + std::to_string(size) + " x " + arrayType->getName() + "]";
        } else {
            nameBegin = arrayType->getNameBegin();
            nameEnd = "[" + std::to_string(size) + "]" + arrayType->getNameEnd();
        }
    }

    ~ArrayType() = default;

    Type* copy() override {
        return new ArrayType(*this);
    }

    bool equals(Type* other) override {
        //TODO: compare size instead of bit count
        return (other->isArray() && other->getBitCount() == getBitCount() && arrayType->equals(other->getElementType()));
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "array_" + arrayType->getNameForRegister() + "_" + std::to_string(size);
    }

    uint32_t getBitCount(bool align = false) override {
        return arrayType->getBitCount(align) * size;
    }

    uint16_t pointerCount() override {
        return arrayType->pointerCount() + 1;
    }

    Type* getBaseType() override {
        return arrayType;
    }

    bool isArray() override {
        return true;
    }
    
    //Getters
    inline uint32_t getSize() const {
        return size;
    }
};

class StructureType : public Type {
private:
    Structure* structure;
    bool decorated = false;

public:
    StructureType(Context& aContext, const std::string& aName) : Type(aContext, TypeID::Structure) {
        structure = context.structures[aName];
        //if (target != Target::GLSL)
        //    nameBegin = "struct ";
        if (!structure) {
            error("use of undeclared structure '" + aName + "'", "StructureType::StructureType");
        }
        if (target == Target::AIR)
            nameBegin = "%_" + aName; //HACK: add "_"
        else
            nameBegin = aName;
    }

    ~StructureType() = default;

    Type* copy() override {
        return new StructureType(*this);
    }

    bool equals(Type* other) override {
        if (!other->isStructure())
            return false;
        StructureType* otherStruct = static_cast<StructureType*>(other);

        return (otherStruct->getStructure() == structure);
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "struct_" + nameBegin;
    }

    uint32_t getBitCount(bool align = false) override {
        uint32_t bitCount = 0;
        for (auto& member : structure->members)
            bitCount += member.type->getBitCount(align);
        
        return bitCount;
    }

    bool isStructure() override {
        return true;
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
    FunctionType(Context& aContext, Type* aReturnType, const std::vector<Type*>& aArguments) : Type(aContext, TypeID::Function), returnType(aReturnType), arguments(aArguments) {
        //TODO: set different name for code backends?
        nameBegin = "ptr";
    }

    ~FunctionType() = default;

    Type* copy() override {
        return new FunctionType(*this);
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        std::string registerName = "func_" + returnType->getNameForRegister();
        for (auto* arg : arguments)
            registerName += "_" + arg->getNameForRegister();
        
        return registerName;
    }

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
};

class VectorType : public Type {
private:
    Type* componentType;
    uint8_t componentCount;

public:
    VectorType(Context& aContext, Type* aComponentType, uint8_t aComponentCount) : Type(aContext, TypeID::Vector), componentType(aComponentType), componentCount(aComponentCount) {
        if (!componentType->isScalar()) {
            error("vectors cannot have non-scalar component type", "VectorType::VectorType");
            return;
        }
        if (componentCount < 2 || componentCount > 4) {
            error("vectors can only have component count of 2, 3 or 4", "VectorType::VectorType");
            return;
        }
        switch (target) {
        case Target::Metal:
            nameBegin = "vec<" + componentType->getName() + ", " + std::to_string(componentCount) + ">";
            break;
        case Target::GLSL:
            switch (componentType->getTypeID()) {
            case TypeID::Integer:
                nameBegin = (componentType->getIsSigned() ? "i" : "u");
                if (componentType->getBitCount() != 32)
                    nameBegin += std::to_string(componentType->getBitCount());
                break;
            case TypeID::Float:
                if (componentType->getBitCount() != 32)
                    nameBegin = "f" + std::to_string(componentType->getBitCount());
                break;
            default:
                break;
            }
            nameBegin += "vec";
            nameBegin += std::to_string(componentCount);
            break;
        case Target::AIR:
            nameBegin = "<" + std::to_string(componentCount) + " x " + componentType->getName() + ">";
            break;
        default:
            break;
        }
    }

    ~VectorType() = default;

    Type* copy() override {
        return new VectorType(*this);
    }

    bool equals(Type* other) override {
        if (!other->isVector())
            return false;
        VectorType* otherVector = static_cast<VectorType*>(other);

        return (otherVector->getComponentCount() == componentCount && componentType->equals(otherVector->getBaseType()));
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "vec_" + componentType->getNameForRegister() + "_" + std::to_string(componentCount);
    }

    uint32_t getBitCount(bool align = false) override {
        uint8_t alignComponentCount = componentCount;
        if (align && alignComponentCount == 3)
            alignComponentCount = 4;
        return componentType->getBitCount() * alignComponentCount;
    }

    std::string getOpPrefix(bool signSensitive, bool needsOrd) override {
        return componentType->getOpPrefix(signSensitive, needsOrd);
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

    bool isVector() override {
        return true;
    }

    Type* getBaseType() override {
        return componentType->copy();
    }

    bool isOperatorFriendly() override {
        return true;
    }

    uint8_t getComponentCount() {
        return componentCount;
    }
};

class TextureType : public Type {
private:
    TextureViewType viewType;
    ScalarType* type;

public:
    TextureType(Context& aContext, TextureViewType aViewType, ScalarType* aType) : Type(aContext, TypeID::Texture), viewType(aViewType), type(aType) {
        if (target == Target::Metal) {
            std::string viewName = "2d"; //TODO: use actual view name
            nameBegin = "texture" + viewName + "<" + type->getName() + ">";
        } else if (target == Target::GLSL) {
            std::string viewName = "2D";
            nameBegin = "texture" + viewName; //TODO: use prefix based on type
        } else if (target == Target::AIR) {
            std::string viewName = "2d"; //TODO: use actual view name
            nameBegin = "%\"struct.metal::texture" + viewName + "\"";
        }
    }

    ~TextureType() = default;

    Type* copy() override {
        return new TextureType(*this);
    }

    bool equals(Type* other) override {
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

    std::string getAttributes() override {
        return "";
    }

    bool isTexture() override {
        return true;
    }

    inline TextureViewType getViewType() {
        return viewType;
    }
};

//TODO: support some template arguments
class SamplerType : public Type {
public:
    SamplerType(Context& aContext) : Type(aContext, TypeID::Sampler) {
        //TODO: add template addguments
        if (TARGET_IS_IR(target)) {
            nameBegin = "%\"struct.metal::sampler\"";
        } else {
            nameBegin = "sampler";
        }
    }

    ~SamplerType() = default;

    Type* copy() override {
        return new SamplerType(*this);
    }

    bool equals(Type* other) override {
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

    std::string getAttributes() override {
        return "";
    }

    bool isSampler() override {
        return true;
    }
};

} //namespace irb

#endif
