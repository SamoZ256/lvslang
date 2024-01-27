#ifndef LVSLANG_AIR_IR_H
#define LVSLANG_AIR_IR_H

#include "../ir.hpp"

#include "function.hpp"

namespace irb {

struct AIRInterfaceVariable {

};

struct AIREntryPoint {
    Value* value;
    FunctionRole functionRole;
    Type* returnType;
    std::vector<Argument> arguments;
};

class AIRBuilder : public IRBuilder {
private:
    std::vector<AIREntryPoint> entryPoints;

public:
    AIRBuilder(Context& aContext, bool aIncludeDebugInformation = false) : IRBuilder(aContext, aIncludeDebugInformation) {
    }

    void opExtension(const std::string& extensionName) override {
    }

    void opImportSTD_EXT(const std::string& stdName) override {
    }

    void opMemoryModel() override {
    }

    void opEntryPoint(Value* entryPoint, FunctionRole functionRole, const std::string& name, Type* returnType, const std::vector<Argument>& arguments) override {
        entryPoints.push_back({entryPoint, functionRole, returnType, arguments});
    }

    void opName(Value* value, const std::string& name) override {
        //TODO: put something here?
    }

    Value* opConstant(ConstantValue* val) override {
        context.popRegisterName();

        return val;
    }

    Value* opStructureDefinition(StructureType* structureType) override {
        Value* value = new Value(context, structureType, context.popRegisterName());
        code += value->getName() + " = type { ";
        const auto& members = structureType->getStructure()->members;
        for (uint32_t i = 0; i < members.size(); i++) {
            if (i != 0)
                code += ", ";
            code += members[i].type->getName();
        }
        code += " }\n\n";

        return value;
    }

    Value* opRegisterFunction(FunctionType* functionType) override {
        return new Value(context, functionType, context.popRegisterName(), "@", false);
    }

    Value* opFunctionDeclaration(FunctionType* functionType, const std::string& name) {
        if (auto* value = functionDeclarations[name])
            return value;

        Value* value = new Value(context, functionType, name, "@", false);

        code += "declare " + functionType->getReturnType()->getName() + " " + value->getName() + "(";
        for (uint32_t i = 0; i < functionType->getArguments().size(); i++) {
            if (i != 0)
                code += ", ";
            code += functionType->getArguments()[i]->getName() + functionType->getArguments()[i]->getAttributes();
        }
        code += ");\n\n";

        functionDeclarations[name] = value;

        return value;
    }

    //TODO: support fast math (in function names)
    Value* opStandardFunctionDeclaration(FunctionType* functionType, const std::string& name) override {
        if (!standardFunctionLUT.count(name)) {
            IRB_INVALID_ARGUMENT_WITH_REASON("name", "there is no such standard function");
            return nullptr;
        }
        
        //TODO: only add template name if there is at least one argument
        std::string fullName = "air." + name + "." + functionType->getArguments()[0]->getTemplateName();

        const auto& standardFunctionInfo = standardFunctionLUT[fullName];

        if (name == "sample") {
            //TODO: do error checks
            functionType = new FunctionType(context, functionType->getReturnType(), {functionType->getArguments()[0], functionType->getArguments()[1], functionType->getArguments()[2], new ScalarType(context, TypeID::Bool, 8, false), new VectorType(context, new ScalarType(context, TypeID::Integer, 32, true), 2), new ScalarType(context, TypeID::Bool, 8, false), new ScalarType(context, TypeID::Float, 32, true), new ScalarType(context, TypeID::Float, 32, true), new ScalarType(context, TypeID::Integer, 32, true)});

            return opFunctionDeclaration(functionType, "air.sample_texture_2d." + functionType->getReturnType()->getTemplateName());
        } else {
            return opFunctionDeclaration(functionType, fullName);
        }
    }

    Value* opFunction(FunctionType* functionType, Value* value = nullptr) override {
        if (!value)
            value = opRegisterFunction(functionType);
        function = new AIRFunction(context, this, functionType, value);

        return function->getValue();
    }

