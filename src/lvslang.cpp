#include "lvslang/lvslang.hpp"

#include <filesystem>

#include "spirv-tools/libspirv.hpp"
#include "spirv-tools/optimizer.hpp"

#include "ast.hpp"

#include "frontends/lvsl/parser.hpp"
#include "frontends/metal/parser.hpp"

namespace lvslang {

bool compile(const CompileOptions& options, std::string& outputCode) {
    context.reset();
    currentIndentation = 0;
    functionDeclarations.clear();
    context.codeHeader = "";
    source = Source{};

    irb::target = options.target;
    irb::spirvVersion = options.spirvVersion;
    lvslang::glslVersion = options.glslVersion;

    switch (irb::target) {
    case irb::Target::None:
        IRB_ERROR("No target specified");
        break;
    case irb::Target::Metal:
        context.codeHeader = "#include <metal_stdlib>\nusing namespace metal;";
        break;
    case irb::Target::GLSL:
        context.codeHeader = "#version " + getGLSLVersionString()/* + " core"*/;
        break;
    case irb::Target::HLSL:
        break;
    case irb::Target::SPIRV:
        builder = new irb::SPIRVBuilder(context, "Lvslang", options.includeDebugInformation);
        break;
    case irb::Target::AIR:
        //TODO: support other data layouts as well
        if (options.includeDebugInformation)
            context.codeHeader = "source_filename = \"" + options.inputName + "\"\n";
        context.codeHeader += "target datalayout = \"e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32\"\n" \
        "target triple = \"air64-apple-macosx14.0.0\"";
        builder = new irb::AIRBuilder(context, "Lvslang", options.includeDebugInformation);
        break;
    default:
        LVSLANG_ERROR_UNSUPPORTED_TARGET("Unknown");
        break;
    }

    //Extensions
    //TODO: enable them only if needed
    enableExtension(irb::Extension::_8bit_storage);
    enableExtension(irb::Extension::_16bit_storage);
    enableExtension(irb::Extension::explicit_arithmetic_types);

    if (irb::target == irb::Target::SPIRV) {
        builder->opImportSTD_EXT("GLSL.std.450");
        builder->opMemoryModel();
    }

    std::string extension = options.inputName.substr(options.inputName.find_last_of('.'));
    bool success;
    if (extension == ".lvsl") {
        lvsl::compileStandardLibrary();
    } else if (extension == ".metal") {
        metal::compileStandardLibrary();
    } else {
        throw std::runtime_error("unsupported output file extension '" + extension + "'");
    }
    
    std::string languageName;
    uint32_t languageVersionMajor, languageVersionMinor, languageVersionPatch;
    if (extension == ".lvsl") {
        languageName = "LVSL";
        languageVersionMajor = 0;
        languageVersionMinor = 7;
        languageVersionPatch = 0;
        success = lvsl::compile(options.source);
    } else if (extension == ".metal") {
        languageName = "Metal";
        languageVersionMajor = 3;
        languageVersionMinor = 1;
        languageVersionPatch = 0;
        success = metal::compile(options.source);
    } else {
        return false;
    }
    
    if (!success)
        return false;

    std::string code = context.codeHeader + (context.codeHeader.empty() ? "" : (irb::target == irb::Target::AIR ? "\n" : "\n\n")) + (TARGET_IS_IR(irb::target) ? builder->getCode((irb::OptimizationLevel)options.optimizationLevel, options.outputAssembly) : context.codeMain);
    if (irb::target == irb::Target::AIR)
        code += static_cast<irb::AIRBuilder*>(builder)->createMetadata(languageName, languageVersionMajor, languageVersionMinor, languageVersionPatch, options.inputName);
    
    //Assemble and optimize
    if (irb::target == irb::Target::SPIRV) {
        //std::cout << code << std::endl;
        //TODO: uncomment?
        //if (options.optimizationLevel == OptimizationLevel::None && options.outputAssembly) {
        //    outputCode = code;
        //} else {
        spv_target_env targetEnv;
        //TODO: use vulkan env?
        switch (options.spirvVersion) {
        case irb::SPIRVVersion::_1_0:
            targetEnv = SPV_ENV_UNIVERSAL_1_0;
            break;
        case irb::SPIRVVersion::_1_1:
            targetEnv = SPV_ENV_UNIVERSAL_1_1;
            break;
        case irb::SPIRVVersion::_1_2:
            targetEnv = SPV_ENV_UNIVERSAL_1_2;
            break;
        case irb::SPIRVVersion::_1_3:
            targetEnv = SPV_ENV_UNIVERSAL_1_3;
            break;
        case irb::SPIRVVersion::_1_4:
            targetEnv = SPV_ENV_UNIVERSAL_1_4;
            break;
        case irb::SPIRVVersion::_1_5:
            targetEnv = SPV_ENV_UNIVERSAL_1_5;
            break;
        case irb::SPIRVVersion::_1_6:
            targetEnv = SPV_ENV_UNIVERSAL_1_6;
            break;
        default:
            break;
        }

        spvtools::SpirvTools core(targetEnv);
        spvtools::Optimizer opt(targetEnv);

        auto printMsgToStderr = [](spv_message_level_t, const char* source, const spv_position_t& pos, const char* message) {
            std::cerr << pos.line << ":" << pos.column << ": " << SET_TEXT_COLOR("31") << "error" << RESET_TEXT_COLOR() << ": " << message << std::endl;
            //std::cout << source << std::endl;
            //std::cout << pos.column << std::endl;
            //for (uint32_t i = 0; i < pos.column - 1; i++)
            //    std::cout << " ";
            //std::cout << "^" << std::endl;
        };
        core.SetMessageConsumer(printMsgToStderr);
        opt.SetMessageConsumer(printMsgToStderr);

        std::vector<uint32_t> binary;
        if (!core.Assemble(code, &binary)) {
            LVSLANG_ERROR("spirv assembler failed");
            return false;
        }
        if (!core.Validate(binary)) {
            LVSLANG_ERROR("spirv validator failed");
            return false;
        }

        switch (options.optimizationLevel) {
        case OptimizationLevel::O0:
            break;
        //TODO: differentiate between these?
        case OptimizationLevel::O1:
        case OptimizationLevel::O2:
        case OptimizationLevel::O3:
            opt.RegisterPerformancePasses();
            break;
        case OptimizationLevel::Os:
            opt.RegisterSizePasses();
            break;
        }
        if (!opt.Run(binary.data(), binary.size(), &binary)) {
            LVSLANG_ERROR("spirv optimizer failed");
            return false;
        }

        if (options.outputAssembly) {
            if (!core.Disassemble(binary, &outputCode, SPV_BINARY_TO_TEXT_OPTION_INDENT | SPV_BINARY_TO_TEXT_OPTION_FRIENDLY_NAMES | SPV_BINARY_TO_TEXT_OPTION_COMMENT)) {
                LVSLANG_ERROR("spirv disassembler failed");
                return false;
            }
        } else {
            outputCode = std::string((const char*)binary.data(), binary.size() * sizeof(binary[0]) / sizeof(char));
        }
        //}
    } else {
        outputCode = code;
    }

    return true;
}

} //namespace lvslang
