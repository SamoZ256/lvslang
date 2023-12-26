#ifndef LVSLANG_PARSER_H
#define LVSLANG_PARSER_H

#include <limits>

#include "lexer.hpp"
#include "../shader_ir_builder/spirv/ir.hpp"
#include "../shader_ir_builder/air/ir.hpp"

//Forward declarations
class FunctionPrototypeAST;

static irb::GLSLVersion glslVersion = irb::GLSLVersion::_1_10;

irb::Context context;
irb::IRBuilder* builder;

static FunctionPrototypeAST* crntFunction = nullptr;
static uint32_t currentIndentation = 0;

struct EnumValue {
    std::string name;
    long value;
};

class Enumeration {
private:
    inline uint16_t getFirstGreaterOrEqualPow2(long value) {
        if (value == 0)
            return 0;
        long thePow = 1;
        for (uint16_t i = 0;; i++) {
            thePow *= 2;
            if (value < thePow)
                return i;
        }

        //Just in case
        throw std::runtime_error("getFirstGreaterOrEqualPow2");

        return 0;
    }

public:
    irb::ScalarType* type;
    std::vector<EnumValue> values;

    Enumeration(const std::vector<EnumValue>& aValues) : values(aValues) {
        if (values.size() == 0) {
            logError("cannot define an enum with 0 values");
            return;
        }
        long minValue = std::numeric_limits<long>::max(), maxValue = std::numeric_limits<long>::min();
        for (auto& value : values) {
            minValue = std::min(minValue, value.value);
            maxValue = std::max(maxValue, value.value);
        }
        minValue = std::min(minValue, (long)0);
        uint16_t numBits = std::max(getFirstGreaterOrEqualPow2(-minValue - 1), getFirstGreaterOrEqualPow2(maxValue));
        if (minValue != 0)
            numBits *= 2;
        //std::cout << "Num bits before: " << (int)numBits << std::endl;
        for (uint8_t possibleBits = 8; possibleBits <= 32; possibleBits *= 2) {
            if (numBits <= possibleBits) {
                numBits = possibleBits;
                break;
            }
        }
        //std::cout << "Num bits: " << (int)numBits << std::endl;

        type = new irb::ScalarType(context, irb::TypeID::Integer, numBits, (minValue != 0));
    }
};

//For swizzled vectors that weren't loaded on codegen
//TODO: enable the @ref checkIfNameAlreadyUsed argument?
class UnloadedSwizzledVectorValue : public irb::Value {
private:
    irb::Value* unloadedVector;
    std::vector<uint8_t> indices;

public:
    UnloadedSwizzledVectorValue(irb::Context& aContext, irb::Value* aUnloadedVector, const std::vector<uint8_t>& aIndices, const std::string& aName = "") : irb::Value(aContext, aUnloadedVector->getType(), aName), unloadedVector(aUnloadedVector), indices(aIndices) {}

    //Getters
    inline irb::Value* getUnloadedVector() const {
        return unloadedVector;
    }

    inline const std::vector<uint8_t>& getIndices() const {
        return indices;
    }
};

struct Variable {
    irb::Value* value;
    bool shouldBeLoaded;
};

static std::map<std::string, Variable> variables;
static std::map<std::string, FunctionPrototypeAST*> functionDeclarations;
static std::map<std::string, Enumeration*> enumerations;

//TODO: increase the bindings gradually
uint32_t getBufferBinding(uint32_t set, uint32_t binding) {
    return 0;
}

uint32_t getTextureBinding(uint32_t set, uint32_t binding) {
    return 0;
}

uint32_t getSamplerBinding(uint32_t set, uint32_t binding) {
    return 0;
}

class EnumType : public irb::Type {
private:
    Enumeration* enumeration;

public:
    EnumType(irb::Context& aContext, const std::string& aName) : Type(aContext) {
        enumeration = enumerations[aName];
        typeID = enumeration->type->getTypeID(); //HACK: set the typeID later
        //if (target != Target::GLSL)
        //    nameBegin = "struct ";
        if (irb::target == irb::Target::GLSL)
            nameBegin = enumeration->type->getNameBegin();
        else if (irb::target == irb::Target::Metal)
            nameBegin = aName;
        else if (irb::target == irb::Target::AIR)
            nameBegin = enumeration->type->getName();

        if (!enumeration) {
            logError("use of undeclared enum '" + aName + "'");
            return;
        }
    }

    ~EnumType() = default;

    irb::Type* copy() override {
        return new EnumType(*this);
    }

    bool equals(Type* other) override {
        EnumType* otherEnum = dynamic_cast<EnumType*>(other);
        if (!otherEnum)
            return false;

        return (otherEnum->getEnum() == enumeration);
    }

    irb::Value* getValue(irb::IRBuilder* builder, bool decorate = false) override {
        return enumeration->type->getValue(builder);
    }

    std::string getNameForRegister() override {
        return "enum_" + nameBegin;
    }

    uint32_t getBitCount(bool align = false) override {
        return enumeration->type->getBitCount();
    }

    irb::Type* getBaseType() override {
        return enumeration->type;
    }

    inline Enumeration* getEnum() {
        return enumeration;
    }
};

std::string getGLSLVersionString() {
    LVSLANG_CHECK_ARGUMENT(irb::GLSLVersion, glslVersion);
    std::string versionStr = irb::glslVersionMap.at(glslVersion);

    switch (glslVersion) {
    case irb::GLSLVersion::None:
        LVSLANG_ERROR_UNSUPPORTED_TARGET_VERSIONS("None", "GLSL");
        break;
    case irb::GLSLVersion::_1_10 ... irb::GLSLVersion::_1_50:
        LVSLANG_ERROR_UNSUPPORTED_TARGET_VERSIONS("1.10 to 1.50", "GLSL");
        break;
    default:
        break;
    }

    return versionStr;
}

inline void enableExtension(irb::Extension extension) {
    auto& ext = irb::extensions[(int)extension];
    if (!std::get<0>(ext)) {
        if (irb::target == irb::Target::GLSL)
            context.codeHeader += "\n\n#extension " + std::get<1>(ext) + " : enable";
        else if (irb::target == irb::Target::SPIRV)
            builder->opExtension(std::get<2>(ext));
        std::get<0>(ext) = true;
    }
}

int getIntTypeFromNumStr(char numTypeStr) {
    switch (numTypeStr) {
    //case 'd':
    //    return TOKEN_TYPE_FLOAT64;
    case 'f':
        return TOKEN_TYPE_FLOAT;
    case 'h':
        return TOKEN_TYPE_HALF;
    case 'i':
        return TOKEN_TYPE_INT;
    case 'u':
        return TOKEN_TYPE_UINT;
    default:
        return 0;
    }
}

irb::ScalarType* createScalarType(int intType) {
    if (!intType)
        intType = TOKEN_TYPE_FLOAT;
    
    irb::TypeID typeID;
    uint32_t bitCount = 0;
    bool isSigned = true;
    switch(intType) {
    case TOKEN_TYPE_VOID:
        typeID = irb::TypeID::Void;
        break;
    case TOKEN_TYPE_BOOL:
        typeID = irb::TypeID::Bool;
        bitCount = 8;
        isSigned = false;
        break;
    case TOKEN_TYPE_CHAR:
        typeID = irb::TypeID::Integer;
        bitCount = 8;
        break;
    case TOKEN_TYPE_SHORT:
        typeID = irb::TypeID::Integer;
        bitCount = 16;
        break;
    case TOKEN_TYPE_INT:
        typeID = irb::TypeID::Integer;
        bitCount = 32;
        break;
    case TOKEN_TYPE_UCHAR:
        typeID = irb::TypeID::Integer;
        bitCount = 8;
        isSigned = false;
        break;
    case TOKEN_TYPE_USHORT:
        typeID = irb::TypeID::Integer;
        bitCount = 16;
        isSigned = false;
        break;
    case TOKEN_TYPE_UINT:
        typeID = irb::TypeID::Integer;
        bitCount = 32;
        isSigned = false;
        break;
    case TOKEN_TYPE_HALF:
        typeID = irb::TypeID::Float;
        bitCount = 16;
        break;
    case TOKEN_TYPE_FLOAT:
        typeID = irb::TypeID::Float;
        bitCount = 32;
        break;
    }

    return new irb::ScalarType(context, typeID, bitCount, isSigned);
}

irb::Attribute getAttributeFromToken(int attrib) {
    switch (attrib) {
    case TOKEN_ATTRIB_CONSTANT:
        return {irb::Attribute::Enum::AddressSpace, {2}};
    case TOKEN_ATTRIB_DEVICE:
        return {irb::Attribute::Enum::AddressSpace, {1}};
    case TOKEN_ATTRIB_BUFFER:
        return {irb::Attribute::Enum::Buffer};
    case TOKEN_ATTRIB_DESCRIPTOR_SET:
        return {irb::Attribute::Enum::DescriptorSet};
    case TOKEN_ATTRIB_POSITION:
        return {irb::Attribute::Enum::Position};
    case TOKEN_ATTRIB_INPUT:
        return {irb::Attribute::Enum::Input};
    case TOKEN_ATTRIB_LOCATION:
        return {irb::Attribute::Enum::Location};
    default:
        return {irb::Attribute::Enum::MaxEnum};
    }
}

bool typeIsPromoted(irb::TypeID a, irb::TypeID b) {
    static irb::TypeID typesSortedByPromotion[] = {
        irb::TypeID::Vector,
        irb::TypeID::Float,
        irb::TypeID::Pointer,
        irb::TypeID::Integer,
        irb::TypeID::Bool
    };
    uint8_t aIndex = 255, bIndex = 255;
    for (uint8_t i = 0; i < sizeof(typesSortedByPromotion) / sizeof(irb::TypeID); i++) {
        if (a == typesSortedByPromotion[i])
            return true;
        if (b == typesSortedByPromotion[i])
            return false;
    }

    throw std::runtime_error("Ooops, some weird type got in here");

    return false;
}

irb::Type* getPromotedType(irb::Type* a, irb::Type* b) {
    return (typeIsPromoted(a->getTypeID(), b->getTypeID()) ? a : b);
}

//Helper structures
class ExpressionAST;
class BlockExpressionAST;

struct IfThenBlock {
    ExpressionAST* condition;
    BlockExpressionAST* block;
};

//Base class
class ExpressionAST {
protected:
    uint32_t debugLine;
    uint32_t debugChar;

    bool loadOnCodegen = true;

public:
    ExpressionAST() {
        debugLine = crntLine;
        debugChar = crntChar;
    }

    virtual ~ExpressionAST() = default;

    virtual irb::Value* codegen(irb::Type* requiredType = nullptr) = 0;

    virtual bool isConstant() {
        return false;
    }

    virtual bool isVariable() {
        return false;
    }
    
    virtual void setLoadOnCodegen(bool aLoadOnCodegen) {
        loadOnCodegen = aLoadOnCodegen;
    }

    //Debugging
    inline void setDebugInfo() {
        crntDebugLine = debugLine;
        crntDebugChar = debugChar;
    }
};

//Number
class NumberExpressionAST : public ExpressionAST {
private:
    double _valueD;
    long _valueL;
    unsigned long _valueU;

    irb::Type* type;

public:
    NumberExpressionAST(double aValueD, long aValueL, unsigned long aValueU, irb::ScalarType* aType) : _valueD(aValueD), _valueL(aValueL), _valueU(aValueU), type(aType) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        if (requiredType) {
            if (requiredType->isScalar()) {
                type = requiredType;
            } else if (requiredType->isVector()) {
                type = requiredType->getBaseType();
            } else {
                logError("cannot cast constant expression of type constant number to '" + requiredType->getName() + "'");
                return nullptr;
            }
        }

