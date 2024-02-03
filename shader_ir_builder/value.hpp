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

    //Matrix
    Matrix    = 0x100,

    //Function
    Function  = 0x200,

    //Builtin
    Texture   = 0x400,
    Sampler   = 0x800,

    //Misc
    Block     = 0x1000,

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
    llvm::Type* handle = nullptr;

    Context& context;
    TypeID typeID;

    std::string attributesStr;

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
        return "";
    }

    virtual std::string getTemplateName() const = 0;

    virtual std::string getCastOpName(Type* castFrom) {
        return "";
    }

    inline std::string getAttributes() const {
        return attributesStr;
    }

    inline void addAttribute(const std::string& attr) {
        //TODO: make this actually do something
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

    inline bool isMatrix() const {
        return typeID & TypeID::Matrix;
    }

    inline bool isTexture() const {
        return typeID & TypeID::Texture;
    }

    inline bool isSampler() const {
        return typeID & TypeID::Sampler;
    }

    virtual bool isOperatorFriendly() {
        return false;
    }

    //Getters
    llvm::Type* getHandle() {
        if (!handle)
            IRB_ERROR("handle is null");
        
        return handle;
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

    virtual std::string getDebugName() const = 0;
};

class Value {
protected:
    llvm::Value* handle = nullptr;

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
    inline llvm::Value* getHandle() {
        if (!handle)
            IRB_ERROR("handle is null");
        
        return handle;
    }

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
    void setHandle(llvm::Value* aHandle) {
        handle = aHandle;
    }

    void setIsConstant(bool aIsConstant) {
        _isConstant = aIsConstant;
    }
};

class UndefinedValue : public Value {
public:
    UndefinedValue(Context& aContext, Type* aType) : Value(aContext, aType, "undef", "", false) {
        if (target == Target::AIR)
            handle = llvm::UndefValue::get(aType->getHandle());
    }
};

class ScalarType : public Type {
private:
    uint32_t bitCount;
    bool isSigned;

public:
    ScalarType(Context& aContext, TypeID aTypeID, uint32_t aBitCount, bool aIsSigned = true) : Type(aContext, aTypeID), bitCount(aBitCount), isSigned(aIsSigned) {
        if (target == Target::AIR) {
            switch (typeID) {
            case TypeID::Bool:
                handle = llvm::Type::getInt1Ty(*context.handle);
                break;
            case TypeID::Integer:
                handle = llvm::Type::getIntNTy(*context.handle, bitCount);
                break;
            case TypeID::Float:
                if (bitCount == 32)
                    handle = llvm::Type::getFloatTy(*context.handle);
                else if (bitCount == 16)
                    handle = llvm::Type::getHalfTy(*context.handle);
                else
                    IRB_INVALID_ARGUMENT_WITH_REASON("bitCount", "bit count of float can only be 16 or 32");
                break;
            default:
                break;
            }
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
            case TypeID::Bool:
                return "Logical";
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

    std::string getTemplateName() const override {
        switch (typeID) {
        case TypeID::Bool:
        case TypeID::Integer:
            return (isSigned ? "i" : "u") + std::to_string(bitCount);
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
        default:
            return "";
        }
    }

    std::string getDebugName() const override {
        std::string strTmp;
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

        return "unknown";
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
    ConstantBool(Context& aContext, bool value) : ConstantValue(aContext, new ScalarType(aContext, TypeID::Bool, 8, false), TARGET_IS_IR(target) ? std::to_string(value) : (value ? "true" : "false")) {
        if (target == Target::AIR)
            handle = llvm::ConstantInt::get(*context.handle, llvm::APInt(1, value, false));
    }
};

class ConstantInt : public ConstantValue {
public:
    ConstantInt(Context& aContext, long value, uint8_t bitCount, bool isSigned) : ConstantValue(aContext, new ScalarType(aContext, TypeID::Integer, bitCount, isSigned), std::to_string(value)) {
        if (target == Target::AIR)
            handle = llvm::ConstantInt::get(*context.handle, llvm::APInt(bitCount, value, isSigned));
    }
};

class ConstantFloat : public ConstantValue {
public:
    ConstantFloat(Context& aContext, float value, uint8_t bitCount) : ConstantValue(aContext, new ScalarType(aContext, TypeID::Float, bitCount, true), target == Target::AIR ? doubleToHEX(value) : std::to_string(value)) {
        if (target == Target::AIR)
            handle = llvm::ConstantFP::get(*context.handle, llvm::APFloat(value));
    }
};

class PointerType : public Type {
private:
    Type* _baseType;
    StorageClass storageClass;
    int addressSpace = -1;

public:
    PointerType(Context& aContext, Type* aBaseType, StorageClass aStorageClass) : Type(aContext, TypeID::Pointer), _baseType(aBaseType), storageClass(aStorageClass) {
        //TODO: set the adress space correctly
        if (target == Target::AIR)
            handle = llvm::PointerType::get(*context.handle, 0u);
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

    std::string getTemplateName() const override {
        return "p" + _baseType->getTemplateName();
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
        } else {
            return "unknown";
        }
    }

    std::string getDebugName() const override {
        return _baseType->getDebugName() + "*";
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
        //TODO: set the address space
        addressSpace = aAddressSpace;
    }
};

class ArrayType : public Type {
private:
    Type* arrayType;
    uint32_t size;

public:
    ArrayType(Context& aContext, Type* aArrayType, uint32_t aSize) : Type(aContext, TypeID::Array), arrayType(aArrayType), size(aSize) {
        if (target == Target::AIR)
            handle = llvm::ArrayType::get(arrayType->getHandle(), size);
    }

    ~ArrayType() = default;

    Type* copy() override {
        return new ArrayType(*this);
    }

    bool equals(Type* other) override {
        if (!other->isArray())
            return false;
        ArrayType* otherArray = static_cast<ArrayType*>(other);

        return (size == otherArray->getSize() && arrayType->equals(other->getElementType()));
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

    std::string getTemplateName() const override {
        return "a" + std::to_string(size) + arrayType->getTemplateName();
    }

    std::string getNameBegin() const override {
        return arrayType->getNameBegin();
    }

    std::string getNameEnd() const override {
        if (TARGET_IS_CODE(target))
            return "[" + std::to_string(size) + "]" + arrayType->getNameEnd();
        
        return "unknown";
    }

    std::string getDebugName() const override {
        return arrayType->getNameBegin() + "[" + std::to_string(size) + "]";
    }
    
    //Getters
    inline uint32_t getSize() const {
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
        
        if (target == Target::AIR) {
            if (!structure->handle) {
                std::vector<llvm::Type*> members;
                members.reserve(structure->members.size());
                for (auto& member : structure->members)
                    members.push_back(member.type->getHandle());
                structure->handle = llvm::StructType::create(members, name);
            }
            handle = structure->handle;
        }
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
        return "struct_" + name;
    }

    uint32_t getBitCount(bool align = false) override {
        uint32_t bitCount = 0;
        for (auto& member : structure->members)
            bitCount += member.type->getBitCount(align);
        
        return bitCount;
    }

    std::string getTemplateName() const override {
        return "s" + name;
    }

    std::string getNameBegin() const override {
        return name;
    }

    std::string getDebugName() const override {
        return "struct " + name;
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
        if (target == Target::AIR) {
            std::vector<llvm::Type*> llvmArguments;
            llvmArguments.reserve(arguments.size());
            for (auto* arg : arguments)
                llvmArguments.push_back(arg->getHandle());
            handle = llvm::FunctionType::get(returnType->getHandle(), llvmArguments, false);
        }
    }

    ~FunctionType() = default;

    Type* copy() override {
        return new FunctionType(*this);
    }

    bool equals(Type* other) override {
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

    std::string getTemplateName() const override {
        std::string templateName;
        for (const auto* arg : arguments)
            templateName += (target == Target::AIR ? "." : "_") + arg->getTemplateName();
        
        return templateName;
    }

    //TODO: make this different in case of code backends
    std::string getNameBegin() const override {
        return "";
    }

    //TODO: implement this
    std::string getDebugName() const override {
        return "FUNCTION_TYPE";
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
    uint32_t componentCount;

public:
    VectorType(Context& aContext, Type* aComponentType, uint32_t aComponentCount) : Type(aContext, TypeID::Vector), componentType(aComponentType), componentCount(aComponentCount) {
        if (!componentType->isScalar()) {
            error("vectors cannot have non-scalar component type", "VectorType::VectorType");
            return;
        }
        if (componentCount < 2 || componentCount > 4) {
            error("vectors can only have component count of 2, 3 or 4", "VectorType::VectorType");
            return;
        }

        if (target == Target::AIR)
            handle = llvm::VectorType::get(componentType->getHandle(), componentCount, false);
    }

    ~VectorType() = default;

    Type* copy() override {
        return new VectorType(*this);
    }

    bool equals(Type* other) override {
        if (!other->isVector())
            return false;
        VectorType* otherVector = static_cast<VectorType*>(other);

        return (componentCount == otherVector->getComponentCount() && componentType->equals(otherVector->getBaseType()));
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "vec" + std::to_string(componentCount) + componentType->getNameForRegister();
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

    std::string getTemplateName() const override {
        return "v" + std::to_string(componentCount) + componentType->getTemplateName();
    }

    std::string getCastOpName(Type* castFrom) override {
        if (castFrom->isVector()) {
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
            return componentType->getName() + std::to_string(componentCount);
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
            name += "vec" + std::to_string(componentCount);

            return name;
        default:
            return "unknown";
        }
    }

    std::string getDebugName() const override {
        return componentType->getDebugName() + std::to_string(componentCount);
    }

    //Getters
    inline uint32_t getComponentCount() const {
        return componentCount;
    }
};

class MatrixType : public Type {
private:
    VectorType* componentType;
    uint32_t columnCount;

public:
    MatrixType(Context& aContext, VectorType* aComponentType, uint32_t aColumnCount) : Type(aContext, TypeID::Matrix), componentType(aComponentType), columnCount(aColumnCount) {
        if (columnCount < 2 || columnCount > 4) {
            error("matrices can only have column count of 2, 3 or 4", "MatrixType::MatrixType");
            return;
        }

        if (target == Target::AIR)
            handle = llvm::ArrayType::get(componentType->getHandle(), columnCount);
    }

    ~MatrixType() = default;

    Type* copy() override {
        return new MatrixType(*this);
    }

    bool equals(Type* other) override {
        if (!other->isMatrix())
            return false;
        MatrixType* otherMatrix = static_cast<MatrixType*>(other);

        return (columnCount == otherMatrix->getColumnCount() && componentType->equals(otherMatrix->getBaseType()));
    }

    Value* getValue(IRBuilder* builder, bool decorate = false) override;

    std::string getNameForRegister() override {
        return "mat" + std::to_string(columnCount) + componentType->getNameForRegister();
    }

    uint32_t getBitCount(bool align = false) override {
        return componentType->getBitCount(align) * columnCount;
    }

    std::string getOpPrefix(bool signSensitive, bool needsOrd) override {
        return componentType->getOpPrefix(signSensitive, needsOrd);
    }

    //TODO: check if this is correct
    std::string getTemplateName() const override {
        return "m" + std::to_string(columnCount) + componentType->getTemplateName();
    }
    
    //TODO: implement this
    std::string getCastOpName(Type* castFrom) override {
        return "Unknown";
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
            return componentType->getBaseType()->getName() + std::to_string(columnCount) + "x" + std::to_string(componentType->getComponentCount());
        case Target::GLSL:
            name += "mat" + std::to_string(columnCount);
            if (columnCount != componentType->getComponentCount())
                name += "x" + std::to_string(componentType->getComponentCount());

            return name;
        default:
            return "unknown";
        }
    }

    std::string getDebugName() const override {
        return componentType->getBaseType()->getName() + std::to_string(columnCount) + "x" + std::to_string(componentType->getComponentCount());
    }

    //Getters
    inline uint32_t getColumnCount() const {
        return columnCount;
    }

    inline VectorType* getComponentType() const {
        return componentType;
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
        
        if (target == Target::AIR)
            handle = llvm::PointerType::get(*context.handle, 1u);
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

    //TODO: change this?
    std::string getTemplateName() const override {
        return "t" + std::to_string((int)viewType) + type->getTemplateName();
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

    std::string getDebugName() const override {
        //TODO: don't hardcode this
        std::string viewTypeStr = "texture2d";

        return viewTypeStr + "<" + type->getDebugName() + ">";
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
        
        if (target == Target::AIR)
            handle = llvm::PointerType::get(*context.handle, 2u);
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

    std::string getTemplateName() const override {
        return "sm";
    }

    std::string getNameBegin() const override {
        //TODO: add template addguments
        if (target == Target::HLSL)
            return "SamplerState";
        else
            return "sampler";
    }

    std::string getDebugName() const override {
        return "sampler";
    }
};

} //namespace irb

#endif
