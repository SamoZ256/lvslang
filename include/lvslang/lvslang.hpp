#ifndef LVSLANG_H
#define LVSLANG_H

#include "../src/common.hpp"

namespace lvslang {

enum class OptimizationLevel {
    O0,
    O1,
    O2,
    O3,
    Os
};

struct CompileOptions {
    std::string source;
    std::string inputName;
    Target target = Target::None;
    irb::SPIRVVersion spirvVersion = irb::SPIRVVersion::_1_4;
    GLSLVersion glslVersion = GLSLVersion::_3_30;
    bool outputAssembly = false;
    OptimizationLevel optimizationLevel = OptimizationLevel::O2;
    bool includeDebugInformation = true;
};

bool compile(const CompileOptions& options, std::string& outputCode);

} // namespace lvslang

#endif
