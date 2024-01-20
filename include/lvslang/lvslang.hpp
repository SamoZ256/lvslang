#ifndef LVSLANG_H
#define LVSLANG_H

#include "common.hpp"

namespace lvslang {

enum class OptimizationLevel {
    None,
    O1,
    O2,
    O3,
    Os
};

struct CompileOptions {
    std::string source;
    std::string inputName;
    irb::Target target = irb::Target::None;
    irb::SPIRVVersion spirvVersion = irb::SPIRVVersion::_1_4;
    GLSLVersion glslVersion = GLSLVersion::_3_30;
    bool outputAssembly = false;
    OptimizationLevel optimizationLevel = OptimizationLevel::O2;
};

bool compile(const CompileOptions& options, std::string& outputCode);

} //namespace lvslang

#endif