        irb::Value* value;
        switch (type->getTypeID()) {
        //case TOKEN_TYPE_FLOAT64:
        //default:
        //    return GET_CONSTANT_NUMBER_CODE(std::to_string(_valueD));
        case irb::TypeID::Float:
            value = new irb::ConstantFloat(context, _valueD, type->getBitCount());
            break;
        //case TOKEN_TYPE_INT64:
        case irb::TypeID::Integer:
            if (type->getIsSigned())
                value = new irb::ConstantInt(context, _valueL, type->getBitCount(), true);
            else
                value = new irb::ConstantInt(context, _valueU, type->getBitCount(), false);
            break;
        default:
            throw std::runtime_error("Constant value is neither int nor float");
            break;
        }
        
        if (TARGET_IS_IR(irb::target)) {
            //TODO: find out why I do this
            if (!context.pushedRegisterName())
                context.pushRegisterName("const");
            value = builder->opConstant(static_cast<irb::ConstantValue*>(value));
        }

        return value;
    }

    bool isConstant() override {
        return true;
    }

    //Getters
    double valueD() {
        return _valueD;
    }

    long valueL() {
        return _valueL;
    }

    unsigned long valueU() {
        return _valueU;
    }
};

//Variable
class VariableExpressionAST : public ExpressionAST {
private:
    std::string _name;
    irb::Type* type;

public:
    VariableExpressionAST(const std::string& aName) : _name(aName) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        auto iter = variables.find(_name);
        if (iter != variables.end()) {
            irb::Value* value = iter->second.value;
            if (loadOnCodegen) {
                if (TARGET_IS_IR(irb::target)) {
                    if (!iter->second.shouldBeLoaded)
                        value = builder->opLoad(value);
                } else {
                    irb::Type* type = value->getType()->getElementType();
                    //TODO: check if type is castable as well
                    bool needsCast = (requiredType && !requiredType->equals(type));
                    std::string castBegin = (needsCast ? requiredType->getName() + "(" : "");
                    std::string castEnd = (needsCast ? ")" : "");
                    value = new irb::Value(context, type, castBegin + value->getRawName() + castEnd);
                }
            }
            if (TARGET_IS_IR(irb::target) && requiredType)
                value = builder->opCast(value, requiredType);

            return value;
        } else {
            logError(("Use of undeclared variable '" + _name + "'").c_str());

            return nullptr;
        }
        
    }

    bool isVariable() override {
        return false;
    }

    std::string& name() { return _name; }
};

//Binary operators
class BinaryExpressionAST : public ExpressionAST {
private:
    std::string op;
    ExpressionAST* lhs;
    ExpressionAST* rhs;

public:
    BinaryExpressionAST(const std::string& aOperator, ExpressionAST* aLHS, ExpressionAST* aRHS) : op(aOperator), lhs(aLHS), rhs(aRHS) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();
        
        if (op == "=")
            lhs->setLoadOnCodegen(false);
        
        irb::Value* l = lhs->codegen();
        irb::Value* r = rhs->codegen((op == "=" ? l->getType()->getElementType() : l->getType()));
        if (!l || !r)
            return nullptr;

        if (op == "=") {
            if (TARGET_IS_IR(irb::target)) {
                if (auto* unloadedVector = dynamic_cast<UnloadedSwizzledVectorValue*>(l)) {
                    irb::Value* loadedVector = builder->opLoad(unloadedVector->getUnloadedVector());
                    if (r->getType()->isScalar()) {
                        for (auto index : unloadedVector->getIndices())
                            builder->opVectorInsert(loadedVector, r, new irb::ConstantInt(context, index, 32, true)); //TODO: should it be signed?
                    } else if (r->getType()->isVector()) {
                        //TODO: check if component count matches and if we are not accessing out of bounds
                        for (uint8_t i = 0; i < unloadedVector->getIndices().size(); i++)
                            loadedVector = builder->opVectorInsert(loadedVector, builder->opVectorExtract(r, new irb::ConstantInt(context, i, 32, true)), new irb::ConstantInt(context, unloadedVector->getIndices()[i], 32, true));
                    } else {
                        logError("cannot assign to vector from type other than scalar and vector");
                        return nullptr;
                    }
                    builder->opStore(unloadedVector->getUnloadedVector(), loadedVector);
                } else {
                    builder->opStore(l, r);
                }
            }

            return new irb::Value(context, r->getType(), l->getRawName() + " = " + r->getRawName());
        }
        
        if (!l->getType()->isOperatorFriendly()) {
            logError("Left-hand operand is not operator friendly");
            return nullptr;
        }
        if (!r->getType()->isOperatorFriendly()) {
            logError("Right-hand operand is not operator friendly");
            return nullptr;
        }

        irb::Type* type = getPromotedType(l->getType(), r->getType());
        if (TARGET_IS_IR(irb::target)) {
            l = builder->opCast(l, type);
            r = builder->opCast(r, type);
        }

        irb::Operation operation;
        if (op == "+") {
            operation = irb::Operation::Add;
        } else if (op == "-") {
            operation = irb::Operation::Subtract;
        } else if (op == "*") {
            operation = irb::Operation::Multiply;
        } else if (op == "/") {
            operation = irb::Operation::Divide;
        } else if (op == "&") {
            operation = irb::Operation::BitwiseAnd;
        } else if (op == "|") {
            operation = irb::Operation::BitwiseOr;
        } else if (op == "==") {
            operation = irb::Operation::LogicalEqual;
        } else if (op == "!=") {
            operation = irb::Operation::LogicalNotEqual;
        } else if (op == "&&") {
            operation = irb::Operation::LogicalAnd;
            type = createScalarType(TOKEN_TYPE_BOOL);
        } else if (op == "||") {
            operation = irb::Operation::LogicalOr;
            type = createScalarType(TOKEN_TYPE_BOOL);
        } else if (op == ">") {
            operation = irb::Operation::GreaterThan;
            type = createScalarType(TOKEN_TYPE_BOOL);
        } else if (op == "<") {
            operation = irb::Operation::LessThan;
            type = createScalarType(TOKEN_TYPE_BOOL);
        } else if (op == ">=") {
            operation = irb::Operation::GreaterThanEqual;
            type = createScalarType(TOKEN_TYPE_BOOL);
        } else if (op == "<=") {
            operation = irb::Operation::LessThanEqual;
            type = createScalarType(TOKEN_TYPE_BOOL);
        }

        if (TARGET_IS_CODE(irb::target)) {
            context.pushRegisterName("bin");
            return new irb::Value(context, type, "(" + l->getRawName() + " " + op + " " + r->getRawName() + ")");
        } else {
            irb::Value* value = builder->opOperation(l, r, type, operation);
            if (requiredType)
                value = builder->opCast(value, requiredType);

            return value;
        }
    }
};

//Block
class BlockExpressionAST : public ExpressionAST {
private:
    std::vector<ExpressionAST*> expressions;

public:
    BlockExpressionAST(std::vector<ExpressionAST*> aExpressions) : expressions(aExpressions) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        //for (uint16_t i = 0; i < currentIndentation; i++)
        //    codeStr += "\t";
        std::string codeStr = "{\n";

        currentIndentation += 1;

        for (auto expr : expressions) {
            irb::Value* value = expr->codegen();
            if (!value)
                return nullptr;
            if (TARGET_IS_CODE(irb::target)) {
                for (uint16_t i = 0; i < currentIndentation; i++)
                    codeStr += "\t";
                codeStr += value->getRawName() + ";\n";
            }
        }

        currentIndentation -= 1;

        for (uint16_t i = 0; i < currentIndentation; i++)
            codeStr += "\t";
        codeStr += "}";
        
        return new irb::Value(context, nullptr, codeStr);
    }
};

struct Argument {
    std::string name;
    irb::Type* type;
    irb::Attributes attributes;
};

//TODO: rename?
enum class FunctionRole {
    Normal,
    Vertex,
    Fragment,
    Kernel,

    MaxEnum
};

//Function declaration
class FunctionPrototypeAST : public ExpressionAST {
private:
    std::string _name;
    irb::Type* type;
    irb::Type* returnType; //Different than type in case of GLSL and SPIR
    std::vector<Argument> _arguments;
    //std::vector<int> attributes;
    bool isDefined;
    FunctionRole functionRole;
    bool isSTDFunction;

    irb::Value* value;
    irb::FunctionType* functionType;

    //Output for SPIRV
    irb::Value* returnVariable = nullptr;
    irb::Value* positionVariable = nullptr;

public:
    FunctionPrototypeAST(const std::string& aName, irb::Type* aType, std::vector<Argument> aArguments/*, const std::vector<int>& aAttributes*/, bool aIsDefined, FunctionRole aFunctionRole, bool aIsSTDFunction = false) : _name(aName), type(aType), _arguments(aArguments)/*, attributes(aAttributes)*/, isDefined(aIsDefined), functionRole(aFunctionRole), isSTDFunction(aIsSTDFunction) {
        std::vector<irb::Type*> argumentTypes;
        if (functionRole == FunctionRole::Normal) {
            argumentTypes.resize((_arguments.size()));
            for (uint32_t i = 0; i < argumentTypes.size(); i++)
                argumentTypes[i] = new irb::PointerType(context, _arguments[i].type, irb::StorageClass::Function);
        }
        returnType = type;
        if (functionRole != FunctionRole::Normal && (irb::target == irb::Target::GLSL || irb::target == irb::Target::SPIRV))
            returnType = new irb::ScalarType(context, irb::TypeID::Void, 0, false);
        functionType = new irb::FunctionType(context, returnType, argumentTypes);
    }

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        functionDeclarations[_name] = this;

        if (irb::target == irb::Target::SPIRV && functionRole != FunctionRole::Normal && type->getTypeID() != irb::TypeID::Void) {
            builder->opDecorate(type->getValue(builder, true), irb::Decoration::Block);
            context.pushRegisterName(_name + "_output");
            returnVariable = builder->opVariable(new irb::PointerType(context, type, irb::StorageClass::Output));
            if (functionRole == FunctionRole::Vertex) {
                builder->opDecorate(returnVariable, irb::Decoration::Location, {"0"});
            
                context.pushRegisterName("position");
                positionVariable = builder->opVariable(new irb::PointerType(context, new irb::VectorType(context, new irb::ScalarType(context, irb::TypeID::Float, 32, true), 4), irb::StorageClass::Output));
                builder->opDecorate(positionVariable, irb::Decoration::Position);
            }
        }

        for (uint32_t i = 0; i < _arguments.size(); i++) {
            Argument& arg = _arguments[i];
            auto& attr = arg.attributes;
            if (attr.addressSpace != 0) {
                irb::PointerType* pointerType = dynamic_cast<irb::PointerType*>(arg.type);
                if (!pointerType) {
                    logError("only pointers can be used with an address space");
                    return nullptr;
                }
                pointerType->setAddressSpace(attr.addressSpace);
            }
            if (arg.type->isTexture())
                attr.isTexture = true;
            else if (arg.type->isSampler())
                attr.isSampler = true;
        }