    Value* opFunctionParameter(Type* type) override {
        Value* argValue = new Value(context, type, context.popRegisterName());
        static_cast<AIRFunction*>(function)->addArgument(argValue);
        //This is required in order to maintain consistency with SPIRV
        Value* value = opVariable(new PointerType(context, type, StorageClass::Function), argValue);

        return value;
    }

    void opFunctionEnd() override {
        function->end();
        code += function->getCode() + "\n\n";
    }

    Block* opBlock() override {
        AIRBlock* block = new AIRBlock(context, context.popRegisterName());

        return block;
    }

    //TODO: support fast math
    Value* opOperation(Value* l, Value* r, Type* type, Operation operation) override {
        if (!type->isOperatorFriendly()) {
            IRB_INVALID_ARGUMENT_WITH_REASON("type", "type is not operator friendly (e.g. is not one of: scalar, pointer, vector)");
            return nullptr;
        }

        Value* value = new Value(context, type, context.popRegisterName());
        if (r->getType()->isVector() && l->getType()->isScalar())
            std::swap(l, r);
        if (l->getType()->isVector() && r->getType()->isScalar()) {
            r = opVectorConstruct(static_cast<VectorType*>(type), std::vector<Value*>(static_cast<VectorType*>(type)->getComponentCount(), r)); //TODO: check if the type is vector
        }
        
        bool needsOrd = (operation == Operation::GreaterThan || operation == Operation::GreaterThanEqual || operation == Operation::LessThan || operation == Operation::LessThanEqual);
        bool signSensitive = (operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || needsOrd);
        bool needsPrefix = (operation == Operation::Add || operation == Operation::Subtract || operation == Operation::Multiply || operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || operation == Operation::And || operation == Operation::Or || operation == Operation::Equal || operation == Operation::NotEqual || needsOrd);

        GET_OPERATION_NAME(operation);

        //TODO: do not use l for getting op prefix?
        std::string prefix = (needsPrefix ? l->getType()->getOpPrefix(signSensitive, false) : "");
        std::string opKindName = "";
        if (operationKindStr != "") {
            opKindName = (prefix == "f" ? "o" : prefix) + operationKindStr + " "; //TODO: support unordered?
            if (prefix != "f")
                prefix = "i";
        }
        getAIRInsertBlock()->addCode(prefix + operationStr + " " + opKindName + l->getNameWithType() + ", " + r->getName(), value);

        return value;
    }

    Value* opLoad(Value* v) override {
        if (!v->getType()->isPointer()) {
            IRB_INVALID_ARGUMENT_WITH_REASON("v", "type of 'v' is not a pointer");
            return nullptr;
        }

        Type* elementType = v->getType()->getElementType();
        Value* value = new Value(context, elementType, context.popRegisterName());
        //TODO: use proper alignment
        getAIRInsertBlock()->addCode("load " + elementType->getName() + ", " + v->getNameWithType() + ", align 4", value);

        return value;
    }

    void opStore(Value* ptr, Value* v) override {
        //TODO: use proper alignment
        getAIRInsertBlock()->addCode("store " + v->getNameWithType() + ", " + ptr->getNameWithType() + ", align 4");
    }

    void opReturn(Value* v = nullptr) override {
        if (v)
            getAIRInsertBlock()->addCode("ret " + v->getNameWithType());
        else
            getAIRInsertBlock()->addCode("ret void");

        getAIRInsertBlock()->setReturned();
    }

