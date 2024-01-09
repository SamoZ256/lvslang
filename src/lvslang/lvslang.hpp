#ifndef LVSLANG_H
#define LVSLANG_H

#include "spirv-tools/libspirv.hpp"
#include "spirv-tools/optimizer.hpp"

#include "frontends/lvsl/parser.hpp"
#include "frontends/metal/parser.hpp"

namespace lvslang {

std::string readFile(const std::string& filename) {
    std::string content;
    std::ifstream file;
    // ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        file.open(filename);
        std::stringstream stream;
        // read file's buffer contents into streams
        stream << file.rdbuf();
        // close file handlers
        file.close();
        // convert stream into string
        content = stream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "Error: could not open file '" << filename << "'" << std::endl;
        throw std::runtime_error("");
    }

    return content;
}

enum class OptimizationLevel {
    None,
    O1,
    O2,
    O3,
    OS
};

struct CompileOptions {
    std::string inputName;
    std::string outputName;
    irb::Target target = irb::Target::None;
    irb::SPIRVVersion spirvVersion = irb::SPIRVVersion::_1_4;
    irb::GLSLVersion glslVersion = irb::GLSLVersion::_3_30;
    bool outputAssembly = false;
    OptimizationLevel optimizationLevel = OptimizationLevel::O2;
};

bool compile(const CompileOptions& options, std::string& outputCode) {
    irb::target = options.target;
    irb::spirvVersion = options.spirvVersion;
    lvslang::glslVersion = options.glslVersion;

    setSource(readFile(options.inputName));

    std::string extension = options.inputName.substr(options.inputName.find_last_of('.'));
    std::string code;
    if (extension == ".lvsl")
        code = lvsl::compile(options.inputName);
    else if (extension == ".metal")
        code = metal::compile(options.inputName);
    else
        throw std::runtime_error("unsupported output file extension '" + extension + "'");
    
    //Assemble and optimize
    if (irb::target == irb::Target::SPIRV) {
        if (options.optimizationLevel == OptimizationLevel::None && options.outputAssembly) {
            outputCode = code;
        } else {
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

            auto printMsgToStderr = [](spv_message_level_t, const char*,
                                        const spv_position_t&, const char* m) {
                std::cerr << "error: " << m << std::endl;
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
            case OptimizationLevel::None:
                break;
            //TODO: differentiate between these?
            case OptimizationLevel::O1:
            case OptimizationLevel::O2:
            case OptimizationLevel::O3:
                opt.RegisterPerformancePasses();
                break;
            case OptimizationLevel::OS:
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
                outputCode = std::string((const char*)binary.data(), binary.size());
            }
        }
    } else if (irb::target == irb::Target::AIR) {
        //TODO: assemble and optimize
        outputCode = code;
    } else {
        outputCode = code;
    }

    return true;
}

} //namespace lvslang

#endif