        if (TARGET_IS_CODE(irb::target)) {
            std::string codeStr;
            std::string argsStr;
            for (uint32_t i = 0; i < _arguments.size(); i++) {
                Argument& arg = _arguments[i];
                auto& attr = arg.attributes;
                if (irb::target == irb::Target::GLSL) {
                    if (functionRole != FunctionRole::Normal) {
                        std::string typeName;
                        if (attr.isInput) {
                            switch (functionRole) {
                            case FunctionRole::Vertex:
                                //TODO: do this error check for every backend?
                                if (!arg.type->isStructure()) {
                                    logError("Entry point argument declared with the 'input' attribute must have a structure type");
                                    return nullptr;
                                }
                                for (const auto& member : static_cast<irb::StructureType*>(arg.type)->getStructure()->members)
                                    codeStr += "layout (location = " + std::to_string(member.attributes.locationIndex) + ") in " + member.type->getName() + " " + member.name + ";\n\n";
                                break;
                            case FunctionRole::Fragment:
                                codeStr += "layout (location = 0) in " + arg.type->getName() + "_Input {\n\t" + arg.type->getName() + " " + arg.name + ";\n};\n\n";
                                break;
                            default:
                                logError("cannot use the 'input' attribute for kernel function");
                                return nullptr;
                            }
                        } else {
                            if (attr.isBuffer) {
                                if (attr.addressSpace == 2)
                                    typeName = "uniform ";
                                else
                                    typeName = "readonly buffer "; //TODO: support other types of buffer as well
                                //We need to get element type, since GLSL treats it without pointer
                                typeName += arg.type->getElementType()->getName() + "_Uniform {\n\t" + arg.type->getElementType()->getName() + " " + arg.name + ";\n}";
                            } else {
                                typeName = "uniform " + arg.type->getName();
                            }
                            codeStr += "layout (set = " + std::to_string(attr.set) + ", binding = " + std::to_string(attr.binding) + ") " + typeName + " " + arg.name + ";\n\n";
                        }
                    } else {
                        if (i != 0)
                            argsStr += ", ";
                        argsStr += arg.type->getName() + " " + arg.name;
                    }
                } else {
                    if (i != 0)
                        argsStr += ", ";

                    std::string addressSpace;
                    if (attr.addressSpace == 2)
                        addressSpace = "constant ";
                    else if (attr.addressSpace == 1)
                        addressSpace = "device ";
                    
                    std::string attribute;
                    if (attr.isBuffer)
                        attribute = " [[buffer(" + std::to_string(getBufferBinding(attr.set, attr.binding)) + ")]]";
                    if (attr.isTexture)
                        attribute = " [[texture(" + std::to_string(getTextureBinding(attr.set, attr.binding)) + ")]]";
                    if (attr.isSampler)
                        attribute = " [[sampler(" + std::to_string(getSamplerBinding(attr.set, attr.binding)) + ")]]";
                    if (attr.isInput)
                        attribute = " [[stage_in]]";

                    argsStr += addressSpace + arg.type->getName() + " " + arg.name + attribute;
                }
            }

            if (functionRole != FunctionRole::Normal) {
                if (irb::target == irb::Target::Metal) {
                    switch (functionRole) {
                    case FunctionRole::Vertex:
                        codeStr = "vertex ";
                        break;
                    case FunctionRole::Fragment:
                        codeStr = "fragment ";
                        break;
                    case FunctionRole::Kernel:
                        codeStr = "kernel ";
                        break;
                    default:
                        break;
                    }
                } else if (irb::target == irb::Target::GLSL) {
                    _name = "main";

                    /*
                    //TODO: do this error check for every backend?
                    if (!type->isStructure()) {
                        logError("Entry point argument declared with the 'input' attribute must have a structure type");
                        return nullptr;
                    }
                    irb::StructureType* structureType = static_cast<irb::StructureType*>(type);
                    uint32_t index = 0;
                    for (const auto& member : structureType->getStructure()->members) {
                        if (!member.attributes.isPosition)
                            codeStr += "layout (location = " + std::to_string(index++) + ") out " + member.type->getName() + " " + member.name + ";\n\n";
                    }
                    */
                    switch (functionRole) {
                    case FunctionRole::Vertex:
                        codeStr += "layout (location = 0) out " + type->getName() + "_Output {\n\t" + type->getName() + " _output;\n} _output;\n\n";
                        break;
                    case FunctionRole::Fragment:
                        //TODO: do this error check for every backend?
                        if (!type->isStructure()) {
                            logError("Entry point argument declared with the 'input' attribute must have a structure type");
                            return nullptr;
                        }
                        for (const auto& member : static_cast<irb::StructureType*>(type)->getStructure()->members)
                            codeStr += "layout (location = " + std::string("0") + ") out " + member.type->getName() + " " + member.name + ";\n\n"; //TODO: use the color index std::to_string(member.attributes.colorIndex)
                        break;
                    default:
                        logError("cannot use the 'output' attribute for kernel function");
                        return nullptr;
                    }
                }
            }
            codeStr += returnType->getName() + " " + _name + "(" + argsStr + ")";
            if (!isDefined)
                codeStr += ";";
            
            return new irb::Value(context, type, codeStr);
        } else {
            if (isSTDFunction) {
                std::string regName = _name;
                regName[0] = toupper(regName[0]);
                regName = "import " + regName;
                value = new irb::Value(context, nullptr, regName);
            } else {
                context.pushRegisterName(_name);
                value = builder->opRegisterFunction(functionType);
                builder->opName(value, _name + "(");
            }

            return new irb::Value(context, functionType);
        }
    }

    //Getters
    inline const std::string& name() const {
        return _name;
    }

    inline const std::vector<Argument>& arguments() const {
        return _arguments;
    }

    inline irb::Attributes& getArgumentAttributes(uint32_t index) {
        return _arguments[index].attributes;
    }

    inline irb::Type* getType() const {
        return type;
    }

    inline FunctionRole getFunctionRole() const {
        return functionRole;
    }

    inline bool getIsSTDFunction() const {
        return isSTDFunction;
    }

    inline irb::Value* getValue() const {
        return value;
    }

    inline irb::FunctionType* getFunctionType() const {
        return functionType;
    }

    inline irb::Value* getReturnVariable() const {
        return returnVariable;
    }

    inline irb::Value* getPositionVariable() const {
        return positionVariable;
    }
};

//Function definition
class FunctionDefinitionAST : public ExpressionAST {
private:
    FunctionPrototypeAST* declaration;
    BlockExpressionAST* body;

public:
    FunctionDefinitionAST(FunctionPrototypeAST* aDeclaration, BlockExpressionAST* aBody) : declaration(aDeclaration), body(aBody) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        crntFunction = declaration;

        irb::Value* declV = declaration->codegen();
        if (!declV)
            return nullptr;
        
        //TODO: check for this
        if (false) {
            logError(("Redefinition of function '" + declaration->name() + "'").c_str());

            return nullptr;
        }
        
        irb::Value* value = nullptr;
        if (TARGET_IS_IR(irb::target)) {
            irb::FunctionType* functionType = static_cast<irb::FunctionType*>(declV->getType());
            context.pushRegisterName(declaration->name());
            value = builder->opFunction(functionType, declaration->getValue());
            if (declaration->getFunctionRole() != FunctionRole::Normal) {
                std::string stageName;
                switch (declaration->getFunctionRole()) {
                case FunctionRole::Vertex:
                    stageName = "Vertex";
                    break;
                case FunctionRole::Fragment:
                    stageName = "Fragment";
                    break;
                case FunctionRole::Kernel:
                    stageName = "Kernel";
                    break;
                default:
                    break;
                }
                builder->opEntryPoint(value, stageName, declaration->name());
                if (irb::target == irb::Target::SPIRV && declaration->getType()->getTypeID() != irb::TypeID::Void) {
                    dynamic_cast<irb::SPIRVBuilder*>(builder)->addInterfaceVariable(declaration->getReturnVariable()); //TODO: change this to static cast?
                    if (declaration->getFunctionRole() == FunctionRole::Vertex)
                        dynamic_cast<irb::SPIRVBuilder*>(builder)->addInterfaceVariable(declaration->getPositionVariable());
                }
                if (declaration->getFunctionRole() == FunctionRole::Fragment)
                    builder->opExecutionMode(value);
            }
        }

        std::string functionHeader;
        for (uint32_t i = 0; i < declaration->arguments().size(); i++) {
            auto& arg = declaration->arguments()[i];
            if (TARGET_IS_CODE(irb::target)) {
                irb::Value* value = new irb::Value(context, new irb::PointerType(context, arg.type, irb::StorageClass::Function), arg.name);
                variables[arg.name] = {value, false};
                if (irb::target == irb::Target::GLSL && declaration->getFunctionRole() == FunctionRole::Vertex && arg.attributes.isInput) {
                    //TODO: throw an error if not structure?
                    irb::StructureType* structureType = dynamic_cast<irb::StructureType*>(arg.type);
                    //HACK: just assemble the input structure
                    functionHeader += "\t" + structureType->getName() + " " + arg.name + ";\n";
                    for (const auto& member : structureType->getStructure()->members)
                        functionHeader += "\t" + arg.name + "." + member.name + " = " + member.name + ";\n";
                }
            } else {
                context.pushRegisterName(arg.name);
                if (irb::target == irb::Target::SPIRV && declaration->getFunctionRole() != FunctionRole::Normal) {
                    irb::Type* type = arg.type;
                    auto& attr = declaration->getArgumentAttributes(i);
                    irb::StorageClass storageClass = irb::StorageClass::MaxEnum;
                    //HACK: when the type is buffer, get the element type
                    if (attr.isBuffer)
                        type = type->getElementType();
                    //TODO: do not hardcode the storage classes
                    if (attr.isBuffer)
                        storageClass = irb::StorageClass::Uniform;
                    else if (attr.isTexture)
                        storageClass = irb::StorageClass::UniformConstant;
                    else if (attr.isSampler)
                        storageClass = irb::StorageClass::UniformConstant;
                    else if (attr.isInput)
                        storageClass = irb::StorageClass::Input;
                    irb::Value* value = builder->opVariable(new irb::PointerType(context, type, storageClass));
                    //TODO: check if these decorations are correct
                    //TODO: support other storage classes as well
                    irb::Structure* structure;
                    switch (storageClass) {
                    case irb::StorageClass::Uniform:
                    case irb::StorageClass::UniformConstant:
                        builder->opDecorate(value, irb::Decoration::DescriptorSet, {std::to_string(attr.set)});
                        builder->opDecorate(value, irb::Decoration::Binding, {std::to_string(attr.binding)});
                        break;
                    case irb::StorageClass::Input:
                        switch (declaration->getFunctionRole()) {
                        case FunctionRole::Vertex:
                            //TODO: do this error check for every backend?
                            if (!type->isStructure()) {
                                logError("Entry point argument declared with the 'input' attribute must have a structure type");
                                return nullptr;
                            }
                            structure = static_cast<irb::StructureType*>(type)->getStructure();
                            for (uint32_t i = 0; i < structure->members.size(); i++)
                                builder->opMemberDecorate(type->getValue(builder), i, irb::Decoration::Location, {std::to_string(structure->members[i].attributes.locationIndex)});
                            break;
                        case FunctionRole::Fragment:
                            builder->opDecorate(value, irb::Decoration::Location, {"0"});
                            break;
                        default:
                            logError("kernel functions cannot have 'input' attribute");
                            return nullptr;
                        }
                        break;
                    default:
                        break;
                    }
                    if (irb::target == irb::Target::SPIRV && attr.isBuffer || (declaration->getFunctionRole() == FunctionRole::Vertex && attr.isInput))
                        builder->opDecorate(type->getValue(builder, true), irb::Decoration::Block);
                    static_cast<irb::SPIRVBuilder*>(builder)->addInterfaceVariable(value);

                    variables[arg.name] = {value, false};
                } else {
                    irb::Value* argValue = builder->opFunctionParameter(arg.type);
                    variables[arg.name] = {argValue, false};
                    if (irb::target == irb::Target::AIR) {
                        //TODO: decorate the argument
                    }
                }
            }
        }

        if (TARGET_IS_IR(irb::target)) {
            irb::Block* block = builder->opBlock();
            builder->setInsertBlock(block);
        }
        
        irb::Value* bodyV = body->codegen();
        if (!bodyV)
            return nullptr;
        
        if (TARGET_IS_CODE(irb::target)) {
            std::string bodyStr = bodyV->getRawName();
            bodyStr = bodyStr.substr(0, 2) + functionHeader + bodyStr.substr(2);
            std::string codeStr = declV->getRawName() + " " + bodyStr;

            value = new irb::Value(context, nullptr, codeStr);
        } else {
            if (!builder->getInsertBlock()->hasReturned()) {
                if (declaration->getFunctionType()->getReturnType()->getTypeID() == irb::TypeID::Void)
                    builder->opReturn();
                else
                    builder->opUnreachable();
            }
            builder->opFunctionEnd();
        }

        return value;
    }
};

//Function call
class CallExpressionAST : public ExpressionAST {
private:
    std::string callee;
    std::vector<ExpressionAST*> arguments;

