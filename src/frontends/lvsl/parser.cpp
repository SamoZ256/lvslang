#include "parser.hpp"

#include "lexer.hpp"
#include "../../ast.hpp"

namespace lvslang {

namespace lvsl {

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
    case TOKEN_ATTRIB_DESCRIPTOR_SET:
        return {irb::Attribute::Enum::DescriptorSet};
    case TOKEN_ATTRIB_POSITION:
        return {irb::Attribute::Enum::Position};
    case TOKEN_ATTRIB_INPUT:
        return {irb::Attribute::Enum::Input};
    case TOKEN_ATTRIB_LOCATION:
        return {irb::Attribute::Enum::Location};
    case TOKEN_ATTRIB_COLOR:
        return {irb::Attribute::Enum::Color};
    default:
        return {irb::Attribute::Enum::MaxEnum};
    }
}

// Binop precedence
static std::map<int, int> binopPrecedence;

inline int getTokenPrecedence() {
    // if (!isascii(crntToken))
    //     return -1;
    
    int op = binopPrecedence[crntToken];
    if (op <= 0)
        return -1;
    
    return op;
}

// Forward declarations
ExpressionAST* parseMain();
ExpressionAST* parseExpression(int expressionPrecedence = 0);

// Skip
void _consumeSkips() {
    while (crntToken == TOKEN_SKIP)
        getNextToken(); // Skip
}

