#ifndef LVSLANG_AST_H
#define LVSLANG_AST_H

#include <limits>

#include "type_name.hpp"

#include "../shader_ir_builder/spirv/ir.hpp"
#include "../shader_ir_builder/air/ir.hpp"

namespace lvslang {

// Forward declarations
class FunctionPrototypeAST;

extern irb::Context context;

struct EnumValue {
    std::string name;
    long value;
};

class Enumeration {
public:
    Enumeration(const std::vector<EnumValue>& aValues, bool aIsClass) : values(aValues), isClass(aIsClass) {
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

    inline irb::ScalarType* getType() const {
        return type;
    }

    inline const std::vector<EnumValue>& getValues() const {
        return values;
    }
    
    inline bool getIsClass() const {
        return isClass;
    }

private:
    irb::ScalarType* type;
    std::vector<EnumValue> values;
    bool isClass;

    inline uint16_t getFirstGreaterOrEqualPow2(long value) {
        if (value == 0)
            return 0;
        long thePow = 1;
        for (uint16_t i = 0;; i++) {
            thePow *= 2;
            if (value < thePow)
                return i;
        }

        // Just in case
        throw std::runtime_error("getFirstGreaterOrEqualPow2");

        return 0;
    }
};

// For swizzled vectors that weren't loaded on codegen
// TODO: enable the @ref checkIfNameAlreadyUsed argument?
class UnloadedSwizzledVectorValue : public irb::Value {
private:
    irb::Value* unloadedVector;
    std::vector<uint8_t> indices;

public:
    UnloadedSwizzledVectorValue(irb::Context& aContext, irb::Value* aUnloadedVector, const std::vector<uint8_t>& aIndices, const std::string& aName = "") : irb::Value(aContext, aUnloadedVector->getType(), aName), unloadedVector(aUnloadedVector), indices(aIndices) {}

