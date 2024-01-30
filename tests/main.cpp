#include <filesystem>
#include <sstream>
#include <fstream>

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

bool outputExpected = false;
std::string baseDir = "../tests";

inline void printTestPassed(const std::string& testName) {
    std::cout << SET_TEXT_COLOR("32") << "Test " << testName << " passed" << RESET_TEXT_COLOR() << std::endl;
}

inline void printTestFailed(const std::string& testName) {
    std::cout << SET_TEXT_COLOR("31") << "Test " << testName << " failed" << RESET_TEXT_COLOR() << std::endl;
}

//TODO: not return anything?
bool _addTest(lvslang::CompileOptions& options, const std::string& testName, const std::string& filename, const std::string& expectedFilename) {
    std::cout << "Testing " << testName << " ..." << std::endl;
    options.inputName = std::filesystem::absolute(filename).string();
    options.source = readFile(filename);
    std::string code;
    bool result = lvslang::compile(options, code);
    if (result) {
        if (outputExpected) {
            writeToFile(expectedFilename, code);
        } else {
            std::string expected = readFile(expectedFilename);
            size_t beginningIndex = 0;
            size_t expectedBeginningIndex = 0;
            if (options.target == irb::Target::AIR) {
                beginningIndex = code.find("\n");
                expectedBeginningIndex = expected.find("\n");
            }
            if (code.substr(beginningIndex) == expected.substr(expectedBeginningIndex)) {
                printTestPassed(testName);
            } else {
                printTestFailed(testName);
                size_t oldPos = beginningIndex;
                size_t pos = beginningIndex;
                size_t oldPos2 = expectedBeginningIndex;
                size_t pos2 = expectedBeginningIndex;
                while (true) {
                    pos = code.find("\n", pos + 1);
                    pos2 = expected.find("\n", pos2 + 1);
                    if (pos == std::string::npos || pos2 == std::string::npos)
                        break;
                    std::string expectedLine = expected.substr(oldPos2, pos2 - oldPos2);
                    std::string actualLine = code.substr(oldPos, pos - oldPos);
                    if (actualLine != expectedLine) {
                        std::cout << "Expected: " << expectedLine << std::endl;
                        std::cout << "Actual: " << actualLine << std::endl;
                    }
                    oldPos = pos;
                    oldPos2 = pos2;
                }

                return false;
            }
        }
    } else {
        printTestFailed(testName);
        //std::cout << "Error:" << std::endl;
        //std::cout << result.error << std::endl;

        return false;
    }

    return true;
}

static const irb::Target targets[] = {irb::Target::AIR, irb::Target::SPIRV, irb::Target::Metal, irb::Target::HLSL, irb::Target::GLSL};
static const std::string targetNames[] = {"AIR", "SPIRV", "Metal", "HLSL", "GLSL"};
static const std::string targetExtensions[] = {"ll", "spvasm", "metal", "hlsl", "glsl"};

static const std::string frontendNames[] = {"Metal", "LVSL"};
static const std::string frontendExtensions[] = {"metal", "lvsl"};

void addTest(const std::string& testName) {
    lvslang::CompileOptions options;
    options.spirvVersion = irb::SPIRVVersion::_1_6;
    options.glslVersion = lvslang::GLSLVersion::_4_50;
    options.outputAssembly = true;
    for (uint32_t i = 0; i < sizeof(frontendNames) / sizeof(std::string); i++) {
        if (!outputExpected || i == 0) {
            for (uint32_t j = 0; j < sizeof(targets) / sizeof(irb::Target); j++) {
                options.target = targets[j];
                _addTest(options, "'" + testName + "' [" + frontendNames[i] + " frontend, " + targetNames[j] + " backend]", baseDir + "/" + testName + "." + frontendExtensions[i], baseDir + "/" + testName + ".expected." + targetExtensions[j]);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    for (uint32_t i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        if (arg == "--output-expected") {
            outputExpected = true;
        } else {
            throw std::runtime_error("unknown option '" + arg + "'");
        }
    }

    addTest("basic");
    addTest("control_flow");
    addTest("vectors");
    addTest("matrices");
    addTest("standard_functions");
    addTest("advanced_features");

    return 0;
}