// Type
irb::Type* _parseTypeExpression(irb::Attributes* attributes = nullptr) {
    irb::Type* type;
    if (tokenIsType(crntToken)) {
        if (crntToken == TOKEN_TYPE_STRUCT) {
            getNextToken(); // 'struct'
            type = new irb::StructureType(context, identifierStr);
        } else if (crntToken == TOKEN_TYPE_ENUM) {
            getNextToken(); // 'enum'
            Enumeration* enumeration = enumerations[identifierStr];
            if (!enumeration) {
                logError("use of undeclared enum '" + identifierStr + "'");
                return nullptr;
            }

            type = enumeration->getType();
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
            irb::TextureAccess access = irb::TextureAccess::Sample;
            if (crntToken == ',') {
                getNextToken(); // ','
                ExpressionAST* accessExpr = parseMain();
                EnumValueExpressionAST* accessEnumExpr = dynamic_cast<EnumValueExpressionAST*>(accessExpr);
                if (!accessEnumExpr || accessEnumExpr->getEnumeration() != enumerations["Access"]) {
                    logError("expected 'Access' enumeration value for the 2nd template argument");
                    return nullptr;
                }
                accessEnumExpr->initialize();
                access = (irb::TextureAccess)accessEnumExpr->getValue().value;
            }
            if (crntToken != TOKEN_OPERATOR_RELATIONAL_GREATER_THAN) {
                logError("expected '>' to match the '<'");
                return nullptr;
            }

            type = new irb::TextureType(context, viewType, scalarType, access);
        } else if (crntToken == TOKEN_TYPE_SAMPLER) {
            type = new irb::SamplerType(context);
        } /* else if (typeIsBuiltin) {
            getNextToken(); // Type
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
                type = new PointerType(context, bufferType, StorageClass::StorageBuffer); // TODO: support @ref Uniform storage class
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
        else if (columnCount != 0)
            type = new irb::MatrixType(context, new irb::VectorType(context, type, rowCount), columnCount);
        getNextToken(); // Type or '>'
    } else {
        logError("unknown type '" + identifierStr + "'");
        return nullptr;
    }

    uint32_t pointerCount = 0;
    for (; crntToken == TOKEN_OPERATOR_ARITHMETIC_MULTIPLY; pointerCount++)
        getNextToken(); // '*'

    std::vector<NumberExpressionAST*> arraySizes;
    while (crntToken == '[') {
        // Skip attributes
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

        // type = new ArrayType(context, type, numArraySize->valueU());
        arraySizes.push_back(numArraySize);
    }

    for (int32_t i = arraySizes.size() - 1; i >= 0; i--)
        type = new irb::ArrayType(context, type, arraySizes[i]->valueU());
    
    if (pointerCount)
        type = new irb::PointerType(context, type, irb::StorageClass::Function, (attributes ? attributes->addressSpace : 0));
    
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
        getNextToken(); // Attribute
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

    if (attributes) {
        for (const auto& attrib : attribs) {
            switch (attrib.attrib) {
            case irb::Attribute::Enum::AddressSpace:
                attributes->addressSpace = attrib.values[0];
                break;
            default:
                break;
            }
        }
    }

    attribs.clear();

    irb::Type* type = _parseTypeExpression(attributes);

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

    if (attributes) {
        for (const auto& attrib : attribs) {
            switch (attrib.attrib) {
            case irb::Attribute::Enum::DescriptorSet:
                attributes->bindings.set = attrib.values[0];
                attributes->bindings.binding = attrib.values[1];
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
            case irb::Attribute::Enum::Color:
                attributes->colorIndex = attrib.values[0];
                break;
            default:
                break;
            }
        }
    }

    return type;
}

// Number
NumberExpressionAST* parseNumberExpression() {
    NumberExpressionAST* result = new NumberExpressionAST(numValueD, numValueL, numValueU, createScalarType(getIntTypeFromNumStr(numTypeStr)));
    getNextToken();

    return result;
}

// Return
ExpressionAST* parseReturnExpression() {
    getNextToken();
    ExpressionAST* returnExpr = parseExpression();

    return new ReturnExpressionAST(returnExpr);
}

// Parenthesis
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

// Braces
BlockExpressionAST* parseBracesExpression() {
    std::vector<ExpressionAST*> expressions;
    getNextToken(); // '{'

    _consumeSkips();

    while (crntToken != '}') {
        ExpressionAST* expr = parseExpression();
        if (!expr)
            return nullptr;
        
        expressions.push_back(expr);
    }

    getNextToken(); // '}'

    return new BlockExpressionAST(expressions);
}

// TODO: support constant array declarations as well
// Square brackets
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

// Identifier
ExpressionAST* parseIdentifierExpression() {
    std::string idName = identifierStr;
    getNextToken(); // Identifier

    // Variable reference
    if (crntToken != '(') {
        if (enumerations.count(idName)) {
            Enumeration* enumeration = enumerations[idName];
            if (crntToken != TOKEN_OPERATOR_DOT) {
                logError("enum name must be followed by '.'");
                return nullptr;
            }
            if (getNextToken() != TOKEN_IDENTIFIER) {
                logError("use of unexpected token '" + std::to_string(crntToken) + "'. expected value name instead");
                return nullptr;
            }
            std::string valueName = identifierStr;
            getNextToken(); // value name

            const EnumValue* value = nullptr;
            for (auto& enumValue : enumeration->getValues()) {
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

        for (auto& enumeration : enumerations) {
            if (!enumeration.second->getIsClass()) {
                for (auto& value : enumeration.second->getValues()) {
                    if (value.name == idName)
                        return new EnumValueExpressionAST(enumeration.second, value);
                }
            }
        }

        return new VariableExpressionAST(idName);
    }
    
    // Function call
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

    // Condition
    ifThenBlock->condition = parseExpression();
    if (!ifThenBlock->condition)
        return nullptr;
    
    ifThenBlock->block = parseExpression();
    if (!ifThenBlock->block)
        return nullptr;

    return ifThenBlock;
}

// If
ExpressionAST* parseIfExpression() {
    getNextToken(); // 'if'

    std::vector<IfThenBlock*> ifThenBlocks;
    
    IfThenBlock* ifThenBlock = _parseIfThenBlock();
    if (!ifThenBlock)
        return nullptr;
    ifThenBlocks.push_back(ifThenBlock);
    
    ExpressionAST* elseBlock = nullptr;
    while (crntToken == TOKEN_ELSE) {
        getNextToken(); // 'else'
        if (crntToken == TOKEN_IF) { // If else
            getNextToken(); // 'if'
            ifThenBlock = _parseIfThenBlock();
            if (!ifThenBlock)
                return nullptr;
            
            ifThenBlocks.push_back(ifThenBlock);
        } else { // Else
            elseBlock = parseExpression();
            if (!elseBlock)
                return nullptr;
            
            break;
        }
    }

    return new IfExpressionAST(ifThenBlocks, elseBlock);
}

// While
ExpressionAST* parseWhileExpression() {
    getNextToken(); // 'while'

    // Condition
    ExpressionAST* condition = parseExpression();
    if (!condition)
        return nullptr;
    
    ExpressionAST* block = parseExpression();
    if (!block)
        return nullptr;

    return new WhileExpressionAST(condition, block, false);
}

// Variable declaration
ExpressionAST* parseVariableDeclarationExpression(bool isGlobal = false) {
    bool isConstant = false;
    if (crntToken == TOKEN_CONST) {
        isConstant = true;
        getNextToken(); // 'const'
    }

    if (crntToken != TOKEN_VAR) {
        logError("Expected 'var' in a variable declaration");
        return nullptr;
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
            
            // std::cout << "CRNT TOKEN: " << crntToken << " : " << char(crntToken) << " : " << identifierStr << std::endl;
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

    return new VariableDeclarationExpressionAST(variableNames, isGlobal, isConstant);
}

// Reference
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

// Single quote
/*
ExpressionAST* parseCharExpression() {
    NumberExpressionAST* expression = new NumberExpressionAST(numValueL, numValueL, numValueL, createScalarType(0));
    getNextToken(); // String

    return expression;
}

// Double quote
ExpressionAST* parseStringExpression() {
    std::vector<ExpressionAST*> values(identifierStr.size());
    for (uint16_t i = 0; i < values.size(); i++)
        values[i] = new NumberExpressionAST(identifierStr[i], identifierStr[i], identifierStr[i], createScalarType(TOKEN_TYPE_CHAR));
        
    ArrayExpressionAST* expression = new ArrayExpressionAST(values);
    getNextToken(); // String

    return expression;
}
*/

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
    irb::Type* type = _parseTypeExpression(); // TODO: parse with attributes as well?
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

ExpressionAST* parseDereferenceExpression() {
    getNextToken(); // '*'
    ExpressionAST* expression = parseMain();
    if (!expression)
        return nullptr;
    
    return new DereferenceExpressionAST(expression);
}

// TODO: implement reference expression
// Main parse
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
        // return parseRegisterExpression();
        logError("'register' is not supported yet");
        return nullptr;
    case TOKEN_IDENTIFIER:
        return parseIdentifierExpression();
    case TOKEN_NUMBER:
        return parseNumberExpression();
    //case TOKEN_CHAR:
    //    return parseCharExpression();
    //case TOKEN_STRING:
    //    return parseStringExpression();
    case '(':
        return parseParenthesisExpression();
    case '{':
        return parseBracesExpression();
    case '[':
        return parseSquareBracketsExpression();
    case TOKEN_OPERATOR_DEREFERENCE:
        return parseDereferenceExpression();
    case TOKEN_TYPE_ENUM_MIN ... TOKEN_TYPE_ENUM_MAX:
        return parseTypeExpression();
    default:
        logError("expected expression");
        return nullptr;
    }
}