    //TODO: support fast math
    //TODO: what should be returned when return type is void?
    Value* opFunctionCall(Value* funcV, const std::vector<Value*>& arguments) override {
        FunctionType* type = dynamic_cast<FunctionType*>(funcV->getType());
        if (!type) {
            IRB_INVALID_ARGUMENT_WITH_REASON("funcV", "type of 'funcV' is not a function");
            return nullptr;
        }

        Value* value = new Value(context, type->getReturnType(), context.popRegisterName());
        std::string code = "call " + type->getReturnType()->getName() + " " + funcV->getName() + "(";
        for (uint32_t i = 0; i < arguments.size(); i++) {
            if (i != 0)
                code += ", ";
            code += arguments[i]->getType()->getName() + type->getArguments()[i]->getAttributes() + " " + arguments[i]->getName();
        }
        code += ")";
        getAIRInsertBlock()->addCode(code, (type->getReturnType()->getTypeID() == TypeID::Void ? nullptr : value));

        return value;
    }

    void opBranch(Block* block) override {
        getAIRInsertBlock()->addCode("br " + block->getNameWithType());
    }

    void opBranchCond(Value* cond, Block* blockTrue, Block* blockFalse) override {
        getAIRInsertBlock()->addCode("br " + cond->getNameWithType() + ", " + blockTrue->getNameWithType() + ", " + blockFalse->getNameWithType());
    }

    void opBlockMerge(Block* block) override {
    }

    void opLoopMerge(Block* block1, Block* block2) override {
    }

    Value* opVectorConstruct(VectorType* type, const std::vector<Value*>& components) override {
        context.popRegisterName();
        bool allComponentsAreConstant = true;
        for (uint8_t i = 0; i < components.size(); i++) {
            if (!components[i]->isConstant()) {
                allComponentsAreConstant = false;
                break;
            }
        }
        if (allComponentsAreConstant) {
            std::string code = "<";
            for (uint8_t i = 0; i < components.size(); i++) {
                if (i != 0)
                    code += ", ";
                code += components[i]->getNameWithType();
            }
            code += ">";
            return new Value(context, type, code, "", false);
        } else {
            Value* value = new UndefinedValue(context, type);
            for (uint8_t i = 0; i < components.size(); i++) {
                value = opVectorInsert(value, components[i], new ConstantInt(context, i, 32, true));
            }

            return value;
        }
    }

    Value* opVectorExtract(Value* vec, ConstantInt* index) override {
        Value* value = new Value(context, vec->getType()->getBaseType(), context.popRegisterName());
        getAIRInsertBlock()->addCode("extractelement " + vec->getNameWithType() + ", " + index->getNameWithType(), value);

        return value;
    }

    Value* opVectorInsert(Value* vec, Value* val, ConstantInt* index) override {
        Value* value = new Value(context, vec->getType(), context.popRegisterName());
        getAIRInsertBlock()->addCode("insertelement " + vec->getNameWithType() + ", " + val->getNameWithType() + ", " + index->getNameWithType(), value);

        return value;
    }

    Value* opGetElementPtr(PointerType* elementType, Value* ptr, const std::vector<Value*>& indexes) override {
        if (!ptr->getType()->isPointer()) {
            IRB_INVALID_ARGUMENT_WITH_REASON("ptr", "type of 'ptr' is not pointer type");
            return nullptr;
        }
        //HACK: set the address space
        elementType->setAddressSpace(static_cast<PointerType*>(ptr->getType())->getAddressSpace());
        Value* value = new Value(context, elementType, context.popRegisterName());
        std::string code = "getelementptr inbounds " + ptr->getType()->getElementType()->getName() + ", " + ptr->getNameWithType() + ", i32 0";
        for (uint32_t i = 0; i < indexes.size(); i++)
            code += ", " + indexes[i]->getNameWithType();
        getAIRInsertBlock()->addCode(code, value);

        return value;
    }

    void opUnreachable() override {
        getAIRInsertBlock()->addCode("unreachable");
    }

