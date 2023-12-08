#ifndef LVSLANG_AIR_IR_H
#define LVSLANG_AIR_IR_H

#include "../ir.hpp"

#include "function.hpp"

namespace irb {

class AIRBuilder : public IRBuilder {
public:
    AIRBuilder(Context& aContext, bool aIncludeDebugInformation = false) : IRBuilder(aContext, aIncludeDebugInformation) {
    }

    void opExtension(const std::string& extensionName) override {
    }

    void opImportSTD_EXT(const std::string& stdName) override {
    }

    void opMemoryModel() override {
    }

    void opEntryPoint(Value* entryPoint, const std::string& executionModel, const std::string& name = "main") override {
    }

    void opExecutionMode(Value* entryPoint, const std::string& origin = "OriginLowerLeft") override {
    }

    void opName(Value* value, const std::string& name) override {
        //TODO: put something here?
    }

    void opDecorate(Value* val, Decoration decoration, const std::vector<std::string>& values = {}) override {
    }

    void opMemberDecorate(Value* val, uint32_t memberIndex, Decoration decoration, const std::vector<std::string>& values = {}) override {
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
        return new Value(context, functionType, context.popRegisterName(), "@");
    }

    Value* opFunctionDeclaration(FunctionType* functionType, Value* value = nullptr) override {
        if (!value)
            value = opRegisterFunction(functionType);

        code += "declare " + functionType->getReturnType()->getName() + " " + value->getName() + "(";
        for (uint32_t i = 0; i < functionType->getArguments().size(); i++) {
            if (i != 0)
                code += ", ";
            code += functionType->getArguments()[i]->getName();
        }
        code += ");\n\n";

        return value;
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
        Value* value = opVariable(new PointerType(context, type, StorageClass::Function), StorageClass::Function, argValue);

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
        bool needsPrefix = (operation == Operation::Add || operation == Operation::Subtract || operation == Operation::Multiply || operation == Operation::Divide || operation == Operation::Modulo || operation == Operation::Remainder || needsOrd);

        GET_OPERATION_NAME(operation);

        //TODO: do not use l for getting op prefix?
        std::string prefix = (needsPrefix ? l->getType()->getOpPrefix(signSensitive, false) : "");
        std::string opKindName = "";
        if (operationKindStr != "") {
            opKindName = (prefix == "f" ? "o" : prefix) + operationKindStr + " "; //TODO: support unordered?
            if (prefix == "u" || prefix == "s")
                prefix = "i";
        }
        getAIRInsertBlock()->addCode(prefix + operationStr + " " + opKindName + l->getNameWithType() + ", " + r->getName(), value->getName());

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
        getAIRInsertBlock()->addCode("load " + elementType->getName() + ", " + v->getNameWithType() + ", align 4", value->getName());

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
            code += arguments[i]->getNameWithType();
        }
        code += ")";
        getAIRInsertBlock()->addCode(code, (type->getReturnType()->getTypeID() == TypeID::Void ? "" : value->getName()));

        return value;
    }

    //TODO: support fast math (in function names as well)
    Value* opSTDFunctionCall_EXT(std::string funcName, FunctionType* type, const std::vector<Value*>& arguments) override {
        //We are going to push to register name so we need to save the value first
        std::string registerName = context.popRegisterName();

        //Adjust the name
        funcName = "air." + funcName;

        Value* functionDecl = builtinFunctionDeclarations[funcName];
        if (!functionDecl) {
            context.pushRegisterName(funcName);
            functionDecl = opFunctionDeclaration(type);
        }
        context.pushRegisterName(registerName);

        return opFunctionCall(functionDecl, arguments);
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
            return new Value(context, type, code, "");
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
        getAIRInsertBlock()->addCode("extractelement " + vec->getNameWithType() + ", " + index->getNameWithType(), value->getName());

        return value;
    }

    Value* opVectorInsert(Value* vec, Value* val, ConstantInt* index) override {
        Value* value = new Value(context, vec->getType(), context.popRegisterName());
        getAIRInsertBlock()->addCode("insertelement " + vec->getNameWithType() + ", " + val->getNameWithType() + ", " + index->getNameWithType(), value->getName());

        return value;
    }

