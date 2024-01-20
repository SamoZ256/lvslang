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

void addTest(lvslang::CompileOptions& options, const std::string& testName, const std::string& filename, const std::string& expected) {
    std::cout << "Test '" << testName << "'..." << std::endl;
    options.source = readFile(filename);
    std::string code;
    bool result = lvslang::compile(options, code);
    if (result) {
        if (code == expected) {
            std::cout << "Test '" << testName << "' passed" << std::endl;
        } else {
            std::cout << "Test '" << testName << "' failed" << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected << std::endl;
            std::cout << "Actual:" << std::endl;
            std::cout << code << std::endl;
        }
    } else {
        std::cout << "Test '" << testName << "' failed" << std::endl;
        //std::cout << "Error:" << std::endl;
        //std::cout << result.error << std::endl;
    }
}

int main() {
    return 0;
}