    //TODO: support fast math
    Value* opCast(Value* val, Type* type) override {
        if (val->getType()->equals(type)) {
            context.popRegisterName();

            return val;
        }
        
        Type* castFromType = val->getType();

        //TODO: support vector casting
        if (type->isScalar() && castFromType->isScalar()) {
            FunctionType* functionType = new FunctionType(context, type, {castFromType});

            //TODO: move the function selection based on type to @ref opSTDFunctionCall_EXT
            std::string functionName = "convert." + type->getOpPrefix(true, false) + "." + type->getTemplateName() + "." + castFromType->getOpPrefix(true, false) + "." + castFromType->getTemplateName();

            Value* funcV = opFunctionDeclaration(functionType, functionName);

            return opFunctionCall(funcV, {val});
        } else if (val->getType()->isScalar() && type->isVector()) {
            return opVectorConstruct(static_cast<VectorType*>(type), std::vector<Value*>(static_cast<VectorType*>(type)->getComponentCount(), val));
        }

        //HACK: just ignore
        return val;
    }

    Value* opSample(Value* funcV, Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) override {
        //TODO: find out what are these arguments
        Value* argument4 = new ConstantBool(context, true);
        Value* argument5 = opVectorConstruct(new VectorType(context, new ScalarType(context, TypeID::Integer, 32, true), 2), {new ConstantInt(context, 0, 32, true), new ConstantInt(context, 0, 32, true)});
        Value* argument6 = new ConstantBool(context, false);
        Value* argument7 = new ConstantFloat(context, 0.0f, 32);
        Value* argument8 = new ConstantFloat(context, 0.0f, 32);
        Value* argument9 = new ConstantInt(context, 0, 32, true);

        return opFunctionCall(funcV, {texture, sampler, coords, argument4, argument5, argument6, argument7, argument8, argument9});
    }

    Value* opVariable(PointerType* type, Value* initializer = nullptr) override {
        Value* value = new Value(context, type, context.popRegisterName());
        //TODO: use proper alignment
        getAIRFunctionBlock()->addCode("alloca " + type->getElementType()->getName() + ", align 4", value);
        if (initializer)
            opStore(value, initializer);
        
        return value;
    }

    void createMetadata();

    //Getters
    std::string getCode() override {
        return code;
    }

private:
    std::string code;

    std::map<std::string, Value*> functionDeclarations;

    void _opDecorate(std::string begin, Decoration decoration, const std::vector<std::string>& values = {}) {
    }

    inline AIRBlock* getAIRInsertBlock() {
        return static_cast<AIRBlock*>(getInsertBlock());
    }

    inline AIRBlock* getAIRFunctionBlock() {
        return static_cast<AIRBlock*>(getFunctionBlock());
    }

    inline AIRBlock* getAIRFirstFunctionBlock() {
        return static_cast<AIRBlock*>(getFirstFunctionBlock());
    }
};

class MetadataValue : public Value {
public:
    MetadataValue(Context& aContext, const std::string& aName = "") : Value(aContext, new ScalarType(aContext, TypeID::Void, 0, true), aName, "!") {}
};

class MetadataBlock : public AIRBlock {
private:
    std::string _addCode(const std::string& instruction, Value* registerToAssign, const std::string& comment) override {
        std::string inst = "\n" + registerToAssign->getName() + " = " + instruction;

        if (comment.size() != 0)
            inst += " ; " + comment;

        return inst;
    }

public:
    using AIRBlock::AIRBlock;
};

//TODO: check if it really called "kernel"
const std::string functionNames[3] = {"vertex", "fragment", "kernel"};

//TODO: support other values whenever there is a 'TODO: here' comment
void AIRBuilder::createMetadata() {
    MetadataBlock* block = new MetadataBlock(context);

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
                return;
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
                str += ", !\"air.arg_type_name\", !\"" + member.type->getName() + "\", !\"air.arg_name\", !\"" + member.name + "\"}"; //TODO: don't use type name directly, use the name as if it was in Metal Shading Language

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
                    return;
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

                    str += ", !\"air.arg_type_name\", !\"" + member.type->getName() + "\", !\"air.arg_name\", !\"" + member.name + "\"}"; //TODO: don't use type name directly, use the name as if it was in Metal Shading Language
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
                        return;
                    }
                    //TODO: support non-structure types as well
                    if (!argument.type->getElementType()->isStructure()) {
                        IRB_ERROR("argument marked with 'buffer' attribute must have element type of structure");
                        return;
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
                        //TODO: don't use type name directly, use the name as if it was in Metal Shading Language
                        structureInfoStr += "i32 " + std::to_string(offset) + ", i32 " + std::to_string(size) + ", i32 0, !\"" + member.type->getName() + "\", !\"" + member.name + "\""; //TODO: here
                        offset += size;
                    }
                    structureInfoStr += "}";

