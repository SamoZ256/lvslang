#ifndef LVSLANG_LVSL_TOKEN_H
#define LVSLANG_LVSL_TOKEN_H

namespace lvslang {

namespace lvsl {

#define TOKEN_TYPE_ENUM_MIN TOKEN_TYPE_SAMPLER
#define TOKEN_TYPE_ENUM_MAX TOKEN_TYPE_VOID

#define TOKEN_ATTRIB_ENUM_MIN TOKEN_ATTRIB_COLOR
#define TOKEN_ATTRIB_ENUM_MAX TOKEN_ATTRIB_NOALIAS

enum Token {
    TOKEN_EOF = -1,
    TOKEN_SKIP = -2,

    // -------- Commands --------
    TOKEN_FUNC = -20,
    TOKEN_VERTEX = -21,
    TOKEN_FRAGMENT = -22,
    TOKEN_KERNEL = -23,
    TOKEN_EXTERN = -24,
    TOKEN_RETURN = -25,
    TOKEN_IF = -26,
    TOKEN_ELSE = -27,
    TOKEN_WHILE = -28,
    TOKEN_FOR = -29,
    TOKEN_VAR = -30,
    TOKEN_CONST = -31,
    TOKEN_REGISTER = -32,
    TOKEN_MEMBER = -33,
    TOKEN_STD_FUNCTION = -34,

    // -------- Primary --------
    TOKEN_IDENTIFIER = -40,
    TOKEN_NUMBER = -41,
    TOKEN_CHAR = -42,
    TOKEN_STRING = -43,

    // -------- Types --------

    // Void
    TOKEN_TYPE_VOID = -60,

    // Int
    TOKEN_TYPE_CHAR = -61,
    TOKEN_TYPE_SHORT = -62,
    TOKEN_TYPE_INT = -63,

    // Unsigned int
    TOKEN_TYPE_BOOL = -64,
    TOKEN_TYPE_UCHAR = -65,
    TOKEN_TYPE_USHORT = -66,
    TOKEN_TYPE_UINT = -67,

    // Float
    TOKEN_TYPE_HALF = -68,
    TOKEN_TYPE_FLOAT = -69,

    // User-defined
    TOKEN_TYPE_STRUCT = -70,
    TOKEN_TYPE_ENUM = -71,

    // Built-in
    TOKEN_TYPE_TEXTURE_1D = -72,
    TOKEN_TYPE_TEXTURE_2D = -73,
    TOKEN_TYPE_TEXTURE_3D = -74,
    TOKEN_TYPE_TEXTURE_1D_ARRAY = -75,
    TOKEN_TYPE_TEXTURE_2D_ARRAY = -76,
    TOKEN_TYPE_TEXTURE_CUBE = -77,
    TOKEN_TYPE_TEXTURE_CUBE_ARRAY = -78,
    TOKEN_TYPE_TEXTURE_BUFFER = -79, // For future use

    TOKEN_TYPE_SAMPLER = -80,

    // -------- Attributes --------

    // Basic
    TOKEN_ATTRIB_NOALIAS = -100,
    TOKEN_ATTRIB_NOUNDEF = -101,
    TOKEN_ATTRIB_NOFREE = -102,
    TOKEN_ATTRIB_NOUNWIND = -103,
    TOKEN_ATTRIB_INACCESSIBLE_MEMORY = -104,
    TOKEN_ATTRIB_MUST_PROGRESS = -105,
    TOKEN_ATTRIB_WILL_RETURN = -106,

    // 'attrib'
    TOKEN_ATTRIB_CONSTANT = -107,
    TOKEN_ATTRIB_DEVICE = -108,

    // '[[attrib]]'
    TOKEN_ATTRIB_DESCRIPTOR_SET = -110,
    TOKEN_ATTRIB_POSITION = -111,
    TOKEN_ATTRIB_INPUT = -112,
    TOKEN_ATTRIB_LOCATION = -113,
    TOKEN_ATTRIB_COLOR = -114,

    // -------- Operators --------