    // Getters
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

inline bool typeIsPromoted(irb::TypeID a, irb::TypeID b) {
    static irb::TypeID typesSortedByPromotion[] = {
        irb::TypeID::Vector,
        irb::TypeID::Matrix,
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

inline irb::Type* findPromotedType(irb::Type* a, irb::Type* b) {
    return (typeIsPromoted(a->getTypeID(), b->getTypeID()) ? a : b);
}

// Base class
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

    virtual bool isConstant() {
        return false;
    }

    virtual bool isVariable() {
        return false;
    }
    
    virtual void setLoadOnCodegen(bool aLoadOnCodegen) {
        loadOnCodegen = aLoadOnCodegen;
    }

    // Getters
    inline irb::Type* getType() const {
        if (!type)
            logError("expression does not have type");

        return type;
    }

    inline irb::Type* getRequiredType() const {
        return requiredType;
    }

    inline bool getLoadOnCodegen() const {
        return loadOnCodegen;
    }

    // Debugging
    inline void setDebugInfo() const {
        source.crntDebugLine = debugLine;
        source.crntDebugChar = debugChar;
    }

protected:
    uint32_t debugLine;
    uint32_t debugChar;

    irb::Type* requiredType = nullptr;

    bool loadOnCodegen = true;

    virtual irb::Type* _initialize() = 0;

private:
    irb::Type* type = nullptr;
};

// Number
class NumberExpressionAST : public ExpressionAST {
public:
    NumberExpressionAST(double aValueD, long aValueL, unsigned long aValueU, irb::ScalarType* aScalarType) : _valueD(aValueD), _valueL(aValueL), _valueU(aValueU), scalarType(aScalarType) {}

    bool isConstant() override {
        return true;
    }

    // Getters
    inline double valueD() const {
        return _valueD;
    }

    inline long valueL() const {
        return _valueL;
    }

    inline unsigned long valueU() const {
        return _valueU;
    }

private:
    double _valueD;
    long _valueL;
    unsigned long _valueU;

    irb::Type* scalarType;

    irb::Type* _initialize() override;
};

// Variable
class VariableExpressionAST : public ExpressionAST {
public:
    VariableExpressionAST(const std::string& aName) : _name(aName) {}

    bool isVariable() override {
        return true;
    }

    // Getters
    inline const std::string& getName() const {
        return _name;
    }

    inline Variable* getVariable() const {
        return variable;
    }

private:
    std::string _name;

    Variable* variable;

    irb::Type* _initialize() override;
};

// TODO: rename to OperationAST?
// Operation
class BinaryExpressionAST : public ExpressionAST {
public:
    BinaryExpressionAST(const std::string& aOperator, ExpressionAST* aLHS, ExpressionAST* aRHS) : op(aOperator), lhs(aLHS), rhs(aRHS) {}

    // Getters
    inline const ExpressionAST* getLHS() const {
        return lhs;
    }

    inline const ExpressionAST* getRHS() const {
        return rhs;
    }

    inline const std::string& getOp() const {
        return op;
    }

    inline irb::Operation getOperation() const {
        return operation;
    }

    inline irb::Type* getPromotedType() const {
        return promotedType;
    }

private:
    std::string op;
    ExpressionAST* lhs;
    ExpressionAST* rhs;

    irb::Operation operation;

    irb::Type* promotedType;

    irb::Type* _initialize() override;
};

// Block
class BlockExpressionAST : public ExpressionAST {
public:
    BlockExpressionAST(std::vector<ExpressionAST*> aExpressions) : expressions(aExpressions) {}

    // Getters
    inline const std::vector<ExpressionAST*>& getExpressions() const {
        return expressions;
    }

private:
    std::vector<ExpressionAST*> expressions;

    irb::Type* _initialize() override;
};

// Function declaration
class FunctionPrototypeAST : public ExpressionAST {
public:
    FunctionPrototypeAST(const std::string& aName, irb::Type* aReturnType, std::vector<irb::Argument> aArguments/*, const std::vector<int>& aAttributes*/, const std::vector<ExpressionAST*> aDefaultValues, bool aIsDefined, bool aIsSTDFunction, irb::FunctionRole aFunctionRole) : _name(aName), returnType(aReturnType), _arguments(aArguments)/*, attributes(aAttributes)*/,defaultValues(aDefaultValues), isDefined(aIsDefined), isSTDFunction(aIsSTDFunction), functionRole(aFunctionRole) {}

    // Getters
    inline const std::string& name() const {
        return _name;
    }

    inline const std::vector<irb::Argument>& arguments() const {
        return _arguments;
    }

    inline const irb::Attributes& getArgumentAttributes(uint32_t index) const {
        return _arguments[index].attributes;
    }

    inline const std::vector<ExpressionAST*>& getDefaultValues() const {
        return defaultValues;
    }

    inline uint32_t getArgumentsWithoutDefaultValueCount() const {
        return argumentsWithoutDefaultValue;
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

    inline const FunctionPrototypeAST* getPreviousDeclaration() const {
        return previousDeclaration;
    }
    
    // Setters
    inline void setIsDefined(bool aIsDefined) {
        isDefined = aIsDefined;
    }

    inline void setValue(irb::Function* aValue) {
        value = aValue;
    }

private:
    std::string _name;
    irb::Type* returnType;
    std::vector<irb::Argument> _arguments;
    // std::vector<int> attributes;
    std::vector<ExpressionAST*> defaultValues;
    bool isDefined;
    bool isSTDFunction;
    irb::FunctionRole functionRole;

    irb::Function* value = nullptr;

    uint32_t argumentsWithoutDefaultValue = 0;

    // Redeclared function
    FunctionPrototypeAST* previousDeclaration = nullptr;

    // For finding the correct overload
    std::string identifier;

    irb::Type* _initialize() override;
};

// Function definition
class FunctionDefinitionAST : public ExpressionAST {
public:
    FunctionDefinitionAST(FunctionPrototypeAST* aDeclaration, BlockExpressionAST* aBody) : declaration(aDeclaration), body(aBody) {}

    // Getters
    inline const FunctionPrototypeAST* getPrototype() const {
        return declaration;
    }

    inline const BlockExpressionAST* getBody() const {
        return body;
    }

private:
    // TODO: rename to prototype
    FunctionPrototypeAST* declaration;
    BlockExpressionAST* body;

    irb::Type* _initialize() override;
};

// Function call
// TODO: rename to FunctionCallAST
class CallExpressionAST : public ExpressionAST {
public:
    CallExpressionAST(const std::string& aCallee, std::vector<ExpressionAST*> aArguments) : callee(aCallee), arguments(aArguments) {}

    // Getters
    inline const std::string& getCallee() const {
        return callee;
    }

    inline const std::vector<ExpressionAST*>& getArguments() const {
        return arguments;
    }

    inline const FunctionPrototypeAST* getPrototype() const {
        return declaration;
    }

private:
    std::string callee;
    std::vector<ExpressionAST*> arguments;

    // TODO: rename to prototype
    FunctionPrototypeAST* declaration = nullptr;

    irb::Type* _initialize() override;
};

// Return
class ReturnExpressionAST : public ExpressionAST {
public:
    ReturnExpressionAST(ExpressionAST* aExpression) : expression(aExpression) {}

    // Getters
    inline const ExpressionAST* getExpression() const {
        return expression;
    }

private:
    ExpressionAST* expression;

    irb::Type* _initialize() override;
};

// If
struct IfThenBlock {
    ExpressionAST* condition;
    ExpressionAST* block;
};

// TODO: rename?
class IfExpressionAST : public ExpressionAST {
public:
    IfExpressionAST(const std::vector<IfThenBlock*>& aIfThenBlocks, ExpressionAST* aElseBlock) : ifThenBlocks(aIfThenBlocks), elseBlock(aElseBlock) {}

    // Getters
    inline const std::vector<IfThenBlock*>& getIfThenBlocks() const {
        return ifThenBlocks;
    }

    inline const ExpressionAST* getElseBlock() const {
        return elseBlock;
    }

private:
    std::vector<IfThenBlock*> ifThenBlocks;
    ExpressionAST* elseBlock;

    irb::Type* _initialize() override;
};

// Inline if else
class InlineIfElseExpressionAST : public ExpressionAST {
public:
    InlineIfElseExpressionAST(ExpressionAST* aCondition, BlockExpressionAST* aThenBlock, BlockExpressionAST* aElseBlock) : condition(aCondition), thenBlock(aThenBlock), elseBlock(aElseBlock) {}

private:
    ExpressionAST* condition;
    BlockExpressionAST* thenBlock;
    BlockExpressionAST* elseBlock;

    // TODO: implement this
    irb::Type* _initialize() override {
        return nullptr;
    }
};

// TODO: rename to WhileLoopAST?
// While
class WhileExpressionAST : public ExpressionAST {
public:
    WhileExpressionAST(ExpressionAST* aCondition, ExpressionAST* aBlock, bool aIsDoWhile) : condition(aCondition), block(aBlock), isDoWhile(aIsDoWhile) {}

    // Getters
    inline const ExpressionAST* getCondition() const {
        return condition;
    }

    inline const ExpressionAST* getBlock() const {
        return block;
    }

    inline bool getIsDoWhile() const {
        return isDoWhile;
    }

private:
    ExpressionAST* condition;
    ExpressionAST* block;

    bool isDoWhile;

    irb::Type* _initialize() override;
};

// Variable declaration
struct VariableDeclaration {
    std::string name;
    irb::Type* type;
    ExpressionAST* expression;
};

// TODO: rename to VariableDeclarationAST?
class VariableDeclarationExpressionAST : public ExpressionAST {
public:
    VariableDeclarationExpressionAST(const std::vector<VariableDeclaration>& aVariableNames, bool aIsGlobal, bool aIsConstant) : variableNames(aVariableNames), isGlobal(aIsGlobal), isConstant(aIsConstant) {}

    // Getters
    inline const std::vector<VariableDeclaration>& getVariableDeclarations() const {
        return variableNames;
    }

    inline bool getIsGlobal() const {
        return isGlobal;
    }

    inline bool getIsConstant() const {
        return isConstant;
    }

private:
    // TODO: rename to variableDeclarations
    std::vector<VariableDeclaration> variableNames;
    bool isGlobal;
    bool isConstant;

    irb::Type* _initialize() override;
};

// Subscript
class SubscriptExpressionAST : public ExpressionAST {
public:
    SubscriptExpressionAST(ExpressionAST* aPtr, ExpressionAST* aIndex) : ptr(aPtr), index(aIndex) {}

    // Getters
    inline const ExpressionAST* getPtr() const {
        return ptr;
    }

    inline const ExpressionAST* getIndex() const {
        return index;
    }

private:
    ExpressionAST* ptr;
    ExpressionAST* index;

    irb::Type* _initialize() override;
};

// TODO: rename to MemberAccessAST?
// Member access
class MemberAccessExpressionAST : public ExpressionAST {
public:
    MemberAccessExpressionAST(ExpressionAST* aExpression, const std::string& aMemberName, bool aExprShouldBeLoadedBeforeAccessingMember) : expression(aExpression), memberName(aMemberName), exprShouldBeLoadedBeforeAccessingMember(aExprShouldBeLoadedBeforeAccessingMember) {}

    // Getters
    inline const ExpressionAST* getExpression() const {
        return expression;
    }

    inline const std::string& getMemberName() const {
        return memberName;
    }

    inline bool getExprShouldBeLoadedBeforeAccessingMember() const {
        return exprShouldBeLoadedBeforeAccessingMember;
    }

    inline uint32_t getMemberIndex() const {
        return memberIndex;
    }

private:
    ExpressionAST* expression;
    std::string memberName;
    bool exprShouldBeLoadedBeforeAccessingMember;

    uint32_t memberIndex = 0;

    irb::Type* _initialize() override;
};

// Structure definition
class StructureDefinitionAST : public ExpressionAST {
public:
    StructureDefinitionAST(const std::string& aName, const std::vector<irb::StructureMember>& aMembers) : name(aName), members(aMembers) {}

    // Getters
    inline const std::string& getName() const {
        return name;
    }

    inline const std::vector<irb::StructureMember>& getMembers() const {
        return members;
    }

private:
    std::string name;
    std::vector<irb::StructureMember> members;

    irb::Type* _initialize() override;
};

// Enumeration definition
class EnumDefinitionAST : public ExpressionAST {
public:
    EnumDefinitionAST(const std::string& aName, const std::vector<EnumValue>& aValues, bool aIsClass) : name(aName), values(aValues), isClass(aIsClass) {}

    // Getters
    inline const std::string& getName() const {
        return name;
    }

    inline const std::vector<EnumValue>& getValues() const {
        return values;
    }

    inline bool getIsClass() const {
        return isClass;
    }

private:
    std::string name;
    std::vector<EnumValue> values;
    bool isClass;

    irb::Type* _initialize() override;
};

// TODO: rename?
// Enumeration value
class EnumValueExpressionAST : public ExpressionAST {
public:
    EnumValueExpressionAST(Enumeration* aEnumeration, const EnumValue& aValue) : enumeration(aEnumeration), value(aValue) {}

    // Getters
    inline Enumeration* getEnumeration() const {
        return enumeration;
    }

    inline const EnumValue& getValue() const {
        return value;
    }

private:
    Enumeration* enumeration;
    const EnumValue& value;

    irb::Type* _initialize() override;
};

// TODO: support other initializer lists as well (for instance sampler)
// TODO: support vector to vector conversion in HLSL
// TODO: rename to InitializerListAST?
// Initializer list
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

    // Getters
    inline irb::Type* getListType() const {
        return listType;
    }

    inline const std::vector<ExpressionAST*>& getExpressions() const {
        return expressions;
    }

private:
    irb::Type* listType;
    std::vector<ExpressionAST*> expressions;

    irb::Type* _initialize() override;
};

class DereferenceExpressionAST : public ExpressionAST {
public:
    DereferenceExpressionAST(ExpressionAST* aExpression) : expression(aExpression) {}

    // Getters
    inline const ExpressionAST* getExpression() const {
        return expression;
    }

private:
    ExpressionAST* expression;

    irb::Type* _initialize() override;
};

class AST {
private:
    std::vector<ExpressionAST*> expressions;

public:
    AST() {}
    
    inline void addExpression(ExpressionAST* expression) {
        expressions.push_back(expression);
    }

    // Getters
    inline const std::vector<ExpressionAST*>& getExpressions() const {
        return expressions;
    }
};

} // namespace lvslang

#endif
