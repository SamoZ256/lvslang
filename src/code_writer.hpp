#ifndef LVSLANG_CODE_WRITER_H
#define LVSLANG_CODE_WRITER_H

#include "ast.hpp"

namespace lvslang {

static std::string extensionLUT[(int)irb::Extension::MaxEnum] = {
    "GL_EXT_shader_8bit_storage",
    "GL_EXT_shader_16bit_storage",
    "GL_EXT_shader_explicit_arithmetic_types"
};

struct CodeValue {
    std::string code;
};

class CodeWriter {
public:
    CodeWriter(Target aTarget, const AST& aAST, GLSLVersion aGLSLVersion) : target(aTarget), ast(aAST), glslVersion(aGLSLVersion) {}

    bool write(std::string& outputCode) {
        std::string codeHeader;
        switch (target) {
        case Target::None:
            IRB_ERROR("No target specified");
            break;
        case Target::Metal:
            codeHeader = "#include <metal_stdlib>\nusing namespace metal;";
            break;
        case Target::HLSL:
            break;
        case Target::GLSL:
            // Check if the GLSL version is supported
            LVSLANG_CHECK_ARGUMENT(GLSLVersion, glslVersion);
            switch (glslVersion) {
            case GLSLVersion::_1_10 ... GLSLVersion::_1_50:
                LVSLANG_ERROR_UNSUPPORTED_TARGET_VERSIONS("1.10 to 1.50", "GLSL");
                break;
            default:
                break;
            }
            
            codeHeader = "#version " + glslVersionMap.at(glslVersion)/* + " core"*/;
            break;
        default:
            LVSLANG_ERROR_UNSUPPORTED_TARGET("[IR target]");
            break;
        }
        
        // TODO: enable them only if needed
        if (target == Target::GLSL) {
            enableGLSLExtension(codeHeader, irb::Extension::_8bit_storage);
            enableGLSLExtension(codeHeader, irb::Extension::_16bit_storage);
            enableGLSLExtension(codeHeader, irb::Extension::explicit_arithmetic_types);
        }
        
        std::string code;
        for (auto* expression : ast.getExpressions()) {
            if (auto* value = codegenExpression(expression)) {
                // HACK: check if it contains something
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
    Target target;
    const AST& ast;

    // GLSL
    GLSLVersion glslVersion;
    bool extensionsEnabled[(int)irb::Extension::MaxEnum] = {false};

    uint32_t currentIndentation = 0;

    // Codegen
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

    CodeValue* codegenDereferenceExpression(const DereferenceExpressionAST* expression);

    // Helper functions
    inline void enableGLSLExtension(std::string& codeHeader, irb::Extension extension) {
        bool& enabled = extensionsEnabled[(int)extension];
        if (!enabled) {
            codeHeader += "\n\n#extension " + extensionLUT[(int)extension] + " : enable";
            enabled = true;
        }
    }
};

} // namespace lvslang

#endif