    FunctionPrototypeAST* declaration;

public:
    CallExpressionAST(const std::string& aCallee, std::vector<ExpressionAST*> aArguments) : callee(aCallee), arguments(aArguments) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        declaration = functionDeclarations[callee];
        if (!declaration) {
            logError(("Use of undeclared function '" + callee + "'").c_str());

            return nullptr;
        }

        if (declaration->arguments().size() != arguments.size()) {
            logError(("Expected " + std::to_string(declaration->arguments().size()) + " arguments, got " + std::to_string(arguments.size()) + " instead").c_str());

            return nullptr;
        }

        std::string argsStr;
        std::vector<irb::Value*> argVs(arguments.size());
        for (uint32_t i = 0; i < arguments.size(); i++) {
            ExpressionAST* arg = arguments[i];
            argVs[i] = arg->codegen(declaration->arguments()[i].type);
            if (TARGET_IS_IR(irb::target) && !arg->isVariable() && !declaration->getIsSTDFunction()) {
                irb::Value* paramV = argVs[i];
                context.pushRegisterName("param");
                argVs[i] = builder->opVariable(new irb::PointerType(context, paramV->getType(), irb::StorageClass::Function));
                builder->opStore(argVs[i], paramV);
            }
            if (i != 0)
                argsStr += ", ";
            argsStr += argVs[i]->getRawName();
        }

        if (TARGET_IS_CODE(irb::target)) {
            std::string code;
            if (declaration->getIsSTDFunction()) {
                switch (irb::target) {
                case irb::Target::Metal:
                    if (callee == "sample")
                        code = argVs[0]->getRawName() + ".sample(" + argVs[1]->getRawName() + ", " + argVs[2]->getRawName() + ")";
                    else if (callee == "sin")
                        code = "sin(" + argVs[0]->getRawName() + ")";
                    break;
                case irb::Target::GLSL:
                    if (callee == "sample")
                        code = "texture(sampler2D(" + argVs[0]->getRawName() + ", " + argVs[1]->getRawName() + "), " + argVs[2]->getRawName() + ")";
                    else if (callee == "sin")
                        code = "sin(" + argVs[0]->getRawName() + ")";
                    break;
                default:
                    break;
                }
            } else {
                code = callee + "(" + argsStr + ")";
            }
            return new irb::Value(context, declaration->getType(), code);
        } else {
            if (declaration->getIsSTDFunction()) {
                std::string name = declaration->name();
                if (name == "sample")
                    return builder->opSample(argVs[0], argVs[1], argVs[2]);
                else
                    return builder->opSTDFunctionCall_EXT(name, declaration->getFunctionType(), argVs);
            } else {
                return builder->opFunctionCall(declaration->getValue(), argVs);
            }
        }
    }
};

//Return
//TODO: enable return without value
class ReturnExpressionAST : public ExpressionAST {
private:
    ExpressionAST* expression;

public:
    ReturnExpressionAST(ExpressionAST* aExpression) : expression(aExpression) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        irb::Type* funcReturnType = crntFunction->getFunctionType()->getReturnType();
        //HACK: only load it later
        if (TARGET_IS_IR(irb::target))
            expression->setLoadOnCodegen(false);
        irb::Value* unloadedReturnV = expression->codegen(funcReturnType->getTypeID() == irb::TypeID::Void ? nullptr : funcReturnType);
        irb::Value* returnV;
        if (TARGET_IS_IR(irb::target))
            returnV = builder->opLoad(unloadedReturnV);
        else
            returnV = unloadedReturnV;
        if (!returnV)
            return nullptr;

        if (TARGET_IS_CODE(irb::target)) {
            if (irb::target == irb::Target::GLSL && crntFunction->getFunctionRole() != FunctionRole::Normal) {
                irb::Type* type = returnV->getType();
                //TODO: support other types besides structure
                if (!type->isStructure()) {
                    logError("Only structures can be returned from an entry point function");
                    return nullptr;
                }
                irb::StructureType* structType = static_cast<irb::StructureType*>(type);
                irb::Structure* structure = structType->getStructure();

                std::string code = "\n\t//Return\n\t";
                for (uint32_t i = 0; i < structure->members.size(); i++) {
                    const irb::StructureMember& member = structure->members[i];
                    std::string memberStr = returnV->getRawName() + "." + member.name;
                    if (member.attributes.isPosition) {
                        code += "gl_Position = " + memberStr;
                    } else {
                        switch (crntFunction->getFunctionRole()) {
                        case FunctionRole::Vertex:
                            code += "_output._output." + member.name + " = " + memberStr;
                            break;
                        case FunctionRole::Fragment:
                            code += member.name + " = " + memberStr;
                            break;
                        default:
                            logError("kernel function cannot return a value");
                            return nullptr;
                        }
                    }
                    if (i != structure->members.size() - 1)
                        code += ";\n\t";
                }

                return new irb::Value(context, nullptr, code);
            } else {
                return new irb::Value(context, returnV->getType(), "return " + returnV->getRawName());
            }
        } else {
            if (irb::target == irb::Target::SPIRV && crntFunction->getFunctionRole() != FunctionRole::Normal) {
                if (crntFunction->getFunctionRole() == FunctionRole::Vertex) {
                    //TODO: do this error check for every backend?
                    if (!crntFunction->getType()->isStructure()) {
                        logError("Entry point argument declared with the 'output' attribute must have a structure type");
                        return nullptr;
                    }
                    irb::Structure* structure = static_cast<irb::StructureType*>(crntFunction->getType())->getStructure();
                    irb::Value* positionV = nullptr;
                    for (uint32_t i = 0; i < structure->members.size(); i++) {
                        if (structure->members[i].attributes.isPosition) {
                            irb::Value* indexV = builder->opConstant(new irb::ConstantInt(context, i, 32, true));
                            positionV = builder->opGetElementPtr(new irb::PointerType(context, structure->members[i].type, irb::StorageClass::Function), unloadedReturnV, {indexV});
                            positionV = builder->opLoad(positionV);
                            break;
                        }
                    }
                    if (positionV)
                        builder->opStore(crntFunction->getPositionVariable(), positionV);
                } else if (crntFunction->getFunctionRole() == FunctionRole::Fragment) {
                    //TODO: do this error check for every backend?
                    if (!crntFunction->getType()->isStructure()) {
                        logError("Entry point argument declared with the 'output' attribute must have a structure type");
                        return nullptr;
                    }
                    irb::Structure* structure = static_cast<irb::StructureType*>(crntFunction->getType())->getStructure();
                    for (uint32_t i = 0; i < structure->members.size(); i++)
                        builder->opMemberDecorate(crntFunction->getType()->getValue(builder), i, irb::Decoration::Location, {"0"}); //TODO: use the color index
                }
                builder->opStore(crntFunction->getReturnVariable(), returnV);
                builder->opReturn();
            } else {
                returnV = builder->opCast(returnV, funcReturnType);
                builder->opReturn(returnV);
            }

            return returnV;
        }
    }
};

//If
class IfExpressionAST : public ExpressionAST {
private:
    std::vector<IfThenBlock*> ifThenBlocks;
    BlockExpressionAST* elseBlock;

public:
    IfExpressionAST(const std::vector<IfThenBlock*>& aIfThenBlocks, BlockExpressionAST* aElseBlock) : ifThenBlocks(aIfThenBlocks), elseBlock(aElseBlock) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        if (TARGET_IS_CODE(irb::target)) {
            std::string codeStr;
            for (uint32_t i = 0; i < ifThenBlocks.size(); i++) {
                if (i != 0)
                    codeStr += " else ";
                codeStr += "if (";
                irb::Value* condV = ifThenBlocks[i]->condition->codegen();
                if (!condV)
                    return nullptr;
                irb::Value* blockV = ifThenBlocks[i]->block->codegen();
                if (!blockV)
                    return nullptr;
                codeStr += condV->getRawName() + ") " + blockV->getRawName();
            }

            if (elseBlock) {
                codeStr += " else ";
                irb::Value* blockV = elseBlock->codegen();
                if (!blockV)
                    return nullptr;
                codeStr += blockV->getRawName();
            }

            return new irb::Value(context, nullptr, codeStr);
        } else {
            std::vector<irb::Block*> elseBs(ifThenBlocks.size()); //Serve as conditions except for the else block
            std::vector<irb::Block*> thenBs(ifThenBlocks.size());
            std::vector<irb::Block*> mergeBs(ifThenBlocks.size());
            for (uint32_t i = 0; i < ifThenBlocks.size(); i++) {
                if (i != 0) {
                    context.pushRegisterName("cond");
                    elseBs[i - 1] = builder->opBlock();
                }
                context.pushRegisterName("then");
                thenBs[i] = builder->opBlock();
                context.pushRegisterName(i == 0 ? "end" : "merge");
                mergeBs[i] = builder->opBlock();
            }
            irb::Block* endB = mergeBs[0];
            if (elseBlock) {
                context.pushRegisterName("else");
                elseBs[elseBs.size() - 1] = builder->opBlock();
            } else {
                elseBs[elseBs.size() - 1] = endB;
            }
            for (uint32_t i = 0; i < ifThenBlocks.size(); i++) {
                irb::Value* condV = ifThenBlocks[i]->condition->codegen();
                builder->opBlockMerge(mergeBs[i]);
                builder->opBranchCond(condV, thenBs[i], elseBs[i]);

                //Current body
                builder->setInsertBlock(thenBs[i]);
                irb::Value* blockV = ifThenBlocks[i]->block->codegen();
                builder->opBranch(mergeBs[i]);

                //Next condition or else block
                builder->setInsertBlock(elseBs[i]);
            }
            if (elseBlock) {
                irb::Value* blockV = elseBlock->codegen();
                builder->opBranch(mergeBs[mergeBs.size() - 1]);
            }
            for (uint32_t i = mergeBs.size() - 1; i > 0; i--) {
                builder->setInsertBlock(mergeBs[i]);
                builder->opBranch(mergeBs[i - 1]);
            }

            //End
            builder->setInsertBlock(endB);

            //TODO: return something else
            return endB;
        }
    }
};

//Inline if else
class InlineIfElseExpressionAST : public ExpressionAST {
private:
    ExpressionAST* condition;
    BlockExpressionAST* thenBlock;
    BlockExpressionAST* elseBlock;

public:
    InlineIfElseExpressionAST(ExpressionAST* aCondition, BlockExpressionAST* aThenBlock, BlockExpressionAST* aElseBlock) : condition(aCondition), thenBlock(aThenBlock), elseBlock(aElseBlock) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        //TODO: implement this

        return nullptr;
    }
};

//While
class WhileExpressionAST : public ExpressionAST {
private:
    ExpressionAST* condition;
    BlockExpressionAST* block;

    bool isDoWhile;

public:
    WhileExpressionAST(ExpressionAST* aCondition, BlockExpressionAST* aBlock, bool aIsDoWhile) : condition(aCondition), block(aBlock), isDoWhile(aIsDoWhile) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        irb::Block* mergeB;
        irb::Block* condB;
        irb::Block* thenB;
        irb::Block* afterThenB;
        irb::Block* endB;
        //TODO: use the same code for both SPIRV and AIR
        if (TARGET_IS_IR(irb::target)) {
            if (irb::target == irb::Target::SPIRV) {
                context.pushRegisterName("loop_merge");
                mergeB = builder->opBlock();
            }
            context.pushRegisterName("loop_cond");
            condB = builder->opBlock();
            context.pushRegisterName("loop");
            thenB = builder->opBlock();
            if (irb::target == irb::Target::SPIRV) {
                context.pushRegisterName("after_loop");
                afterThenB = builder->opBlock();
            } else {
                mergeB = condB;
                afterThenB = condB;
            }
            context.pushRegisterName("end");
            endB = builder->opBlock();

            builder->opBranch(isDoWhile ? thenB : mergeB);

            //Merge
            if (irb::target == irb::Target::SPIRV) {
                builder->setInsertBlock(mergeB);
                builder->opLoopMerge(endB, afterThenB);
                builder->opBranch(condB);
            }

            //Condition
            builder->setInsertBlock(condB);
        }
        