    // Logical
    TOKEN_OPERATOR_LOGICAL_AND = -120,
    TOKEN_OPERATOR_LOGICAL_OR = -121,
    TOKEN_OPERATOR_LOGICAL_NOT = -122,

    // Relational
    TOKEN_OPERATOR_RELATIONAL_IS_EQUAL = -123,
    TOKEN_OPERATOR_RELATIONAL_IS_NOT_EQUAL = -124,
    TOKEN_OPERATOR_RELATIONAL_LESS_THAN = -125,
    TOKEN_OPERATOR_RELATIONAL_GREATER_THAN = -126,
    TOKEN_OPERATOR_RELATIONAL_LESS_THAN_OR_EQUAL = -127,
    TOKEN_OPERATOR_RELATIONAL_GREATER_THAN_OR_EQUAL = -128,

    // Bitwise
    TOKEN_OPERATOR_BITWISE_AND = -129,
    TOKEN_OPERATOR_BITWISE_OR = -130,
    TOKEN_OPERATOR_BITWISE_LEFT_SHIFT = -131,
    TOKEN_OPERATOR_BITWISE_RIGHT_SHIFT = -132,
    TOKEN_OPERATOR_BITWISE_NOT = -133,
    TOKEN_OPERATOR_BITWISE_POW = -134,

    // Arithmetic
    TOKEN_OPERATOR_ARITHMETIC_PLUS = -135,
    TOKEN_OPERATOR_ARITHMETIC_MINUS = -136,
    TOKEN_OPERATOR_ARITHMETIC_MULTIPLY = -137,
    TOKEN_OPERATOR_ARITHMETIC_DIVIDE = -138,
    TOKEN_OPERATOR_ARITHMETIC_MODULO = -139,

    // Assignment
    TOKEN_OPERATOR_ASSIGNMENT_ASSIGN = -140,
    TOKEN_OPERATOR_ASSIGNMENT_ADD_AND_ASSIGN = -141,
    TOKEN_OPERATOR_ASSIGNMENT_SUBTRACT_AND_ASSIGN = -142,
    TOKEN_OPERATOR_ASSIGNMENT_MULTIPLY_AND_ASSIGN = -143,
    TOKEN_OPERATOR_ASSIGNMENT_DIVIDE_AND_ASSIGN = -144,
    TOKEN_OPERATOR_ASSIGNMENT_MODULO_AND_ASSIGN = -145,
    TOKEN_OPERATOR_ASSIGNMENT_AND_AND_ASSIGN = -146,
    TOKEN_OPERATOR_ASSIGNMENT_OR_AND_ASSIGN = -147,
    TOKEN_OPERATOR_ASSIGNMENT_LEFT_SHIFT_AND_ASSIGN = -148,
    TOKEN_OPERATOR_ASSIGNMENT_RIGHT_SHIFT_AND_ASSIGN = -149,
    TOKEN_OPERATOR_ASSIGNMENT_POW_AND_ASSIGN = -150,

    // Ternary
    TOKEN_OPERATOR_TERNARY_CONDITIONAL = -151, // TODO: should probably be split into two (e.g. ? and :)
    
    // Other
    TOKEN_OPERATOR_DOT = -152,
    TOKEN_OPERATOR_FUNCTION_RETURN_TYPE = -153,
};

const int TOKEN_OPERATOR_REFERENCE = TOKEN_OPERATOR_LOGICAL_AND;
const int TOKEN_OPERATOR_DEREFERENCE = TOKEN_OPERATOR_ARITHMETIC_MULTIPLY;

inline bool tokenIsType(int token) {
    return (token >= TOKEN_TYPE_ENUM_MIN && token <= TOKEN_TYPE_ENUM_MAX);
}

inline bool tokenIsTextureType(int token) {
    return (token >= TOKEN_TYPE_TEXTURE_BUFFER && token <= TOKEN_TYPE_TEXTURE_1D);
}

inline bool tokenIsAttrib(int token) {
    return (token >= TOKEN_ATTRIB_ENUM_MIN && token <= TOKEN_ATTRIB_ENUM_MAX);
}

} // namespace lvsl

} // namespace lvslang

#endif
