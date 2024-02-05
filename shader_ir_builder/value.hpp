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

public:
    Type(Context& aContext, TypeID aTypeID = TypeID::None) : context(aContext), typeID(aTypeID) {}

    virtual ~Type() {}

    virtual Type* copy() = 0;
    
    Context& getContext() const {
        return context;
    }

    virtual bool equals(Type* other) {
        return false;
    }

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

    //TODO: move this to spirv backend
    virtual std::string getOpPrefix(bool signSensitive, bool needsOrd) {
        return "";
    }

    //TODO: move this to air backend
    virtual std::string getTemplateName() const = 0;

    //TODO: move this to spirv backend
    virtual std::string getCastOpName(Type* castFrom) {
        return "";
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

    //TODO: remove this?
    virtual bool getIsSigned() {
        return false;
    }

    TypeID getTypeID() {
        return typeID;
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
        if (name == "") {
            if (target == Target::SPIRV)
                name = std::to_string(context.crntRegisterNumber++);
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
    Type* elementType;
    StorageClass storageClass;

public:
    PointerType(Context& aContext, Type* aElementType, StorageClass aStorageClass, uint64_t addressSpace = 0) : Type(aContext, TypeID::Pointer), elementType(aElementType), storageClass(aStorageClass) {
        //TODO: set the adress space correctly
        if (target == Target::AIR)
            handle = llvm::PointerType::get(*context.handle, addressSpace);
    }

    ~PointerType() = default;

    Type* copy() override {
        return new PointerType(*this);
    }

    bool equals(Type* other) override {
        return (other->isPointer() && elementType->equals(other->getElementType()));
    }

    uint32_t getBitCount(bool align = false) override {
        return 64;
    }

    uint16_t pointerCount() override {
        return 1;
    }

    //TODO: override @ref getOpPrefix

    std::string getTemplateName() const override {
        return "p" + elementType->getTemplateName();
    }

    Type* getElementType() override {
        return elementType;
    }

    bool isOperatorFriendly() override {
        return true;
    }

    std::string getDebugName() const override {
        return elementType->getDebugName() + "*";
    }

    //Getters
    inline StorageClass getStorageClass() const {
        return storageClass;
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

    std::string getDebugName() const override {
        return arrayType->getDebugName() + "[" + std::to_string(size) + "]";
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

    uint32_t getBitCount(bool align = false) override {
        uint32_t bitCount = 0;
        for (auto& member : structure->members)
            bitCount += member.type->getBitCount(align);
        
        return bitCount;
    }

    std::string getTemplateName() const override {
        return "s" + name;
    }

    std::string getDebugName() const override {
        return "struct " + name;
    }

    inline Structure* getStructure() {
        return structure;
    }

    const std::string& getName() const {
        return name;
    }
};

class FunctionType : public Type {
private:
    Type* returnType;
    std::vector<Type*> arguments;

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

    std::string getTemplateName() const override {
        std::string templateName;
        for (const auto* arg : arguments)
            templateName += (target == Target::AIR ? "." : "_") + arg->getTemplateName();
        
        return templateName;
    }

    //TODO: implement this
    std::string getDebugName() const override {
        return "FUNCTION_TYPE";
    }

    //Getters
    inline Type* getReturnType() const {
        return returnType;
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
        return componentType;
    }

    bool isOperatorFriendly() override {
        return true;
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
        return componentType;
    }

    bool isOperatorFriendly() override {
        return true;
    }

    std::string getDebugName() const override {
        return componentType->getBaseType()->getDebugName() + std::to_string(columnCount) + "x" + std::to_string(componentType->getComponentCount());
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

    uint32_t getBitCount(bool align = false) override {
        return 64; //TODO: check if this is correct
    }

    std::string getTemplateName() const override {
        return "sm";
    }

    std::string getDebugName() const override {
        return "sampler";
    }
};

} //namespace irb

#endif
