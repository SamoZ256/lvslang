#include <filesystem>
#include <sstream>
#include <fstream>

#include <argumentum/argparse.h>

#include "lvslang/lvslang.hpp"

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
        std::cout << SET_TEXT_COLOR("31") << "error:" << RESET_TEXT_COLOR() << " no such file or directory '" << filename << "'" << std::endl;
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

int main(int argc, char* argv[]) {
    lvslang::CompileOptions options;
    std::string outputName;

    std::vector<std::string> spirvVersions;
    for (auto& it : irb::spirvVersionMap)
        spirvVersions.push_back(it.second);
    std::vector<std::string> glslVersions;
    for (auto& it : lvslang::glslVersionMap)
        glslVersions.push_back(it.second);

    auto parser = argumentum::argument_parser{};
    auto params = parser.params();
    parser.config().program(argv[0]).description("LVSLANG compiler");
    parser.config().usage("lvslang [options] input-file");
    params.add_parameter(outputName, "--output", "-o").nargs(1).help("Output file (write to standard output if not specified).");
    params.add_parameter(options.inputName, "input-file").nargs(1).required().help("Input file.");
    params.add_parameter(options.target, "--msl")
        .nargs(0)
        .action([&](auto& target, const std::string& value) {
            target = irb::Target::Metal;
        })
        .help("Output Metal Shading Language.");
    params.add_parameter(options.target, "--hlsl")
        .nargs(0)
        .action([&](auto& target, const std::string& value) {
            target = irb::Target::HLSL;
        })
        .help("Output HLSL.");
    params.add_parameter(options.target, "--glsl")
        .nargs(0)
        .action([&](auto& target, const std::string& value) {
            target = irb::Target::GLSL;
        })
        .help("Output GLSL.");
    params.add_parameter(options.target, "--spirv")
        .nargs(0)
        .action([&](auto& target, const std::string& value) {
            target = irb::Target::SPIRV;
        })
        .help("Output Vulkan SPIRV.");
    params.add_parameter(options.target, "--air")
        .nargs(0)
        .action([&](auto& target, const std::string& value) {
            target = irb::Target::AIR;
        })
        .help("Output Metal's AIR.");
    params.add_parameter(options.outputAssembly, "--output-assembly", "-S").nargs(0).help("Output assembly instead of bytecode (SPIR-V and AIR only)");
    params.add_parameter(options.optimizationLevel, "--O0")
        .nargs(0)
        .default_value(options.optimizationLevel)
        .action([&](auto& target, const std::string& value) {
            target = lvslang::OptimizationLevel::O0;
        })
        .help("Disable optimizations.");
    params.add_parameter(options.optimizationLevel, "--O1")
        .nargs(0)
        .default_value(options.optimizationLevel)
        .action([&](auto& target, const std::string& value) {
            target = lvslang::OptimizationLevel::O1;
        })
        .help("Small optimizations.");
    params.add_parameter(options.optimizationLevel, "--O2")
        .nargs(0)
        .default_value(options.optimizationLevel)
        .action([&](auto& target, const std::string& value) {
            target = lvslang::OptimizationLevel::O2;
        })
        .help("Regular optimizations.");
    params.add_parameter(options.optimizationLevel, "--O3")
        .nargs(0)
        .default_value(options.optimizationLevel)
        .action([&](auto& target, const std::string& value) {
            target = lvslang::OptimizationLevel::O3;
        })
        .help("All optimizations.");
    params.add_parameter(options.optimizationLevel, "--Os")
        .nargs(0)
        .default_value(options.optimizationLevel)
        .action([&](auto& target, const std::string& value) {
            target = lvslang::OptimizationLevel::Os;
        })
        .help("Optimize for size.");
    params.add_parameter(options.spirvVersion, "--spirv-version")
        .nargs(1)
        .choices(spirvVersions)
        .action([&](auto& target, const std::string& value) {
            for (auto& it : irb::spirvVersionMap) {
                if (it.second == value) {
                    options.spirvVersion = it.first;
                    break;
                }
            }
        })
        .help("SPIR-V version. Can be one of: (1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6). Default is 1.4.");
    params.add_parameter(options.glslVersion, "--glsl-version")
        .nargs(1)
        .choices(glslVersions)
        .action([&](auto& target, const std::string& value) {
            for (auto& it : lvslang::glslVersionMap) {
                if (it.second == value) {
                    target = it.first;
                    break;
                }
            }
        })
        .help("GLSL version. Can be one of: (110, 120, 130, 140, 150, 330, 400, 410, 420, 430, 440, 450). Default is 330.");

    if (!parser.parse_args(argc, argv, 1))
        return 1;
    
    spirvVersions.clear();
    glslVersions.clear();

    if (options.inputName == "") {
        LVSLANG_ERROR("no input sources specified");
        return 1;
    }
    options.inputName = std::filesystem::absolute(options.inputName).string();
    options.source = readFile(options.inputName);
    
    std::string code;
    if (!lvslang::compile(options, code))
        return 1;

    if (outputName == "")
        std::cout << code;
    else
        writeToFile(outputName, code);

    return 0;
}