        irb::Value* condV = condition->codegen();
        if (!condV)
            return nullptr;

        if (TARGET_IS_CODE(irb::target)) {
            irb::Value* blockV = block->codegen();
            if (!blockV)
                return nullptr;

            std::string codeStr;
            if (isDoWhile)
                codeStr += "do (";
            else
                codeStr += "while (";
            codeStr += condV->getRawName() + ")";
            codeStr += blockV->getRawName();

            return new irb::Value(context, nullptr, codeStr);
        } else {
            builder->opBranchCond(condV, thenB, endB);

            //Then
            builder->setInsertBlock(thenB);
            irb::Value* blockV = block->codegen();
            if (!blockV)
                return nullptr;
            builder->opBranch(afterThenB);

            //After then
            if (irb::target == irb::Target::SPIRV) {
                builder->setInsertBlock(afterThenB);
                builder->opBranch(mergeB);
            }

            //End
            builder->setInsertBlock(endB);

            return endB;
        }
    }
};

//Variable declaration
struct VariableDeclaration {
    std::string name;
    irb::Type* type;
    ExpressionAST* expression;
};

class VariableDeclarationExpressinAST : public ExpressionAST {
private:
    std::vector<VariableDeclaration> variableNames;
    bool isGlobal;
    bool isConstant;

public:
    VariableDeclarationExpressinAST(const std::vector<VariableDeclaration>& aVariableNames, bool aIsGlobal, bool aIsConstant) : variableNames(aVariableNames), isGlobal(aIsGlobal), isConstant(aIsConstant) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        std::string codeStr;

       irb::Value* value = nullptr;
        for (uint32_t i = 0; i < variableNames.size(); i++) {
            const std::string& varName = variableNames[i].name;
            irb::Type* type = variableNames[i].type;
            ExpressionAST* initExpression = variableNames[i].expression;

            irb::Value* initV = nullptr;
            if (initExpression) {
                if (isGlobal && !initExpression->isConstant()) {
                    logError("global variable can only be initialized using a constant expression");
                    return nullptr;
                }
                //TODO: uncomment?
                //context.pushRegisterName(varName + "_init");
                initV = initExpression->codegen(type);
                if (!initV)
                    return nullptr;
            } else if (!type) {
                logError("cannot deduce type without initial value");
                return nullptr;
            }
            if (!type) {
                type = initV->getType()->copy();
            }

            if (isConstant) {
                if (irb::target == irb::Target::Metal && isGlobal)
                    codeStr += "constant ";
                else
                    codeStr += "const ";
            }

            codeStr += type->getNameBegin() + " " + varName + type->getNameEnd();
            if (initExpression)
                codeStr += " = " + initV->getRawName();
            if (isGlobal)
                codeStr += ";";
            
            irb::PointerType* varType = new irb::PointerType(context, type, irb::StorageClass::Function);
            if (TARGET_IS_IR(irb::target)) {
                context.pushRegisterName(varName);
                if (isConstant && isGlobal)
                    value = initV;
                else
                    value = builder->opVariable(varType, (initExpression && initExpression->isConstant() ? initV : nullptr));
                if (initExpression && !initExpression->isConstant())
                    builder->opStore(value, initV);
                variables[varName] = {value, isGlobal};
            } else {
                value = new irb::Value(context, varType, codeStr);
                variables[varName] = {new irb::Value(context, varType, varName), isGlobal};
            }
        }

        return value;
    }
};

//Array
class ArrayExpressionAST : public ExpressionAST {
private:
    std::vector<ExpressionAST*> values;

    irb::Type* type;

public:
    ArrayExpressionAST(const std::vector<ExpressionAST*>& aValues) : values(aValues) {}

    //TODO: implement for IR as well
    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        type = new irb::ArrayType(context, createScalarType(TOKEN_TYPE_CHAR), values.size());

        std::string codeStr = "{";
        for (uint32_t i = 0; i < values.size(); i++) {
            if (!values[i]->isConstant()) {
                logError("all values in a constant array initializer must be constant");

                return nullptr;
            }
            irb::Value* valueV = values[i]->codegen();
            if (!valueV)
                return nullptr;
            if (i != 0)
                codeStr += ", ";
            codeStr += valueV->getRawName();
        }
        codeStr += "}";

        return new irb::Value(context, type, codeStr);
    }
};

//Subscript
class SubscriptExpressionAST : public ExpressionAST {
private:
    ExpressionAST* ptr;
    ExpressionAST* index;

    irb::PointerType* type;

public:
    SubscriptExpressionAST(ExpressionAST* aPtr, ExpressionAST* aIndex) : ptr(aPtr), index(aIndex) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        ptr->setLoadOnCodegen(false);
        irb::Value* ptrV = ptr->codegen();
        irb::Value* indexV = index->codegen();
        if (!ptrV || !indexV)
            return nullptr;
        if (!indexV->getType()->isOperatorFriendly()) {
            logError("only operator friendly types can be used for indexing");
            return nullptr;
        }
        type = dynamic_cast<irb::PointerType*>(ptrV->getType());
        if (!type) {
            logError("cannot index into a non-pointer value");
            return nullptr;
        }

        irb::PointerType* elementType = new irb::PointerType(context, type->getElementType()->getBaseType(), type->getStorageClass());
        if (TARGET_IS_CODE(irb::target)) {
            return new irb::Value(context, elementType, ptrV->getRawName() + "[" + indexV->getRawName() + "]");
        } else {
            irb::Value* value = builder->opGetElementPtr(elementType, ptrV, {indexV});
            if (loadOnCodegen)
                value = builder->opLoad(value);
            if (requiredType)
                value = builder->opCast(value, requiredType);

            return value;
        }
    }
};

//TODO: support chained unloaded vector swizzle
class MemberAccessExpressionAST : public ExpressionAST {
private:
    ExpressionAST* expression;
    std::string memberName;

    irb::Type* type = nullptr;

public:
    MemberAccessExpressionAST(ExpressionAST* aExpression, const std::string& aMemberName) : expression(aExpression), memberName(aMemberName) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        expression->setLoadOnCodegen(false);
        irb::Value* exprV = expression->codegen();
        if (!exprV)
            return nullptr;
        irb::PointerType* exprType = dynamic_cast<irb::PointerType*>(exprV->getType());
        if (!exprType) {
            logError("cannot access member of non-pointer value");
            return nullptr;
        }
        irb::Type* elementExprType = exprType->getElementType();
        if (elementExprType->isStructure()) {
            irb::Structure* structure = static_cast<irb::StructureType*>(elementExprType)->getStructure();
            
            uint32_t memberIndex;
            for (memberIndex = 0; memberIndex < structure->members.size(); memberIndex++) {
                if (memberName == structure->members[memberIndex].name) {
                    type = new irb::PointerType(context, structure->members[memberIndex].type, exprType->getStorageClass()); //TODO: move this to structure definition
                    break;
                }
            }

            if (!type) {
                logError("structure '" + elementExprType->getName() + "' has no member named '" + memberName + "'");
                return nullptr;
            }

            if (TARGET_IS_CODE(irb::target)) {
                return new irb::Value(context, type, exprV->getRawName() + "." + memberName);
            } else {
                irb::Value* indexV = builder->opConstant(new irb::ConstantInt(context, memberIndex, 32, true));
                irb::Value* elementV = builder->opGetElementPtr(type, exprV, {indexV});
                if (loadOnCodegen)
                    elementV = builder->opLoad(elementV);

                return elementV;
            }
        } else if (elementExprType->isVector()) {
            irb::Type* type;
            if (memberName.size() == 1)
                type = elementExprType->getBaseType();
            else
                type = new irb::VectorType(context, elementExprType->getBaseType(), memberName.size());
            if (TARGET_IS_CODE(irb::target)) {
                irb::Type* trueType = type;
                //HACK: get the pointer type
                if (!loadOnCodegen)
                    trueType = new irb::PointerType(context, type, irb::StorageClass::Function);
                return new irb::Value(context, trueType, exprV->getRawName() + "." + memberName);
            } else {
                irb::Value* loadedVector;
                std::vector<irb::Value*> components;
                std::vector<uint8_t> indices;
                if (loadOnCodegen) {
                    loadedVector = builder->opLoad(exprV);
                    components.reserve(memberName.size());
                } else {
                    indices.reserve(memberName.size());
                }
                for (uint8_t i = 0; i < memberName.size(); i++) {
                    int8_t index;
                    switch (memberName[i]) {
                    case 'x':
                    case 'r':
                        index = 0;
                        break;
                    case 'y':
                    case 'g':
                        index = 1;
                        break;
                    case 'z':
                    case 'b':
                        index = 2;
                        break;
                    case 'w':
                    case 'a':
                        index = 3;
                        break;
                    default:
                        index = -1;
                        break;
                    }
                    if (loadOnCodegen)
                        components.push_back(builder->opVectorExtract(loadedVector, new irb::ConstantInt(context, index, 32, false)));
                    else
                        indices.push_back(index);
                }
                
                if (loadOnCodegen) {
                    if (components.size() == 1)
                        return components[0];
                    return builder->opVectorConstruct(static_cast<irb::VectorType*>(type), components);
                } else {
                    return new UnloadedSwizzledVectorValue(context, exprV, indices);
                }
            }
        } else {
            logError("the '.' operator only operates on structures and vectors");
            return nullptr;
        }
    }
};

class StructureDefinitionAST : public ExpressionAST {
private:
    std::string name;
    std::vector<irb::StructureMember> members;

public:
    StructureDefinitionAST(const std::string& aName, const std::vector<irb::StructureMember>& aMembers) : name(aName), members(aMembers) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        if (context.structures[name]) {
            logError("redefinition of structure '" + name + "'");
            return nullptr;
        }

        std::string codeStr = "struct " + name + " {\n";
        for (auto& member : members) {
            std::string attributesEnd;
            if (irb::target == irb::Target::Metal) {
                if (member.attributes.isPosition)
                    attributesEnd += " [[position]]";
                if (member.attributes.locationIndex != -1)
                    attributesEnd += " [[attribute(" + std::to_string(member.attributes.locationIndex) + ")]]";
            }
            codeStr += "\t" + member.type->getNameBegin() + " " + member.name + member.type->getNameEnd() + attributesEnd + ";\n";
        }
        codeStr += "};";

        irb::Structure* structure = new irb::Structure;
        structure->members = members;
        context.structures[name] = structure;

        irb::StructureType* type = new irb::StructureType(context, name);
        if (TARGET_IS_IR(irb::target)) {
            context.pushRegisterName(name);

            return builder->opStructureDefinition(type);
        } else {
            return new irb::Value(context, type, codeStr);
        }
    }
};

class EnumDefinitionAST : public ExpressionAST {
private:
    std::string name;
    std::vector<EnumValue> values;

public:
    EnumDefinitionAST(const std::string& aName, const std::vector<EnumValue>& aValues) : name(aName), values(aValues) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        if (enumerations[name]) {
            logError("redefinition of enum '" + name + "'");
            return nullptr;
        }

        std::string codeStr;
        if (irb::target == irb::Target::Metal) {
            codeStr = "enum " + name + " {\n";
            for (auto& value : values)
                codeStr += "\t" + value.name + " = " + std::to_string(value.value) + ",\n";
            codeStr += "};";
        } else {
            codeStr = "//Enum '" + name + "'";
        }

        Enumeration* enumeration = new Enumeration(values);
        enumerations[name] = enumeration;

        return new irb::Value(context, new EnumType(context, name), codeStr);
    }
};

class EnumValueExpressionAST : public ExpressionAST {
private:
    Enumeration* enumeration;
    EnumValue& value;

public:
    EnumValueExpressionAST(Enumeration* aEnumeration, EnumValue& aValue) : enumeration(aEnumeration), value(aValue) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        if (TARGET_IS_IR(irb::target)) {
            return builder->opConstant(new irb::ConstantValue(context, enumeration->type, std::to_string(value.value)));
        } else {
            if (irb::target == irb::Target::Metal)
                return new irb::Value(context, enumeration->type, value.name);
            else
                return new irb::Value(context, enumeration->type, std::to_string(value.value));
        }
    }
};