// Binary
ExpressionAST* parseBinOpRHS(int expressionPrecedence, ExpressionAST* lhs) {
    while (true) {
        int tokenPrecedence = getTokenPrecedence();

        if (tokenPrecedence < expressionPrecedence)
            return lhs;
        
        std::string binOp = operatorStr;
        getNextToken(); // binop

        ExpressionAST* rhs;
        std::string memberName;
        bool exprShouldBeLoadedBeforeAccessingMember = false;
        if (binOp == "->") {
            binOp = ".";
            exprShouldBeLoadedBeforeAccessingMember = true;
        }
        if (binOp == ".") {
            if (crntToken != TOKEN_IDENTIFIER) {
                logError("expected member name after the '.' operator");
                return nullptr;
            }

            memberName = identifierStr;
            getNextToken(); // Member name
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
            lhs = new MemberAccessExpressionAST(lhs, memberName, exprShouldBeLoadedBeforeAccessingMember);
        else
            lhs = new BinaryExpressionAST(binOp, lhs, rhs);
    }
}

// Function declaration
FunctionPrototypeAST* parseFunctionPrototype(bool isDefined = false, bool isSTDFunction = false, irb::FunctionRole functionRole = irb::FunctionRole::Normal) {
    if (crntToken != TOKEN_IDENTIFIER) {
        logError("excpected function name");
        return nullptr;
    }
    std::string functionName = identifierStr;
    getNextToken(); // function name

    if (crntToken != '(') {
        logError("expected '(' after function name");
        return nullptr;
    }

    std::vector<irb::Argument> arguments;
    std::vector<ExpressionAST*> defaultValues;
    do {
        getNextToken(); // '(' or ','
        _consumeSkips();
        std::string name;
        if (crntToken == TOKEN_IDENTIFIER) {
            name = identifierStr;
            if (getNextToken() == ':') {
                getNextToken(); // ':'
            } else {
                logError("expected argument type");
                return nullptr;
            }
        } else if (!(tokenIsType(crntToken) || tokenIsAttrib(crntToken))) {
            break;
        }
        irb::Attributes argAttributes;
        irb::Type* type = _parseTypeWithAttributesExpression(&argAttributes);
        if (!type)
            return nullptr;
        ExpressionAST* defaultValue = nullptr;
        if (crntToken == TOKEN_OPERATOR_ASSIGNMENT_ASSIGN) {
            getNextToken(); // '='
            defaultValue = parseExpression();
            if (!defaultValue)
                return nullptr;
        }
        arguments.push_back(irb::Argument{name, type, argAttributes});
        defaultValues.push_back(defaultValue);
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

    return new FunctionPrototypeAST(functionName, functionType, arguments/*, attributes*/, defaultValues, isDefined, isSTDFunction, functionRole);
}

// Function definition
ExpressionAST* parseFunctionDefinition(bool isSTDFunction = false, irb::FunctionRole functionRole = irb::FunctionRole::Normal) {
    getNextToken(); // 'func', 'vertex', 'fragment' or 'kernel'
    FunctionPrototypeAST* declaration = parseFunctionPrototype(true, isSTDFunction, functionRole);
    if (!declaration)
        return nullptr;
    
    if (crntToken != '{') {
        declaration->setIsDefined(false);
        return declaration;
    }
    
    if (BlockExpressionAST* expr = dynamic_cast<BlockExpressionAST*>(parseExpression()))
        return new FunctionDefinitionAST(declaration, expr);
    
    return nullptr;
}

// TODO: remove this
// Extern
FunctionPrototypeAST* parseExtern() {
    getNextToken(); // 'extern'

    return parseFunctionPrototype();
}

// TODO: support forward declaration
// Structure declaration
StructureDefinitionAST* parseStructureDeclaration(bool isSTD = false) {
    getNextToken(); // 'struct'
    if (crntToken != TOKEN_IDENTIFIER) {
        logError("expected structure name after 'struct'");
        return nullptr;
    }
    std::string structName = identifierStr;
    getNextToken(); // Structure name

    if (crntToken != '{') {
        logError("expected '{' after structure name");
        return nullptr;
    }
    getNextToken(); // '{'

    _consumeSkips();

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

        _consumeSkips();
    }

    if (crntToken != '}') {
        logError("expected '}' to match the '{'");
        return nullptr;
    }
    getNextToken(); // '}'

    return new StructureDefinitionAST(structName, members, isSTD);
}

// TODO: rename to 'parseEnumDefinition'
EnumDefinitionAST* parseEnumDeclaration(bool isSTD = false) {
    getNextToken(); // 'enum'

    bool isClass = false;
    if (crntToken == TOKEN_CLASS) {
        getNextToken(); // 'class'
        isClass = true;
    }
    
    if (crntToken != TOKEN_IDENTIFIER) {
        logError("expected structure name after 'enum'");
        return nullptr;
    }
    std::string enumName = identifierStr;
    getNextToken(); // Enum name

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
        _consumeSkips();

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
            getNextToken(); // Value
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

    _consumeSkips();

    if (crntToken != '}') {
        logError("expected '}' to match the '{'");
        return nullptr;
    }
    getNextToken(); // '}'

    return new EnumDefinitionAST(enumName, values, isClass, isSTD);
}

ExpressionAST* parseExpression(int expressionPrecedence) {
    _consumeSkips();
    
    ExpressionAST* lhs = parseMain();
    if (!lhs)
        return nullptr;
    
    ExpressionAST* expr = parseBinOpRHS(expressionPrecedence, lhs);

    _consumeSkips();

    return expr;
}

// Main loop
bool mainLoop(AST& ast) {
    // Reset
    resetLexer();

    getNextToken();
    bool success = true;
    while (true) {
        ExpressionAST* expression = nullptr;
        bool skipUntilBlockEnd = true;
        switch (crntToken) {
        case TOKEN_EOF:
            return success;
        case TOKEN_SKIP:
            getNextToken(); // ';'
            skipUntilBlockEnd = false;
            break;
        case TOKEN_FUNC:
            expression = parseFunctionDefinition();
            break;
        case TOKEN_VERTEX:
            expression = parseFunctionDefinition(false, irb::FunctionRole::Vertex);
            break;
        case TOKEN_FRAGMENT:
            expression = parseFunctionDefinition(false, irb::FunctionRole::Fragment);
            break;
        case TOKEN_KERNEL:
            expression = parseFunctionDefinition(false, irb::FunctionRole::Kernel);
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
        case TOKEN_STD:
            getNextToken(); // 'STD'
            switch (crntToken) {
            case TOKEN_FUNC:
                expression = parseFunctionDefinition(true, irb::FunctionRole::Normal);
                break;
            case TOKEN_TYPE_STRUCT:
                expression = parseStructureDeclaration(true);
                break;
            case TOKEN_TYPE_ENUM:
                expression = parseEnumDeclaration(true);
                break;
            default:
                logError("'STD' can only be used with functions, structures and enumerations");
                break;
            }
            break;
        default:
            logError("unknown top level token '" + std::to_string(crntToken) + "'");
            break;
        }

        if (expression) {
            if (expression->initialize())
                ast.addExpression(expression);
            else
                success = false;
        } else if (skipUntilBlockEnd) {
            // TODO: set it to 0 if outside of block
            int blocksToSkip = 1;
            while (true) {
                getNextToken();
                if (crntToken == TOKEN_EOF)
                    return false;
                if (crntToken == '{')
                    blocksToSkip++;
                else if (crntToken == '}')
                    blocksToSkip--;
                if (blocksToSkip == 0) {
                    getNextToken();
                    break;
                }
            }
            success = false;
        }
    }
}

std::string standardLibrarySource = {
    #include "standard_library.inc"
};

bool compileStandardLibrary(AST& ast) {
    setSource(standardLibrarySource);

    return mainLoop(ast);
}

bool compile(AST& ast, const std::string& source) {
    binopPrecedence[TOKEN_OPERATOR_LOGICAL_AND                      ] = 8;
    binopPrecedence[TOKEN_OPERATOR_LOGICAL_OR                       ] = 8;
    // binopPrecedence[TOKEN_OPERATOR_NOT                              ] = 0;

    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_IS_EQUAL              ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_IS_NOT_EQUAL          ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_LESS_THAN             ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_GREATER_THAN          ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_LESS_THAN_OR_EQUAL    ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_GREATER_THAN_OR_EQUAL ] = 10;

    binopPrecedence[TOKEN_OPERATOR_BITWISE_AND                      ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_OR                       ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_LEFT_SHIFT               ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_RIGHT_SHIFT              ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_NOT                      ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_POW                      ] = 100;

    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_PLUS                  ] = 20;
    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_MINUS                 ] = 20;
    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_MULTIPLY              ] = 40;
    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_DIVIDE                ] = 40;
    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_MODULO                ] = 80;

    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_ASSIGN                ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_ADD_AND_ASSIGN        ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_SUBTRACT_AND_ASSIGN   ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_MULTIPLY_AND_ASSIGN   ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_DIVIDE_AND_ASSIGN     ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_MODULO_AND_ASSIGN     ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_AND_AND_ASSIGN        ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_OR_AND_ASSIGN         ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_LEFT_SHIFT_AND_ASSIGN ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_RIGHT_SHIFT_AND_ASSIGN] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_POW_AND_ASSIGN        ] = 4;

    binopPrecedence[TOKEN_OPERATOR_REFERENCE                        ] = 200;
    binopPrecedence[TOKEN_OPERATOR_DEREFERENCE                      ] = 200;
    binopPrecedence[TOKEN_OPERATOR_DOT                              ] = 400;
    binopPrecedence[TOKEN_OPERATOR_FUNCTION_RETURN_TYPE             ] = 400;

    setSource(source);

    return mainLoop(ast);
}

} // namespace lvsl

} // namespace lvslang
