#ifndef LVSLANG_AST_H
#define LVSLANG_AST_H

#include <limits>

#include "type_name.hpp"

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
    irb::Type* type;
    irb::Value* value;
    bool shouldBeLoaded;
};

extern std::map<std::string, Variable> variables;
extern std::map<std::string, std::vector<FunctionPrototypeAST*> > functionDeclarations;
extern std::map<std::string, Enumeration*> enumerations;

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
public:
    ExpressionAST() {
        debugLine = source.crntLine;
        debugChar = source.crntChar;
    }

    virtual ~ExpressionAST() = default;

    irb::Type* initialize(irb::Type* aRequiredType = nullptr) {
        uint32_t oldDebugLine = source.crntDebugLine;
        uint32_t oldDebugChar = source.crntDebugChar;
        setDebugInfo();

        requiredType = aRequiredType;
        type = _initialize();
        
        source.crntDebugLine = oldDebugLine;
        source.crntDebugChar = oldDebugChar;

        return (requiredType ? requiredType : type);
    }

    irb::Value* codegen() {
        uint32_t oldDebugLine = source.crntDebugLine;
        uint32_t oldDebugChar = source.crntDebugChar;
        setDebugInfo();

        irb::Value* value = _codegen();
        if (!value)
            return nullptr;
        
        source.crntDebugLine = oldDebugLine;
        source.crntDebugChar = oldDebugChar;
        
        if (requiredType) {
            if (TARGET_IS_IR(irb::target))
                return builder->opCast(value, requiredType);
            else if (!value->getType()->equals(requiredType) && !type->equals(requiredType))
                return new irb::Value(context, requiredType, getTypeName(requiredType) + "(" + value->getRawName() + ")");
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

    //Getters
    inline irb::Type* getType() const {
        if (!type)
            logError("expression does not have type");

        return type;
    }

    //Debugging
    inline void setDebugInfo() {
        source.crntDebugLine = debugLine;
        source.crntDebugChar = debugChar;
    }

protected:
    uint32_t debugLine;
    uint32_t debugChar;

    irb::Type* requiredType = nullptr;

    bool loadOnCodegen = true;

    virtual irb::Type* _initialize() = 0;

    virtual irb::Value* _codegen() = 0;

private:
    irb::Type* type = nullptr;
};

/*
class TopLevelAST : public ExpressionAST {
public:
    TopLevelAST(const std::vector<ExpressionAST*>& aExpressions) : expressions(aExpressions) {}

private:
    std::vector<ExpressionAST*> expressions;
    
    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};
*/

//Number
class NumberExpressionAST : public ExpressionAST {
public:
    NumberExpressionAST(double aValueD, long aValueL, unsigned long aValueU, irb::ScalarType* aScalarType) : _valueD(aValueD), _valueL(aValueL), _valueU(aValueU), scalarType(aScalarType) {}

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

private:
    double _valueD;
    long _valueL;
    unsigned long _valueU;

    irb::Type* scalarType;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Variable
class VariableExpressionAST : public ExpressionAST {
public:
    VariableExpressionAST(const std::string& aName) : _name(aName) {}

    bool isVariable() override {
        return true;
    }

    std::string& name() { return _name; }

private:
    std::string _name;

    Variable* variable;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//TODO: rename to OperationAST?
//Operation
class BinaryExpressionAST : public ExpressionAST {
public:
    BinaryExpressionAST(const std::string& aOperator, ExpressionAST* aLHS, ExpressionAST* aRHS) : op(aOperator), lhs(aLHS), rhs(aRHS) {}

private:
    std::string op;
    ExpressionAST* lhs;
    ExpressionAST* rhs;

    irb::Operation operation;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Block
class BlockExpressionAST : public ExpressionAST {
public:
    BlockExpressionAST(std::vector<ExpressionAST*> aExpressions) : expressions(aExpressions) {}

private:
    std::vector<ExpressionAST*> expressions;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Function declaration
class FunctionPrototypeAST : public ExpressionAST {
public:
    FunctionPrototypeAST(const std::string& aName, irb::Type* aReturnType, std::vector<irb::Argument> aArguments/*, const std::vector<int>& aAttributes*/, bool aIsDefined, bool aIsSTDFunction, irb::FunctionRole aFunctionRole) : _name(aName), returnType(aReturnType), _arguments(aArguments)/*, attributes(aAttributes)*/, isDefined(aIsDefined), isSTDFunction(aIsSTDFunction), functionRole(aFunctionRole) {}

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

    inline irb::Type* getReturnType() const {
        return returnType;
    }

    inline irb::FunctionRole getFunctionRole() const {
        return functionRole;
    }

    inline irb::Function* getValue() const {
        return value;
    }

    inline bool getIsDefined() const {
        return isDefined;
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

private:
    std::string _name;
    irb::Type* returnType;
    std::vector<irb::Argument> _arguments;
    //std::vector<int> attributes;
    bool isDefined;
    bool isSTDFunction;
    irb::FunctionRole functionRole;

    irb::Function* value = nullptr;

    //For finding the correct overload
    std::string identifier;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Function definition
class FunctionDefinitionAST : public ExpressionAST {
private:
    FunctionPrototypeAST* declaration;
    BlockExpressionAST* body;

public:
    FunctionDefinitionAST(FunctionPrototypeAST* aDeclaration, BlockExpressionAST* aBody) : declaration(aDeclaration), body(aBody) {}

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Function call
class CallExpressionAST : public ExpressionAST {
public:
    CallExpressionAST(const std::string& aCallee, std::vector<ExpressionAST*> aArguments) : callee(aCallee), arguments(aArguments) {}

private:
    std::string callee;
    std::vector<ExpressionAST*> arguments;

    FunctionPrototypeAST* declaration = nullptr;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Return
class ReturnExpressionAST : public ExpressionAST {
public:
    ReturnExpressionAST(ExpressionAST* aExpression) : expression(aExpression) {}

private:
    ExpressionAST* expression;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//If
struct IfThenBlock {
    ExpressionAST* condition;
    ExpressionAST* block;
};

//TODO: rename?
class IfExpressionAST : public ExpressionAST {
public:
    IfExpressionAST(const std::vector<IfThenBlock*>& aIfThenBlocks, ExpressionAST* aElseBlock) : ifThenBlocks(aIfThenBlocks), elseBlock(aElseBlock) {}

private:
    std::vector<IfThenBlock*> ifThenBlocks;
    ExpressionAST* elseBlock;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Inline if else
class InlineIfElseExpressionAST : public ExpressionAST {
public:
    InlineIfElseExpressionAST(ExpressionAST* aCondition, BlockExpressionAST* aThenBlock, BlockExpressionAST* aElseBlock) : condition(aCondition), thenBlock(aThenBlock), elseBlock(aElseBlock) {}

private:
    ExpressionAST* condition;
    BlockExpressionAST* thenBlock;
    BlockExpressionAST* elseBlock;

    //TODO: implement this
    irb::Type* _initialize() override {
        return nullptr;
    }

    //TODO: implement this
    irb::Value* _codegen() override {
        return nullptr;
    }
};

//TODO: rename to WhileLoopAST?
//While
class WhileExpressionAST : public ExpressionAST {
public:
    WhileExpressionAST(ExpressionAST* aCondition, ExpressionAST* aBlock, bool aIsDoWhile) : condition(aCondition), block(aBlock), isDoWhile(aIsDoWhile) {}

private:
    ExpressionAST* condition;
    ExpressionAST* block;

    bool isDoWhile;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Variable declaration
struct VariableDeclaration {
    std::string name;
    irb::Type* type;
    ExpressionAST* expression;
};

//TODO: rename to VariableDeclarationAST?
class VariableDeclarationExpressionAST : public ExpressionAST {
public:
    VariableDeclarationExpressionAST(const std::vector<VariableDeclaration>& aVariableNames, bool aIsGlobal, bool aIsConstant) : variableNames(aVariableNames), isGlobal(aIsGlobal), isConstant(aIsConstant) {}

private:
    std::vector<VariableDeclaration> variableNames;
    bool isGlobal;
    bool isConstant;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Subscript
class SubscriptExpressionAST : public ExpressionAST {
public:
    SubscriptExpressionAST(ExpressionAST* aPtr, ExpressionAST* aIndex) : ptr(aPtr), index(aIndex) {}

private:
    ExpressionAST* ptr;
    ExpressionAST* index;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//TODO: rename to MemberAccessAST?
//Member access
class MemberAccessExpressionAST : public ExpressionAST {
public:
    MemberAccessExpressionAST(ExpressionAST* aExpression, const std::string& aMemberName, bool aExprShouldBeLoadedBeforeAccessingMember) : expression(aExpression), memberName(aMemberName), exprShouldBeLoadedBeforeAccessingMember(aExprShouldBeLoadedBeforeAccessingMember) {}

private:
    ExpressionAST* expression;
    std::string memberName;
    bool exprShouldBeLoadedBeforeAccessingMember;

    uint32_t memberIndex = 0;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Structure definition
class StructureDefinitionAST : public ExpressionAST {
private:
    std::string name;
    std::vector<irb::StructureMember> members;

public:
    StructureDefinitionAST(const std::string& aName, const std::vector<irb::StructureMember>& aMembers) : name(aName), members(aMembers) {}

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//Enumeration definition
class EnumDefinitionAST : public ExpressionAST {
public:
    EnumDefinitionAST(const std::string& aName, const std::vector<EnumValue>& aValues) : name(aName), values(aValues) {}

private:
    std::string name;
    std::vector<EnumValue> values;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//TODO: rename?
//Enumeration value
class EnumValueExpressionAST : public ExpressionAST {
public:
    EnumValueExpressionAST(Enumeration* aEnumeration, EnumValue& aValue) : enumeration(aEnumeration), value(aValue) {}

private:
    Enumeration* enumeration;
    EnumValue& value;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

//TODO: support other initializer lists as well (for instance sampler)
//TODO: support vector to vector conversion in HLSL
//TODO: rename to InitializerListAST?
//Initializer list
class InitializerListExpressionAST : public ExpressionAST {
public:
    InitializerListExpressionAST(irb::Type* aListType, std::vector<ExpressionAST*> aExpressions) : listType(aListType), expressions(aExpressions) {}

    bool isConstant() override {
        for (auto* expression : expressions) {
            if (!expression->isConstant())
                return false;
        }

        return true;
    }

private:
    irb::Type* listType;
    std::vector<ExpressionAST*> expressions;

    irb::Type* _initialize() override;

    irb::Value* _codegen() override;
};

} //namespace lvslang

#endif
