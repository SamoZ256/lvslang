#include "function.hpp"

#include "ir.hpp"

#include "type_handle.hpp"

namespace irb {

AIRFunction::AIRFunction(Context& aContext, IRBuilder* builder, FunctionType* type, const std::string& aName) : Function(aContext, type, aName) {
    llvm::Function* llvmFunction = llvm::Function::Create(static_cast<llvm::FunctionType*>(getTypeLLVMHandle(type)), llvm::Function::ExternalLinkage, name, static_cast<AIRBuilder*>(builder)->getLLVMModule().get());
    for (uint32_t i = 0; i < type->getArguments().size(); i++) {
        Type* argumentType = type->getArguments()[i];
        llvm::Argument* llvmArgument = llvmFunction->getArg(i);
        if (argumentType->isTexture() || argumentType->isSampler()) {
            llvmArgument->addAttr(llvm::Attribute::get(*context.handle, llvm::Attribute::AttrKind::NoCapture));
            llvmArgument->addAttr(llvm::Attribute::get(*context.handle, llvm::Attribute::AttrKind::ReadOnly));
        }
    }
    handle = llvmFunction;
}

void AIRFunction::end(IRBuilder* builder) {
    llvm::verifyFunction(*static_cast<llvm::Function*>(handle));
}

void AIRFunction::addArgument(Value* argument, const std::string& name) {
    llvm::Argument* llvmArgument = static_cast<llvm::Function*>(handle)->getArg(argumentIndex++);
    llvmArgument->setName(name);
    argument->setHandle(llvmArgument);
}

} // namespace irb
