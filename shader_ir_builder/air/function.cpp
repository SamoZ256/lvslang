#include "function.hpp"

#include "ir.hpp"

namespace irb {

AIRFunction::AIRFunction(Context& aContext, IRBuilder* builder, FunctionType* type, const std::string& aName) : Function(aContext, type, aName) {
    llvm::Function* llvmFunction = llvm::Function::Create(static_cast<llvm::FunctionType*>(type->getHandle()), llvm::Function::ExternalLinkage, name, static_cast<AIRBuilder*>(builder)->getLLVMModule().get());
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

void AIRFunction::addArgument(Value* argument) {
    llvm::Argument* llvmArgument = static_cast<llvm::Function*>(handle)->getArg(argumentIndex++);
    llvmArgument->setName(argument->getRawName());
    argument->setHandle(llvmArgument);
}

} //namespace irb
