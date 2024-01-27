#ifndef LVSLANG_AST_H
#define LVSLANG_AST_H

#include <limits>

#include "../../shader_ir_builder/spirv/ir.hpp"
#include "../../shader_ir_builder/air/ir.hpp"

namespace lvslang {

//Forward declarations
class FunctionPrototypeAST;

static GLSLVersion glslVersion = GLSLVersion::_1_10;

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
        for (uint8_t possibleBits = 8; possibleBits <= 32; possibleBits *= 2) {
            if (numBits <= possibleBits) {
                numBits = possibleBits;
                break;
            }
        }

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
static std::map<std::string, std::vector<FunctionPrototypeAST*> > functionDeclarations;
static std::map<std::string, Enumeration*> enumerations;

class EnumType : public irb::Type {
private:
    Enumeration* enumeration;

    std::string name;

public:
    EnumType(irb::Context& aContext, const std::string& aName) : Type(aContext), name(aName) {
        enumeration = enumerations[name];
        typeID = enumeration->type->getTypeID(); //HACK: set the typeID later
        //if (target != Target::GLSL)
        //    nameBegin = "struct ";

        if (!enumeration) {
            logError("use of undeclared enum '" + name + "'");
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
        return "enum_" + name;
    }

    uint32_t getBitCount(bool align = false) override {
        return enumeration->type->getBitCount();
    }

    irb::Type* getBaseType() override {
        return enumeration->type;
    }

    std::string getTemplateName() const override {
        return "e" + name;
    }

    std::string getNameBegin() const override {
        if (irb::target == irb::Target::Metal || irb::target == irb::Target::HLSL)
            return name;
        else if (irb::target == irb::Target::GLSL)
            return enumeration->type->getNameBegin();
        else if (irb::target == irb::Target::AIR)
            return enumeration->type->getName();
        else
            return "unknown";
    }

    //Getters
    inline Enumeration* getEnum() {
        return enumeration;
    }
};

std::string getGLSLVersionString() {
    LVSLANG_CHECK_ARGUMENT(GLSLVersion, glslVersion);
    std::string versionStr = glslVersionMap.at(glslVersion);

    switch (glslVersion) {
    case GLSLVersion::_1_10 ... GLSLVersion::_1_50:
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

struct IfThenBlock {
    ExpressionAST* condition;
    ExpressionAST* block;
};

//Base class
class ExpressionAST {
protected:
    uint32_t debugLine;
    uint32_t debugChar;

    bool loadOnCodegen = true;

public:
    ExpressionAST() {
        debugLine = source.crntLine;
        debugChar = source.crntChar;
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
        source.crntDebugLine = debugLine;
        source.crntDebugChar = debugChar;
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
        case irb::TypeID::Bool:
            value = new irb::ConstantBool(context, _valueU);
            break;
        case irb::TypeID::Integer:
            if (type->getIsSigned())
                value = new irb::ConstantInt(context, _valueL, type->getBitCount(), true);
            else
                value = new irb::ConstantInt(context, _valueU, type->getBitCount(), false);
            break;
        case irb::TypeID::Float:
            value = new irb::ConstantFloat(context, _valueD, type->getBitCount());
            break;
        default:
            logError("constant value is not bool, int or float");
            return nullptr;
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
                    //TODO: only load when needed? @ref shouldBeLoaded
                    irb::Type* type = value->getType()->getElementType();
                    //TODO: check if type is castable as well
                    std::string castBegin, castEnd;
                    if (requiredType && !requiredType->equals(type)) {
                        castBegin = requiredType->getName() + "(";
                        castEnd = ")";
                        type = requiredType;
                    }
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
        return true;
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
        irb::Type* lType = l->getType();
        if (op == "=") {
            if (auto* unloadedVector = dynamic_cast<UnloadedSwizzledVectorValue*>(l))
                lType = unloadedVector->getUnloadedVector()->getType()->getElementType()->getBaseType();
            else
                lType = lType->getElementType();
        }
        irb::Value* r = rhs->codegen(lType);
        if (!l || !r)
            return nullptr;

        if (op == "=") {
            if (TARGET_IS_IR(irb::target)) {
                if (auto* unloadedVector = dynamic_cast<UnloadedSwizzledVectorValue*>(l)) {
                    irb::Value* loadedVector = builder->opLoad(unloadedVector->getUnloadedVector());
                    if (r->getType()->isScalar()) {
                        for (auto index : unloadedVector->getIndices())
                            loadedVector = builder->opVectorInsert(loadedVector, r, new irb::ConstantInt(context, index, 32, true)); //TODO: should it be signed?
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
                    if (!r->getType()->equals(l->getType()->getElementType())) {
                        //TODO: use @ref getDebugName instead of @ref getName
                        logError("cannot assign to variable of type '" + l->getType()->getName() + "' from type '" + r->getType()->getName() + "'");
                        return nullptr;
                    }
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
        //TODO: move this to the codegen of l and r
        if (TARGET_IS_IR(irb::target)) {
            l = builder->opCast(l, type);
            r = builder->opCast(r, type);
        } else {
            if (!type->equals(l->getType()))
                l = new irb::Value(context, type, type->getName() + "(" + l->getRawName() + ")");
            if (!type->equals(r->getType()))
                r = new irb::Value(context, type, type->getName() + "(" + r->getRawName() + ")");
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
            operation = irb::Operation::Equal;
            type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
        } else if (op == "!=") {
            operation = irb::Operation::NotEqual;
            type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
        } else if (op == "&&") {
            operation = irb::Operation::And;
            type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
        } else if (op == "||") {
            operation = irb::Operation::Or;
            type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
        } else if (op == ">") {
            operation = irb::Operation::GreaterThan;
            type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
        } else if (op == "<") {
            operation = irb::Operation::LessThan;
            type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
        } else if (op == ">=") {
            operation = irb::Operation::GreaterThanEqual;
            type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
        } else if (op == "<=") {
            operation = irb::Operation::LessThanEqual;
            type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
        }

        if (TARGET_IS_CODE(irb::target)) {
            return new irb::Value(context, type, "(" + l->getRawName() + " " + op + " " + r->getRawName() + ")");
        } else {
            context.pushRegisterName("op");
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

//Function declaration
class FunctionPrototypeAST : public ExpressionAST {
private:
    std::string _name;
    irb::Type* type;
    std::vector<irb::Argument> _arguments;
    //std::vector<int> attributes;
    bool isDefined;
    bool isSTDFunction;
    irb::FunctionRole functionRole;

    irb::Value* value;
    irb::FunctionType* functionType;

    //For finding the correct overload
    std::string identifier;

public:
    FunctionPrototypeAST(const std::string& aName, irb::Type* aType, std::vector<irb::Argument> aArguments/*, const std::vector<int>& aAttributes*/, bool aIsDefined, bool aIsSTDFunction, irb::FunctionRole aFunctionRole) : _name(aName), type(aType), _arguments(aArguments)/*, attributes(aAttributes)*/, isDefined(aIsDefined), isSTDFunction(aIsSTDFunction), functionRole(aFunctionRole) {
        uint32_t bufferBinding = 0, textureBinding = 0, samplerBinding = 0;
        for (uint32_t i = 0; i < _arguments.size(); i++) {
            irb::Argument& arg = _arguments[i];
            auto& attr = arg.attributes;
            if (attr.addressSpace != 0) {
                irb::PointerType* pointerType = dynamic_cast<irb::PointerType*>(arg.type);
                if (!pointerType) {
                    logError("only pointers can be used with an address space");
                    return;
                }
                pointerType->setAddressSpace(attr.addressSpace);
            }
            if (functionRole != irb::FunctionRole::Normal) {
                //TDOO: save the bindings for reflection
                if (arg.type->isTexture()) {
                    attr.isTexture = true;
                    attr.bindings.texture = textureBinding++;
                } else if (arg.type->isSampler()) {
                    attr.isSampler = true;
                    attr.bindings.sampler = samplerBinding++;
                } else if (!attr.isInput) {
                    irb::PointerType* pointerType = dynamic_cast<irb::PointerType*>(arg.type);
                    if (!pointerType) {
                        logError("only pointers can be used as buffers");
                        return;
                    }
                    attr.isBuffer = true;
                    attr.bindings.buffer = bufferBinding++;
                    if ((irb::target == irb::Target::SPIRV || irb::target == irb::Target::GLSL || irb::target == irb::Target::HLSL) && functionRole != irb::FunctionRole::Normal)
                        arg.type = arg.type->getElementType();
                    pointerType->addAttribute(" noundef \"air-buffer-no-alias\"");
                }
            }
        }

        std::vector<irb::Type*> argumentTypes;
        argumentTypes.resize((_arguments.size()));
        for (uint32_t i = 0; i < argumentTypes.size(); i++)
            argumentTypes[i] = _arguments[i].type;
        functionType = new irb::FunctionType(context, type, argumentTypes);

        identifier = functionType->getTemplateName();
    }

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        functionDeclarations[_name].push_back(this);

        if (TARGET_IS_CODE(irb::target)) {
            if (isSTDFunction)
                return new irb::Value(context, nullptr, "");
                
            std::string codeStr;
            std::string argsStr;
            std::string entryPointStr;
            for (uint32_t i = 0; i < _arguments.size(); i++) {
                irb::Argument& arg = _arguments[i];
                auto& attr = arg.attributes;
                if (i != 0)
                    argsStr += ", ";
                if (irb::target == irb::Target::Metal) {
                    std::string addressSpace;
                    if (attr.addressSpace == 2)
                        addressSpace = "constant ";
                    else if (attr.addressSpace == 1)
                        addressSpace = "device ";
                    
                    std::string attribute;
                    if (attr.isBuffer)
                        attribute = " [[buffer(" + std::to_string(attr.bindings.buffer) + ")]]";
                    if (attr.isTexture)
                        attribute = " [[texture(" + std::to_string(attr.bindings.texture) + ")]]";
                    if (attr.isSampler)
                        attribute = " [[sampler(" + std::to_string(attr.bindings.sampler) + ")]]";
                    if (attr.isInput)
                        attribute = " [[stage_in]]";

                    argsStr += addressSpace + arg.type->getName() + " " + arg.name + attribute;
                } else if (irb::target == irb::Target::HLSL) {
                    argsStr += arg.type->getName() + " " + arg.name;

                    //Entry point
                    if (functionRole != irb::FunctionRole::Normal) {
                        if (!attr.isInput) {
                            if (attr.isBuffer) {
                                entryPointStr += "cbuffer "; //TODO: support other types of buffer as well
                                //We need to get element type, since HLSL treats it without pointer
                                entryPointStr += arg.name + "_Uniform : register(b" + std::to_string(attr.bindings.buffer) + ") {\n\t" + arg.type->getName() + " " + arg.name + ";\n}";
                            } else if (attr.isTexture) {
                                entryPointStr += arg.type->getName() + " " + arg.name + " : register(t" + std::to_string(attr.bindings.sampler) + ")";
                            } else if (attr.isSampler) {
                                entryPointStr += arg.type->getName() + " " + arg.name + " : register(s" + std::to_string(attr.bindings.sampler) + ")";
                            }
                            entryPointStr += ";\n\n";
                        }
                    }
                } else {
                    argsStr += arg.type->getName() + " " + arg.name;

                    //Entry point
                    if (functionRole != irb::FunctionRole::Normal) {
                        std::string typeName;
                        if (attr.isInput) {
                            switch (functionRole) {
                            case irb::FunctionRole::Vertex:
                                //TODO: do this error check for every backend?
                                if (!arg.type->isStructure()) {
                                    logError("Entry point argument declared with the 'input' attribute must have a structure type");
                                    return nullptr;
                                }
                                for (const auto& member : static_cast<irb::StructureType*>(arg.type)->getStructure()->members)
                                    entryPointStr += "layout (location = " + std::to_string(member.attributes.locationIndex) + ") in " + member.type->getName() + " " + member.name + ";\n\n";
                                break;
                            case irb::FunctionRole::Fragment:
                                entryPointStr += "layout (location = 0) in " + arg.type->getName() + "_Input {\n\t" + arg.type->getName() + " " + arg.name + ";\n};\n\n";
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
                                typeName += arg.name + "_Uniform {\n\t" + arg.type->getName() + " " + arg.name + ";\n}";
                            } else {
                                typeName = "uniform " + arg.type->getName();
                            }
                            entryPointStr += "layout (set = " + std::to_string(attr.bindings.set) + ", binding = " + std::to_string(attr.bindings.binding) + ") " + typeName;
                            if (!attr.isBuffer)
                                entryPointStr += " " + arg.name;
                            entryPointStr += ";\n\n";
                        }
                    }
                }
            }

            if (functionRole != irb::FunctionRole::Normal) {
                if (irb::target == irb::Target::Metal) {
                    switch (functionRole) {
                    case irb::FunctionRole::Vertex:
                        codeStr = "vertex ";
                        break;
                    case irb::FunctionRole::Fragment:
                        codeStr = "fragment ";
                        break;
                    case irb::FunctionRole::Kernel:
                        codeStr = "kernel ";
                        break;
                    default:
                        break;
                    }
                } else if (irb::target == irb::Target::HLSL) {
                    if (type->getTypeID() != irb::TypeID::Void) {
                        entryPointStr += "struct " + type->getName() + "_Output {\n\t" + type->getName() + " output : TEXCOORD0;\n";
                        if (functionRole == irb::FunctionRole::Vertex)
                            entryPointStr += "\tfloat4 position : SV_Position;\n";
                        entryPointStr += "};\n\n";
                    }

                    //Entry point
                    std::string argsStr;
                    for (const auto& argument : _arguments) {
                        if (argument.attributes.isInput) {
                            argsStr += argument.type->getName() + " " + argument.name;
                            break;
                        }
                    }
                    entryPointStr += type->getName() + "_Output _" + _name + "(" + argsStr + ") {\n";

                    //-------- Entry point call --------
                    entryPointStr += "\t//Entry point call\n";
                    std::string outputVarName = "_entryPointOutput";
                    entryPointStr += "\t" + (type->getTypeID() == irb::TypeID::Void ? "" : type->getName() + " " + outputVarName + " = ") + _name + "(";
                    for (uint32_t i = 0; i < _arguments.size(); i++) {
                        if (i != 0)
                            entryPointStr += ", ";
                        entryPointStr += _arguments[i].name;
                    }
                    entryPointStr += ");\n";

                    //-------- Output --------
                    if (type->getTypeID() != irb::TypeID::Void) {
                        entryPointStr += "\n\t//Output\n\t" + type->getName() + "_Output __output;\n\t__output.output = " + outputVarName + ";\n";
                        if (functionRole == irb::FunctionRole::Vertex) {
                            //TODO: support non-structure types as well
                            if (!type->isStructure()) {
                                logError("Entry point output must have a structure type");
                                return nullptr;
                            }
                            irb::Structure* structure = static_cast<irb::StructureType*>(type)->getStructure();
                            for (const auto& member : structure->members) {
                                if (member.attributes.isPosition) {
                                    entryPointStr += "\t__output.position = " + outputVarName + "." + member.name + ";\n";
                                    break;
                                }
                            }
                        }
                        entryPointStr += "\n\treturn __output;\n";
                    }

                    entryPointStr += "}\n\n";
                } else if (irb::target == irb::Target::GLSL) {
                    switch (functionRole) {
                    case irb::FunctionRole::Vertex:
                        entryPointStr += "layout (location = 0) out " + type->getName() + "_Output {\n\t" + type->getName() + " _output;\n} _output;\n\n";
                        break;
                    case irb::FunctionRole::Fragment:
                        //TODO: do this error check for every backend?
                        if (!type->isStructure()) {
                            logError("Entry point argument declared with the 'input' attribute must have a structure type");
                            return nullptr;
                        }
                        for (const auto& member : static_cast<irb::StructureType*>(type)->getStructure()->members)
                            entryPointStr += "layout (location = " + std::to_string(member.attributes.colorIndex) + ") out " + member.type->getName() + " " + member.name + ";\n\n";
                        break;
                    default:
                        logError("cannot use the 'output' attribute for kernel function");
                        return nullptr;
                    }

                    //Entry point
                    entryPointStr += "void main() {\n";

                    //-------- Input --------
                    entryPointStr += "\t//Input\n";
                    for (uint32_t i = 0; i < _arguments.size(); i++) {
                        if (functionRole == irb::FunctionRole::Vertex && _arguments[i].attributes.isInput) {
                            //TODO: throw an error if not structure?
                            irb::StructureType* structureType = dynamic_cast<irb::StructureType*>(_arguments[i].type);
                            //HACK: just assemble the input structure
                            entryPointStr += "\t" + structureType->getName() + " " + _arguments[i].name + ";\n";
                            for (const auto& member : structureType->getStructure()->members)
                                entryPointStr += "\t" + _arguments[i].name + "." + member.name + " = " + member.name + ";\n";
                        }
                    }
                    entryPointStr += "\n";

                    //-------- Entry point call --------
                    entryPointStr += "\t//Entry point call\n";
                    std::string outputVarName = "_entryPointOutput";
                    entryPointStr += "\t" + (type->getTypeID() == irb::TypeID::Void ? "" : type->getName() + " " + outputVarName + " = ") + _name + "(";
                    for (uint32_t i = 0; i < _arguments.size(); i++) {
                        if (i != 0)
                            entryPointStr += ", ";
                        entryPointStr += _arguments[i].name;
                    }

                    //-------- Output --------
                    if (type->getTypeID() != irb::TypeID::Void) {
                        entryPointStr += ");\n\n\t//Output\n";

                        //TODO: support other types besides structure
                        if (!type->isStructure()) {
                            logError("Only structures can be returned from an entry point function");
                            return nullptr;
                        }
                        irb::StructureType* structType = static_cast<irb::StructureType*>(type);
                        irb::Structure* structure = structType->getStructure();

                        for (uint32_t i = 0; i < structure->members.size(); i++) {
                            const irb::StructureMember& member = structure->members[i];
                            std::string memberStr = outputVarName + "." + member.name;
                            entryPointStr += "\t";
                            if (member.attributes.isPosition) {
                                entryPointStr += "gl_Position = " + memberStr + ";\n\t";
                            }
                            switch (functionRole) {
                            case irb::FunctionRole::Vertex:
                                entryPointStr += "_output._output." + member.name + " = " + memberStr;
                                break;
                            case irb::FunctionRole::Fragment:
                                entryPointStr += member.name + " = " + memberStr;
                                break;
                            default:
                                logError("'kernel' functions cannot return a value");
                                break;
                            }
                            entryPointStr += ";\n";
                        }
                    }
                    
                    entryPointStr += "}\n\n";
                }
            }
            codeStr += type->getName() + " " + _name + "(" + argsStr + ")";
            if ((irb::target == irb::Target::GLSL || irb::target == irb::Target::HLSL) && functionRole != irb::FunctionRole::Normal)
                codeStr += ";\n\n" + entryPointStr + codeStr;
            if (!isDefined)
                codeStr += ";";
            
            return new irb::Value(context, type, codeStr);
        } else {
            /*if (isSTDFunction) {
                std::string regName = _name;
                regName[0] = toupper(regName[0]);
                regName = "import " + regName;
                value = new irb::Value(context, nullptr, regName);
            } else {*/
            if (isSTDFunction) {
                value = builder->opStandardFunctionDeclaration(functionType, _name);
            } else {
                context.pushRegisterName(_name);
                value = builder->opRegisterFunction(functionType);
            }
            builder->opName(value, _name + "(");

            return new irb::Value(context, functionType);
        }
    }

    //Getters
    inline const std::string& name() const {
        return _name;
    }

    inline const std::vector<irb::Argument>& arguments() const {
        return _arguments;
    }

    inline irb::Attributes& getArgumentAttributes(uint32_t index) {
        return _arguments[index].attributes;
    }

    inline irb::Type* getType() const {
        return type;
    }

    inline irb::FunctionRole getFunctionRole() const {
        return functionRole;
    }

    inline irb::Value* getValue() const {
        return value;
    }

    inline irb::FunctionType* getFunctionType() const {
        return functionType;
    }

    inline bool getIsSTDFunction() const {
        return isSTDFunction;
    }

    inline const std::string& getIdentifier() const {
        return identifier;
    }
    
    //Setters
    inline void setIsDefined(bool aIsDefined) {
        isDefined = aIsDefined;
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
            value = builder->opFunction(functionType, declaration->getValue());
            if (declaration->getFunctionRole() != irb::FunctionRole::Normal) {
                builder->opEntryPoint(value, declaration->getFunctionRole(), declaration->name(), declaration->getType(), declaration->arguments());
                if (irb::target == irb::Target::SPIRV && declaration->getType()->getTypeID() != irb::TypeID::Void) {
                    //builder->opAddInterfaceVariable(declaration->getReturnVariable()); //TODO: change this to static cast?
                    //if (declaration->getFunctionRole() == FunctionRole::Vertex)
                    //    builder->opAddInterfaceVariable(declaration->getPositionVariable());
                }
            }
        }

        for (uint32_t i = 0; i < declaration->arguments().size(); i++) {
            auto& arg = declaration->arguments()[i];
            if (arg.name != "") {
                if (TARGET_IS_CODE(irb::target)) {
                    irb::Value* value = new irb::Value(context, new irb::PointerType(context, arg.type, irb::StorageClass::Function), arg.name);
                    variables[arg.name] = {value, false};
                } else {
                    auto& attr = declaration->getArgumentAttributes(i);
                    context.pushRegisterName(arg.name);
                    irb::Type* type = arg.type;
                    irb::Value* argValue = builder->opFunctionParameter(type);
                    variables[arg.name] = {argValue, false};
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
            //bodyStr = bodyStr.substr(0, 2) + functionHeader + bodyStr.substr(2);
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

public:
    CallExpressionAST(const std::string& aCallee, std::vector<ExpressionAST*> aArguments) : callee(aCallee), arguments(aArguments) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        if (functionDeclarations.count(callee)) {
            const auto& declarations = functionDeclarations[callee];
            FunctionPrototypeAST* declaration = nullptr;
            std::string argsStr;
            std::vector<irb::Value*> argVs(arguments.size());
            for (uint32_t i = 0; i < arguments.size(); i++) {
                ExpressionAST* arg = arguments[i];
                argVs[i] = arg->codegen(declarations.size() == 1 ? declarations[0]->arguments()[i].type : nullptr);
                if (!argVs[i])
                    return nullptr;
                if (i != 0)
                    argsStr += ", ";
                argsStr += argVs[i]->getRawName();
            }

            std::string identifier;
            //TODO: move this to a separate function?
            for (auto* argV : argVs)
                identifier += (irb::target == irb::Target::AIR ? "." : "_") + argV->getType()->getTemplateName();

            //Find suitable function overload
            if (declarations.size() == 1) {
                declaration = declarations[0];

                if (declaration->arguments().size() != arguments.size()) {
                    logError(("Expected " + std::to_string(declaration->arguments().size()) + " arguments, got " + std::to_string(arguments.size()) + " instead").c_str());
                    return nullptr;
                }
                
                if (identifier != declaration->getIdentifier()) {
                    for (uint32_t i = 0; i < arguments.size(); i++) {
                        if (!argVs[i]->getType()->equals(declaration->arguments()[i].type)) {
                            logError(("Argument " + std::to_string(i + 1) + " of function '" + callee + "' has type '" + declaration->arguments()[i].type->getName() + "', got '" + argVs[i]->getType()->getName() + "' instead").c_str());
                            return nullptr;
                        }
                    }
                }
            } else {
                for (auto* decl : declarations) {
                    if (identifier == decl->getIdentifier()) {
                        declaration = decl;
                        break;
                    }
                }
                if (!declaration) {
                    logError("no matching function overload found");
                    return nullptr;
                }
            }

            for (uint32_t i = 0; i < arguments.size(); i++) {
                if (irb::target == irb::Target::SPIRV && !declaration->getIsSTDFunction()) {
                    context.pushRegisterName("param");
                    argVs[i] = builder->opVariable(new irb::PointerType(context, argVs[i]->getType(), irb::StorageClass::Function), argVs[i]);
                }
            }

            if (TARGET_IS_CODE(irb::target)) {
                std::string code;
                if (callee == "sample") {
                    switch (irb::target) {
                    case irb::Target::Metal:
                        code = argVs[0]->getRawName() + ".sample(" + argVs[1]->getRawName() + ", " + argVs[2]->getRawName() + ")";
                        break;
                    case irb::Target::HLSL:
                        code = argVs[0]->getRawName() + ".SampleLevel(" + argVs[1]->getRawName() + ", " + argVs[2]->getRawName() + ", 0.0f)";
                        break;
                    case irb::Target::GLSL:
                        code = "texture(sampler2D(" + argVs[0]->getRawName() + ", " + argVs[1]->getRawName() + "), " + argVs[2]->getRawName() + ")"; //TODO: support other samplers + textures as well
                        break;
                    default:
                        break;
                    }
                } else {
                    code = callee + "(" + argsStr + ")";
                }

                return new irb::Value(context, declaration->getType(), code);
            } else {
                if (callee == "sample")
                    return builder->opSample(declaration->getValue(), argVs[0], argVs[1], argVs[2]);

                return builder->opFunctionCall(declaration->getValue(), argVs);
            }
        } else {
            logError(("Use of undeclared function '" + callee + "'").c_str());
            return nullptr;
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
        irb::Value* returnV = expression->codegen(funcReturnType->getTypeID() == irb::TypeID::Void ? nullptr : funcReturnType);
        if (!returnV)
            return nullptr;

        if (TARGET_IS_CODE(irb::target)) {
            return new irb::Value(context, returnV->getType(), "return " + returnV->getRawName());
        } else {
            returnV = builder->opCast(returnV, funcReturnType);
            builder->opReturn(returnV);

            return returnV;
        }
    }
};

//If
class IfExpressionAST : public ExpressionAST {
private:
    std::vector<IfThenBlock*> ifThenBlocks;
    ExpressionAST* elseBlock;

public:
    IfExpressionAST(const std::vector<IfThenBlock*>& aIfThenBlocks, ExpressionAST* aElseBlock) : ifThenBlocks(aIfThenBlocks), elseBlock(aElseBlock) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        if (TARGET_IS_CODE(irb::target)) {
            std::string codeStr;
            for (uint32_t i = 0; i < ifThenBlocks.size(); i++) {
                if (i != 0)
                    codeStr += " else ";
                codeStr += "if (";
                irb::Value* condV = ifThenBlocks[i]->condition->codegen(new irb::ScalarType(context, irb::TypeID::Bool, 8, false));
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
                irb::Value* condV = ifThenBlocks[i]->condition->codegen(new irb::ScalarType(context, irb::TypeID::Bool, 8, false));
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
    ExpressionAST* block;

    bool isDoWhile;

public:
    WhileExpressionAST(ExpressionAST* aCondition, ExpressionAST* aBlock, bool aIsDoWhile) : condition(aCondition), block(aBlock), isDoWhile(aIsDoWhile) {}

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
        
        irb::Value* condV = condition->codegen(new irb::ScalarType(context, irb::TypeID::Bool, 8, false));
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
                
                if (type && !initV->getType()->equals(type)) {
                    //TODO: use @ref getDebugName instead of @ref getName
                    logError("cannot initialize variable of type '" + type->getName() + "' with value of type '" + initV->getType()->getName() + "'");
                    return nullptr;
                }
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

//TODO: get rid of this and replace it with @ref InitializerListAST?
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

        type = new irb::ArrayType(context, new irb::ScalarType(context, irb::TypeID::Integer, 8, true), values.size());

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
    bool exprShouldBeLoadedBeforeAccessingMember;

    irb::PointerType* type = nullptr;

public:
    MemberAccessExpressionAST(ExpressionAST* aExpression, const std::string& aMemberName, bool aExprShouldBeLoadedBeforeAccessingMember) : expression(aExpression), memberName(aMemberName), exprShouldBeLoadedBeforeAccessingMember(aExprShouldBeLoadedBeforeAccessingMember) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        expression->setLoadOnCodegen(false);
        irb::Value* exprV = expression->codegen();
        if (exprShouldBeLoadedBeforeAccessingMember) {
            if (irb::target == irb::Target::AIR)
                exprV = builder->opLoad(exprV);
            else if (irb::target == irb::Target::Metal)
                exprV = new irb::Value(context, exprV->getType()->getElementType(), "(*" + exprV->getRawName() + ")");
        }
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
                    type = new irb::PointerType(context, structure->members[memberIndex].type, exprType->getStorageClass()); //TODO: move this to structure definition?
                    break;
                }
            }

            if (!type) {
                logError("structure '" + elementExprType->getName() + "' has no member named '" + memberName + "'");
                return nullptr;
            }

            if (TARGET_IS_CODE(irb::target)) {
                return new irb::Value(context, (loadOnCodegen ? type->getElementType() : type), exprV->getRawName() + "." + memberName);
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
                if (member.attributes.colorIndex != -1)
                    attributesEnd += " [[color(" + std::to_string(member.attributes.colorIndex) + ")]]";
            } else if (irb::target == irb::Target::HLSL) {
                //TODO: add commas between attributes
                //TODO: uncomment?
                //if (member.attributes.isPosition)
                //    attributesEnd += " : SV_Position";
                if (member.attributes.locationIndex != -1)
                    attributesEnd += " : TEXCOORD" + std::to_string(member.attributes.locationIndex); //TODO: don't always use texcoord?
                if (member.attributes.colorIndex != -1)
                    attributesEnd += " : SV_Target" + std::to_string(member.attributes.colorIndex); //TODO: check if this is correct
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
        if (irb::target == irb::Target::Metal || irb::target == irb::Target::HLSL) {
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
            if (irb::target == irb::Target::Metal || irb::target == irb::Target::HLSL)
                return new irb::Value(context, enumeration->type, value.name);
            else
                return new irb::Value(context, enumeration->type, std::to_string(value.value));
        }
    }
};

//TODO: support other initializer lists as well (for instance sampler)
//TODO: support vector to vector conversion in HLSL
class InitializerListExpressionAST : public ExpressionAST {
private:
    irb::Type* type;
    std::vector<ExpressionAST*> expressions;

public:
    InitializerListExpressionAST(irb::Type* aType, std::vector<ExpressionAST*> aExpressions) : type(aType), expressions(aExpressions) {}

    irb::Value* codegen(irb::Type* requiredType = nullptr) override {
        setDebugInfo();

        std::vector<irb::Value*> components;
        components.reserve(expressions.size());
        for (auto* expression : expressions) {
            irb::Value* component = expression->codegen();
            if (!component)
                return nullptr;
            if (TARGET_IS_IR(irb::target))
                component = builder->opCast(component, (type->isScalar() ? type : type->getBaseType()));
            components.push_back(component);
        }
        
        //"Unpack" the vectors
        for (uint32_t i = 0; i < components.size(); i++) {
            irb::Value* component = components[i];
            if (auto vectorType = dynamic_cast<irb::VectorType*>(component->getType())) {
                components.erase(components.begin() + i);
                for (uint8_t j = 0; j < vectorType->getComponentCount(); j++) {
                    irb::Value* vectorComponent;
                    if (TARGET_IS_IR(irb::target))
                        vectorComponent = builder->opCast(builder->opVectorExtract(component, new irb::ConstantInt(context, j, 32, true)), type->getBaseType());
                    else
                        vectorComponent = new irb::Value(context, vectorType->getBaseType(), component->getRawName() + "[" + std::to_string(j) + "]");
                    components.insert(components.begin() + i + j, vectorComponent);
                }
            }
        }

        if (type->isScalar()) {
            if (components.size() != 1) {
                logError("scalar initializer list must have exactly one value");
                return nullptr;
            }
        } else if (type->isArray()) {
            uint32_t size = static_cast<irb::ArrayType*>(type)->getSize();
            if (components.size() > size) {
                logError("array initializer cannot be larger than the array itself (" + std::to_string(components.size()) + " > " + std::to_string(size) + ")");
                return nullptr;
            }
        } else if (type->isVector()) {
            uint32_t componentCount = static_cast<irb::VectorType*>(type)->getComponentCount();
            if (components.size() > componentCount) {
                logError("vector initializer cannot be larger than the vector itself (" + std::to_string(components.size()) + " > " + std::to_string(componentCount) + ")");
                return nullptr;
            }
            if (components.size() != componentCount && components.size() != 1) {
                logError("not enough components in initializer to construct a vector (got " + std::to_string(components.size()) + ", expected either " + std::to_string(componentCount) + " or 1)");
                return nullptr;
            }
        } else {
            logError("cannot use initializer list to create a type '" + type->getName() + "'"); //TODO: get the name in a different way?
            return nullptr;
        }

        if (TARGET_IS_IR(irb::target)) {
            if (type->isScalar())
                return builder->opCast(components[0], type);
            if (type->isArray()) {
                //TODO: implement this
                logError("array initializer lists are not supported for IR backends yet");
                return nullptr;
            }
            if (type->isVector()) {
                irb::VectorType* vectorType = static_cast<irb::VectorType*>(type);
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

} //namespace lvslang

#endif
