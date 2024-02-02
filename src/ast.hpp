#ifndef LVSLANG_AST_H
#define LVSLANG_AST_H

#include <limits>

#include "common.hpp"

#include "../shader_ir_builder/spirv/ir.hpp"
#include "../shader_ir_builder/air/ir.hpp"

namespace lvslang {

//Forward declarations
class FunctionPrototypeAST;

extern irb::Context context;
extern irb::IRBuilder* builder;

extern GLSLVersion glslVersion;

extern FunctionPrototypeAST* crntFunction;
extern uint32_t currentIndentation;

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

extern std::map<std::string, Variable> variables;
extern std::map<std::string, std::vector<FunctionPrototypeAST*> > functionDeclarations;
extern std::map<std::string, Enumeration*> enumerations;

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

    std::string getDebugName() const override {
        return "enum " + name;
    }

    //Getters
    inline Enumeration* getEnum() {
        return enumeration;
    }
};

inline std::string getGLSLVersionString() {
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

inline bool typeIsPromoted(irb::TypeID a, irb::TypeID b) {
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

inline irb::Type* getPromotedType(irb::Type* a, irb::Type* b) {
    return (typeIsPromoted(a->getTypeID(), b->getTypeID()) ? a : b);
}

//Base class
class ExpressionAST {
protected:
    uint32_t debugLine;
    uint32_t debugChar;

    bool loadOnCodegen = true;

    virtual irb::Value* _codegen(irb::Type* requiredType = nullptr) = 0;

public:
    ExpressionAST() {
        debugLine = source.crntLine;
        debugChar = source.crntChar;
    }

    virtual ~ExpressionAST() = default;

    irb::Value* codegen(irb::Type* requiredType = nullptr) {
        setDebugInfo();

        irb::Value* value = _codegen(requiredType);
        if (!value)
            return nullptr;
        if (requiredType) {
            if (TARGET_IS_IR(irb::target))
                return builder->opCast(value, requiredType);
            else if (!value->getType()->equals(requiredType))
                return new irb::Value(context, requiredType, requiredType->getName() + "(" + value->getRawName() + ")");
        }
        
        return value;
    }

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

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;

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

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;

    bool isVariable() override {
        return true;
    }

    std::string& name() { return _name; }
};

//TODO: rename to OperationAST?
//Operation
class BinaryExpressionAST : public ExpressionAST {
private:
    std::string op;
    ExpressionAST* lhs;
    ExpressionAST* rhs;

public:
    BinaryExpressionAST(const std::string& aOperator, ExpressionAST* aLHS, ExpressionAST* aRHS) : op(aOperator), lhs(aLHS), rhs(aRHS) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//Block
class BlockExpressionAST : public ExpressionAST {
private:
    std::vector<ExpressionAST*> expressions;

public:
    BlockExpressionAST(std::vector<ExpressionAST*> aExpressions) : expressions(aExpressions) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override {
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

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;

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

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//Function call
class CallExpressionAST : public ExpressionAST {
private:
    std::string callee;
    std::vector<ExpressionAST*> arguments;

public:
    CallExpressionAST(const std::string& aCallee, std::vector<ExpressionAST*> aArguments) : callee(aCallee), arguments(aArguments) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//Return
class ReturnExpressionAST : public ExpressionAST {
private:
    ExpressionAST* expression;

public:
    ReturnExpressionAST(ExpressionAST* aExpression) : expression(aExpression) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//If
struct IfThenBlock {
    ExpressionAST* condition;
    ExpressionAST* block;
};

//TODO: rename?
class IfExpressionAST : public ExpressionAST {
private:
    std::vector<IfThenBlock*> ifThenBlocks;
    ExpressionAST* elseBlock;

public:
    IfExpressionAST(const std::vector<IfThenBlock*>& aIfThenBlocks, ExpressionAST* aElseBlock) : ifThenBlocks(aIfThenBlocks), elseBlock(aElseBlock) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//Inline if else
class InlineIfElseExpressionAST : public ExpressionAST {
private:
    ExpressionAST* condition;
    BlockExpressionAST* thenBlock;
    BlockExpressionAST* elseBlock;

public:
    InlineIfElseExpressionAST(ExpressionAST* aCondition, BlockExpressionAST* aThenBlock, BlockExpressionAST* aElseBlock) : condition(aCondition), thenBlock(aThenBlock), elseBlock(aElseBlock) {}

    //TODO: implement this
    irb::Value* _codegen(irb::Type* requiredType = nullptr) override {
        return nullptr;
    }
};

//TODO: rename to WhileLoopAST?
//While
class WhileExpressionAST : public ExpressionAST {
private:
    ExpressionAST* condition;
    ExpressionAST* block;

    bool isDoWhile;

public:
    WhileExpressionAST(ExpressionAST* aCondition, ExpressionAST* aBlock, bool aIsDoWhile) : condition(aCondition), block(aBlock), isDoWhile(aIsDoWhile) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//Variable declaration
struct VariableDeclaration {
    std::string name;
    irb::Type* type;
    ExpressionAST* expression;
};

//TODO: rename to VariableDeclarationAST?
class VariableDeclarationExpressionAST : public ExpressionAST {
private:
    std::vector<VariableDeclaration> variableNames;
    bool isGlobal;
    bool isConstant;

public:
    VariableDeclarationExpressionAST(const std::vector<VariableDeclaration>& aVariableNames, bool aIsGlobal, bool aIsConstant) : variableNames(aVariableNames), isGlobal(aIsGlobal), isConstant(aIsConstant) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//Subscript
class SubscriptExpressionAST : public ExpressionAST {
private:
    ExpressionAST* ptr;
    ExpressionAST* index;

    irb::PointerType* type;

public:
    SubscriptExpressionAST(ExpressionAST* aPtr, ExpressionAST* aIndex) : ptr(aPtr), index(aIndex) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//TODO: rename to MemberAccessAST?
//Member access
class MemberAccessExpressionAST : public ExpressionAST {
private:
    ExpressionAST* expression;
    std::string memberName;
    bool exprShouldBeLoadedBeforeAccessingMember;

    irb::PointerType* type = nullptr;

public:
    MemberAccessExpressionAST(ExpressionAST* aExpression, const std::string& aMemberName, bool aExprShouldBeLoadedBeforeAccessingMember) : expression(aExpression), memberName(aMemberName), exprShouldBeLoadedBeforeAccessingMember(aExprShouldBeLoadedBeforeAccessingMember) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//Structure definition
class StructureDefinitionAST : public ExpressionAST {
private:
    std::string name;
    std::vector<irb::StructureMember> members;

public:
    StructureDefinitionAST(const std::string& aName, const std::vector<irb::StructureMember>& aMembers) : name(aName), members(aMembers) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//Enumeration definition
class EnumDefinitionAST : public ExpressionAST {
private:
    std::string name;
    std::vector<EnumValue> values;

public:
    EnumDefinitionAST(const std::string& aName, const std::vector<EnumValue>& aValues) : name(aName), values(aValues) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//TODO: rename?
//Enumeration value
class EnumValueExpressionAST : public ExpressionAST {
private:
    Enumeration* enumeration;
    EnumValue& value;

public:
    EnumValueExpressionAST(Enumeration* aEnumeration, EnumValue& aValue) : enumeration(aEnumeration), value(aValue) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;
};

//TODO: support other initializer lists as well (for instance sampler)
//TODO: support vector to vector conversion in HLSL
//TODO: rename to InitializerListAST?
//Initializer list
class InitializerListExpressionAST : public ExpressionAST {
private:
    irb::Type* type;
    std::vector<ExpressionAST*> expressions;

public:
    InitializerListExpressionAST(irb::Type* aType, std::vector<ExpressionAST*> aExpressions) : type(aType), expressions(aExpressions) {}

    irb::Value* _codegen(irb::Type* requiredType = nullptr) override;

    bool isConstant() override {
        for (auto* expression : expressions) {
            if (!expression->isConstant())
                return false;
        }

        return true;
    }
};

} //namespace lvslang

#endif
