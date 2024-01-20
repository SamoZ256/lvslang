#include <filesystem>
#include <sstream>
#include <fstream>

#include "lvslang/lvslang.hpp"

#define INVALID_COMMAND_LINE_ARGUMENT(arg) std::cout << "Invalid command line argument '" + std::string(arg) + "'" << std::endl;

std::string readFile(const std::string& filename) {
    std::string content;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(filename);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        content = stream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "Error: could not open file '" << filename << "'" << std::endl;
        throw std::runtime_error("");
    }

    return content;
}

void writeToFile(const std::string& filename, const std::string& source) {
    std::ofstream file;
    file.open(filename);
    file << source;
    file.close();
}

enum class Modifier {
    None,
    Output,
    SPIRVVersion,
    GLSLVersion,

    MaxEnum
};

int main(int argc, char* argv[]) {
    lvslang::CompileOptions options;
    Modifier modifier = Modifier::None;
    std::string spirvVersionStr;
    std::string glslVersionStr;
    for (uint32_t i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        //Option
        if (arg[0] == '-') {
            if (arg.size() == 1)
                throw std::runtime_error("'-' must be followed by an option");
            if (arg[1] == '-') {
                if (arg.size() == 2)
                    throw std::runtime_error("'--' must be followed by an option");

                if (arg == "--msl") {
                    options.target = irb::Target::Metal;
                } else if (arg == "--hlsl") {
                    options.target = irb::Target::HLSL;
                } else if (arg == "--glsl") {
                    options.target = irb::Target::GLSL;
                } else if (arg == "--spirv") {
                    options.target = irb::Target::SPIRV;
                } else if (arg == "--air") {
                    options.target = irb::Target::AIR;
                } else if (arg == "--spirv-version") {
                    modifier = Modifier::SPIRVVersion;
                } else if (arg == "--glsl-version") {
                    modifier = Modifier::GLSLVersion;
                } else {
                    INVALID_COMMAND_LINE_ARGUMENT(arg);
                    return 1;
                }
            } else {
                if (arg == "-o") {
                    modifier = Modifier::Output;
                } else if (arg == "-S") {
                    options.outputAssembly = true;
                } else if (arg == "-O0") {
                    options.optimizationLevel = lvslang::OptimizationLevel::None;
                } else if (arg == "-O1") {
                    options.optimizationLevel = lvslang::OptimizationLevel::O1;
                } else if (arg == "-O2") {
                    options.optimizationLevel = lvslang::OptimizationLevel::O2;
                } else if (arg == "-O3") {
                    options.optimizationLevel = lvslang::OptimizationLevel::O3;
                } else if (arg == "-Os") {
                    options.optimizationLevel = lvslang::OptimizationLevel::Os;
                } else {
                    INVALID_COMMAND_LINE_ARGUMENT(arg);
                    return 1;
                }
            }
        } else {
            switch (modifier) {
            case Modifier::None: //Input
                options.inputName = arg;
                break;
            case Modifier::Output: //Output
                options.outputName = arg;
                break;
            case Modifier::SPIRVVersion: //SPIRVVersion
                spirvVersionStr = arg;
                break;
            case Modifier::GLSLVersion: //GLSLVersion
                glslVersionStr = arg;
                break;
            default:
                break;
            }

            modifier = Modifier::None;
        }
    }

    if (options.inputName == "") {
        LVSLANG_ERROR("no input sources specified");
        return 1;
    }
    options.source = readFile(options.inputName);
    
    if (spirvVersionStr != "") {
        bool found = false;
        for (auto& it : irb::spirvVersionMap) {
            if (it.second == spirvVersionStr) {
                options.spirvVersion = it.first;
                found = true;
                break;
            }
        }
        if (!found)
            INVALID_COMMAND_LINE_ARGUMENT("spirv version");
    }
    
    if (glslVersionStr != "") {
        bool found = false;
        for (auto& it : lvslang::glslVersionMap) {
            if (it.second == glslVersionStr) {
                options.glslVersion = it.first;
                found = true;
                break;
            }
        }
        if (!found)
            INVALID_COMMAND_LINE_ARGUMENT("glsl version");
    }
    
    std::string code;
    if (!lvslang::compile(options, code))
        return 1;

    if (options.outputName == "")
        std::cout << code;
    else
        writeToFile(options.outputName, code);

    return 0;
}
