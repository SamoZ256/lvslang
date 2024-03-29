#include "lexer.hpp"

#include "../../common.hpp"
#include "../../../shader_ir_builder/value.hpp"

namespace lvslang {

namespace lvsl {

int getTypeFromString(const std::string& strType) {
    componentCount = 0;
    columnCount = 0;
    rowCount = 0;
    if (strType == "void")
        return TOKEN_TYPE_VOID;

    if (strType == "char")
        return TOKEN_TYPE_CHAR;
    if (strType == "short")
        return TOKEN_TYPE_SHORT;
    if (strType == "int")
        return TOKEN_TYPE_INT;
    //if (strType == "int64")
    //    return TOKEN_TYPE_INT64;

    if (strType == "bool")
        return TOKEN_TYPE_BOOL;
    if (strType == "uchar")
        return TOKEN_TYPE_UCHAR;
    if (strType == "ushort")
        return TOKEN_TYPE_USHORT;
    if (strType == "uint")
        return TOKEN_TYPE_UINT;
    //if (strType == "uint64")
    //    return TOKEN_TYPE_UINT64;

    if (strType == "half")
        return TOKEN_TYPE_HALF;
    if (strType == "float")
        return TOKEN_TYPE_FLOAT;
    //if (strType == "float64")
    //    return TOKEN_TYPE_FLOAT64;
    
    if (strType == "char2") {
        componentCount = 2;
        return TOKEN_TYPE_CHAR;
    } if (strType == "char3") {
        componentCount = 3;
        return TOKEN_TYPE_CHAR;
    } if (strType == "char4") {
        componentCount = 4;
        return TOKEN_TYPE_CHAR;
    } if (strType == "short2") {
        componentCount = 2;
        return TOKEN_TYPE_SHORT;
    } if (strType == "short3") {
        componentCount = 3;
        return TOKEN_TYPE_SHORT;
    } if (strType == "short4") {
        componentCount = 4;
        return TOKEN_TYPE_SHORT;
    } if (strType == "int2") {
        componentCount = 2;
        return TOKEN_TYPE_INT;
    } if (strType == "int3") {
        componentCount = 3;
        return TOKEN_TYPE_INT;
    } if (strType == "int4") {
        componentCount = 4;
        return TOKEN_TYPE_INT;
    }
    
    if (strType == "bool2") {
        componentCount = 2;
        return TOKEN_TYPE_BOOL;
    } if (strType == "bool3") {
        componentCount = 3;
        return TOKEN_TYPE_BOOL;
    } if (strType == "bool4") {
        componentCount = 4;
        return TOKEN_TYPE_BOOL;
    } if (strType == "uchar2") {
        componentCount = 2;
        return TOKEN_TYPE_UCHAR;
    } if (strType == "uchar3") {
        componentCount = 3;
        return TOKEN_TYPE_UCHAR;
    } if (strType == "uchar4") {
        componentCount = 4;
        return TOKEN_TYPE_UCHAR;
    } if (strType == "ushort2") {
        componentCount = 2;
        return TOKEN_TYPE_USHORT;
    } if (strType == "ushort3") {
        componentCount = 3;
        return TOKEN_TYPE_USHORT;
    } if (strType == "ushort4") {
        componentCount = 4;
        return TOKEN_TYPE_USHORT;
    } if (strType == "uint2") {
        componentCount = 2;
        return TOKEN_TYPE_UINT;
    } if (strType == "uint3") {
        componentCount = 3;
        return TOKEN_TYPE_UINT;
    } if (strType == "uint4") {
        componentCount = 4;
        return TOKEN_TYPE_UINT;
    }

    if (strType == "half2") {
        componentCount = 2;
        return TOKEN_TYPE_HALF;
    } if (strType == "half3") {
        componentCount = 3;
        return TOKEN_TYPE_HALF;
    } if (strType == "half4") {
        componentCount = 4;
        return TOKEN_TYPE_HALF;
    } if (strType == "float2") {
        componentCount = 2;
        return TOKEN_TYPE_FLOAT;
    } if (strType == "float3") {
        componentCount = 3;
        return TOKEN_TYPE_FLOAT;
    } if (strType == "float4") {
        componentCount = 4;
        return TOKEN_TYPE_FLOAT;
    }

    if (strType == "half2x2") {
        columnCount = 2;
        rowCount = 2;
        return TOKEN_TYPE_HALF;
    } if (strType == "half2x3") {
        columnCount = 2;
        rowCount = 3;
        return TOKEN_TYPE_HALF;
    } if (strType == "half2x4") {
        columnCount = 2;
        rowCount = 4;
        return TOKEN_TYPE_HALF;
    } if (strType == "half3x2") {
        columnCount = 3;
        rowCount = 2;
        return TOKEN_TYPE_HALF;
    } if (strType == "half3x3") {
        columnCount = 3;
        rowCount = 3;
        return TOKEN_TYPE_HALF;
    } if (strType == "half3x4") {
        columnCount = 3;
        rowCount = 4;
        return TOKEN_TYPE_HALF;
    }  if (strType == "half4x2") {
        columnCount = 4;
        rowCount = 2;
        return TOKEN_TYPE_HALF;
    }  if (strType == "half4x3") {
        columnCount = 4;
        rowCount = 3;
        return TOKEN_TYPE_HALF;
    }  if (strType == "half4x4") {
        columnCount = 4;
        rowCount = 4;
        return TOKEN_TYPE_HALF;
    }

    if (strType == "float2x2") {
        columnCount = 2;
        rowCount = 2;
        return TOKEN_TYPE_FLOAT;
    } if (strType == "float2x3") {
        columnCount = 2;
        rowCount = 3;
        return TOKEN_TYPE_FLOAT;
    } if (strType == "float2x4") {
        columnCount = 2;
        rowCount = 4;
        return TOKEN_TYPE_FLOAT;
    } if (strType == "float3x2") {
        columnCount = 3;
        rowCount = 2;
        return TOKEN_TYPE_FLOAT;
    } if (strType == "float3x3") {
        columnCount = 3;
        rowCount = 3;
        return TOKEN_TYPE_FLOAT;
    } if (strType == "float3x4") {
        columnCount = 3;
        rowCount = 4;
        return TOKEN_TYPE_FLOAT;
    }  if (strType == "float4x2") {
        columnCount = 4;
        rowCount = 2;
        return TOKEN_TYPE_FLOAT;
    }  if (strType == "float4x3") {
        columnCount = 4;
        rowCount = 3;
        return TOKEN_TYPE_FLOAT;
    }  if (strType == "float4x4") {
        columnCount = 4;
        rowCount = 4;
        return TOKEN_TYPE_FLOAT;
    }
    
    if (strType == "struct")
        return TOKEN_TYPE_STRUCT;
    if (strType == "enum")
        return TOKEN_TYPE_ENUM;

    if (identifierStr == "texture1D")
        return TOKEN_TYPE_TEXTURE_1D;
    if (identifierStr == "texture2D")
        return TOKEN_TYPE_TEXTURE_2D;
    if (identifierStr == "texture3D")
        return TOKEN_TYPE_TEXTURE_3D;
    if (identifierStr == "texture1D_array")
        return TOKEN_TYPE_TEXTURE_1D_ARRAY;
    if (identifierStr == "texture2D_array")
        return TOKEN_TYPE_TEXTURE_2D_ARRAY;
    if (identifierStr == "textureCube")
        return TOKEN_TYPE_TEXTURE_CUBE;
    if (identifierStr == "textureCube_array")
        return TOKEN_TYPE_TEXTURE_CUBE_ARRAY;
    if (identifierStr == "texture_buffer")
        return TOKEN_TYPE_TEXTURE_BUFFER;

    if (identifierStr == "sampler")
        return TOKEN_TYPE_SAMPLER;
    
    /*
    if (strType == "buffer") {
        typeIsBuiltin = true;
        builtinTypeID = TypeID::Buffer;
        return TOKEN_TYPE_BUFFER;
    } if (strType == "texture") {
        typeIsBuiltin = true;
        builtinTypeID = TypeID::Texture;
        return TOKEN_TYPE_TEXTURE;
    } if (strType == "sampler") {
        typeIsBuiltin = true;
        builtinTypeID = TypeID::Sampler;
        return TOKEN_TYPE_SAMPLER;
    }
    */
    
    return 0;
}

int getOperatorFromString(const std::string& operatorStr) {
    if (operatorStr == "&&")
        return TOKEN_OPERATOR_LOGICAL_AND;
    if (operatorStr == "||")
        return TOKEN_OPERATOR_LOGICAL_OR;
    if (operatorStr == "!")
        return TOKEN_OPERATOR_LOGICAL_NOT;

    if (operatorStr == "==")
        return TOKEN_OPERATOR_RELATIONAL_IS_EQUAL;
    if (operatorStr == "!=")
        return TOKEN_OPERATOR_RELATIONAL_IS_NOT_EQUAL;
    if (operatorStr == "<")
        return TOKEN_OPERATOR_RELATIONAL_LESS_THAN;
    if (operatorStr == ">")
        return TOKEN_OPERATOR_RELATIONAL_GREATER_THAN;
    if (operatorStr == "<=")
        return TOKEN_OPERATOR_RELATIONAL_LESS_THAN_OR_EQUAL;
    if (operatorStr == ">=")
        return TOKEN_OPERATOR_RELATIONAL_GREATER_THAN_OR_EQUAL;

    if (operatorStr == "&")
        return TOKEN_OPERATOR_BITWISE_AND;
    if (operatorStr == "|")
        return TOKEN_OPERATOR_BITWISE_OR;
    if (operatorStr == "<<")
        return TOKEN_OPERATOR_BITWISE_OR;
    if (operatorStr == ">>")
        return TOKEN_OPERATOR_BITWISE_OR;
    if (operatorStr == "~")
        return TOKEN_OPERATOR_BITWISE_OR;
    if (operatorStr == "^")
        return TOKEN_OPERATOR_BITWISE_OR;

    if (operatorStr == "+")
        return TOKEN_OPERATOR_ARITHMETIC_PLUS;
    if (operatorStr == "-")
        return TOKEN_OPERATOR_ARITHMETIC_MINUS;
    if (operatorStr == "*")
        return TOKEN_OPERATOR_ARITHMETIC_MULTIPLY;
    if (operatorStr == "/")
        return TOKEN_OPERATOR_ARITHMETIC_DIVIDE;
    if (operatorStr == "%")
        return TOKEN_OPERATOR_ARITHMETIC_MODULO;

    if (operatorStr == "=")
        return TOKEN_OPERATOR_ASSIGNMENT_ASSIGN;
    if (operatorStr == "+=")
        return TOKEN_OPERATOR_ASSIGNMENT_ADD_AND_ASSIGN;
    if (operatorStr == "-=")
        return TOKEN_OPERATOR_ASSIGNMENT_SUBTRACT_AND_ASSIGN;
    if (operatorStr == "*=")
        return TOKEN_OPERATOR_ASSIGNMENT_MULTIPLY_AND_ASSIGN;
    if (operatorStr == "/=")
        return TOKEN_OPERATOR_ASSIGNMENT_DIVIDE_AND_ASSIGN;
    if (operatorStr == "%=")
        return TOKEN_OPERATOR_ASSIGNMENT_MODULO_AND_ASSIGN;
    if (operatorStr == "&=")
        return TOKEN_OPERATOR_ASSIGNMENT_AND_AND_ASSIGN;
    if (operatorStr == "|=")
        return TOKEN_OPERATOR_ASSIGNMENT_OR_AND_ASSIGN;
    if (operatorStr == "<<=")
        return TOKEN_OPERATOR_ASSIGNMENT_LEFT_SHIFT_AND_ASSIGN;
    if (operatorStr == ">>=")
        return TOKEN_OPERATOR_ASSIGNMENT_RIGHT_SHIFT_AND_ASSIGN;
    if (operatorStr == "^=")
        return TOKEN_OPERATOR_ASSIGNMENT_POW_AND_ASSIGN;
    
    // TODO: ternary operator

    if (operatorStr == ".")
        return TOKEN_OPERATOR_DOT;
    if (operatorStr == "->")
        return TOKEN_OPERATOR_FUNCTION_RETURN_TYPE;
    
    return 0;
}

struct Macro {
    std::vector<std::string> arguments;
    std::string body;
};

std::map<std::string, Macro> macros;

int lastChar;

void resetLexer() {
    lastChar = ' ';
    macros.clear();
}

inline void skipWhitespaces() {
    while (isspace(lastChar) && lastChar != '\n')
        lastChar = getNextChar();
}

inline std::string getIdentifier() {
    std::string str(1, lastChar);
    while (isalnum(lastChar = getNextChar()) || lastChar == '_')
        str += lastChar;

    return str;
}

int _getNextToken() {
    // Whitespace
    skipWhitespaces();
        
    if (lastChar == ';' || lastChar == '\n') {
        lastChar = getNextChar();
        
        return TOKEN_SKIP;
    }

    // Comment
    if (lastChar == '/') {
        lastChar = getNextChar();
        if (lastChar == '/') {
            do {
                lastChar = getNextChar();
            } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

            if (lastChar != EOF)
                return _getNextToken();
        } else {
            operatorStr = "/";
            return TOKEN_OPERATOR_ARITHMETIC_DIVIDE;
        }
    }

    // Macros
    while (lastChar == '#') {
        if (isalpha(lastChar = getNextChar())) {
            std::string macroKeyword = getIdentifier();
            skipWhitespaces();
            
            if (macroKeyword == "define") { // Define
                if (isalpha(lastChar) || lastChar == '_') {
                    std::string macroName = getIdentifier();
                    
                    Macro macro;
                    if (lastChar == '(') {
                        do {
                            lastChar = getNextChar(); // '(' or ','
                            skipWhitespaces();
                            macro.arguments.push_back(getIdentifier());
                            skipWhitespaces();
                        } while (lastChar == ',');
                        if (lastChar != ')') {
                            logError("expected ')' to match the '(' in the macro definition");
                            lastChar = getNextChar();
                            return 0;
                        }
                        lastChar = getNextChar();
                    }
                    skipWhitespaces();

                    while (lastChar != EOF && lastChar != '\n' && lastChar != '\r') {
                        macro.body += lastChar;
                        lastChar = getNextChar();
                    }

                    macros[macroName] = macro;
                } else {
                    logError("expected macro name");
                    lastChar = getNextChar();
                    return 0;
                }
            } else if (macroKeyword == "undef") { // Undefine
                std::string macroName = getIdentifier();
                macros.erase(macroName);
            } else if (macroKeyword == "ifdef" || macroKeyword == "ifndef") { // If defined / not defined
                std::string macroName = getIdentifier();
                bool exprTrue = (macros.find(macroName) != macros.end());
                if (macroKeyword == "ifndef")
                    exprTrue = !exprTrue;
                
                while (lastChar != 0 && lastChar != '\n' && lastChar != '\r')
                    lastChar = getNextChar();
                lastChar = getNextChar();

                std::string codeTrue;
                while (lastChar != 0 && lastChar != '#') {
                    codeTrue += lastChar;
                    lastChar = getNextChar();
                }
                lastChar = getNextChar();

                macroKeyword = getIdentifier();
                std::string codeFalse;
                if (macroKeyword == "else") { // Else
                    while (lastChar != 0 && lastChar != '\n' && lastChar != '\r')
                        lastChar = getNextChar();
                    lastChar = getNextChar();

                    while (lastChar != 0 && lastChar != '#') {
                        codeFalse += lastChar;
                        lastChar = getNextChar();
                    }
                    lastChar = getNextChar();

                    macroKeyword = getIdentifier();
                    if (macroKeyword == "endif") { // End if
                        // Do nothing
                    } else {
                        logError("expected 'endif' after 'else'");
                        lastChar = getNextChar();
                        return 0;
                    }
                } else if (macroKeyword == "endif") { // End if
                    // Do nothing
                } else {
                    logError("expected 'else' or 'endif' after 'ifdef' or 'ifndef'");
                    lastChar = getNextChar();
                    return 0;
                }
                lastChar = getNextChar();

                bool pushedMacro = false;
                if (exprTrue) {
                    source.macroStack.push_back({codeTrue});
                    pushedMacro = true;
                } else if (!codeFalse.empty()) {
                    source.macroStack.push_back({codeFalse});
                    pushedMacro = true;
                }
                
                // Start consuming the macro
                if (pushedMacro)
                    lastChar = getNextChar();
                
                return _getNextToken();
            }
        } else {
            logError("expected macro after '#'");
            lastChar = getNextChar();
            return 0;
        }
        while (isspace(lastChar))
            lastChar = getNextChar();   
    }
    
    // Text
    if (isalpha(lastChar) || lastChar == '_') {
        identifierStr = getIdentifier();

        if (identifierStr == "func")
            return TOKEN_FUNC;
        if (identifierStr == "vertex")
            return TOKEN_VERTEX;
        if (identifierStr == "fragment")
            return TOKEN_FRAGMENT;
        if (identifierStr == "kernel")
            return TOKEN_KERNEL;
        if (identifierStr == "extern")
            return TOKEN_EXTERN;
        if (identifierStr == "return")
            return TOKEN_RETURN;
        if (identifierStr == "if")
            return TOKEN_IF;
        if (identifierStr == "else")
            return TOKEN_ELSE;
        if (identifierStr == "while")
            return TOKEN_WHILE;
        if (identifierStr == "for")
            return TOKEN_FOR;
        if (identifierStr == "var")
            return TOKEN_VAR;
        if (identifierStr == "const")
            return TOKEN_CONST;
        if (identifierStr == "register")
            return TOKEN_REGISTER;
        if (identifierStr == "member")
            return TOKEN_MEMBER;
        if (identifierStr == "class")
            return TOKEN_CLASS;
        if (identifierStr == "STD")
            return TOKEN_STD;
        
        int type = getTypeFromString(identifierStr);
        if (type != 0)
            return type;
        
        if (identifierStr == "noalias")
            return TOKEN_ATTRIB_NOALIAS;
        if (identifierStr == "noundef")
            return TOKEN_ATTRIB_NOUNDEF;
        if (identifierStr == "nofree")
            return TOKEN_ATTRIB_NOFREE;
        if (identifierStr == "nounwind")
            return TOKEN_ATTRIB_NOUNWIND;
        if (identifierStr == "inaccessible_memory")
            return TOKEN_ATTRIB_INACCESSIBLE_MEMORY;
        if (identifierStr == "must_progress")
            return TOKEN_ATTRIB_MUST_PROGRESS;
        if (identifierStr == "will_return")
            return TOKEN_ATTRIB_WILL_RETURN;

        if (identifierStr == "constant")
            return TOKEN_ATTRIB_CONSTANT;
        if (identifierStr == "device")
            return TOKEN_ATTRIB_DEVICE;

        if (identifierStr == "descriptor_set")
            return TOKEN_ATTRIB_DESCRIPTOR_SET;
        if (identifierStr == "position")
            return TOKEN_ATTRIB_POSITION;
        if (identifierStr == "input")
            return TOKEN_ATTRIB_INPUT;
        if (identifierStr == "location")
            return TOKEN_ATTRIB_LOCATION;
        if (identifierStr == "color")
            return TOKEN_ATTRIB_COLOR;
        
        // Macro
        auto pos = macros.find(identifierStr);
        if (pos != macros.end()) {
            const auto& macro = pos->second;
            std::vector<std::string> params;
            if (lastChar == '(') {
                do {
                    lastChar = getNextChar();
                    skipWhitespaces();
                    std::string param;
                    int32_t parenCount = 0;
                    while (lastChar != 0 && (lastChar != ',' || parenCount > 0) && (lastChar != ')' || parenCount > 0)) {
                        if (lastChar == '(')
                            parenCount++;
                        if (lastChar == ')')
                            parenCount--;
                        param += lastChar;
                        lastChar = getNextChar();
                    }
                    params.push_back(param);
                } while (lastChar == ',');
                if (lastChar != ')') {
                    logError("expected ')' to match the '(' in a macro call");
                    lastChar = getNextChar();
                    return 0;
                }
                lastChar = getNextChar();
            }

            if (params.size() != macro.arguments.size()) {
                logError("expected " + std::to_string(macro.arguments.size()) + " arguments in a macro call, got " + std::to_string(params.size()) + " instead");
                lastChar = getNextChar();
                return 0;
            }

            std::string macroBody = macro.body;

            // Replace parameters
            for (uint32_t i = 0; i < macro.arguments.size(); i++) {
                std::string param = macro.arguments[i];
                std::string arg = params[i];
                size_t pos = 0;
                while ((pos = macroBody.find(param, pos)) != std::string::npos) {
                    bool shouldReplace = true;

                    // Check if it's a part of another identifier
                    if (pos > 0) {
                        char c = macroBody[pos - 1];
                        if (isalpha(c) || c == '_')
                            shouldReplace = false;
                    }
                    if (pos + param.length() < macroBody.length()) {
                        char c = macroBody[pos + param.length()];
                        if (isalnum(c) || c == '_')
                            shouldReplace = false;
                    }

                    if (shouldReplace) {
                        macroBody.replace(pos, param.length(), arg);
                        pos += arg.length();
                    }
                }
            }

            source.macroStack.push_back({macroBody});

            // Start consuming the macro
            lastChar = getNextChar();

            return _getNextToken();
        }
        
        return TOKEN_IDENTIFIER;
    }

    // Operator
    if (charIsOperator(lastChar)) {
        operatorStr = "";
        do {
            operatorStr += lastChar;
            lastChar = getNextChar();
        } while (charIsOperator(lastChar));

        int op = getOperatorFromString(operatorStr);
        if (!op) {
            logError("unknown operator '" + operatorStr + "'");
            lastChar = getNextChar();
            return 0;
        }

        return op;
    }

    // Number
    if (isdigit(lastChar) || lastChar == '.') {
        std::string numStr;
        bool dotUsed = false;
        do {
            if (lastChar == '.')
                dotUsed = true;
            numStr += lastChar;
            lastChar = getNextChar();
        } while (isdigit(lastChar) || (lastChar == '.' && !dotUsed));
        switch (lastChar) {
            //case 'd':
            case 'f':
            case 'h':
            case 'i':
            case 'u':
                numTypeStr = lastChar;
                lastChar = getNextChar();
                break;
            default:
                numTypeStr = 0;
                break;
        }

        numValueD = strtod(numStr.c_str(), nullptr);
        numValueL = strtol(numStr.c_str(), nullptr, 0);
        numValueU = strtoul(numStr.c_str(), nullptr, 0);

        if (!numTypeStr) {
            if (dotUsed)
                numTypeStr = 'f';
            else
                numTypeStr = 'i';
        }

        return TOKEN_NUMBER;
    }

    // Single quote string
    if (lastChar == '\'') {
        lastChar = getNextChar();
        if (lastChar == '\\') {
            lastChar = getNextChar();
            lastChar = getEscapedVersionOfChar(lastChar);
        }
        numValueL = lastChar;

        lastChar = getNextChar();
        if (lastChar != '\'') {
            logError("Expected enclosing ' (single quote)");
            lastChar = getNextChar();
            return 0;
        }
        lastChar = getNextChar();

        return TOKEN_CHAR;
    }
    
    // Double quote string
    if (lastChar == '"') {
        identifierStr = "";
        bool escape = false;
        while (true) {
            lastChar = getNextChar();
            if (lastChar == '"')
                break;
            if (lastChar == '\\') {
                escape = true;
                continue;
            }
            if (escape) {
                lastChar = getEscapedVersionOfChar(lastChar);
                escape = false;
            }
            identifierStr += lastChar;
        }
        lastChar = getNextChar();

        return TOKEN_STRING;
    }

    // End of file
    if (lastChar == 0) // TODO: find out why EOF should be -1 intead of 1
        return TOKEN_EOF;
    
    // Character as ASCII
    char thisChar = lastChar;
    lastChar = getNextChar();

    return thisChar;
}

int getNextToken() {
    return crntToken = _getNextToken();
}

} // namespace lvsl

} // namespace lvslang
