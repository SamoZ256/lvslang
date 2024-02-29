#ifndef IRB_AIR_TYPE_HANDLE_H
#define IRB_AIR_TYPE_HANDLE_H

#include "../value.hpp"

namespace irb {

llvm::Type* getTypeLLVMHandle(Type* type);

} // namespace irb

#endif
