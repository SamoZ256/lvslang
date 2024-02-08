#include "ast.hpp"

namespace lvslang {

irb::Context context;
irb::IRBuilder* builder;

GLSLVersion glslVersion = GLSLVersion::_1_10;

irb::Type* crntFunctionReturnType = nullptr;

uint32_t currentIndentation = 0;

std::map<std::string, Variable> variables;
std::map<std::string, std::vector<FunctionPrototypeAST*> > functionDeclarations;
std::map<std::string, Enumeration*> enumerations;

/*
irb::Value* TopLevelAST::_codegen() {
    for (auto* expression : expressions) {
        if (!expression->codegen())
            return nullptr;
    }
}
*/

irb::Type* NumberExpressionAST::_initialize() {
    if (requiredType) {
        if (requiredType->isScalar()) {
            scalarType = requiredType;
        } else if (requiredType->isVector()) {
            scalarType = requiredType->getBaseType();
        } else {
            logError("cannot cast constant expression of type constant number to '" + requiredType->getDebugName() + "'");
            return nullptr;
        }
    }

    if (scalarType->getTypeID() != irb::TypeID::Bool && scalarType->getTypeID() != irb::TypeID::Integer && scalarType->getTypeID() != irb::TypeID::Float) {
        logError("constant value is not bool, int or float");
        return nullptr;
    }

    return scalarType;
}

irb::Value* NumberExpressionAST::_codegen() {
    irb::ConstantValue* value;
    switch (getType()->getTypeID()) {
    case irb::TypeID::Bool:
        value = new irb::ConstantBool(context, _valueU);
        break;
    case irb::TypeID::Integer:
        if (getType()->getIsSigned())
            value = new irb::ConstantInt(context, _valueL, getType()->getBitCount(), true);
        else
            value = new irb::ConstantInt(context, _valueU, getType()->getBitCount(), false);
        break;
    case irb::TypeID::Float:
        value = new irb::ConstantFloat(context, _valueD, getType()->getBitCount());
        break;
    default:
        break;
    }
    
    if (TARGET_IS_IR(irb::target)) {
        //TODO: find out why I do this
        if (!context.pushedRegisterName())
            context.pushRegisterName("const");

        return builder->opConstant(value);
    }

    return value;
}

irb::Type* VariableExpressionAST::_initialize() {
    auto iter = variables.find(_name);
    if (iter != variables.end()) {
        variable = &iter->second;
        if (loadOnCodegen && variable->shouldBeLoaded)
            return variable->type->getElementType();
        else
            return variable->type;
    } else {
        logError("Use of undeclared variable '" + _name + "'");
        return nullptr;
    }
}

irb::Value* VariableExpressionAST::_codegen() {
    irb::Value* value = variable->value;
    if (loadOnCodegen && variable->shouldBeLoaded) {
        if (TARGET_IS_IR(irb::target))
            value = builder->opLoad(value);
        else
            value = new irb::Value(context, getType(), value->getRawName());
    }

    return value;
}

irb::Type* BinaryExpressionAST::_initialize() {
    if (op == "=")
        lhs->setLoadOnCodegen(false);
    
    irb::Type* lType = lhs->initialize();
    if (!lType)
        return nullptr;
    irb::Type* rType = rhs->initialize(op == "=" ? lType->getElementType() : lType);
    if (!rType)
        return nullptr;

    if (op == "=")
        return lType->getElementType();
    
    if (!lType->isOperatorFriendly()) {
        logError("Left-hand operand is not operator friendly");
        return nullptr;
    }
    if (!rType->isOperatorFriendly()) {
        logError("Right-hand operand is not operator friendly");
        return nullptr;
    }

    irb::Type* type = getPromotedType(lType, rType);

    if (op == "+") {
        operation = irb::Operation::Add;
    } else if (op == "-") {
        operation = irb::Operation::Subtract;
    } else if (op == "*") {
        operation = irb::Operation::Multiply;
    } else if (op == "/") {
        operation = irb::Operation::Divide;
    } else if (op == "&") {
        operation = irb::Operation::BitwiseAnd;
    } else if (op == "|") {
        operation = irb::Operation::BitwiseOr;
    } else if (op == "==") {
        operation = irb::Operation::Equal;
        type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
    } else if (op == "!=") {
        operation = irb::Operation::NotEqual;
        type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
    } else if (op == "&&") {
        operation = irb::Operation::And;
        type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
    } else if (op == "||") {
        operation = irb::Operation::Or;
        type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
    } else if (op == ">") {
        operation = irb::Operation::GreaterThan;
        type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
    } else if (op == "<") {
        operation = irb::Operation::LessThan;
        type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
    } else if (op == ">=") {
        operation = irb::Operation::GreaterThanEqual;
        type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
    } else if (op == "<=") {
        operation = irb::Operation::LessThanEqual;
        type = new irb::ScalarType(context, irb::TypeID::Bool, 8, false);
    }

    return type;
}

irb::Value* BinaryExpressionAST::_codegen() {
    irb::Value* l = lhs->codegen();
    if (!l)
        return nullptr;
    irb::Value* r = rhs->codegen();
    if (!r)
        return nullptr;

    if (op == "=") {
        if (TARGET_IS_IR(irb::target)) {
            if (auto* unloadedVector = dynamic_cast<UnloadedSwizzledVectorValue*>(l)) {
                irb::Value* loadedVector = builder->opLoad(unloadedVector->getUnloadedVector());
                if (r->getType()->isScalar()) {
                    for (auto index : unloadedVector->getIndices())
                        loadedVector = builder->opVectorInsert(loadedVector, r, new irb::ConstantInt(context, index, 32, true)); //TODO: should it be signed?
                } else if (r->getType()->isVector()) {
                    //TODO: check if component count matches and if we are not accessing out of bounds
                    for (uint8_t i = 0; i < unloadedVector->getIndices().size(); i++)
                        loadedVector = builder->opVectorInsert(loadedVector, builder->opVectorExtract(r, new irb::ConstantInt(context, i, 32, true)), new irb::ConstantInt(context, unloadedVector->getIndices()[i], 32, true));
                } else {
                    logError("cannot assign to vector from type other than scalar and vector");
                    return nullptr;
                }
                builder->opStore(unloadedVector->getUnloadedVector(), loadedVector);
            } else {
                builder->opStore(l, r);
            }
        }

        return new irb::Value(context, getType(), l->getRawName() + " = " + r->getRawName());
    }

    if (TARGET_IS_CODE(irb::target)) {
        return new irb::Value(context, getType(), "(" + l->getRawName() + " " + op + " " + r->getRawName() + ")");
    } else {
        context.pushRegisterName("op");
        irb::Value* value = builder->opOperation(l, r, getType(), operation);

        return value;
    }
}

irb::Type* BlockExpressionAST::_initialize() {
    for (auto expr : expressions) {
        irb::Type* type = expr->initialize();
        if (!type)
            return nullptr;
    }
    
    //TODO: return something else?
    return new irb::ScalarType(context, irb::TypeID::Void, 0);
}

irb::Value* BlockExpressionAST::_codegen() {
    std::string codeStr = "{\n";

    currentIndentation += 1;

    for (auto expr : expressions) {
        irb::Value* value = expr->codegen();
        if (!value)
            return nullptr;
        if (TARGET_IS_CODE(irb::target)) {
            for (uint16_t i = 0; i < currentIndentation; i++)
                codeStr += "\t";
            codeStr += value->getRawName() + ";\n";
        }
    }

    currentIndentation -= 1;

    for (uint16_t i = 0; i < currentIndentation; i++)
        codeStr += "\t";
    codeStr += "}";
    
    return new irb::Value(context, getType(), codeStr);
}

irb::Type* FunctionPrototypeAST::_initialize() {
    uint32_t bufferBinding = 0, textureBinding = 0, samplerBinding = 0;
    for (uint32_t i = 0; i < _arguments.size(); i++) {
        irb::Argument& arg = _arguments[i];
        auto& attr = arg.attributes;
        if (attr.addressSpace != 0) {
            irb::PointerType* pointerType = dynamic_cast<irb::PointerType*>(arg.type);
            if (!pointerType) {
                logError("only pointers can be used with an address space");
                return nullptr;
            }
            //pointerType->setAddressSpace(attr.addressSpace);
        }
        if (functionRole != irb::FunctionRole::Normal) {
            //TDOO: save the bindings for reflection
            if (arg.type->isTexture()) {
                attr.isTexture = true;
                attr.bindings.texture = textureBinding++;
            } else if (arg.type->isSampler()) {
                attr.isSampler = true;
                attr.bindings.sampler = samplerBinding++;
            } else if (!attr.isInput) {
                irb::PointerType* pointerType = dynamic_cast<irb::PointerType*>(arg.type);
                if (!pointerType) {
                    logError("only pointers can be used as buffers");
                    return nullptr;
                }
                attr.isBuffer = true;
                attr.bindings.buffer = bufferBinding++;
                if ((irb::target == irb::Target::SPIRV || irb::target == irb::Target::GLSL || irb::target == irb::Target::HLSL) && functionRole != irb::FunctionRole::Normal)
                    arg.type = arg.type->getElementType();
                //pointerType->addAttribute(" noundef \"air-buffer-no-alias\"");
            }
        }
    }

    std::vector<irb::Type*> argumentTypes;
    argumentTypes.resize((_arguments.size()));
    for (uint32_t i = 0; i < argumentTypes.size(); i++)
        argumentTypes[i] = _arguments[i].type;
    irb::FunctionType* functionType = new irb::FunctionType(context, returnType, argumentTypes);

    identifier = functionType->getTemplateName();

    //Check for redefinition
    if (isDefined) {
        if (functionDeclarations.count(_name)) {
            const auto& declarations = functionDeclarations[_name];
            for (const auto& declaration : declarations) {
                if (identifier == declaration->getIdentifier()) {
                    if (returnType->equals(declaration->getReturnType())) {
                        if (declaration->getIsDefined()) {
                            logError("redefinition of function '" + _name + "'");
                            return nullptr;
                        } else {
                            previousDeclaration = declaration;
                        }
                    } else {
                        logError("cannot distinguish functions '" + _name + "' based on return type alone");
                        return nullptr;
                    }
                }
            }
        }
    }

    functionDeclarations[_name].push_back(this);

    crntFunctionReturnType = functionType->getReturnType();

    return functionType;
}

irb::Value* FunctionPrototypeAST::_codegen() {
    if (TARGET_IS_CODE(irb::target)) {
        if (isSTDFunction)
            return new irb::Value(context, nullptr, "");
            
        std::string codeStr;
        std::string argsStr;
        std::string entryPointStr;
        for (uint32_t i = 0; i < _arguments.size(); i++) {
            irb::Argument& arg = _arguments[i];
            auto& attr = arg.attributes;
            if (i != 0)
                argsStr += ", ";
            if (irb::target == irb::Target::Metal) {
                std::string addressSpace;
                if (attr.addressSpace == 2)
                    addressSpace = "constant ";
                else if (attr.addressSpace == 1)
                    addressSpace = "device ";
                
                std::string attribute;
                if (attr.isBuffer)
                    attribute = " [[buffer(" + std::to_string(attr.bindings.buffer) + ")]]";
                if (attr.isTexture)
                    attribute = " [[texture(" + std::to_string(attr.bindings.texture) + ")]]";
                if (attr.isSampler)
                    attribute = " [[sampler(" + std::to_string(attr.bindings.sampler) + ")]]";
                if (attr.isInput)
                    attribute = " [[stage_in]]";

                argsStr += addressSpace + getTypeName(arg.type) + " " + arg.name + attribute;
            } else if (irb::target == irb::Target::HLSL) {
                argsStr += getTypeName(arg.type) + " " + arg.name;

                //Entry point
                if (functionRole != irb::FunctionRole::Normal) {
                    if (!attr.isInput) {
                        if (attr.isBuffer) {
                            entryPointStr += "cbuffer "; //TODO: support other types of buffer as well
                            //We need to get element type, since HLSL treats it without pointer
                            entryPointStr += arg.name + "_Uniform : register(b" + std::to_string(attr.bindings.buffer) + ") {\n\t" + getTypeName(arg.type) + " " + arg.name + ";\n}";
                        } else if (attr.isTexture) {
                            entryPointStr += getTypeName(arg.type) + " " + arg.name + " : register(t" + std::to_string(attr.bindings.sampler) + ")";
                        } else if (attr.isSampler) {
                            entryPointStr += getTypeName(arg.type) + " " + arg.name + " : register(s" + std::to_string(attr.bindings.sampler) + ")";
                        }
                        entryPointStr += ";\n\n";
                    }
                }
            } else {
                argsStr += getTypeName(arg.type) + " " + arg.name;

                //Entry point
                if (functionRole != irb::FunctionRole::Normal) {
                    std::string typeName;
                    if (attr.isInput) {
                        switch (functionRole) {
                        case irb::FunctionRole::Vertex:
                            //TODO: do this error check for every backend?
                            if (!arg.type->isStructure()) {
                                logError("Entry point argument declared with the 'input' attribute must have a structure type");
                                return nullptr;
                            }
                            for (const auto& member : static_cast<irb::StructureType*>(arg.type)->getStructure()->members)
                                entryPointStr += "layout (location = " + std::to_string(member.attributes.locationIndex) + ") in " + getTypeName(member.type) + " " + member.name + ";\n\n";
                            break;
                        case irb::FunctionRole::Fragment:
                            entryPointStr += "layout (location = 0) in " + getTypeName(arg.type) + "_Input {\n\t" + getTypeName(arg.type) + " " + arg.name + ";\n};\n\n";
                            break;
                        default:
                            logError("cannot use the 'input' attribute for kernel function");
                            return nullptr;
                        }
                    } else {
                        if (attr.isBuffer) {
                            if (attr.addressSpace == 2)
                                typeName = "uniform ";
                            else
                                typeName = "readonly buffer "; //TODO: support other types of buffer as well
                            //We need to get element type, since GLSL treats it without pointer
                            typeName += arg.name + "_Uniform {\n\t" + getTypeName(arg.type) + " " + arg.name + ";\n}";
                        } else {
                            typeName = "uniform " + getTypeName(arg.type);
                        }
                        entryPointStr += "layout (set = " + std::to_string(attr.bindings.set) + ", binding = " + std::to_string(attr.bindings.binding) + ") " + typeName;
                        if (!attr.isBuffer)
                            entryPointStr += " " + arg.name;
                        entryPointStr += ";\n\n";
                    }
                }
            }
        }

        if (functionRole != irb::FunctionRole::Normal) {
            if (irb::target == irb::Target::Metal) {
                switch (functionRole) {
                case irb::FunctionRole::Vertex:
                    codeStr = "vertex ";
                    break;
                case irb::FunctionRole::Fragment:
                    codeStr = "fragment ";
                    break;
                case irb::FunctionRole::Kernel:
                    codeStr = "kernel ";
                    break;
                default:
                    break;
                }
            } else if (irb::target == irb::Target::HLSL) {
                if (returnType->getTypeID() != irb::TypeID::Void) {
                    entryPointStr += "struct " + getTypeName(returnType) + "_Output {\n\t" + getTypeName(returnType) + " output : TEXCOORD0;\n";
                    if (functionRole == irb::FunctionRole::Vertex)
                        entryPointStr += "\tfloat4 position : SV_Position;\n";
                    entryPointStr += "};\n\n";
                }

                //Entry point
                std::string argsStr;
                for (const auto& argument : _arguments) {
                    if (argument.attributes.isInput) {
                        argsStr += getTypeName(argument.type) + " " + argument.name;
                        break;
                    }
                }
                entryPointStr += getTypeName(returnType) + "_Output _" + _name + "(" + argsStr + ") {\n";

                //-------- Entry point call --------
                entryPointStr += "\t//Entry point call\n";
                std::string outputVarName = "_entryPointOutput";
                entryPointStr += "\t" + (returnType->getTypeID() == irb::TypeID::Void ? "" : getTypeName(returnType) + " " + outputVarName + " = ") + _name + "(";
                for (uint32_t i = 0; i < _arguments.size(); i++) {
                    if (i != 0)
                        entryPointStr += ", ";
                    entryPointStr += _arguments[i].name;
                }
                entryPointStr += ");\n";

                //-------- Output --------
                if (returnType->getTypeID() != irb::TypeID::Void) {
                    entryPointStr += "\n\t//Output\n\t" + getTypeName(returnType) + "_Output __output;\n\t__output.output = " + outputVarName + ";\n";
                    if (functionRole == irb::FunctionRole::Vertex) {
                        //TODO: support non-structure types as well
                        if (!returnType->isStructure()) {
                            logError("Entry point output must have a structure type");
                            return nullptr;
                        }
                        irb::Structure* structure = static_cast<irb::StructureType*>(returnType)->getStructure();
                        for (const auto& member : structure->members) {
                            if (member.attributes.isPosition) {
                                entryPointStr += "\t__output.position = " + outputVarName + "." + member.name + ";\n";
                                break;
                            }
                        }
                    }
                    entryPointStr += "\n\treturn __output;\n";
                }

                entryPointStr += "}\n\n";
            } else if (irb::target == irb::Target::GLSL) {
                switch (functionRole) {
                case irb::FunctionRole::Vertex:
                    entryPointStr += "layout (location = 0) out " + getTypeName(returnType) + "_Output {\n\t" + getTypeName(returnType) + " _output;\n} _output;\n\n";
                    break;
                case irb::FunctionRole::Fragment:
                    //TODO: do this error check for every backend?
                    if (!returnType->isStructure()) {
                        logError("Entry point argument declared with the 'input' attribute must have a structure type");
                        return nullptr;
                    }
                    for (const auto& member : static_cast<irb::StructureType*>(returnType)->getStructure()->members)
                        entryPointStr += "layout (location = " + std::to_string(member.attributes.colorIndex) + ") out " + getTypeName(member.type) + " " + member.name + ";\n\n";
                    break;
                default:
                    logError("cannot use the 'output' attribute for kernel function");
                    return nullptr;
                }

                //Entry point
                entryPointStr += "void main() {\n";

                //-------- Input --------
                entryPointStr += "\t//Input\n";
                for (uint32_t i = 0; i < _arguments.size(); i++) {
                    if (functionRole == irb::FunctionRole::Vertex && _arguments[i].attributes.isInput) {
                        //TODO: throw an error if not structure?
                        irb::StructureType* structureType = dynamic_cast<irb::StructureType*>(_arguments[i].type);
                        //HACK: just assemble the input structure
                        entryPointStr += "\t" + getTypeName(structureType) + " " + _arguments[i].name + ";\n";
                        for (const auto& member : structureType->getStructure()->members)
                            entryPointStr += "\t" + _arguments[i].name + "." + member.name + " = " + member.name + ";\n";
                    }
                }
                entryPointStr += "\n";

                //-------- Entry point call --------
                entryPointStr += "\t//Entry point call\n";
                std::string outputVarName = "_entryPointOutput";
                entryPointStr += "\t" + (returnType->getTypeID() == irb::TypeID::Void ? "" : getTypeName(returnType) + " " + outputVarName + " = ") + _name + "(";
                for (uint32_t i = 0; i < _arguments.size(); i++) {
                    if (i != 0)
                        entryPointStr += ", ";
                    entryPointStr += _arguments[i].name;
                }

                //-------- Output --------
                if (returnType->getTypeID() != irb::TypeID::Void) {
                    entryPointStr += ");\n\n\t//Output\n";

                    //TODO: support other types besides structure
                    if (!returnType->isStructure()) {
                        logError("Only structures can be returned from an entry point function");
                        return nullptr;
                    }
                    irb::StructureType* structType = static_cast<irb::StructureType*>(returnType);
                    irb::Structure* structure = structType->getStructure();

                    for (uint32_t i = 0; i < structure->members.size(); i++) {
                        const irb::StructureMember& member = structure->members[i];
                        std::string memberStr = outputVarName + "." + member.name;
                        entryPointStr += "\t";
                        if (member.attributes.isPosition) {
                            entryPointStr += "gl_Position = " + memberStr + ";\n\t";
                        }
                        switch (functionRole) {
                        case irb::FunctionRole::Vertex:
                            entryPointStr += "_output._output." + member.name + " = " + memberStr;
                            break;
                        case irb::FunctionRole::Fragment:
                            entryPointStr += member.name + " = " + memberStr;
                            break;
                        default:
                            logError("'kernel' functions cannot return a value");
                            break;
                        }
                        entryPointStr += ";\n";
                    }
                }
                
                entryPointStr += "}\n\n";
            }
        }
        codeStr += getTypeName(returnType) + " " + _name + "(" + argsStr + ")";
        if ((irb::target == irb::Target::GLSL || irb::target == irb::Target::HLSL) && functionRole != irb::FunctionRole::Normal)
            codeStr += ";\n\n" + entryPointStr + codeStr;
        if (!isDefined)
            codeStr += ";";
        
        return new irb::Value(context, getType(), codeStr);
    } else {
        /*if (isSTDFunction) {
            std::string regName = _name;
            regName[0] = toupper(regName[0]);
            regName = "import " + regName;
            value = new irb::Value(context, nullptr, regName);
        } else {*/
        if (previousDeclaration) {
            return value = previousDeclaration->getValue();
        } else {
            if (isSTDFunction) {
                value = builder->opStandardFunctionDeclaration(static_cast<irb::FunctionType*>(getType()), _name);
            } else {
                value = builder->opFunction(static_cast<irb::FunctionType*>(getType()), _name);
                //TODO: name the function properly
                builder->opName(value, _name + "(");
            }
        }

        return value;
    }
}

irb::Type* FunctionDefinitionAST::_initialize() {
    irb::Type* type = declaration->initialize();
    if (!type)
        return nullptr;

    //HACK: register the arguments as variables
    for (uint32_t i = 0; i < declaration->arguments().size(); i++) {
        auto& arg = declaration->arguments()[i];
        if (arg.name != "")
            variables[arg.name] = {new irb::PointerType(context, arg.type, irb::StorageClass::Function), nullptr, true};
    }
    
    if (!body->initialize())
        return nullptr;
    
    return type;
}

irb::Value* FunctionDefinitionAST::_codegen() {
    irb::Value* value = declaration->codegen();
    if (!value)
        return nullptr;
    
    if (TARGET_IS_IR(irb::target)) {
        irb::FunctionType* functionType = static_cast<irb::FunctionType*>(value->getType());
        builder->setActiveFunction(declaration->getValue());
        if (declaration->getFunctionRole() != irb::FunctionRole::Normal)
            builder->opEntryPoint(value, declaration->getFunctionRole(), declaration->name(), static_cast<irb::FunctionType*>(declaration->getType())->getReturnType(), declaration->arguments());

        context.pushRegisterName("entry");
        irb::Block* block = builder->opBlock(declaration->getValue());
        builder->setInsertBlock(block);
    }

    for (uint32_t i = 0; i < declaration->arguments().size(); i++) {
        auto& arg = declaration->arguments()[i];
        if (arg.name != "") {
            if (TARGET_IS_CODE(irb::target)) {
                irb::Value* value = new irb::Value(context, new irb::PointerType(context, arg.type, irb::StorageClass::Function), arg.name);
                variables[arg.name].value = value;
            } else {
                auto& attr = declaration->getArgumentAttributes(i);
                context.pushRegisterName(arg.name);
                irb::Type* type = arg.type;
                irb::Value* argValue = builder->opFunctionParameter(declaration->getValue(), type);
                variables[arg.name].value = argValue;
            }
        }
    }
    
    irb::Value* bodyV = body->codegen();
    if (!bodyV)
        return nullptr;
    
    if (TARGET_IS_CODE(irb::target)) {
        std::string bodyStr = bodyV->getRawName();
        std::string codeStr = value->getRawName() + " " + bodyStr;

        value = new irb::Value(context, nullptr, codeStr);
    } else {
        if (!builder->getInsertBlock()->hasReturned()) {
            if (static_cast<irb::FunctionType*>(declaration->getType())->getReturnType()->getTypeID() == irb::TypeID::Void)
                builder->opReturn();
            else
                builder->opUnreachable();
        }
        builder->opFunctionEnd(declaration->getValue());
    }

    return value;
}

irb::Type* CallExpressionAST::_initialize() {
    if (functionDeclarations.count(callee)) {
        const auto& declarations = functionDeclarations[callee];
        std::vector<irb::Type*> argTypes(arguments.size());
        for (uint32_t i = 0; i < arguments.size(); i++) {
            ExpressionAST* arg = arguments[i];
            argTypes[i] = arg->initialize(declarations.size() == 1 ? declarations[0]->arguments()[i].type : nullptr);
            if (!argTypes[i])
                return nullptr;
        }

        std::string identifier;
        //TODO: move this to a separate function?
        for (auto* argType : argTypes)
            identifier += (irb::target == irb::Target::AIR ? "." : "_") + argType->getTemplateName();

        //Find suitable function overload
        if (declarations.size() == 1) {
            declaration = declarations[0];

            if (declaration->arguments().size() != arguments.size()) {
                logError(("Expected " + std::to_string(declaration->arguments().size()) + " arguments, got " + std::to_string(arguments.size()) + " instead").c_str());
                return nullptr;
            }
            
            if (identifier != declaration->getIdentifier()) {
                for (uint32_t i = 0; i < arguments.size(); i++) {
                    if (!argTypes[i]->equals(declaration->arguments()[i].type)) {
                        logError(("Argument " + std::to_string(i + 1) + " of function '" + callee + "' has type '" + declaration->arguments()[i].type->getDebugName() + "', got '" + argTypes[i]->getDebugName() + "' instead").c_str());
                        return nullptr;
                    }
                }
            }
        } else {
            for (auto* decl : declarations) {
                if (identifier == decl->getIdentifier()) {
                    declaration = decl;
                    break;
                }
            }
            if (!declaration) {
                logError("no matching function overload found");
                return nullptr;
            }
        }
    } else {
        logError("Use of undeclared function '" + callee + "'");
        return nullptr;
    }

    return static_cast<irb::FunctionType*>(declaration->getType())->getReturnType();
}

irb::Value* CallExpressionAST::_codegen() {
    std::string argsStr;
    std::vector<irb::Value*> argVs(arguments.size());
    for (uint32_t i = 0; i < arguments.size(); i++) {
        ExpressionAST* arg = arguments[i];
        argVs[i] = arg->codegen();
        if (!argVs[i])
            return nullptr;
        if (i != 0)
            argsStr += ", ";
        argsStr += argVs[i]->getRawName();
    }

    if (irb::target == irb::Target::SPIRV && !declaration->getIsSTDFunction()) {
        for (uint32_t i = 0; i < arguments.size(); i++) {
            context.pushRegisterName("param");
            argVs[i] = builder->opVariable(new irb::PointerType(context, argVs[i]->getType(), irb::StorageClass::Function), argVs[i]);
        }
    }

    if (TARGET_IS_CODE(irb::target)) {
        std::string code;
        if (callee == "sample") {
            switch (irb::target) {
            case irb::Target::Metal:
                code = argVs[0]->getRawName() + ".sample(" + argVs[1]->getRawName() + ", " + argVs[2]->getRawName() + ")";
                break;
            case irb::Target::HLSL:
                code = argVs[0]->getRawName() + ".SampleLevel(" + argVs[1]->getRawName() + ", " + argVs[2]->getRawName() + ", 0.0f)";
                break;
            case irb::Target::GLSL:
                code = "texture(sampler2D(" + argVs[0]->getRawName() + ", " + argVs[1]->getRawName() + "), " + argVs[2]->getRawName() + ")"; //TODO: support other samplers + textures as well
                break;
            default:
                break;
            }
        } else {
            code = callee + "(" + argsStr + ")";
        }

        return new irb::Value(context, getType(), code);
    } else {
        if (callee == "sample")
            return builder->opSample(declaration->getValue(), argVs[0], argVs[1], argVs[2]);

        return builder->opFunctionCall(declaration->getValue(), argVs);
    }
}

irb::Type* ReturnExpressionAST::_initialize() {
    irb::Type* type;
    if (expression)
        type = expression->initialize(crntFunctionReturnType);
    else
        type = new irb::ScalarType(context, irb::TypeID::Void, 0);

    return type;
}

irb::Value* ReturnExpressionAST::_codegen() {
    irb::Value* returnV = nullptr;
    if (expression) {
        returnV = expression->codegen();
        if (!returnV)
            return nullptr;
    }

    if (TARGET_IS_CODE(irb::target)) {
        return new irb::Value(context, returnV->getType(), "return" + (returnV ? " " + returnV->getRawName() : ""));
    } else {
        builder->opReturn(returnV);

        return returnV;
    }
}

irb::Type* IfExpressionAST::_initialize() {
    for (uint32_t i = 0; i < ifThenBlocks.size(); i++) {
        if (!ifThenBlocks[i]->condition->initialize(new irb::ScalarType(context, irb::TypeID::Bool, 8, false)))
            return nullptr;
        if (!ifThenBlocks[i]->block->initialize())
            return nullptr;
    }

    if (elseBlock) {
        if (!elseBlock->initialize())
            return nullptr;
    }

    //TODO: return something else?
    return new irb::ScalarType(context, irb::TypeID::Void, 0);
}

irb::Value* IfExpressionAST::_codegen() {
    if (TARGET_IS_CODE(irb::target)) {
        std::string codeStr;
        for (uint32_t i = 0; i < ifThenBlocks.size(); i++) {
            if (i != 0)
                codeStr += " else ";
            codeStr += "if (";
            irb::Value* condV = ifThenBlocks[i]->condition->codegen();
            if (!condV)
                return nullptr;
            irb::Value* blockV = ifThenBlocks[i]->block->codegen();
            if (!blockV)
                return nullptr;
            codeStr += condV->getRawName() + ") " + blockV->getRawName();
        }

        if (elseBlock) {
            codeStr += " else ";
            irb::Value* blockV = elseBlock->codegen();
            if (!blockV)
                return nullptr;
            codeStr += blockV->getRawName();
        }

        return new irb::Value(context, nullptr, codeStr);
    } else {
        std::vector<irb::Block*> elseBs(ifThenBlocks.size()); //Serve as conditions except for the else block
        std::vector<irb::Block*> thenBs(ifThenBlocks.size());
        std::vector<irb::Block*> mergeBs(ifThenBlocks.size());
        for (uint32_t i = 0; i < ifThenBlocks.size(); i++) {
            if (i != 0) {
                context.pushRegisterName("cond");
                elseBs[i - 1] = builder->opBlock(builder->getActiveFunction());
            }
            context.pushRegisterName("then");
            thenBs[i] = builder->opBlock(builder->getActiveFunction());
            context.pushRegisterName(i == 0 ? "end" : "merge");
            mergeBs[i] = builder->opBlock(builder->getActiveFunction());
        }
        irb::Block* endB = mergeBs[0];
        if (elseBlock) {
            context.pushRegisterName("else");
            elseBs[elseBs.size() - 1] = builder->opBlock(builder->getActiveFunction());
        } else {
            elseBs[elseBs.size() - 1] = endB;
        }
        for (uint32_t i = 0; i < ifThenBlocks.size(); i++) {
            irb::Value* condV = ifThenBlocks[i]->condition->codegen();
            builder->opBlockMerge(mergeBs[i]);
            builder->opBranchCond(condV, thenBs[i], elseBs[i]);

            //Current body
            builder->setInsertBlock(thenBs[i]);
            irb::Value* blockV = ifThenBlocks[i]->block->codegen();
            builder->opBranch(mergeBs[i]);

            //Next condition or else block
            builder->setInsertBlock(elseBs[i]);
        }
        if (elseBlock) {
            irb::Value* blockV = elseBlock->codegen();
            builder->opBranch(mergeBs[mergeBs.size() - 1]);
        }
        for (uint32_t i = mergeBs.size() - 1; i > 0; i--) {
            builder->setInsertBlock(mergeBs[i]);
            builder->opBranch(mergeBs[i - 1]);
        }

        //End
        builder->setInsertBlock(endB);

        //TODO: return something else
        return endB;
    }
}

irb::Type* WhileExpressionAST::_initialize() {
    if (!condition->initialize(new irb::ScalarType(context, irb::TypeID::Bool, 8, false)))
        return nullptr;

    if (!block->initialize())
        return nullptr;
    
    //TODO: return something else?
    return new irb::ScalarType(context, irb::TypeID::Void, 0);
}

irb::Value* WhileExpressionAST::_codegen() {
    irb::Block* mergeB;
    irb::Block* condB;
    irb::Block* thenB;
    irb::Block* afterThenB;
    irb::Block* endB;
    //TODO: use the same code for both SPIRV and AIR
    if (TARGET_IS_IR(irb::target)) {
        if (irb::target == irb::Target::SPIRV) {
            context.pushRegisterName("loop_merge");
            mergeB = builder->opBlock(builder->getActiveFunction());
        }
        context.pushRegisterName("loop_cond");
        condB = builder->opBlock(builder->getActiveFunction());
        context.pushRegisterName("loop");
        thenB = builder->opBlock(builder->getActiveFunction());
        if (irb::target == irb::Target::SPIRV) {
            context.pushRegisterName("after_loop");
            afterThenB = builder->opBlock(builder->getActiveFunction());
        } else {
            mergeB = condB;
            afterThenB = condB;
        }
        context.pushRegisterName("end");
        endB = builder->opBlock(builder->getActiveFunction());

        builder->opBranch(isDoWhile ? thenB : mergeB);

        //Merge
        if (irb::target == irb::Target::SPIRV) {
            builder->setInsertBlock(mergeB);
            builder->opLoopMerge(endB, afterThenB);
            builder->opBranch(condB);
        }

        //Condition
        builder->setInsertBlock(condB);
    }
    
    irb::Value* condV = condition->codegen();
    if (!condV)
        return nullptr;

    if (TARGET_IS_CODE(irb::target)) {
        irb::Value* blockV = block->codegen();
        if (!blockV)
            return nullptr;

        std::string codeStr;
        if (isDoWhile)
            codeStr += "do (";
        else
            codeStr += "while (";
        codeStr += condV->getRawName() + ")";
        codeStr += blockV->getRawName();

        return new irb::Value(context, nullptr, codeStr);
    } else {
        builder->opBranchCond(condV, thenB, endB);

        //Then
        builder->setInsertBlock(thenB);
        irb::Value* blockV = block->codegen();
        if (!blockV)
            return nullptr;
        builder->opBranch(afterThenB);

        //After then
        if (irb::target == irb::Target::SPIRV) {
            builder->setInsertBlock(afterThenB);
            builder->opBranch(mergeB);
        }

        //End
        builder->setInsertBlock(endB);

        return endB;
    }
}

irb::Type* VariableDeclarationExpressionAST::_initialize() {
    irb::Type* finalType = nullptr;
    for (uint32_t i = 0; i < variableNames.size(); i++) {
        const std::string& varName = variableNames[i].name;
        irb::Type* type = variableNames[i].type;
        ExpressionAST* initExpression = variableNames[i].expression;

        irb::Type* initType = nullptr;
        if (initExpression) {
            if (isGlobal && !initExpression->isConstant()) {
                logError("global variable can only be initialized using a constant expression");
                return nullptr;
            }
            initType = initExpression->initialize(type);
            if (!initType)
                return nullptr;
            
            if (type && !initType->equals(type)) {
                logError("cannot initialize variable of type '" + type->getDebugName() + "' with value of type '" + initType->getDebugName() + "'");
                return nullptr;
            }
        } else if (!type) {
            logError("cannot deduce type without initial value");
            return nullptr;
        }
        if (!type)
            type = initType;
        
        finalType = new irb::PointerType(context, type, irb::StorageClass::Function);
        variables[varName] = {finalType, nullptr, !isGlobal};
    }

    return finalType;
}

irb::Value* VariableDeclarationExpressionAST::_codegen() {
    irb::Value* value = nullptr;
    for (uint32_t i = 0; i < variableNames.size(); i++) {
        const std::string& varName = variableNames[i].name;
        irb::Type* type = variableNames[i].type;
        ExpressionAST* initExpression = variableNames[i].expression;

        irb::Value* initV = nullptr;
        if (initExpression) {
            //TODO: uncomment?
            //context.pushRegisterName(varName + "_init");
            initV = initExpression->codegen();
            if (!initV)
                return nullptr;
        }
        if (!type)
            type = initV->getType();
        
        irb::PointerType* varType = new irb::PointerType(context, type, irb::StorageClass::Function);
        if (TARGET_IS_IR(irb::target)) {
            context.pushRegisterName(varName);
            if (isConstant && isGlobal)
                value = initV;
            else
                value = builder->opVariable(varType, (initExpression && initExpression->isConstant() ? initV : nullptr));
            if (initExpression && !initExpression->isConstant())
                builder->opStore(value, initV);
            variables[varName].value = value;
        } else {
            std::string codeStr;
            if (isConstant) {
                if (irb::target == irb::Target::Metal && isGlobal)
                    codeStr += "constant ";
                else
                    codeStr += "const ";
            }

            codeStr += getTypeNameBegin(type) + " " + varName + getTypeNameEnd(type);
            if (initExpression)
                codeStr += " = " + initV->getRawName();
            if (isGlobal)
                codeStr += ";";

            value = new irb::Value(context, varType, codeStr);
            variables[varName].value = new irb::Value(context, varType, varName);
        }
    }

    return value;
}

irb::Type* SubscriptExpressionAST::_initialize() {
    ptr->setLoadOnCodegen(false);
    irb::Type* ptrType = ptr->initialize();
    irb::Type* indexType = index->initialize();
    if (!ptrType || !indexType)
        return nullptr;
    if (!indexType->isOperatorFriendly()) {
        logError("only operator friendly types can be used for indexing");
        return nullptr;
    }
    irb::PointerType* type = dynamic_cast<irb::PointerType*>(ptrType);
    if (!type) {
        logError("cannot index into a non-pointer value");
        return nullptr;
    }

    return new irb::PointerType(context, type->getElementType()->getBaseType(), type->getStorageClass());
}

irb::Value* SubscriptExpressionAST::_codegen() {
    irb::Value* ptrV = ptr->codegen();
    irb::Value* indexV = index->codegen();
    if (!ptrV || !indexV)
        return nullptr;

    if (TARGET_IS_CODE(irb::target)) {
        return new irb::Value(context, getType(), ptrV->getRawName() + "[" + indexV->getRawName() + "]");
    } else {
        irb::Value* value = builder->opGetElementPtr(static_cast<irb::PointerType*>(getType()), ptrV, {indexV});
        if (loadOnCodegen)
            value = builder->opLoad(value);

        return value;
    }
}

irb::Type* MemberAccessExpressionAST::_initialize() {
    expression->setLoadOnCodegen(false);
    irb::Type* exprType = expression->initialize();
    if (!exprType)
        return nullptr;
    if (exprShouldBeLoadedBeforeAccessingMember) {
        if (irb::target == irb::Target::AIR || irb::target == irb::Target::Metal)
            exprType = exprType->getElementType();
    }
    if (!exprType->isPointer()) {
        logError("cannot access member of non-pointer value");
        return nullptr;
    }
    irb::Type* elementExprType = exprType->getElementType();
    if (elementExprType->isStructure()) {
        irb::Structure* structure = static_cast<irb::StructureType*>(elementExprType)->getStructure();
        
        for (; memberIndex < structure->members.size(); memberIndex++) {
            if (memberName == structure->members[memberIndex].name) {
                const auto& structMember = structure->members[memberIndex];
                if (loadOnCodegen)
                    return structMember.type;
                else
                    return new irb::PointerType(context, structMember.type, irb::StorageClass::Function);
            }
        }

        logError("type '" + elementExprType->getDebugName() + "' has no member named '" + memberName + "'");
        return nullptr;
    } else if (elementExprType->isVector()) {
        irb::Type* type;
        if (memberName.size() == 1)
            type = elementExprType->getBaseType();
        else
            type = new irb::VectorType(context, elementExprType->getBaseType(), memberName.size());

        //TODO: check if the components are correct

        if (loadOnCodegen)
            return type;
        else
            return new irb::PointerType(context, type, irb::StorageClass::Function);
    } else {
        logError("the '.' operator only operates on structures and vectors");
        return nullptr;
    }
}

//TODO: support chained unloaded vector swizzle
irb::Value* MemberAccessExpressionAST::_codegen() {
    irb::Value* exprV = expression->codegen();
    if (!exprV)
        return nullptr;
    if (exprShouldBeLoadedBeforeAccessingMember) {
        if (irb::target == irb::Target::AIR)
            exprV = builder->opLoad(exprV);
        else if (irb::target == irb::Target::Metal)
            exprV = new irb::Value(context, exprV->getType()->getElementType(), "(*" + exprV->getRawName() + ")");
    }
    irb::PointerType* exprType = static_cast<irb::PointerType*>(exprV->getType());
    irb::Type* elementExprType = exprType->getElementType();
    if (elementExprType->isStructure()) {
        if (TARGET_IS_CODE(irb::target)) {
            return new irb::Value(context, getType(), exprV->getRawName() + "." + memberName);
        } else {
            irb::PointerType* type = (loadOnCodegen ? new irb::PointerType(context, getType(), irb::StorageClass::Function) : static_cast<irb::PointerType*>(getType()));
            irb::Value* indexV = builder->opConstant(new irb::ConstantInt(context, memberIndex, 32, true));
            irb::Value* elementV = builder->opGetElementPtr(type, exprV, {indexV});
            if (loadOnCodegen)
                elementV = builder->opLoad(elementV);

            return elementV;
        }
    } else if (elementExprType->isVector()) {
        irb::Type* type;
        if (memberName.size() == 1)
            type = elementExprType->getBaseType();
        else
            type = new irb::VectorType(context, elementExprType->getBaseType(), memberName.size());
        if (TARGET_IS_CODE(irb::target)) {
            irb::Type* trueType = type;
            //HACK: get the pointer type
            if (!loadOnCodegen)
                trueType = new irb::PointerType(context, type, irb::StorageClass::Function);
            return new irb::Value(context, trueType, exprV->getRawName() + "." + memberName);
        } else {
            irb::Value* loadedVector;
            std::vector<irb::Value*> components;
            std::vector<uint8_t> indices;
            if (loadOnCodegen) {
                loadedVector = builder->opLoad(exprV);
                components.reserve(memberName.size());
            } else {
                indices.reserve(memberName.size());
            }
            for (uint8_t i = 0; i < memberName.size(); i++) {
                int8_t index;
                switch (memberName[i]) {
                case 'x':
                case 'r':
                    index = 0;
                    break;
                case 'y':
                case 'g':
                    index = 1;
                    break;
                case 'z':
                case 'b':
                    index = 2;
                    break;
                case 'w':
                case 'a':
                    index = 3;
                    break;
                default:
                    index = -1;
                    break;
                }
                if (loadOnCodegen)
                    components.push_back(builder->opVectorExtract(loadedVector, new irb::ConstantInt(context, index, 32, false)));
                else
                    indices.push_back(index);
            }
            
            if (loadOnCodegen) {
                if (components.size() == 1)
                    return components[0];
                return builder->opConstruct(static_cast<irb::VectorType*>(type), components);
            } else {
                return new UnloadedSwizzledVectorValue(context, exprV, indices);
            }
        }
    } else {
        logError("the '.' operator only operates on structures and vectors");
        return nullptr;
    }
}

irb::Type* StructureDefinitionAST::_initialize() {
    if (context.structures[name]) {
        logError("redefinition of structure '" + name + "'");
        return nullptr;
    }

    irb::Structure* structure = new irb::Structure;
    structure->members = members;
    context.structures[name] = structure;

    return new irb::StructureType(context, name);
}

irb::Value* StructureDefinitionAST::_codegen() {
    std::string codeStr = "struct " + name + " {\n";
    for (auto& member : members) {
        std::string attributesEnd;
        if (irb::target == irb::Target::Metal) {
            if (member.attributes.isPosition)
                attributesEnd += " [[position]]";
            if (member.attributes.locationIndex != -1)
                attributesEnd += " [[attribute(" + std::to_string(member.attributes.locationIndex) + ")]]";
            if (member.attributes.colorIndex != -1)
                attributesEnd += " [[color(" + std::to_string(member.attributes.colorIndex) + ")]]";
        } else if (irb::target == irb::Target::HLSL) {
            //TODO: add commas between attributes
            //TODO: uncomment?
            //if (member.attributes.isPosition)
            //    attributesEnd += " : SV_Position";
            if (member.attributes.locationIndex != -1)
                attributesEnd += " : TEXCOORD" + std::to_string(member.attributes.locationIndex); //TODO: don't always use texcoord?
            if (member.attributes.colorIndex != -1)
                attributesEnd += " : SV_Target" + std::to_string(member.attributes.colorIndex); //TODO: check if this is correct
        }
        codeStr += "\t" + getTypeNameBegin(member.type) + " " + member.name + getTypeNameEnd(member.type) + attributesEnd + ";\n";
    }
    codeStr += "};";

    if (TARGET_IS_IR(irb::target)) {
        context.pushRegisterName(name);

        return builder->opStructureDefinition(static_cast<irb::StructureType*>(getType()));
    } else {
        return new irb::Value(context, getType(), codeStr);
    }
}

irb::Type* EnumDefinitionAST::_initialize() {
    if (enumerations[name]) {
        logError("redefinition of enum '" + name + "'");
        return nullptr;
    }

    Enumeration* enumeration = new Enumeration(values);
    enumerations[name] = enumeration;

    return enumeration->type;
}

irb::Value* EnumDefinitionAST::_codegen() {
    std::string codeStr;
    if (irb::target == irb::Target::Metal || irb::target == irb::Target::HLSL) {
        codeStr = "enum " + name + " {\n";
        for (auto& value : values)
            codeStr += "\t" + value.name + " = " + std::to_string(value.value) + ",\n";
        codeStr += "};";
    } else {
        codeStr = "//Enum '" + name + "'";
    }

    return new irb::Value(context, getType(), codeStr);
}

irb::Type* EnumValueExpressionAST::_initialize() {
    return enumeration->type;
}

irb::Value* EnumValueExpressionAST::_codegen() {
    if (TARGET_IS_IR(irb::target)) {
        return builder->opConstant(new irb::ConstantValue(context, enumeration->type, std::to_string(value.value)));
    } else {
        if (irb::target == irb::Target::Metal || irb::target == irb::Target::HLSL)
            return new irb::Value(context, enumeration->type, value.name);
        else
            return new irb::Value(context, enumeration->type, std::to_string(value.value));
    }
}

irb::Type* InitializerListExpressionAST::_initialize() {
    std::vector<irb::Type*> components;
    components.reserve(expressions.size());
    for (auto* expression : expressions) {
        irb::Type* component = expression->initialize();
        if (!component)
            return nullptr;
        components.push_back(component);
    }
    
    //"Unpack" the vectors
    if (listType->isVector()) {
        for (uint32_t i = 0; i < components.size(); i++) {
            irb::Type* component = components[i];
            if (auto vectorType = dynamic_cast<irb::VectorType*>(component)) {
                components.erase(components.begin() + i);
                for (uint8_t j = 0; j < vectorType->getComponentCount(); j++)
                    components.insert(components.begin() + i + j, vectorType->getBaseType());
            }
        }
    }

    if (listType->isScalar()) {
        if (components.size() != 1) {
            logError("scalar initializer list must have exactly one value");
            return nullptr;
        }
    } else if (listType->isArray()) {
        uint32_t size = static_cast<irb::ArrayType*>(listType)->getSize();
        if (components.size() > size) {
            logError("array initializer cannot be larger than the array itself (" + std::to_string(components.size()) + " > " + std::to_string(size) + ")");
            return nullptr;
        }
    } else if (listType->isVector()) {
        uint32_t componentCount = static_cast<irb::VectorType*>(listType)->getComponentCount();
        if (components.size() > componentCount) {
            logError("vector initializer cannot be larger than the vector itself (" + std::to_string(components.size()) + " > " + std::to_string(componentCount) + ")");
            return nullptr;
        }
        if (components.size() != componentCount && components.size() != 1) {
            logError("not enough components in initializer to construct a vector (got " + std::to_string(components.size()) + ", expected either " + std::to_string(componentCount) + " or 1)");
            return nullptr;
        }
    } else if (listType->isMatrix()) {
        uint32_t columnCount = static_cast<irb::MatrixType*>(listType)->getColumnCount();
        if (components.size() > columnCount) {
            logError("matrix initializer cannot be larger than the matrix itself (" + std::to_string(components.size()) + " > " + std::to_string(columnCount) + ")");
            return nullptr;
        }
        if (components.size() != columnCount && components.size() != 1) {
            logError("not enough components in initializer to construct a matrix (got " + std::to_string(components.size()) + ", expected either " + std::to_string(columnCount) + " or 1)");
            return nullptr;
        }
    } else {
        logError("cannot use initializer list to create a type '" + listType->getDebugName() + "'");
        return nullptr;
    }

    return listType;
}

irb::Value* InitializerListExpressionAST::_codegen() {
    std::vector<irb::Value*> components;
    components.reserve(expressions.size());
    for (auto* expression : expressions) {
        irb::Value* component = expression->codegen();
        if (!component)
            return nullptr;
        if (TARGET_IS_IR(irb::target) && component->getType()->isScalar())
            component = builder->opCast(component, (getType()->isScalar() ? getType() : getType()->getBaseType()));
        components.push_back(component);
    }

    //HACK: for code backends
    std::vector<irb::Value*> originalComponents = components;
    
    //"Unpack" the vectors
    if (getType()->isVector()) {
        for (uint32_t i = 0; i < components.size(); i++) {
            irb::Value* component = components[i];
            if (auto vectorType = dynamic_cast<irb::VectorType*>(component->getType())) {
                components.erase(components.begin() + i);
                for (uint8_t j = 0; j < vectorType->getComponentCount(); j++) {
                    irb::Value* vectorComponent;
                    if (TARGET_IS_IR(irb::target))
                        vectorComponent = builder->opCast(builder->opVectorExtract(component, new irb::ConstantInt(context, j, 32, true)), getType()->getBaseType());
                    else
                        vectorComponent = new irb::Value(context, vectorType->getBaseType(), component->getRawName() + "[" + std::to_string(j) + "]");
                    components.insert(components.begin() + i + j, vectorComponent);
                }
            }
        }
    }

    if (TARGET_IS_IR(irb::target)) {
        if (getType()->isScalar())
            return builder->opCast(components[0], getType());
        if (getType()->isArray()) {
            //TODO: implement this
            logError("array initializer lists are not supported for IR backends yet");
            return nullptr;
        }
        if (getType()->isVector()) {
            irb::VectorType* vectorType = static_cast<irb::VectorType*>(getType());
            //Fill the list in case it is just a one value initializer
            if (components.size() == 1) {
                components.reserve(vectorType->getComponentCount());
                for (uint8_t i = 1; i < vectorType->getComponentCount(); i++)
                    components.push_back(components[0]);
            }
            context.pushRegisterName("const_vector");

            return builder->opConstruct(vectorType, components);
        }
        if (getType()->isMatrix()) {
            irb::MatrixType* matrixType = static_cast<irb::MatrixType*>(getType());
            //Fill the list in case it is just a one value initializer
            if (components.size() == 1) {
                components.reserve(matrixType->getColumnCount());
                irb::Value* component;
                if (components[0]->getType()->isVector()) {
                    component = components[0];
                } else if (components[0]->getType()->isScalar()) {
                    component = builder->opConstruct(matrixType->getComponentType(), std::vector(matrixType->getComponentType()->getComponentCount(), components[0]));
                } else {
                    logError("cannot initialize matrix with a value of type '" + components[0]->getType()->getDebugName() + "'");
                    return nullptr;
                }
                for (uint8_t i = 1; i < matrixType->getColumnCount(); i++)
                    components.push_back(component);
            }

            return builder->opConstruct(matrixType, components);
        }

        return nullptr;
    } else {
        std::string codeStr = getTypeName(getType()) + "(";
        for (uint32_t i = 0; i < originalComponents.size(); i++) {
            if (i != 0)
                codeStr += ", ";
            codeStr += originalComponents[i]->getRawName();
        }

        return new irb::Value(context, getType(), codeStr + ")");
    }
}

} //namespace lvslang
