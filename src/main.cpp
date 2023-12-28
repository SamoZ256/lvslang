#include <string>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>

#include "frontends/lvsl/parser.hpp"

#define INVALID_COMMAND_LINE_ARGUMENT(arg) std::cout << "Invalid command line argument '" arg "'" << std::endl;

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

void writeToFile(const std::string& filename, const std::string& source) {
    std::ofstream file;
    file.open(filename);
    file << source;
    file.close();
}

struct Options {
    std::string inputName;
    bool inputSpecified = false;
    std::string outputName;
    bool outputSpecified = false;
    std::string version;
    bool versionSpecified = false;
    irb::Target target = irb::Target::None;
};

enum class Modifier {
    None,
    Output,
    Version,

    MaxEnum
};

int main(int argc, char* argv[]) {
    Options options;
    Modifier modifier = Modifier::None;
    for (uint32_t i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        //Option
        if (arg[0] == '-') {
            if (arg.size() == 1)
                throw std::runtime_error("'-' must be followed by option");
            if (arg[1] == '-') {
                if (arg.size() == 2)
                    throw std::runtime_error("'-' must be followed by option");
                std::string optionName = arg.substr(2);
                if (optionName == "msl")
                    options.target = irb::Target::Metal;
                else if (optionName == "glsl")
                    options.target = irb::Target::GLSL;
                else if (optionName == "spirv")
                    options.target = irb::Target::SPIRV;
                else if (optionName == "air")
                    options.target = irb::Target::AIR;
                else if (optionName == "version")
                    modifier = Modifier::Version;
            } else {
                for (uint32_t j = 1; j < arg.size(); j++) {
                    switch (arg[j]) {
                    case 'o':
                        modifier = Modifier::Output;
                        break;
                    }
                }
            }
        } else {
            switch (modifier) {
            case Modifier::None: //Input
                options.inputName = arg;
                options.inputSpecified = true;
                break;
            case Modifier::Output: //Output
                options.outputName = arg;
                options.outputSpecified = true;
                break;
            case Modifier::Version: //Version
                options.version = arg;
                options.versionSpecified = true;
            default:
                break;
            }

            modifier = Modifier::None;
        }
    }
    irb::target = options.target;

    if (!options.inputSpecified)
        throw std::runtime_error("No input sources specified");
    
    if (options.versionSpecified) {
        bool found = false;
        for (auto& it : irb::glslVersionMap) {
            if (it.second == options.version) {
                glslVersion = it.first;
                found = true;
                break;
            }
        }
        if (!found)
            INVALID_COMMAND_LINE_ARGUMENT("version");
    }

    binopPrecedence[TOKEN_OPERATOR_LOGICAL_AND                      ] = 8;
    binopPrecedence[TOKEN_OPERATOR_LOGICAL_OR                       ] = 8;
    //binopPrecedence[TOKEN_OPERATOR_NOT                              ] = 0;

    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_IS_EQUAL              ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_IS_NOT_EQUAL          ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_LESS_THAN             ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_GREATER_THAN          ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_LESS_THAN_OR_EQUAL    ] = 10;
    binopPrecedence[TOKEN_OPERATOR_RELATIONAL_GREATER_THAN_OR_EQUAL ] = 10;

    binopPrecedence[TOKEN_OPERATOR_BITWISE_AND                      ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_OR                       ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_LEFT_SHIFT               ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_RIGHT_SHIFT              ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_NOT                      ] = 100;
    binopPrecedence[TOKEN_OPERATOR_BITWISE_POW                      ] = 100;

    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_PLUS                  ] = 20;
    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_MINUS                 ] = 20;
    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_MULTIPLY              ] = 40;
    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_DIVIDE                ] = 40;
    binopPrecedence[TOKEN_OPERATOR_ARITHMETIC_MODULO                ] = 80;

    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_ASSIGN                ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_ADD_AND_ASSIGN        ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_SUBTRACT_AND_ASSIGN   ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_MULTIPLY_AND_ASSIGN   ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_DIVIDE_AND_ASSIGN     ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_MODULO_AND_ASSIGN     ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_AND_AND_ASSIGN        ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_OR_AND_ASSIGN         ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_LEFT_SHIFT_AND_ASSIGN ] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_RIGHT_SHIFT_AND_ASSIGN] = 4;
    binopPrecedence[TOKEN_OPERATOR_ASSIGNMENT_POW_AND_ASSIGN        ] = 4;

    binopPrecedence[TOKEN_OPERATOR_REFERENCE                        ] = 200;
    binopPrecedence[TOKEN_OPERATOR_DEREFERENCE                      ] = 200;
    binopPrecedence[TOKEN_OPERATOR_DOT                              ] = 400;
    binopPrecedence[TOKEN_OPERATOR_FUNCTION_RETURN_TYPE             ] = 400;

    //HACK: hard-coded enum definition
    /*
    std::vector<EnumValue> enumValues = {
        {"First", -14},
        {"Second", 31}
    };
    Enumeration* enumeration = new Enumeration(enumValues);
    enumerations["MyEnum"] = enumeration;
    */

    setSource(readFile(options.inputName));

    compile(options.inputName);

    if (options.outputSpecified) {
        writeToFile(options.outputName, getCompiledCode());
    } else {
        std::cout << getCompiledCode();
    }

    return 0;
}
