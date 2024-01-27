#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

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
        std::cout << "error: no such file or directory '" << filename << "'" << std::endl;
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

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Expected exactly 3 arguments" << std::endl;
        return 1;
    }

    std::string source = readFile(argv[1]);
    std::string output = "\"";
    size_t oldPos = 0;
    size_t pos = 0;
    while ((pos = source.find("\n", pos)) != std::string::npos) {
        if (pos != oldPos) {
            output += source.substr(oldPos, pos - oldPos);
            output += "\\n\" \\\n\"";
        }
        pos++;
        oldPos = pos;
    }
    output += "\"";

    writeToFile(argv[2], output);
}
