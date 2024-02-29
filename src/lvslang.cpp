#include "lvslang/lvslang.hpp"

#include <filesystem>

#include "ir_writer.hpp"
#include "code_writer.hpp"

#include "frontends/lvsl/parser.hpp"
#include "frontends/metal/parser.hpp"

namespace lvslang {

bool compile(const CompileOptions& options, std::string& outputCode) {
    context.reset();
    functionDeclarations.clear();
    source = Source{};
    for (auto& ext : irb::extensions)
        std::get<0>(ext) = false;

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
    
    if (options.target == Target::AIR || options.target == Target::SPIRV) {
        IRWriter writer(options.target, ast, (irb::OptimizationLevel)options.optimizationLevel, options.outputAssembly, options.includeDebugInformation, options.inputName, options.spirvVersion, languageName, languageVersionMajor, languageVersionMinor, languageVersionPatch);

        return writer.write(outputCode);
    } else {
        CodeWriter writer(options.target, ast, options.glslVersion);

        return writer.write(outputCode);
    }
}

} // namespace lvslang