    Value* opGetElementPtr(Type* elementType, Value* ptr, const std::vector<Value*>& indexes) override {
        Value* value = new Value(context, elementType, context.popRegisterName());
        std::string code = "getelementptr inbounds " + ptr->getType()->getElementType()->getName() + ", " + ptr->getNameWithType();
        for (uint32_t i = 0; i < indexes.size(); i++)
            code += ", " + indexes[i]->getNameWithType();
        getAIRInsertBlock()->addCode(code, value->getName());

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

            bool needsSTDCall = false;
            std::string opName;
            switch (castFromType->getTypeID()) {
            case TypeID::Bool:
            case TypeID::Integer:
                switch (type->getTypeID()) {
                case TypeID::Bool:
                case TypeID::Integer:
                    if (castFromType->getBitCount() > type->getBitCount()) {
                        opName = "trunc";
                    } else if (castFromType->getBitCount() < type->getBitCount()) {
                        opName = "zext";
                        //TODO: uncomment?
                        //if (!castFromType->getIsSigned())
                        //    opName += " nneg";
                    } else {
                        context.popRegisterName();

                        return val;
                    }
                    break;
                case TypeID::Float:
                    needsSTDCall = true;
                    break;
                default:
                    break;
                }
                break;
            case TypeID::Float:
                switch (type->getTypeID()) {
                case TypeID::Bool:
                case TypeID::Integer:
                    needsSTDCall = true;
                    break;
                case TypeID::Float:
                    if (castFromType->getBitCount() > type->getBitCount())
                        opName = "fptrunc";
                    else
                        opName = "fpext";
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }

            if (needsSTDCall) {
                //TODO: move the function selection based on type to @ref opSTDFunctionCall_EXT
                std::string functionName = "convert." + type->getBuiltinFunctionTypeName() + "." + castFromType->getBuiltinFunctionTypeName();
                return opSTDFunctionCall_EXT(functionName, functionType, {val});
            } else {
                Value* value = new Value(context, type, context.popRegisterName());
                getAIRInsertBlock()->addCode(opName + " " + val->getNameWithType() + " to " + type->getName(), value->getName());

            }
        } else if (val->getType()->isScalar() && type->isVector()) {
            return opVectorConstruct(static_cast<VectorType*>(type), std::vector<Value*>(static_cast<VectorType*>(type)->getComponentCount(), val));
        }

        //HACK: just ignore
        return val;
    }

    Value* opSample(Value* texture, Value* sampler, Value* coords, Value* lod = nullptr) override {
        //TODO: find out what are these arguments
        Value* argument4 = new ConstantBool(context, true);
        Value* argument5 = opVectorConstruct(new VectorType(context, new ScalarType(context, TypeID::Integer, 32, true), 2), {new ConstantInt(context, 0, 32, true), new ConstantInt(context, 0, 32, true)});
        Value* argument6 = new ConstantBool(context, false);
        Value* argument7 = new ConstantFloat(context, 0.0f, 32);
        Value* argument8 = new ConstantFloat(context, 0.0f, 32);
        Value* argument9 = new ConstantInt(context, 0, 32, true);

        FunctionType* type = new FunctionType(context, new VectorType(context, texture->getType()->getElementType()->getBaseType(), 4), {texture->getType(), sampler->getType(), coords->getType(), argument4->getType(), argument5->getType(), argument6->getType(), argument7->getType(), argument8->getType(), argument9->getType()});

        //TODO: remove the hardoced types in the name
        return opSTDFunctionCall_EXT("sample_texture_2d.v4f32", type, {texture, sampler, coords, argument4, argument5, argument6, argument7, argument8, argument9});
    }

    Value* opVariable(PointerType* type, StorageClass storageClass, Value* initializer = nullptr) override {
        Value* value = new Value(context, type, context.popRegisterName());
        //TODO: use proper alignment
        getAIRFunctionBlock()->addCode("alloca " + type->getElementType()->getName() + ", align 4", value->getName());
        if (initializer)
            opStore(value, initializer);
        
        return value;
    }

    //Getters
    std::string getCode() override {
        return code;
    }

private:
    std::string code;

    std::map<std::string, Value*> builtinFunctionDeclarations;

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

} //namespace irb

#endif
