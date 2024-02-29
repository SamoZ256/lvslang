#ifndef LVSLANG_SPIRV_FUNCTION_H
#define LVSLANG_SPIRV_FUNCTION_H

#include "../function.hpp"

#include "block.hpp"

namespace irb {

class SPIRVFunction : public Function {
private:
    std::string property = "None"; // TODO: support other as well (for instance "DontInline")

    std::string code;

public:
    using Function::Function;

    void end(IRBuilder* builder) override;

    // Getters
    const std::string& getCode() {
        return code;
    }
};

} // namespace irb

#endif
