#include "lvslang/lvslang.hpp"

#include <filesystem>

#include "ast.hpp"

#include "frontends/lvsl/parser.hpp"
#include "frontends/metal/parser.hpp"

namespace lvslang {

bool compile(const CompileOptions& options, std::string& outputCode) {
    context.reset();
    currentIndentation = 0;
    functionDeclarations.clear();
    source = Source{};

    irb::target = options.target;
    irb::spirvVersion = options.spirvVersion;
    lvslang::glslVersion = options.glslVersion;

    std::string codeHeader;
    switch (irb::target) {
    case irb::Target::None:
        IRB_ERROR("No target specified");
        break;
    case irb::Target::Metal:
        codeHeader = "#include <metal_stdlib>\nusing namespace metal;";
        break;
    case irb::Target::GLSL:
        codeHeader = "#version " + getGLSLVersionString()/* + " core"*/;
        break;
    case irb::Target::HLSL:
        break;
    case irb::Target::SPIRV:
        builder = new irb::SPIRVBuilder(context, "Lvslang", options.includeDebugInformation);
        break;
    case irb::Target::AIR:
        //TODO: support other data layouts as well
        if (options.includeDebugInformation)
            codeHeader = "source_filename = \"" + options.inputName + "\"\n";
        codeHeader += "target datalayout = \"e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32\"\n" \
        "target triple = \"air64-apple-macosx14.0.0\"";
        builder = new irb::AIRBuilder(context, "Lvslang", options.includeDebugInformation);
        break;
    default:
        LVSLANG_ERROR_UNSUPPORTED_TARGET("Unknown");
        break;
    }

    //Extensions
    //TODO: enable them only if needed
    enableExtension(codeHeader, irb::Extension::_8bit_storage);
    enableExtension(codeHeader, irb::Extension::_16bit_storage);
    enableExtension(codeHeader, irb::Extension::explicit_arithmetic_types);

    if (irb::target == irb::Target::SPIRV) {
        builder->opImportSTD_EXT("GLSL.std.450");
        builder->opMemoryModel();
    }

    std::string extension = options.inputName.substr(options.inputName.find_last_of('.'));
    AST ast;
    bool success;
    if (extension == ".lvsl") {
        success = lvsl::compileStandardLibrary(ast);
    } else if (extension == ".metal") {
        success = metal::compileStandardLibrary(ast);
    } else {
        throw std::runtime_error("unsupported output file extension '" + extension + "'");
    }

    if (!success)
        return false;
    
    std::string languageName;
    uint32_t languageVersionMajor, languageVersionMinor, languageVersionPatch;
    if (extension == ".lvsl") {
        languageName = "LVSL";
        languageVersionMajor = 0;
        languageVersionMinor = 7;
        languageVersionPatch = 0;
        success = lvsl::compile(ast, options.source);
    } else if (extension == ".metal") {
        languageName = "Metal";
        languageVersionMajor = 3;
        languageVersionMinor = 1;
        languageVersionPatch = 0;
        success = metal::compile(ast, options.source);
    } else {
        return false;
    }
    
    if (!success)
        return false;
    
    std::string code;
    for (auto* expression : ast.getExpressions()) {
        if (auto* value = expression->codegen()) {
            std::string crntCode = value->getRawName();
            //HACK: check if it contains something
            if (TARGET_IS_CODE(irb::target) && crntCode.size() > 0)
                code += crntCode + "\n\n";
        }
    }
    if (TARGET_IS_IR(irb::target)) {
        success = builder->getCode(code, (irb::OptimizationLevel)options.optimizationLevel, options.outputAssembly, options.spirvVersion);
        if (!success)
            return false;
    }

    code = codeHeader + (codeHeader.empty() ? "" : (irb::target == irb::Target::AIR ? "\n" : "\n\n")) + code;
    if (irb::target == irb::Target::AIR)
        code += static_cast<irb::AIRBuilder*>(builder)->createMetadata(languageName, languageVersionMajor, languageVersionMinor, languageVersionPatch, options.inputName);
    
    outputCode = code;

    return true;
}

} //namespace lvslang
