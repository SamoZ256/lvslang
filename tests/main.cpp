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

bool outputExpected = false;
std::string baseDir = "../tests";

#define SET_COLOR(color) std::cout << "\x1b[" color "m";

#define RESET_COLOR() SET_COLOR("0")

void printTestPassed(const std::string& testName) {
    SET_COLOR("32");
    std::cout << "Test '" << testName << "' passed" << std::endl;
    RESET_COLOR();
}

void printTestFailed(const std::string& testName) {
    SET_COLOR("31");
    std::cout << "Test '" << testName << "' failed" << std::endl;
    RESET_COLOR();
}

void _addTest(lvslang::CompileOptions& options, const std::string& testName, const std::string& filename, const std::string& expectedFilename) {
    std::cout << "Testing '" << testName << "' ..." << std::endl;
    options.inputName = filename;
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
                    if (pos == std::string::npos && pos2 == std::string::npos)
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
            }
        }
    } else {
        printTestFailed(testName);
        //std::cout << "Error:" << std::endl;
        //std::cout << result.error << std::endl;
    }
}

void addTest(const std::string& testName) {
    lvslang::CompileOptions options;
    options.spirvVersion = irb::SPIRVVersion::_1_6;
    options.glslVersion = lvslang::GLSLVersion::_4_50;
    options.outputAssembly = true;
    options.target = irb::Target::AIR;
    _addTest(options, testName + " [Metal frontend, AIR backend]", baseDir + "/" + testName + ".metal", baseDir + "/" + testName + ".expected.ll");
    if (!outputExpected)
        _addTest(options, testName + " [LVSL frontend, AIR backend]", baseDir + "/" + testName + ".lvsl", baseDir + "/" + testName + ".expected.ll");
    options.target = irb::Target::SPIRV;
    _addTest(options, testName + " [Metal frontend, SPIRV backend]", baseDir + "/" + testName + ".metal", baseDir + "/" + testName + ".expected.spvasm");
    if (!outputExpected)
        _addTest(options, testName + " [LVSL frontend, SPIRV backend]", baseDir + "/" + testName + ".lvsl", baseDir + "/" + testName + ".expected.spvasm");
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
    addTest("standard_functions");

    return 0;
}
