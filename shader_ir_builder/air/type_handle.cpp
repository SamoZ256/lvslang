#include "type_handle.hpp"

namespace irb {

llvm::Type* getStructureTypeLLVMHandle(StructureType* type) {
    Structure* structure = type->getStructure();
    if (!structure->handle) {
        std::vector<llvm::Type*> members;
        members.reserve(structure->members.size());
        for (auto& member : structure->members)
            members.push_back(getTypeLLVMHandle(member.type));
        structure->handle = llvm::StructType::create(members, type->getName());
    }
    return structure->handle;
}

llvm::FunctionType* getFunctionTypeLLVMHandle(FunctionType* type) {
    std::vector<llvm::Type*> llvmArguments;
    llvmArguments.reserve(type->getArguments().size());
    for (auto* arg : type->getArguments())
        llvmArguments.push_back(getTypeLLVMHandle(arg));
    return llvm::FunctionType::get(getTypeLLVMHandle(type->getReturnType()), llvmArguments, false);
}

llvm::Type* getTypeLLVMHandle(Type* type) {
    switch (type->getTypeID()) {
    case TypeID::Void:
        return llvm::Type::getVoidTy(*type->getContext().handle);
    case TypeID::Bool:
        return llvm::Type::getInt1Ty(*type->getContext().handle);
    case TypeID::Integer:
        return llvm::Type::getIntNTy(*type->getContext().handle, type->getBitCount());
    case TypeID::Float:
        if (type->getBitCount() == 32)
            return llvm::Type::getFloatTy(*type->getContext().handle);
        else if (type->getBitCount() == 16)
            return llvm::Type::getHalfTy(*type->getContext().handle);
        
        IRB_INVALID_ARGUMENT_WITH_REASON("type->getBitCount()", "bit count of float can only be 16 or 32");
        return nullptr;
    case TypeID::Pointer:
        return llvm::PointerType::get(*type->getContext().handle, static_cast<PointerType*>(type)->getAddressSpace());
    case TypeID::Array:
        return llvm::ArrayType::get(getTypeLLVMHandle(type->getBaseType()), static_cast<ArrayType*>(type)->getSize());
    case TypeID::Structure:
        return getStructureTypeLLVMHandle(static_cast<StructureType*>(type));
    case TypeID::Function:
        return getFunctionTypeLLVMHandle(static_cast<FunctionType*>(type));
    case TypeID::Vector:
        return llvm::VectorType::get(getTypeLLVMHandle(type->getBaseType()), static_cast<VectorType*>(type)->getComponentCount(), false);
    case TypeID::Matrix:
        return llvm::ArrayType::get(getTypeLLVMHandle(type->getBaseType()), static_cast<MatrixType*>(type)->getColumnCount());
    case TypeID::Texture:
        return llvm::PointerType::get(*type->getContext().handle, 1u);
    case TypeID::Sampler:
        return llvm::PointerType::get(*type->getContext().handle, 2u);
    default:
        return nullptr;
    }
}

} // namespace irb