//TODO: support other initializer lists as well (for instance sampler)
//TODO: enable vector from vector initialization (for instance float3(float2(0.2, 0.3), 0.4))
class InitializerListExpressionAST : public ExpressionAST {
private:
    irb::Type* type;
    std::vector<ExpressionAST*> expressions;

public:
    InitializerListExpressionAST(irb::Type* aType, std::vector<ExpressionAST*> aExpressions) : type(aType), expressions(aExpressions) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        if (type->isScalar()) {
            if (expressions.size() != 1) {
                logError("scalar initializer list must have exactly one value");
                return nullptr;
            }
        } else if (type->isArray()) {
            uint32_t size = static_cast<irb::ArrayType*>(type)->getSize();
            if (expressions.size() > size) {
                logError("array initializer cannot be larger than the array itself (" + std::to_string(expressions.size()) + " > " + std::to_string(size) + ")");
                return nullptr;
            }
        } else if (type->isVector()) {
            uint32_t componentCount = static_cast<irb::VectorType*>(type)->getComponentCount();
            if (expressions.size() > componentCount) {
                logError("vector initializer cannot be larger than the vector itself (" + std::to_string(expressions.size()) + " > " + std::to_string(componentCount) + ")");
                return nullptr;
            }
            if (expressions.size() != componentCount && expressions.size() != 1) {
                logError("not enough components in initializer to construct a vector (got " + std::to_string(expressions.size()) + ", expected either " + std::to_string(componentCount) + " or 1)");
                return nullptr;
            }
        } else {
            logError("cannot use initializer list to create a type '" + type->getName() + "'"); //TODO: get the name in a different way?
            return nullptr;
        }

        if (TARGET_IS_IR(irb::target)) {
            if (type->isScalar())
                return expressions[0]->codegen(type);
            if (type->isArray()) {
                //TODO: implement this
                return nullptr;
            }
            if (type->isVector()) {
                irb::VectorType* vectorType = static_cast<irb::VectorType*>(type);
                std::vector<irb::Value*> components;
                components.reserve((expressions.size()));
                for (auto* expression : expressions)
                    components.push_back(expression->codegen(vectorType->getBaseType()));
                //Fill the list in case it is just a one value initializer
                if (components.size() == 1) {
                    //TODO: do this in a more elegant way?
                    components.reserve(vectorType->getComponentCount());
                    for (uint8_t i = 0; i < vectorType->getComponentCount() - 1; i++)
                        components.push_back(components[0]);
                }
                context.pushRegisterName("const_vector");

                return builder->opVectorConstruct(vectorType, components);
            }

            return nullptr;
        } else {
            std::string codeStr = type->getName() + "(";
            for (uint32_t i = 0; i < expressions.size(); i++) {
                irb::Value* value = expressions[i]->codegen(type->isScalar() ? type : type->getBaseType());
                if (i != 0)
                    codeStr += ", ";
                codeStr += value->getRawName();
            }

            return new irb::Value(context, type, codeStr + ")");
        }
    }

    virtual bool isConstant() override {
        for (auto* expression : expressions) {
            if (!expression->isConstant())
                return false;
        }

        return true;
    }
};

//Parsing expressions

//Binop precedence
static std::map<int, int> binopPrecedence;

static int getTokenPrecedence() {
    //if (!isascii(crntToken))
    //    return -1;
    
    int op = binopPrecedence[crntToken];
    if (op <= 0)
        return -1;
    
    return op;
}

//Forward declarations
ExpressionAST* parseMain();
ExpressionAST* parseExpression(int expressionPrecedence = 0);

//Type
irb::Type* _parseTypeExpression() {
    irb::Type* type;
    if (tokenIsType(crntToken)) {
        if (crntToken == TOKEN_TYPE_STRUCT) {
            getNextToken(); // 'struct'
            type = new irb::StructureType(context, identifierStr);
        } else if (crntToken == TOKEN_TYPE_ENUM) {
            getNextToken(); // 'enum'
            type = new EnumType(context, identifierStr);
        } else if (tokenIsTextureType(crntToken)) {
            irb::TextureViewType viewType;
            switch (crntToken) {
            case TOKEN_TYPE_TEXTURE_1D:
                viewType = irb::TextureViewType::_1D;
                break;
            case TOKEN_TYPE_TEXTURE_2D:
                viewType = irb::TextureViewType::_2D;
                break;
            case TOKEN_TYPE_TEXTURE_3D:
                viewType = irb::TextureViewType::_3D;
                break;
            case TOKEN_TYPE_TEXTURE_1D_ARRAY:
                viewType = irb::TextureViewType::_1DArray;
                break;
            case TOKEN_TYPE_TEXTURE_2D_ARRAY:
                viewType = irb::TextureViewType::_2DArray;
                break;
            case TOKEN_TYPE_TEXTURE_CUBE:
                viewType = irb::TextureViewType::Cube;
                break;
            case TOKEN_TYPE_TEXTURE_CUBE_ARRAY:
                viewType = irb::TextureViewType::CubeArray;
                break;
            default:
                break;
            }
            if (getNextToken() != TOKEN_OPERATOR_RELATIONAL_LESS_THAN) {
                logError("no default template found for textureXX");
                return nullptr;
            }
            getNextToken(); // '<'
            irb::Type* textureType = _parseTypeExpression();
            if (!textureType->isScalar()) {
                logError("expected scalar type for the 1st template argument");
                return nullptr;
            }
            irb::ScalarType* scalarType = static_cast<irb::ScalarType*>(textureType);
            if (crntToken != TOKEN_OPERATOR_RELATIONAL_GREATER_THAN) {
                logError("expected '>' to match the '<'");
                return nullptr;
            }

            type = new irb::TextureType(context, viewType, scalarType);
            if (irb::target == irb::Target::AIR) {
                irb::PointerType* pointerType = new irb::PointerType(context, type, irb::StorageClass::Function);
                pointerType->setAddressSpace(1);
                type = pointerType;
            }
        } else if (crntToken == TOKEN_TYPE_SAMPLER) {
            type = new irb::SamplerType(context);
            if (irb::target == irb::Target::AIR) {
                irb::PointerType* pointerType = new irb::PointerType(context, type, irb::StorageClass::Function);
                pointerType->setAddressSpace(2);
                type = pointerType;
            }
        } /* else if (typeIsBuiltin) {
            getNextToken(); //Type
            Type* bufferType;
            switch (builtinTypeID) {
            case TypeID::Buffer:
                if (crntToken != TOKEN_OPERATOR_RELATIONAL_LESS_THAN) {
                    logError("no default template found for 'buffer'");
                    return nullptr;
                }
                getNextToken(); // '<'
                bufferType = _parseTypeExpression();
                if (!bufferType)
                    return nullptr;
                type = new PointerType(context, bufferType, StorageClass::StorageBuffer); //TODO: support @ref Uniform storage class
                break;
            case TypeID::Texture:
            case TypeID::Sampler:
                logError("'texture' and 'sampler' are not supported yet");
                return nullptr;
            default:
                return nullptr;
            }
        }*/ else {
            type = createScalarType(crntToken);
        }
        if (componentCount != 0)
            type = new irb::VectorType(context, type, componentCount);
        getNextToken(); //Type or '>'
    } else {
        logError("unknown type '" + identifierStr + "'");
        return nullptr;
    }

    uint32_t pointerCount = 0;
    for (; crntToken == TOKEN_OPERATOR_ARITHMETIC_MULTIPLY; pointerCount++)
        getNextToken(); // '*'

    std::vector<NumberExpressionAST*> arraySizes;
    while (crntToken == '[') {
        //Skip attributes
        if (getNextToken() == '[')
            break;
        ExpressionAST* arraySize = parseExpression();
        if (!arraySize)
            return nullptr;
        NumberExpressionAST* numArraySize = dynamic_cast<NumberExpressionAST*>(arraySize);
        if (!numArraySize) {
            logError("array size must be a constant number");
            return nullptr;
        }
        /*
        if (!arraySize || !arraySize->isConstant()) {
            logError("array declaration must contain a constant size expression");

            return nullptr;
        }
        */

        if (crntToken != ']') {
            logError("expected ']' to match the '['");
            return nullptr;
        }
        getNextToken(); // ']'

        //type = new ArrayType(context, type, numArraySize->valueU());
        arraySizes.push_back(numArraySize);
    }

    for (int32_t i = arraySizes.size() - 1; i >= 0; i--)
        type = new irb::ArrayType(context, type, arraySizes[i]->valueU());
    
    if (pointerCount)
        type = new irb::PointerType(context, type, irb::StorageClass::Function);
    
    return type;
}

irb::Type* _parseTypeWithAttributesExpression(irb::Attributes* attributes = nullptr) {
    std::vector<irb::Attribute> attribs;
    while (/*crntToken == '['*/tokenIsAttrib(crntToken)) {
        //getNextToken(); // '['
        //if (tokenIsType(crntToken)) {
        //    break;
        //}
        /*
        if (crntToken != '[') {
            logError("expected second '[' in an attribute");

            return nullptr;
        }
        if (!tokenIsAttrib(getNextToken())) {
            logError(("expected attribute name, got '" + std::to_string(crntToken) + "' instead").c_str());

            return nullptr;
        }
        */
        if (!attributes) {
            logError("cannot use attribute on this expression");
            return nullptr;
        }
        attribs.push_back(getAttributeFromToken(crntToken));
        getNextToken(); //Attribute
        /*
        for (uint8_t i = 0; i < 2; i++) {
            if (crntToken != ']') {
                logError("expected ']' to match the '['");
                
                return nullptr;
            }
            getNextToken(); // ']'
        }
        */
    }

    /*
    if (!tokenIsType(crntToken)) {
        logError("unknown type ''");

        return nullptr;
    }
    */

    irb::Type* type = _parseTypeExpression();

    while (crntToken == '[') {
        if (!attributes) {
            logError("cannot use attribute on this expression");
            return nullptr;
        }
        /*
        if (getNextToken() != '[') {
            logError("expected double '[' in an attribute");
            return nullptr;
        }
        */
        getNextToken(); // '['
        if (!tokenIsAttrib(crntToken)) {
            logError("unknown attribute '" + std::to_string(crntToken) + "'");
            return nullptr;
        }
        irb::Attribute attrib{getAttributeFromToken(crntToken)};
        if (getNextToken() == '(') {
            do {
                if (getNextToken() != TOKEN_NUMBER) {
                    logError("");
                    return nullptr;
                }
                attrib.values.push_back(numValueU);
            } while (getNextToken() == ',');
            if (crntToken != ')') {
                logError("expected ')' to match the '('");
                return nullptr;
            }
            getNextToken(); // ')'
        }

        for (uint8_t i = 0; i < 2; i++) {
            if (crntToken != ']') {
                logError("expected ']' to match the '[' in attribute");
                return nullptr;
            }
            getNextToken(); // ']'
        }
        attribs.push_back(attrib);

        if (crntToken != '[')
            break;
        getNextToken(); // '['
    }

    for (const auto& attrib : attribs) {
        switch (attrib.attrib) {
        case irb::Attribute::Enum::AddressSpace:
            attributes->addressSpace = attrib.values[0];
            break;
        case irb::Attribute::Enum::Buffer:
            attributes->isBuffer = true;
            break;
        case irb::Attribute::Enum::DescriptorSet:
            attributes->set = attrib.values[0];
            attributes->binding = attrib.values[1];
            break;
        case irb::Attribute::Enum::Position:
            attributes->isPosition = true;
            break;
        case irb::Attribute::Enum::Input:
            attributes->isInput = true;
            break;
        case irb::Attribute::Enum::Location:
            attributes->locationIndex = attrib.values[0];
            break;
        default:
            break;
        }
    }

    return type;
}

//Number
NumberExpressionAST* parseNumberExpression() {
    NumberExpressionAST* result = new NumberExpressionAST(numValueD, numValueL, numValueU, createScalarType(getIntTypeFromNumStr(numTypeStr)));
    getNextToken();

    return result;
}

