#include "ir.hpp"

#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Bitcode/BitcodeWriter.h"

namespace irb {

//TODO: uncomment
/*
struct StandardFunctionInfo {
    std::vector<std::pair<llvm::Attribute::AttrKind, uint64_t> > attributes = {{llvm::Attribute::AttrKind::NoUnwind, 0}, {llvm::Attribute::AttrKind::WillReturn, 0}, {llvm::Attribute::AttrKind::Memory, 0}};
};

static std::map<std::string, StandardFunctionInfo> standardFunctionLUT = {
    {"abs", {}},
    {"acos", {}},
    {"acosh", {}},
    {"asin", {}},
    {"asinh", {}},
    {"atan", {}},
    {"atanh", {}},
    {"ceil", {}},
    {"clamp", {}},
    {"cos", {}},
    {"cosh", {}},
    {"cross", {}},
    {"distance", {}},
    {"dot", {}},
    {"exp", {}},
    {"exp2", {}},
    {"floor", {}},
    {"fract", {}},
    //TODO: add image functions
    //TODO: add transpose
    {"isinf", {}},
    {"isnan", {}},
    {"length", {}},
    {"log", {}},
    {"log2", {}},
    {"max", {}},
    {"min", {}},
    {"mix", {}},
    {"normalize", {}},
    {"pow", {}},
    {"reflect", {}},
    {"refract", {}},
    {"round", {}},
    {"sample", {{{llvm::Attribute::AttrKind::Convergent, 0}, {llvm::Attribute::AttrKind::NoUnwind, 0}, {llvm::Attribute::AttrKind::WillReturn, 0}, {llvm::Attribute::AttrKind::Memory, 1}}}},
    {"sign", {}},
    {"sin", {}},
    {"sinh", {}},
    {"smoothstep", {}},
    {"sqrt", {}},
    {"step", {}},
    {"tan", {}},
    {"tanh", {}}
    //TODO: add transpose function
};
*/

void AIRBuilder::opEntryPoint(Value* entryPoint, FunctionRole functionRole, const std::string& name, Type* returnType, const std::vector<Argument>& arguments) {
    entryPoints.push_back({entryPoint, functionRole, returnType, arguments});
    if (FunctionType* functionType = dynamic_cast<FunctionType*>(entryPoint->getType())) {
        llvm::Function* llvmFunction = static_cast<llvm::Function*>(entryPoint->getHandle());
        for (uint32_t i = 0; i < functionType->getArguments().size(); i++) {
            Type* argumentType = functionType->getArguments()[i];
            llvm::Argument* llvmArgument = llvmFunction->getArg(i);
            if (argumentType->isPointer() && !argumentType->isTexture() && !argumentType->isSampler()) {
                llvmArgument->addAttr(llvm::Attribute::get(*context.handle, llvm::Attribute::AttrKind::NoUndef));
                llvmArgument->addAttr(llvm::Attribute::get(*context.handle, "air-buffer-no-alias"));
            }
        }
    } else {
        IRB_INVALID_ARGUMENT_WITH_REASON("entryPoint", "entry point is not a function");
        return;
    }
}

Value* AIRBuilder::opConstant(ConstantValue* val) {
    context.popRegisterName();

    return val;
}

Value* AIRBuilder::opStructureDefinition(StructureType* structureType) {
    return new Value(context, structureType, context.popRegisterName());
}

//TODO: support fast math (in function names)
Function* AIRBuilder::opStandardFunctionDeclaration(FunctionType* functionType, const std::string& name) {
    //TODO: uncomment
    /*
    if (!standardFunctionLUT.count(name)) {
        IRB_INVALID_ARGUMENT_WITH_REASON("name", "there is no such standard function");
        return nullptr;
    }

    const auto& standardFunctionInfo = standardFunctionLUT[name];
    */
    
    //TODO: only add template name if there is at least one argument
    std::string fullName = "air." + name + "." + functionType->getArguments()[0]->getTemplateName();

    if (name == "sample") {
        //TODO: do error checks
        functionType = new FunctionType(context, functionType->getReturnType(), {functionType->getArguments()[0], functionType->getArguments()[1], functionType->getArguments()[2], new ScalarType(context, TypeID::Bool, 8, false), new VectorType(context, new ScalarType(context, TypeID::Integer, 32, true), 2), new ScalarType(context, TypeID::Bool, 8, false), new ScalarType(context, TypeID::Float, 32, true), new ScalarType(context, TypeID::Float, 32, true), new ScalarType(context, TypeID::Integer, 32, true)});
        
        //TODO: uncomment
        return opFunctionDeclaration(functionType, "air.sample_texture_2d." + functionType->getReturnType()->getTemplateName(), /*standardFunctionInfo.attributes*/{{llvm::Attribute::AttrKind::Convergent, 0}, {llvm::Attribute::AttrKind::NoUnwind, 0}, {llvm::Attribute::AttrKind::WillReturn, 0}, {llvm::Attribute::AttrKind::Memory, 1}});
    } else {
        //TODO: uncomment
        return opFunctionDeclaration(functionType, fullName, /*standardFunctionInfo.attributes*/{{llvm::Attribute::AttrKind::NoUnwind, 0}, {llvm::Attribute::AttrKind::WillReturn, 0}, {llvm::Attribute::AttrKind::Memory, 0}});
    }
}

Function* AIRBuilder::opFunction(FunctionType* functionType, const std::string& name) {
    return new AIRFunction(context, this, functionType, name + functionType->getTemplateName());
}

Value* AIRBuilder::opFunctionParameter(Function* function, Type* type) {
    Value* argValue = new Value(context, type, context.popRegisterName());
    static_cast<AIRFunction*>(function)->addArgument(argValue);
    //This is required in order to maintain consistency with SPIRV
    Value* value = opVariable(new PointerType(context, type, StorageClass::Function), argValue);

    return value;
}

void AIRBuilder::opFunctionEnd(Function* function) {
    function->end(this);
}

Block* AIRBuilder::opBlock(Function* function) {
    AIRBlock* block = new AIRBlock(context, function, context.popRegisterName());

    return block;
}

//TODO: support fast math
Value* AIRBuilder::opOperation(Value* l, Value* r, Type* type, Operation operation) {
    if (!type->isOperatorFriendly()) {
        IRB_INVALID_ARGUMENT_WITH_REASON("type", "type is not operator friendly (e.g. is not one of: scalar, pointer, vector)");
        return nullptr;
    }

    if (r->getType()->isVector() && l->getType()->isScalar())
        std::swap(l, r);
    if (l->getType()->isVector() && r->getType()->isScalar())
        r = opConstruct(static_cast<VectorType*>(type), std::vector<Value*>(static_cast<VectorType*>(type)->getComponentCount(), r)); //TODO: check if the type is vector

    Value* value = new Value(context, (type->getTypeID() == TypeID::Bool && l->getType()->isVector() ? new VectorType(context, type, static_cast<VectorType*>(l->getType())->getComponentCount()) : type), context.popRegisterName());
    
    bool needsOrd = (operation == Operation::GreaterThan || operation == Operation::GreaterThanEqual || operation == Operation::LessThan || operation == Operation::LessThanEqual);
    bool signSensitive = (operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || needsOrd);
    bool needsPrefix = (operation == Operation::Add || operation == Operation::Subtract || operation == Operation::Multiply || operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || operation == Operation::And || operation == Operation::Or || operation == Operation::Equal || operation == Operation::NotEqual || needsOrd);

    GET_OPERATION_NAME(operation);

    //TODO: do not use l for getting op prefix?
    std::string prefix = (needsPrefix ? l->getType()->getOpPrefix(signSensitive, false) : "");

    llvm::Value* llvmValue;
    switch (operation) {
        case Operation::Add:
            if (prefix == "f")
                llvmValue = handle->CreateFAdd(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateAdd(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::Subtract:
            if (prefix == "f")
                llvmValue = handle->CreateFSub(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateSub(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::Multiply:
            if (prefix == "f")
                llvmValue = handle->CreateFMul(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateMul(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::Divide:
            if (prefix == "f")
                llvmValue = handle->CreateFDiv(l->getHandle(), r->getHandle(), value->getRawName());
            else if (prefix == "s")
                llvmValue = handle->CreateSDiv(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateUDiv(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::Modulo:
            IRB_ERROR("modulo is not supported in AIR");
            break;
        case Operation::Remainder:
            if (prefix == "f")
                llvmValue = handle->CreateFRem(l->getHandle(), r->getHandle(), value->getRawName());
            else if (prefix == "s")
                llvmValue = handle->CreateSRem(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateURem(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::And:
            llvmValue = handle->CreateAnd(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::Or:
            llvmValue = handle->CreateOr(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::Equal:
            //TODO: support unordered
            if (prefix == "f")
                llvmValue = handle->CreateFCmpOEQ(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateICmpEQ(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::NotEqual:
            //TODO: support unordered
            if (prefix == "f")
                llvmValue = handle->CreateFCmpONE(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateICmpNE(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::GreaterThan:
            //TODO: support unordered
            if (prefix == "f")
                llvmValue = handle->CreateFCmpOGT(l->getHandle(), r->getHandle(), value->getRawName());
            else if (prefix == "s")
                llvmValue = handle->CreateICmpSGT(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateICmpUGT(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::GreaterThanEqual:
            //TODO: support unordered
            if (prefix == "f")
                llvmValue = handle->CreateFCmpOGE(l->getHandle(), r->getHandle(), value->getRawName());
            else if (prefix == "s")
                llvmValue = handle->CreateICmpSGE(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateICmpUGE(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::LessThan:
            //TODO: support unordered
            if (prefix == "f")
                llvmValue = handle->CreateFCmpOLT(l->getHandle(), r->getHandle(), value->getRawName());
            else if (prefix == "s")
                llvmValue = handle->CreateICmpSLT(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateICmpULT(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        case Operation::LessThanEqual:
            //TODO: support unordered
            if (prefix == "f")
                llvmValue = handle->CreateFCmpOLE(l->getHandle(), r->getHandle(), value->getRawName());
            else if (prefix == "s")
                llvmValue = handle->CreateICmpSLE(l->getHandle(), r->getHandle(), value->getRawName());
            else
                llvmValue = handle->CreateICmpULE(l->getHandle(), r->getHandle(), value->getRawName());
            break;
        default:
            IRB_ERROR("unsupported operation");
            return nullptr;
    }
    value->setHandle(llvmValue);

    //"Unpack" the vector
    if (type->getTypeID() == TypeID::Bool && value->getType()->isVector()) {
        std::vector<Value*> resultComponents(static_cast<VectorType*>(value->getType())->getComponentCount());
        for (uint8_t i = 0; i < resultComponents.size(); i++) {
            context.pushRegisterName("vec_op_unpack");
            resultComponents[i] = opVectorExtract(value, new ConstantInt(context, i, 32, true));
        }
        value = resultComponents[0];
        for (uint8_t i = 1; i < resultComponents.size(); i++)
            value = opOperation(value, resultComponents[i], type, operation);
    }

    return value;
}

Value* AIRBuilder::opLoad(Value* v) {
    if (!v->getType()->isPointer()) {
        IRB_INVALID_ARGUMENT_WITH_REASON("v", "type of 'v' is not a pointer");
        return nullptr;
    }

    Type* elementType = v->getType()->getElementType();
    Value* value = new Value(context, elementType, context.popRegisterName());

    value->setHandle(handle->CreateLoad(elementType->getHandle(), v->getHandle(), value->getRawName()));

    return value;
}

void AIRBuilder::opStore(Value* ptr, Value* v) {
    handle->CreateStore(v->getHandle(), ptr->getHandle());
}

void AIRBuilder::opReturn(Value* v) {
    AIRBlock* block = getAIRInsertBlock();
    if (block->hasReturned()) {
        IRB_ERROR("cannot have more than 1 return instruction in a single block");
        return;
    }
    
    if (v)
        handle->CreateRet(v->getHandle());
    else
        handle->CreateRetVoid();

    getAIRInsertBlock()->setReturned();
}

//TODO: support fast math
//TODO: what should be returned when return type is void?
Value* AIRBuilder::opFunctionCall(Value* funcV, const std::vector<Value*>& arguments) {
    FunctionType* type = dynamic_cast<FunctionType*>(funcV->getType());
    if (!type) {
        IRB_INVALID_ARGUMENT_WITH_REASON("funcV", "type of 'funcV' is not a function");
        return nullptr;
    }

    Value* value = new Value(context, type->getReturnType(), context.popRegisterName());

    std::vector<llvm::Value*> llvmArguments;
    llvmArguments.reserve(arguments.size());
    for (const auto& argument : arguments)
        llvmArguments.push_back(argument->getHandle());
    value->setHandle(handle->CreateCall(static_cast<llvm::FunctionType*>(type->getHandle()), funcV->getHandle(), llvmArguments, value->getRawName()));

    return value;
}

void AIRBuilder::opBranch(Block* block) {
    handle->CreateBr(static_cast<AIRBlock*>(block)->getHandle());
}

void AIRBuilder::opBranchCond(Value* cond, Block* blockTrue, Block* blockFalse) {
    handle->CreateCondBr(cond->getHandle(), static_cast<AIRBlock*>(blockTrue)->getHandle(), static_cast<AIRBlock*>(blockFalse)->getHandle());
}

Value* AIRBuilder::opConstruct(Type* type, const std::vector<Value*>& components) {
    context.popRegisterName();
    bool allComponentsAreConstant = true;
    for (uint8_t i = 0; i < components.size(); i++) {
        if (!components[i]->isConstant()) {
            allComponentsAreConstant = false;
            break;
        }
    }
    if (allComponentsAreConstant) {
        Value* value = new Value(context, type);
        value->setIsConstant(true);

        std::vector<llvm::Constant*> llvmComponents;
        llvmComponents.reserve(components.size());
        for (const auto& component : components)
            llvmComponents.push_back(static_cast<llvm::Constant*>(component->getHandle()));
        value->setHandle(llvm::ConstantVector::get(llvmComponents));

        return value;
    } else {
        Value* value = new UndefinedValue(context, type);
        for (uint8_t i = 0; i < components.size(); i++)
            value = opVectorInsert(value, components[i], new ConstantInt(context, i, 32, true));

        return value;
    }
}

Value* AIRBuilder::opVectorExtract(Value* vec, ConstantInt* index) {
    Value* value = new Value(context, vec->getType()->getBaseType(), context.popRegisterName());

    value->setHandle(handle->CreateExtractElement(vec->getHandle(), index->getHandle(), value->getRawName()));

    return value;
}

Value* AIRBuilder::opVectorInsert(Value* vec, Value* val, ConstantInt* index) {
    Value* value = new Value(context, vec->getType(), context.popRegisterName());

    value->setHandle(handle->CreateInsertElement(vec->getHandle(), val->getHandle(), index->getHandle(), value->getRawName()));

    return value;
}

Value* AIRBuilder::opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes) {
    if (!ptr->getType()->isPointer()) {
        IRB_INVALID_ARGUMENT_WITH_REASON("ptr", "type of 'ptr' is not pointer type");
        return nullptr;
    }
    //elementType->setAddressSpace(static_cast<PointerType*>(ptr->getType())->getAddressSpace());
    Value* value = new Value(context, elementType, context.popRegisterName());

    std::vector<llvm::Value*> llvmIndexes;
    llvmIndexes.reserve(indexes.size() + 1);
    //Access the value at pointer first
    llvmIndexes.push_back(handle->getInt32(0));
    for (const auto& index : indexes)
        llvmIndexes.push_back(index->getHandle());
    value->setHandle(handle->CreateInBoundsGEP(ptr->getType()->getElementType()->getHandle(), ptr->getHandle(), llvmIndexes, value->getRawName()));

    return value;
}

void AIRBuilder::opUnreachable() {
    handle->CreateUnreachable();
}

//TODO: support fast math
Value* AIRBuilder::opCast(Value* val, Type* type) {
    if (val->getType()->equals(type)) {
        context.popRegisterName();

        return val;
    }
    
    Type* castFromType = val->getType();

    //TODO: support vector casting
    if (type->isScalar() && castFromType->isScalar()) {
        FunctionType* functionType = new FunctionType(context, type, {castFromType});

        if (type->getTypeID() == TypeID::Float && castFromType->getTypeID() == TypeID::Float) {
            Value* value = new Value(context, type);
            if (castFromType->getBitCount() > type->getBitCount())
                value->setHandle(handle->CreateFPTrunc(val->getHandle(), type->getHandle(), value->getRawName()));
            else
                value->setHandle(handle->CreateFPExt(val->getHandle(), type->getHandle(), value->getRawName()));

            return value;
        }
        std::string functionName = "air.convert." + type->getOpPrefix(true, false) + "." + type->getTemplateName() + "." + castFromType->getOpPrefix(true, false) + "." + castFromType->getTemplateName();

        Value* funcV = opFunctionDeclaration(functionType, functionName, {{llvm::Attribute::AttrKind::NoUnwind, 0}, {llvm::Attribute::AttrKind::WillReturn, 0}, {llvm::Attribute::AttrKind::Memory, 0}});

        return opFunctionCall(funcV, {val});
    } else if (val->getType()->isScalar() && type->isVector()) {
        VectorType* vectorType = static_cast<VectorType*>(type);

        return opConstruct(vectorType, std::vector<Value*>(static_cast<VectorType*>(type)->getComponentCount(), opCast(val, vectorType->getBaseType())));
    }

    //HACK: just ignore
    return val;
}

Value* AIRBuilder::opSample(Value* funcV, Value* texture, Value* sampler, Value* coords, Value* lod) {
    //TODO: find out what are these arguments
    Value* argument4 = new ConstantBool(context, true);
    Value* argument5 = opConstruct(new VectorType(context, new ScalarType(context, TypeID::Integer, 32, true), 2), {new ConstantInt(context, 0, 32, true), new ConstantInt(context, 0, 32, true)});
    Value* argument6 = new ConstantBool(context, false);
    Value* argument7 = new ConstantFloat(context, 0.0f, 32);
    Value* argument8 = new ConstantFloat(context, 0.0f, 32);
    Value* argument9 = new ConstantInt(context, 0, 32, true);

    return opFunctionCall(funcV, {texture, sampler, coords, argument4, argument5, argument6, argument7, argument8, argument9});
}

Value* AIRBuilder::opVariable(PointerType* type, Value* initializer) {
    Value* value = new Value(context, type, context.popRegisterName());
    
    value->setHandle(handle->CreateAlloca(type->getElementType()->getHandle(), nullptr, value->getRawName()));

    if (initializer)
        opStore(value, initializer);
    
    return value;
}

static uint32_t metadataCounter = 0;

class MetadataValue : public Value {
public:
    MetadataValue(Context& aContext, const std::string& aName = "") : Value(aContext, new ScalarType(aContext, TypeID::Void, 0, true), (aName == "" ? std::to_string(metadataCounter++) : aName), "!") {}
};

class MetadataBlock {
public:
    void addCodeToBeginning(const std::string& instruction, Value* registerToAssign = nullptr, const std::string& comment = "") {
        codeBegin += _addCode(instruction, registerToAssign, comment);
    }

    void addCode(const std::string& instruction, Value* registerToAssign = nullptr, const std::string& comment = "") {
        code += _addCode(instruction, registerToAssign, comment);
    }

    std::string getCode() {
        return codeBegin + (codeBegin.size() == 0 ? "" : "\n") + code + "\n";
    }

private:
    std::string codeBegin;
    std::string code;

    std::string _addCode(const std::string& instruction, Value* registerToAssign, const std::string& comment) {
        std::string inst = "\n" + registerToAssign->getName() + " = " + instruction;

        if (comment.size() != 0)
            inst += " ; " + comment;

        return inst;
    }
};

//TODO: check if it really called "kernel"
const std::string functionNames[3] = {"vertex", "fragment", "kernel"};

//TODO: support other values whenever there is a 'TODO: here' comment
std::string AIRBuilder::createMetadata(const std::string& languageName, uint32_t languageVersionMajor, uint32_t languageVersionMinor, uint32_t languageVersionPatch, const std::string& sourceFilenameStr) {
    metadataCounter = 0;

    MetadataBlock* block = new MetadataBlock();

    MetadataValue* sdkVersion = new MetadataValue(context);
    MetadataValue* wcharSize = new MetadataValue(context);
    MetadataValue* framePointer = new MetadataValue(context);
    MetadataValue* maxDeviceBuffers = new MetadataValue(context);
    MetadataValue* maxConstantBuffers = new MetadataValue(context);
    MetadataValue* maxThreadgroupBuffers = new MetadataValue(context);
    MetadataValue* maxTextures = new MetadataValue(context);
    MetadataValue* maxReadWriteTextures = new MetadataValue(context);
    MetadataValue* maxSamplers = new MetadataValue(context);

    block->addCode("!{i32 2, !\"SDK Version\", [2 x i32] [i32 14, i32 0]}", sdkVersion); //TODO: here
    block->addCode("!{i32 1, !\"wchar_size\", i32 4}", wcharSize); //TODO: here
    block->addCode("!{i32 7, !\"frame-pointer\", i32 2}", framePointer); //TODO: here
    block->addCode("!{i32 7, !\"air.max_device_buffers\", i32 31}", maxDeviceBuffers); //TODO: here
    block->addCode("!{i32 7, !\"air.max_constant_buffers\", i32 31}", maxConstantBuffers); //TODO: here
    block->addCode("!{i32 7, !\"air.max_threadgroup_buffers\", i32 31}", maxThreadgroupBuffers); //TODO: here
    block->addCode("!{i32 7, !\"air.max_textures\", i32 128}", maxTextures); //TODO: here
    block->addCode("!{i32 7, !\"air.max_read_write_textures\", i32 8}", maxReadWriteTextures); //TODO: here
    block->addCode("!{i32 7, !\"air.max_samplers\", i32 16}", maxSamplers); //TODO: here

    std::vector<MetadataValue*> entryPointFunctionInfos[3];

    for (const auto& entryPoint : entryPoints) {
        MetadataValue* entryPointInfo = new MetadataValue(context);
        MetadataValue* entryPointOutputs = new MetadataValue(context);
        MetadataValue* entryPointInputs = new MetadataValue(context);

        std::vector<std::pair<MetadataValue*, std::string> > outputs;
        std::vector<std::pair<MetadataValue*, std::string> > inputs;
        std::string outputsStr;
        std::string inputsStr;

        if (entryPoint.returnType->getTypeID() != TypeID::Void) {
            //TODO: support non-structure types as well
            if (!entryPoint.returnType->isStructure()) {
                IRB_ERROR("Blah blah");
                return "";
            }

            Structure* structure = static_cast<StructureType*>(entryPoint.returnType)->getStructure();
            for (uint32_t i = 0; i < structure->members.size(); i++) {
                const auto& member = structure->members[i];
                MetadataValue* crntOutput = new MetadataValue(context);
                std::string str = "!{";
                if (entryPoint.functionRole == FunctionRole::Vertex) {
                    if (member.attributes.isPosition)
                        str += "!\"air.position\"";
                    else
                        str += "!\"air.vertex_output\", !\"generated(randomstuff)\""; //TODO: find out what should be inside 'generated'
                } else if (entryPoint.functionRole == FunctionRole::Fragment) {
                    str += "!\"air.render_target\", i32 " + std::to_string(member.attributes.colorIndex) + ", i32 0"; //TODO: find out if the last argument should always be 0
                }
                str += ", !\"air.arg_type_name\", !\"" + member.type->getDebugName() + "\", !\"air.arg_name\", !\"" + member.name + "\"}";

                if (i != 0)
                    outputsStr += ", ";
                outputsStr += crntOutput->getName();
                outputs.emplace_back(crntOutput, str);
            }
        }
        uint32_t inputIndex = 0;
        for (uint32_t i = 0; i < entryPoint.arguments.size(); i++) {
            const auto& argument = entryPoint.arguments[i];
            if (argument.attributes.isInput) {
                //TODO: support non-structure types as well
                if (!argument.type->isStructure()) {
                    IRB_ERROR("argument marked with 'buffer' attribute must have element type of structure");
                    return "";
                }
                Structure* structure = static_cast<StructureType*>(argument.type)->getStructure();
                for (uint32_t j = 0; j < structure->members.size(); j++) {
                    const auto& member = structure->members[j];
                    MetadataValue* crntInput = new MetadataValue(context);
                    std::string str = "!{i32 " + std::to_string(inputIndex) + ", ";

                    if (entryPoint.functionRole == FunctionRole::Vertex) {
                        str += "!\"air.vertex_input\", !\"air.location_index\", i32 " + std::to_string(j) + ", i32 1"; //TODO: here
                    } else if (entryPoint.functionRole == FunctionRole::Fragment) {
                        if (member.attributes.isPosition)
                            str += "!\"air.position\", !\"air.center\", !\"air.no_perspective\"";
                        else
                            str += "!\"air.fragment_input\", !\"generated(randomstuff)\", !\"air.center\", !\"air.perspective\""; //TODO: here
                    }

                    str += ", !\"air.arg_type_name\", !\"" + member.type->getDebugName() + "\", !\"air.arg_name\", !\"" + member.name + "\"}";
                    if (inputIndex != 0)
                        inputsStr += ", ";
                    inputsStr += crntInput->getName();
                    inputs.emplace_back(crntInput, str);
                    inputIndex++;
                }
            } else {
                MetadataValue* crntInput = new MetadataValue(context);
                MetadataValue* structureInfo = nullptr;
                std::string str = "!{i32 " + std::to_string(inputIndex) + ", ";
                std::string structureInfoStr;
                if (argument.attributes.isBuffer) {
                    if (!argument.type->isPointer()) {
                        IRB_ERROR("argument marked with 'buffer' attribute must have pointer type");
                        return "";
                    }
                    //TODO: support non-structure types as well
                    if (!argument.type->getElementType()->isStructure()) {
                        IRB_ERROR("argument marked with 'buffer' attribute must have element type of structure");
                        return "";
                    }
                    StructureType* structureType = static_cast<StructureType*>(argument.type->getElementType());

                    //Structure info
                    structureInfo = new MetadataValue(context);
                    structureInfoStr = "!{";
                    uint32_t offset = 0;
                    for (uint32_t j = 0; j < structureType->getStructure()->members.size(); j++) {
                        const auto& member = structureType->getStructure()->members[j];
                        uint32_t size = member.type->getBitCount(true) / 8;
                        if (j != 0)
                            structureInfoStr += ", ";
                        structureInfoStr += "i32 " + std::to_string(offset) + ", i32 " + std::to_string(size) + ", i32 0, !\"" + member.type->getDebugName() + "\", !\"" + member.name + "\""; //TODO: here
                        offset += size;
                    }
                    structureInfoStr += "}";

                    uint32_t align = 8; //TODO: do not hardcode this
                    str += "!\"air.buffer\", !\"air.location_index\", i32 " + std::to_string(argument.attributes.bindings.buffer) + ", i32 1, !\"air.read\", !\"air.address_space\", i32 " + std::to_string(argument.type->getHandle()->getPointerAddressSpace()) + ", !\"air.struct_type_info\", " + structureInfo->getName() + ", !\"air.arg_type_size\", i32 " + std::to_string(structureType->getBitCount(true) / 8) + ", !\"air.arg_type_align_size\", i32 " + std::to_string(align);
                } else if (argument.attributes.isTexture) {
                    //TODO: do not hardcode template arguments
                    str += "!\"air.texture\", !\"air.location_index\", i32 " + std::to_string(argument.attributes.bindings.texture) + ", i32 1, !\"air.sample\"";
                } else if (argument.attributes.isSampler) {
                    str += "!\"air.sampler\", !\"air.location_index\", i32 " + std::to_string(argument.attributes.bindings.sampler) + ", i32 1";
                } else {
                    IRB_ERROR("Every entry point input must be marked with exactly one of these attributes: 'input', 'buffer', 'texture' or 'sampler'");
                    return "";
                }
                str += ", !\"air.arg_type_name\", !\"" + argument.type->getDebugName() + "\", !\"air.arg_name\", !\"" + argument.name + "\"}";
                if (inputIndex != 0)
                    inputsStr += ", ";
                inputsStr += crntInput->getName();
                inputs.emplace_back(crntInput, str);
                if (structureInfo)
                    inputs.emplace_back(structureInfo, structureInfoStr);
                inputIndex++;
            }
        }

        block->addCode("!{ptr @" + entryPoint.value->getRawName() + ", " + entryPointOutputs->getName() + ", " + entryPointInputs->getName() + "}", entryPointInfo);
        block->addCode("!{" + outputsStr + "}", entryPointOutputs); //TODO: here
        //TODO: add output information
        block->addCode("!{" + inputsStr + "}", entryPointInputs); //TODO: here
        //TODO: add input information

        for (const auto& output : outputs)
            block->addCode(output.second, output.first);
        for (const auto& input : inputs)
            block->addCode(input.second, input.first);

        entryPointFunctionInfos[(int)entryPoint.functionRole - 1].push_back(entryPointInfo);
    }

    MetadataValue* denorms = new MetadataValue(context);
    MetadataValue* fastMath = new MetadataValue(context);
    MetadataValue* framebufferFetch = new MetadataValue(context);
    MetadataValue* identification;
    if (includeDebugInformation)
        identification = new MetadataValue(context);
    MetadataValue* version = new MetadataValue(context);
    MetadataValue* languageVersion;
    MetadataValue* sourceFilename;
    if (includeDebugInformation) {
        languageVersion = new MetadataValue(context);
        sourceFilename = new MetadataValue(context);
    }

    block->addCode("!{!\"air.compile.denorms_disable\"}", denorms); //TODO: here
    block->addCode("!{!\"air.compile.fast_math_disable\"}", fastMath); //TODO: here
    block->addCode("!{!\"air.compile.framebuffer_fetch_enable\"}", framebufferFetch); //TODO: here
    if (includeDebugInformation)
        block->addCode("!{!\"" + compilerName + "\"}", identification);
    block->addCode("!{i32 2, i32 6, i32 0}", version); //TODO: here
    if (includeDebugInformation) {
        block->addCode("!{!\"" + languageName + "\", i32 " + std::to_string(languageVersionMajor) + ", i32 " + std::to_string(languageVersionMinor) + ", i32 " + std::to_string(languageVersionPatch) + "}", languageVersion);
        block->addCode("!{!\"" + sourceFilenameStr + "\"}", sourceFilename);
    }

    MetadataValue* llvmModuleFlags = new MetadataValue(context, "llvm.module.flags");
    MetadataValue* airFunctions[3] = {nullptr};
    for (uint8_t i = 0; i < 3; i++) {
        if (entryPointFunctionInfos[i].size() != 0)
            airFunctions[i] = new MetadataValue(context, "air." + functionNames[i]);
    }
    MetadataValue* airCompileOptions = new MetadataValue(context, "air.compile_options");
    MetadataValue* llvmIdent = new MetadataValue(context, "llvm.ident");
    MetadataValue* airVersion = new MetadataValue(context, "air.version");
    MetadataValue* airLanguageVersion = new MetadataValue(context, "air.language_version");
    MetadataValue* airSourceFilename = new MetadataValue(context, "air.source_file_name");

    block->addCodeToBeginning("!{" + sdkVersion->getName() + ", " + wcharSize->getName() + ", " + framePointer->getName() + ", " + maxDeviceBuffers->getName() + ", " + maxConstantBuffers->getName() + ", " + maxThreadgroupBuffers->getName() + ", " + maxTextures->getName() + ", " + maxReadWriteTextures->getName() + ", " + maxSamplers->getName() + "}", llvmModuleFlags);
    for (uint8_t i = 0; i < 3; i++) {
        if (airFunctions[i]) {
            std::string code = "!{";
            for (uint32_t j = 0; j < entryPointFunctionInfos[i].size(); j++) {
                if (j != 0)
                    code += ", ";
                code += entryPointFunctionInfos[i][j]->getName();
            }
            code += "}";
            block->addCodeToBeginning(code, airFunctions[i]);
        }
    }
    block->addCodeToBeginning("!{" + denorms->getName() + ", " + fastMath->getName() + ", " + framebufferFetch->getName() + "}", airCompileOptions);
    if (includeDebugInformation)
        block->addCodeToBeginning("!{" + identification->getName() + "}", llvmIdent);
    block->addCodeToBeginning("!{" + version->getName() + "}", airVersion);
    if (includeDebugInformation) {
        block->addCodeToBeginning("!{" + languageVersion->getName() + "}", airLanguageVersion);
        block->addCodeToBeginning("!{" + sourceFilename->getName() + "}", airSourceFilename);
    }

    return block->getCode();
}

std::string AIRBuilder::getCode(OptimizationLevel optimizationLevel, bool outputAssembly) {
    //Uncomment if something goes wrong
    /*
    std::string tempCode;
    llvm::raw_string_ostream tempStream(tempCode);
    llvmModule->print(tempStream, nullptr);
    std::cout << tempCode << std::endl;

    std::unique_ptr<llvm::MemoryBuffer> buffer = llvm::MemoryBuffer::getMemBuffer(llvm::StringRef(tempCode));
    llvm::SMDiagnostic error;
    llvmModule = llvm::parseIR(buffer->getMemBufferRef(), error, *context.handle);
    if (!llvmModule) {
        error.print("llvm-code", llvm::errs());
        return "";
    }
    */

    llvm::LoopAnalysisManager LAM;
    llvm::FunctionAnalysisManager FAM;
    llvm::CGSCCAnalysisManager CGAM;
    llvm::ModuleAnalysisManager MAM;

    llvm::PassBuilder PB;

    //Register passes
    PB.registerModuleAnalyses(MAM);
    PB.registerCGSCCAnalyses(CGAM);
    PB.registerFunctionAnalyses(FAM);
    PB.registerLoopAnalyses(LAM);
    PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

    //CreatePassManager
    llvm::OptimizationLevel optLevel;
    switch (optimizationLevel) {
    case OptimizationLevel::O0:
        optLevel = llvm::OptimizationLevel::O0;
        break;
    case OptimizationLevel::O1:
        optLevel = llvm::OptimizationLevel::O1;
        break;
    case OptimizationLevel::O2:
        optLevel = llvm::OptimizationLevel::O2;
        break;
    case OptimizationLevel::O3:
        optLevel = llvm::OptimizationLevel::O3;
        break;
    case OptimizationLevel::Os:
        optLevel = llvm::OptimizationLevel::Os;
        break;
    }
    llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(optLevel);

    //Run optimizations
    MPM.run(*llvmModule, MAM);

    //Remove the "memory" attribute, since xcrun metallib would throw "LLVM ERROR: Invalid bitcode file!"
    for (auto &function : *llvmModule)
        function.removeFnAttr(llvm::Attribute::AttrKind::Memory);

    std::string outputCode;
    llvm::raw_string_ostream stream(outputCode);
    if (outputAssembly) {
        stream << *llvmModule;
        stream.flush();
    } else {
        llvm::WriteBitcodeToFile(*llvmModule, stream);
    }

    return outputCode;
}

Function* AIRBuilder::opFunctionDeclaration(FunctionType* functionType, const std::string& name, const std::vector<std::pair<llvm::Attribute::AttrKind, uint64_t> >& attributes) {
    if (auto* value = functionDeclarations[name])
        return value;

    Function* value = new AIRFunction(context, this, functionType, name);
    for (const auto& attribute : attributes)
        static_cast<llvm::Function*>(value->getHandle())->addFnAttr(llvm::Attribute::get(*context.handle, attribute.first, attribute.second));

    functionDeclarations[name] = value;

    return value;
}

} //namespace irb
