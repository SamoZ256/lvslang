#ifndef LVSLANG_IR_WRITER_H
#define LVSLANG_IR_WRITER_H

#include "ast.hpp"

namespace lvslang {

class IRWriter {
public:
    IRWriter(irb::Target aTarget, const AST& aAST, irb::OptimizationLevel aOptimizationLevel, bool aOutputAssembly, bool aIncludeDebugInformation, std::string aSourceFilename, irb::SPIRVVersion aSpirvVersion, std::string aLanguageName, uint32_t aLanguageVersionMajor, uint32_t aLanguageVersionMinor, uint32_t aLanguageVersionPatch) : target(aTarget), ast(aAST), optimizationLevel(aOptimizationLevel), outputAssembly(aOutputAssembly), includeDebugInformation(aIncludeDebugInformation), sourceFilename(aSourceFilename), spirvVersion(aSpirvVersion), languageName(aLanguageName), languageVersionMajor(aLanguageVersionMajor), languageVersionMinor(aLanguageVersionMinor), languageVersionPatch(aLanguageVersionPatch) {}

    bool write(std::string& outputCode) {
        std::string codeHeader;
        switch (target) {
        case irb::Target::None:
            IRB_ERROR("No target specified");
            break;
        case irb::Target::SPIRV:
            builder = new irb::SPIRVBuilder(context, "Lvslang", includeDebugInformation);
            break;
        case irb::Target::AIR:
            //TODO: support other data layouts as well
            if (includeDebugInformation)
                codeHeader = "source_filename = \"" + sourceFilename + "\"\n";
            codeHeader += "target datalayout = \"e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32\"\n" \
            "target triple = \"air64-apple-macosx14.0.0\"";
            builder = new irb::AIRBuilder(context, "Lvslang", includeDebugInformation);
            break;
        default:
            LVSLANG_ERROR_UNSUPPORTED_TARGET("[Code target]");
            break;
        }
        
        //TODO: enable them only if needed
        if (irb::target == irb::Target::SPIRV) {
            enableSPIRVExtension(irb::Extension::_8bit_storage);
            enableSPIRVExtension(irb::Extension::_16bit_storage);
            enableSPIRVExtension(irb::Extension::explicit_arithmetic_types);
            
            builder->opImportSTD_EXT("GLSL.std.450");
            builder->opMemoryModel();
        }
        
        std::string code;
        for (auto* expression : ast.getExpressions()) {
            if (!expression->codegen())
                return false;
        }
        bool success = builder->getCode(code, (irb::OptimizationLevel)optimizationLevel, outputAssembly, spirvVersion);
        if (!success)
            return false;

        if (irb::target == irb::Target::AIR)
            code += static_cast<irb::AIRBuilder*>(builder)->createMetadata(languageName, languageVersionMajor, languageVersionMinor, languageVersionPatch, sourceFilename);
        outputCode = codeHeader + (codeHeader.empty() ? "" : (irb::target == irb::Target::AIR ? "\n" : "\n\n")) + code;

        return true;
    }

private:
    irb::Target target;
    const AST& ast;

    irb::OptimizationLevel optimizationLevel;
    bool outputAssembly;
    bool includeDebugInformation;
    std::string sourceFilename;
    irb::SPIRVVersion spirvVersion;
    std::string languageName;
    uint32_t languageVersionMajor, languageVersionMinor, languageVersionPatch;
};

} //namespace lvslang

#endif