//Return
ExpressionAST* parseReturnExpression() {
    getNextToken();
    ExpressionAST* returnExpr = parseExpression();

    return new ReturnExpressionAST(returnExpr);
}

//Parenthesis
ExpressionAST* parseParenthesisExpression() {
    getNextToken(); // '('
    ExpressionAST* v = parseExpression();
    if (!v)
        return nullptr;
    
    if (crntToken != ')') {
        logError("expected ')'");

        return nullptr;
    }
    
    getNextToken();

    return v;
}

//Braces
BlockExpressionAST* parseBracesExpression() {
    std::vector<ExpressionAST*> expressions;
    getNextToken();
    while (crntToken != '}') {
        ExpressionAST* expr = parseExpression();
        if (!expr)
            return nullptr;

        //Get rid of semicolons
        while (crntToken == TOKEN_SKIP) {
            getNextToken();
        }
        
        expressions.push_back(expr);
    }

    getNextToken(); // '}'

    return new BlockExpressionAST(expressions);
}

//TODO: support constant array declarations as well
//Square brackets
ExpressionAST* parseSquareBracketsExpression() {
    getNextToken(); // '['
    ExpressionAST* ptr = parseExpression();
    if (!ptr)
        return nullptr;

    if (crntToken != ':') {
        logError("Expected ':' in a subscript expression");

        return nullptr;
    }
    getNextToken(); // ':'

    ExpressionAST* index = parseExpression();
    if (!index)
        return nullptr;
    
    if (crntToken != ']') {
        logError("Expected ']' to match the '['");

        return nullptr;
    }
    getNextToken(); // ']'

    return new SubscriptExpressionAST(ptr, index);
}

//Identifier
ExpressionAST* parseIdentifierExpression() {
    std::string idName = identifierStr;
    getNextToken(); //Identifier

    //Variable reference
    if (crntToken != '(') {
        if (auto* enumeration = enumerations[idName]) {
            if (crntToken != TOKEN_OPERATOR_DOT) {
                logError("enum name must be followed by '.'");
                return nullptr;
            }
            if (getNextToken() != TOKEN_IDENTIFIER) {
                logError("use of unexpected token '" + std::to_string(crntToken) + "'. expected value name instead");
                return nullptr;
            }
            std::string valueName = identifierStr;
            getNextToken(); //value name

            EnumValue* value = nullptr;
            for (auto& enumValue : enumeration->values) {
                if (valueName == enumValue.name) {
                    value = &enumValue;
                    break;
                }
            }
            if (!value) {
                logError("enum '" + idName + "' does not have a value named '" + valueName + "'");
                return nullptr;
            }

            return new EnumValueExpressionAST(enumeration, *value);

        }
        return new VariableExpressionAST(idName);
    }
    
    //Function call
    getNextToken(); // '('
    std::vector<ExpressionAST*> arguments;
    if (crntToken != ')') {
        while (true) {
            if (ExpressionAST* arg = parseExpression())
                arguments.push_back(arg);
            else
                return nullptr;
            
            if (crntToken == ')')
                break;
            
            if (crntToken != ',') {
                logError("Expected ')' or ',' in a function call");

                return nullptr;
            }
            getNextToken();
        }
    }

    getNextToken(); // ')'

    return new CallExpressionAST(idName, arguments);
}

IfThenBlock* _parseIfThenBlock() {
    IfThenBlock* ifThenBlock = new IfThenBlock;

    //Condition
    ifThenBlock->condition = parseExpression();
    if (!ifThenBlock->condition)
        return nullptr;
    
    ifThenBlock->block = static_cast<BlockExpressionAST*>(parseExpression());
    if (!ifThenBlock->block)
        return nullptr;

    return ifThenBlock;
}

//If
ExpressionAST* parseIfExpression() {
    getNextToken(); // 'if'

    std::vector<IfThenBlock*> ifThenBlocks;
    
    IfThenBlock* ifThenBlock = _parseIfThenBlock();
    if (!ifThenBlock)
        return nullptr;
    ifThenBlocks.push_back(ifThenBlock);
    
    BlockExpressionAST* elseBlock = nullptr;
    while (crntToken == TOKEN_ELSE) {
        getNextToken(); // 'else'
        if (crntToken == TOKEN_IF) { //If else
            getNextToken(); // 'if'
            ifThenBlock = _parseIfThenBlock();
            if (!ifThenBlock)
                return nullptr;
            
            ifThenBlocks.push_back(ifThenBlock);
        } else { //Else
            elseBlock = static_cast<BlockExpressionAST*>(parseExpression());
            if (!elseBlock)
                return nullptr;
            
            break;
        }
    }

    return new IfExpressionAST(ifThenBlocks, elseBlock);
}

//While
ExpressionAST* parseWhileExpression() {
    getNextToken(); // 'while'

    //Condition
    ExpressionAST* condition = parseExpression();
    if (!condition)
        return nullptr;
    
    BlockExpressionAST* block = static_cast<BlockExpressionAST*>(parseExpression());
    if (!block)
        return nullptr;

    return new WhileExpressionAST(condition, block, false);
}

//Variable declaration
ExpressionAST* parseVariableDeclarationExpression(bool isGlobal = false) {
    bool isConstant = false;
    if (crntToken == TOKEN_CONST) {
        isConstant = true;
        getNextToken(); // 'const'
    }

    if (crntToken != TOKEN_VAR) {
        logError("Expected 'var' in a variable declaration");
    }
    getNextToken(); // 'var'

    std::vector<VariableDeclaration> variableNames;

    if (crntToken != TOKEN_IDENTIFIER) {
        logError("expected variable name after 'var'");

        return nullptr;
    }

    while (true) {
        std::string name = identifierStr;

        irb::Type* type = nullptr;
        if (getNextToken() == ':') {
            getNextToken(); // ':'
            type = _parseTypeWithAttributesExpression();
        }

        ExpressionAST* initExpr = nullptr;
        if (crntToken == TOKEN_OPERATOR_ASSIGNMENT_ASSIGN) {
            getNextToken(); // '='

            initExpr = parseExpression();

            if (!initExpr)
                return nullptr;

            //if (name == "theDouble")
            //    initExpr = nullptr;
            
            //std::cout << "CRNT TOKEN: " << crntToken << " : " << char(crntToken) << " : " << identifierStr << std::endl;
        }

        variableNames.push_back({name, type, initExpr});

        if (crntToken != ',')
            break;
        
        getNextToken(); // ','

        if (crntToken != TOKEN_IDENTIFIER) {
            logError("expected variable name in variable declaration list");

            return nullptr;
        }
    }

    return new VariableDeclarationExpressinAST(variableNames, isGlobal, isConstant);
}

//Reference
/*
ReferenceExpressionAST* parseReferenceExpression() {
    getNextToken(); // '&'
    if (crntToken != TOKEN_IDENTIFIER) {
        logError("expected variable name after '&'");

        return nullptr;
    }
    ExpressionAST* expression = parseIdentifierExpression();

    VariableExpressionAST* variableExpr = static_cast<VariableExpressionAST*>(expression);
    if (!variableExpr) {
        logError("expected variable name after '&'");

        return nullptr;
    }

    return new ReferenceExpressionAST(variableExpr);
}
*/

//Single quote
ExpressionAST* parseCharExpression() {
    NumberExpressionAST* expression = new NumberExpressionAST(numValueL, numValueL, numValueL, createScalarType(0));
    getNextToken(); //String

    return expression;
}

//Double quote
ExpressionAST* parseStringExpression() {
    std::vector<ExpressionAST*> values(identifierStr.size());
    for (uint16_t i = 0; i < values.size(); i++)
        values[i] = new NumberExpressionAST(identifierStr[i], identifierStr[i], identifierStr[i], createScalarType(TOKEN_TYPE_CHAR));
        
    ArrayExpressionAST* expression = new ArrayExpressionAST(values);
    getNextToken(); //String

    return expression;
}

/*
RegisterExpressionAST* parseRegisterExpression() {
    if (getNextToken() != '(') {
        logError("'register' must be followed by '('");

        return nullptr;
    }
    if (getNextToken() != TOKEN_NUMBER) {
        logError("register expression must contain a register number");

        return nullptr;
    }

    NumberExpressionAST* registerNumberExpr = parseNumberExpression();
    long registerNumber = registerNumberExpr->valueL();
    if (registerNumber < 0 && registerNumber >= REGISTER_COUNT) {
        logError("register number must be in the range [0, " + std::to_string(REGISTER_COUNT) + "] excluding " + std::to_string(REGISTER_COUNT));
    }

    if (getNextToken() != ')') {
        logError("expected ')' to match the '('");

        return nullptr;
    }
    getNextToken(); // ')'

    return new RegisterExpressionAST(registerNumber);
}
*/

InitializerListExpressionAST* parseTypeExpression() {
    irb::Type* type = _parseTypeExpression(); //TODO: parse with attributes as well?
    if (crntToken != '(') {
        logError("expected '(' after type");
        return nullptr;
    }
    std::vector<ExpressionAST*> expressions;
    do {
        getNextToken(); // '(' or ','
        expressions.push_back(parseExpression());
    } while (crntToken == ',');
    if (crntToken != ')') {
        logError("expected ')' after initializer list to match the '('");
        return nullptr;
    }
    getNextToken(); // ')'
    InitializerListExpressionAST* expression = new InitializerListExpressionAST(type, expressions);

    return expression;
}

//Main parse
ExpressionAST* parseMain() {
    switch (crntToken) {
    case TOKEN_RETURN:
        return parseReturnExpression();
    case TOKEN_IF:
        return parseIfExpression();
    case TOKEN_WHILE:
        return parseWhileExpression();
    case TOKEN_FOR:
        logError("'for' is not supported yet");
        return nullptr;
    case TOKEN_VAR:
    case TOKEN_CONST:
        return parseVariableDeclarationExpression();
    case TOKEN_REGISTER:
        //return parseRegisterExpression();
        logError("'register' is not supported yet");
        return nullptr;
    case TOKEN_IDENTIFIER:
        return parseIdentifierExpression();
    case TOKEN_NUMBER:
        return parseNumberExpression();
    case TOKEN_CHAR:
        return parseCharExpression();
    case TOKEN_STRING:
        return parseStringExpression();
    case '(':
        return parseParenthesisExpression();
    case '{':
        return parseBracesExpression();
    case '[':
        return parseSquareBracketsExpression();
    case TOKEN_TYPE_ENUM_MIN ... TOKEN_TYPE_ENUM_MAX:
        return parseTypeExpression();
    default:
        logError("expected expression");
        return nullptr;
    }
}

//Binary
ExpressionAST* parseBinOpRHS(int expressionPrecedence, ExpressionAST* lhs) {
    while (true) {
        int tokenPrecedence = getTokenPrecedence();

        if (tokenPrecedence < expressionPrecedence)
            return lhs;
        
        std::string binOp = operatorStr;
        getNextToken(); //binop

        ExpressionAST* rhs;
        std::string memberName;
        if (binOp == ".") {
            if (crntToken != TOKEN_IDENTIFIER) {
                logError("expected member name after the '.' operator");
                return nullptr;
            }

            memberName = identifierStr;
            getNextToken(); //Member name
        } else {
            rhs = parseMain();
            if (!rhs)
                return nullptr;
        }
        
        int nextPrecedence = getTokenPrecedence();
        if (tokenPrecedence < nextPrecedence) {
            if (binOp == ".")
                throw std::runtime_error("For some reason, the '.' had lower precedence than something else");
            rhs = parseBinOpRHS(tokenPrecedence + 1, rhs);
            if (!rhs)
                return nullptr;
        }

        if (binOp == ".")
            lhs = new MemberAccessExpressionAST(lhs, memberName);
        else
            lhs = new BinaryExpressionAST(binOp, lhs, rhs);
    }
}

