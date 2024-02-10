#ifndef LVSLANG_CODE_WRITER_H
#define LVSLANG_CODE_WRITER_H

#include "ast.hpp"

namespace lvslang {

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
            if (auto* value = expression->codegen()) {
                std::string crntCode = value->getRawName();
                //HACK: check if it contains something
                if (crntCode.size() > 0)
                    code += crntCode + "\n\n";
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
};

} //namespace lvslang

#endif
