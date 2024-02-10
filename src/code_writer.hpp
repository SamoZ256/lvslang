#ifndef LVSLANG_CODE_WRITER_H
#define LVSLANG_CODE_WRITER_H

#include "ast.hpp"

namespace lvslang {

struct CodeValue {
    std::string code;
};

class CodeWriter {
public:
    CodeWriter(irb::Target aTarget, const AST& aAST) : target(aTarget), ast(aAST) {}

    bool write(std::string& outputCode) {
        std::string codeHeader;
        switch (target) {
        case irb::Target::None:
            IRB_ERROR("No target specified");
            break;
        case irb::Target::Metal:
            codeHeader = "#include <metal_stdlib>\nusing namespace metal;";
            break;
        case irb::Target::HLSL:
            break;
        case irb::Target::GLSL:
            codeHeader = "#version " + getGLSLVersionString()/* + " core"*/;
            break;
        default:
            LVSLANG_ERROR_UNSUPPORTED_TARGET("[IR target]");
            break;
        }
        
        //TODO: enable them only if needed
        if (irb::target == irb::Target::GLSL) {
            enableGLSLExtension(codeHeader, irb::Extension::_8bit_storage);
            enableGLSLExtension(codeHeader, irb::Extension::_16bit_storage);
            enableGLSLExtension(codeHeader, irb::Extension::explicit_arithmetic_types);
        }
        
        std::string code;
        for (auto* expression : ast.getExpressions()) {
            if (auto* value = codegenExpression(expression)) {
                //HACK: check if it contains something
                if (value->code.size() > 0)
                    code += value->code + "\n\n";
            } else {
                return false;
            }
        }

        outputCode = codeHeader + (codeHeader.empty() ? "" : "\n\n") + code;

        return true;
    }

private:
    irb::Target target;
    const AST& ast;

    uint32_t currentIndentation = 0;

    CodeValue* codegenExpression(const ExpressionAST* expression);

    CodeValue* codegenNumberExpression(const NumberExpressionAST* expression);

    CodeValue* codegenVariableExpression(const VariableExpressionAST* expression);

    CodeValue* codegenBinaryExpression(const BinaryExpressionAST* expression);

    CodeValue* codegenBlockExpression(const BlockExpressionAST* expression);

    CodeValue* codegenFunctionPrototype(const FunctionPrototypeAST* expression);

    CodeValue* codegenFunctionDefinition(const FunctionDefinitionAST* expression);

    CodeValue* codegenFunctionCall(const CallExpressionAST* expression);

    CodeValue* codegenReturnExpression(const ReturnExpressionAST* expression);

    CodeValue* codegenIfExpression(const IfExpressionAST* expression);

    CodeValue* codegenWhileExpression(const WhileExpressionAST* expression);

    CodeValue* codegenVariableDeclaration(const VariableDeclarationExpressionAST* expression);

    CodeValue* codegenSubscriptExpression(const SubscriptExpressionAST* expression);

    CodeValue* codegenMemberAccessExpression(const MemberAccessExpressionAST* expression);

    CodeValue* codegenStructureDefinition(const StructureDefinitionAST* expression);

    CodeValue* codegenEnumDefinition(const EnumDefinitionAST* expression);

    CodeValue* codegenEnumValueExpression(const EnumValueExpressionAST* expression);

    CodeValue* codegenInitializerListExpression(const InitializerListExpressionAST* expression);
};

} //namespace lvslang

#endif