//Function declaration
FunctionPrototypeAST* parseFunctionPrototype(bool isDefined = false, FunctionRole functionRole = FunctionRole::Normal) {
    if (crntToken != TOKEN_IDENTIFIER) {
        logError("excpected function name");

        return nullptr;
    }
    std::string functionName = identifierStr;
    getNextToken(); //function name

    if (crntToken != '(') {
        logError("expected '(' after function name");

        return nullptr;
    }

    std::vector<Argument> arguments;
    do {
        if (getNextToken() == TOKEN_IDENTIFIER) {
            std::string name = identifierStr;
            if (getNextToken() == ':') {
                getNextToken(); // ':'
                irb::Attributes argAttributes;
                irb::Type* type = _parseTypeWithAttributesExpression(&argAttributes);
                if (!type)
                    return nullptr;
                arguments.push_back(Argument{name, type, argAttributes});
            } else {
                logError("expected argument type");

                return nullptr;
            }
        } else
            break;
    } while (crntToken == ',');
    if (crntToken != ')') {
        logError("expected ')' to match the '('");

        return nullptr;
    }

    irb::Type* functionType = createScalarType(TOKEN_TYPE_VOID);
    irb::Attributes attributes;
    if (getNextToken() == TOKEN_OPERATOR_FUNCTION_RETURN_TYPE) {
        /*
        if (getNextToken() != '>') {
            logError(("use of unexpected '-" + std::string(1, char(crntToken)) + "' after function prototype").c_str());

            return nullptr;
        }
        */

        getNextToken(); // '->'

        /*
        if (!tokenIsType(crntToken)) {
            logError("expected function type");

            return nullptr;
        }
        */
        functionType = _parseTypeWithAttributesExpression(&attributes);
    }

    return new FunctionPrototypeAST(functionName, functionType, arguments/*, attributes*/, isDefined, functionRole);
}

//TODO: support forward declarations
//Function definition
FunctionDefinitionAST* parseFunctionDefinition(FunctionRole functionRole = FunctionRole::Normal) {
    getNextToken(); // 'func' or 'entry_point'
    FunctionPrototypeAST* declaration = parseFunctionPrototype(true, functionRole);
    if (!declaration)
        return nullptr;
    
    if (ExpressionAST* expr = parseExpression())
        return new FunctionDefinitionAST(declaration, static_cast<BlockExpressionAST*>(expr));
    
    return nullptr;
}

//Extern
FunctionPrototypeAST* parseExtern() {
    getNextToken(); // 'extern'

    return parseFunctionPrototype();
}

//TODO: support forward declaration
//Structure declaration
StructureDefinitionAST* parseStructureDeclaration() {
    getNextToken(); // 'struct'
    if (crntToken != TOKEN_IDENTIFIER) {
        logError("expected structure name after 'struct'");
        return nullptr;
    }
    std::string structName = identifierStr;
    getNextToken(); //Structure name

    if (crntToken != '{') {
        logError("expected '{' after structure name");
        return nullptr;
    }
    getNextToken(); // '{'

    std::vector<irb::StructureMember> members;
    while (crntToken == TOKEN_MEMBER) {
        if (getNextToken() != TOKEN_IDENTIFIER) {
            logError("expected member name after 'member'");
            return nullptr;
        }
        std::string memberName = identifierStr;

        if (getNextToken() != ':') {
            logError("expected ':' after member name");
            return nullptr;
        }
        getNextToken(); // ':'
        irb::Attributes attributes;
        irb::Type* memberType = _parseTypeWithAttributesExpression(&attributes);
        members.push_back({memberName, memberType, attributes});

        while (crntToken == TOKEN_SKIP)
            getNextToken(); //Skip
    }

    if (crntToken != '}') {
        logError("expected '}' to match the '{'");
        return nullptr;
    }
    getNextToken(); // '}'

    return new StructureDefinitionAST(structName, members);
}

EnumDefinitionAST* parseEnumDeclaration() {
    getNextToken(); // 'enum'
    if (crntToken != TOKEN_IDENTIFIER) {
        logError("expected structure name after 'enum'");
        return nullptr;
    }
    std::string enumName = identifierStr;
    getNextToken(); //Enum name

    if (crntToken != '{') {
        logError("expected '{' after enum name");
        return nullptr;
    }
    getNextToken(); // '{'

    std::vector<EnumValue> values;
    bool needsComma = false;
    while (true) {
        bool hasComma = true;
        if (needsComma) {
            if (crntToken == ',')
                getNextToken(); // ','
            else
                hasComma = false;
        }

        if (crntToken != TOKEN_IDENTIFIER)
            break;
        if (!hasComma) {
            logError("expected ',' between enum values");
            return nullptr;
        }
        std::string valueName = identifierStr;

        long value;
        bool hasValue = false;
        if (getNextToken() == TOKEN_OPERATOR_ASSIGNMENT_ASSIGN) {
            if (getNextToken() != TOKEN_NUMBER) {
                logError("expected numeric value after '=' inside enum");
                return nullptr;
            }
            value = numValueL;
            hasValue = true;
            getNextToken(); //Value
        }
        if (!hasValue) {
            value = 0;
            while (true) {
                bool shouldContinue = false;
                for (auto& val : values) {
                    if (val.value == value)
                        shouldContinue = true;
                }
                if (shouldContinue) {
                    value += 1;
                    continue;
                }
                break;
            }
        }
        needsComma = true;

        values.push_back({valueName, value});
    }

    if (crntToken != '}') {
        logError("expected '}' to match the '{'");
        return nullptr;
    }
    getNextToken(); // '}'

    return new EnumDefinitionAST(enumName, values);
}

ExpressionAST* parseExpression(int expressionPrecedence) {
    while (crntToken == TOKEN_SKIP) {
        getNextToken(); //Skip
    }

    ExpressionAST* lhs = parseMain();
    if (!lhs)
        return nullptr;
    
    ExpressionAST* expr = parseBinOpRHS(expressionPrecedence, lhs);

    return expr;
}

//Main loop
void mainLoop() {
    while (true) {
        ExpressionAST* expression = nullptr;
        switch (crntToken) {
        case TOKEN_EOF:
            return;
        case TOKEN_SKIP:
            getNextToken(); // ';'
            break;
        case TOKEN_FUNC:
            expression = parseFunctionDefinition();
            break;
        case TOKEN_VERTEX:
            expression = parseFunctionDefinition(FunctionRole::Vertex);
            break;
        case TOKEN_FRAGMENT:
            expression = parseFunctionDefinition(FunctionRole::Fragment);
            break;
        case TOKEN_KERNEL:
            expression = parseFunctionDefinition(FunctionRole::Kernel);
            break;
        case TOKEN_EXTERN:
            expression = parseExtern();
            break;
        case TOKEN_VAR:
        case TOKEN_CONST:
            expression = parseVariableDeclarationExpression(true);
            break;
        case TOKEN_TYPE_STRUCT:
            expression = parseStructureDeclaration();
            break;
        case TOKEN_TYPE_ENUM:
            expression = parseEnumDeclaration();
            break;
        default:
            logError("unknown top level token '" + std::to_string(crntToken) + "'");
            getNextToken(); //For recovery
            break;
        }

        if (expression) {
            if (auto* value = expression->codegen()) {
                context.codeMain += value->getRawName() + "\n\n";
            }
        }
    }
}

inline void addStandardFuncion(const std::string& name, irb::Type* type, const std::vector<Argument>& arguments) {
    FunctionPrototypeAST* declaration = new FunctionPrototypeAST(name, type, arguments, false, FunctionRole::Normal, true);
    functionDeclarations[name] = declaration;
    declaration->codegen();
}

void compile(const std::string& sourceName) {
    switch (irb::target) {
    case irb::Target::None:
        IRB_ERROR("No target specified");
        break;
    case irb::Target::Metal:
        context.codeHeader = "#include <metal_stdlib>\nusing namespace metal;";
        break;
    case irb::Target::GLSL:
        context.codeHeader = "#version " + getGLSLVersionString() + " core";
        break;
    case irb::Target::HLSL:
        LVSLANG_ERROR_UNSUPPORTED_TARGET("HLSL");
        break;
    case irb::Target::SPIRV:
        builder = new irb::SPIRVBuilder(context, true);
        break;
    case irb::Target::AIR:
        //TODO: support other data layouts as well
        //TODO: target triple should be omitted so as to prevent llvm-opt errors
        context.codeHeader = \
        "source_filename = \"" + sourceName + "\"\n" \
        "target datalayout = \"e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32\"\n" \
        "target triple = \"air64-apple-macosx14.0.0\"";
        builder = new irb::AIRBuilder(context, true);
        break;
    default:
        LVSLANG_ERROR_UNSUPPORTED_TARGET("Unknown");
        break;
    }

    //Standard library
    addStandardFuncion("sin", createScalarType(TOKEN_TYPE_FLOAT), {{.type = createScalarType(TOKEN_TYPE_FLOAT)}});
    addStandardFuncion("sample", new irb::VectorType(context, createScalarType(TOKEN_TYPE_FLOAT), 4), {{.type = new irb::TextureType(context, irb::TextureViewType::_2D, createScalarType(TOKEN_TYPE_FLOAT))}, {.type = new irb::SamplerType(context)}, {.type = new irb::VectorType(context, createScalarType(TOKEN_TYPE_FLOAT), 2)}}); //TODO: overload this function?

    //Extensions
    //TODO: enable them only if needed
    enableExtension(irb::Extension::_8bit_storage);
    enableExtension(irb::Extension::_16bit_storage);
    enableExtension(irb::Extension::explicit_arithmetic_types);

    if (irb::target == irb::Target::SPIRV) {
        builder->opImportSTD_EXT("GLSL.std.450");
        builder->opMemoryModel();
    }

    getNextToken();
    mainLoop();
}

std::string getCompiledCode() {
    std::string code = context.codeHeader + "\n\n" + (TARGET_IS_IR(irb::target) ? builder->getCode() : context.codeMain);
    if (irb::target == irb::Target::AIR) {
        //TODO: remove all the hardcoding
        code += \
        "!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}\n" \
        "!air.vertex = !{!9}\n" \
        "!air.compile_options = !{!11, !12, !13}\n" \
        "!llvm.ident = !{!14}\n" \
        "!air.version = !{!15}\n" \
        "!air.language_version = !{!16}\n" \
        "!air.source_file_name = !{!17}\n" \
        "\n" \
        "!0 = !{i32 2, !\"SDK Version\", [2 x i32] [i32 14, i32 0]}\n" \
        "!1 = !{i32 1, !\"wchar_size\", i32 4}\n" \
        "!2 = !{i32 7, !\"frame-pointer\", i32 2}\n" \
        "!3 = !{i32 7, !\"air.max_device_buffers\", i32 31}\n" \
        "!4 = !{i32 7, !\"air.max_constant_buffers\", i32 31}\n" \
        "!5 = !{i32 7, !\"air.max_threadgroup_buffers\", i32 31}\n" \
        "!6 = !{i32 7, !\"air.max_textures\", i32 128}\n" \
        "!7 = !{i32 7, !\"air.max_read_write_textures\", i32 8}\n" \
        "!8 = !{i32 7, !\"air.max_samplers\", i32 16}\n" \
        "!9 = !{ptr @vertexMain, !10, !10}\n" \
        "!10 = !{}\n" \
        "!11 = !{!\"air.compile.denorms_disable\"}\n" \
        "!12 = !{!\"air.compile.fast_math_enable\"}\n" \
        "!13 = !{!\"air.compile.framebuffer_fetch_enable\"}\n" \
        "!14 = !{!\"Apple metal version 32023.35 (metalfe-32023.35)\"}\n" \
        "!15 = !{i32 2, i32 6, i32 0}\n" \
        "!16 = !{!\"Metal\", i32 3, i32 1, i32 0}\n" \
        "!17 = !{!\"/Users/samuliak/Desktop/lvslang/test.metal\"}\n" \
        "!18 = distinct !{!18, !19}\n" \
        "!19 = !{!\"llvm.loop.mustprogress\"}";
    }

    return code;
}

#endif