                    uint32_t align = 8; //TODO: do not hardcode this
                    str += "!\"air.buffer\", !\"air.location_index\", i32 " + std::to_string(argument.attributes.bindings.buffer) + ", i32 1, !\"air.read\", !\"air.address_space\", i32 " + std::to_string(static_cast<PointerType*>(argument.type)->getAddressSpace()) + ", !\"air.struct_type_info\", " + structureInfo->getName() + ", !\"air.arg_type_size\", i32 " + std::to_string(structureType->getBitCount(true) / 8) + ", !\"air.arg_type_align_size\", i32 " + std::to_string(align);
                } else if (argument.attributes.isTexture) {
                    //TODO: do not hardcode template arguments
                    str += "!\"air.texture\", !\"air.location_index\", i32 " + std::to_string(argument.attributes.bindings.texture) + ", i32 1, !\"air.sample\"";
                } else if (argument.attributes.isSampler) {
                    str += "!\"air.sampler\", !\"air.location_index\", i32 " + std::to_string(argument.attributes.bindings.sampler) + ", i32 1";
                } else {
                    IRB_ERROR("Every entry point input must be marked with exactly one of these attributes: 'input', 'buffer', 'texture' or 'sampler'");
                    return;
                }
                str += ", !\"air.arg_type_name\", !\"" + argument.type->getName() + "\", !\"air.arg_name\", !\"" + argument.name + "\"}"; //TODO: don't use type name directly, use the name as if it was in Metal Shading Language
                if (inputIndex != 0)
                    inputsStr += ", ";
                inputsStr += crntInput->getName();
                inputs.emplace_back(crntInput, str);
                if (structureInfo)
                    inputs.emplace_back(structureInfo, structureInfoStr);
                inputIndex++;
            }
        }

        block->addCode("!{" + entryPoint.value->getNameWithType() + ", " + entryPointOutputs->getName() + ", " + entryPointInputs->getName() + "}", entryPointInfo);
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
    MetadataValue* identification = new MetadataValue(context);
    MetadataValue* version = new MetadataValue(context);
    MetadataValue* languageVersion = new MetadataValue(context);
    MetadataValue* sourceFilename = new MetadataValue(context);

    block->addCode("!{!\"air.compile.denorms_disable\"}", denorms); //TODO: here
    block->addCode("!{!\"air.compile.fast_math_disable\"}", fastMath); //TODO: here
    block->addCode("!{!\"air.compile.framebuffer_fetch_enable\"}", framebufferFetch); //TODO: here
    block->addCode("!{!\"Lvslang\"}", identification); //TODO: here
    block->addCode("!{i32 2, i32 6, i32 0}", version); //TODO: here
    block->addCode("!{!\"LVSL\", i32 0, i32 7, i32 0}", languageVersion); //TODO: here
    block->addCode("!{!\"/Users/samuliak/Desktop/lvslang/test.lvsl\"}", sourceFilename); //TODO: here

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
    block->addCodeToBeginning("!{" + identification->getName() + "}", llvmIdent);
    block->addCodeToBeginning("!{" + version->getName() + "}", airVersion);
    block->addCodeToBeginning("!{" + languageVersion->getName() + "}", airLanguageVersion);
    block->addCodeToBeginning("!{" + sourceFilename->getName() + "}", airSourceFilename);

    code += block->getCode();
}

} //namespace irb

#endif
