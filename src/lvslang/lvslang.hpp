#ifndef LVSLANG_H
#define LVSLANG_H

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

std::string compile(irb::Target aTarget, const std::string& sourceName) {
    irb::target = aTarget;

    setSource(readFile(sourceName));

    std::string extension = sourceName.substr(sourceName.find_last_of('.'));
    if (extension == ".lvsl")
        return lvsl::compile(sourceName);
    else if (extension == ".metal")
        return metal::compile(sourceName);
    else
        throw std::runtime_error("unsupported output file extension '" + extension + "'");
    
    return "";
}

} //namespace lvslang

#endif
