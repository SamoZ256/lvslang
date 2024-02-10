#include "code_writer.hpp"

namespace lvslang {

CodeValue* CodeWriter::codegenExpression(const ExpressionAST* expression) {
    uint32_t oldDebugLine = source.crntDebugLine;
    uint32_t oldDebugChar = source.crntDebugChar;
    expression->setDebugInfo();
    
    CodeValue* value;
    if (auto* e = dynamic_cast<const NumberExpressionAST*>(expression)) {
        value = codegenNumberExpression(e);
    } else if (auto* e = dynamic_cast<const VariableExpressionAST*>(expression)) {
        value = codegenVariableExpression(e);
    } else if (auto* e = dynamic_cast<const BinaryExpressionAST*>(expression)) {
        value = codegenBinaryExpression(e);
    } else if (auto* e = dynamic_cast<const BlockExpressionAST*>(expression)) {
        value = codegenBlockExpression(e);
    } else if (auto* e = dynamic_cast<const FunctionPrototypeAST*>(expression)) {
        value = codegenFunctionPrototype(e);
    } else if (auto* e = dynamic_cast<const FunctionDefinitionAST*>(expression)) {
        value = codegenFunctionDefinition(e);
    } else if (auto* e = dynamic_cast<const CallExpressionAST*>(expression)) {
        value = codegenFunctionCall(e);
    } else if (auto* e = dynamic_cast<const ReturnExpressionAST*>(expression)) {
        value = codegenReturnExpression(e);
    } else if (auto* e = dynamic_cast<const IfExpressionAST*>(expression)) {
        value = codegenIfExpression(e);
    } else if (auto* e = dynamic_cast<const WhileExpressionAST*>(expression)) {
        value = codegenWhileExpression(e);
    } else if (auto* e = dynamic_cast<const VariableDeclarationExpressionAST*>(expression)) {
        value = codegenVariableDeclaration(e);
    } else if (auto* e = dynamic_cast<const SubscriptExpressionAST*>(expression)) {
        value = codegenSubscriptExpression(e);
    } else if (auto* e = dynamic_cast<const MemberAccessExpressionAST*>(expression)) {
        value = codegenMemberAccessExpression(e);
    } else if (auto* e = dynamic_cast<const StructureDefinitionAST*>(expression)) {
        value = codegenStructureDefinition(e);
    } else if (auto* e = dynamic_cast<const EnumDefinitionAST*>(expression)) {
        value = codegenEnumDefinition(e);
    } else if (auto* e = dynamic_cast<const EnumValueExpressionAST*>(expression)) {
        value = codegenEnumValueExpression(e);
    } else if (auto* e = dynamic_cast<const InitializerListExpressionAST*>(expression)) {
        value = codegenInitializerListExpression(e);
    } else {
        LVSLANG_ERROR("unknown expression type");
        return nullptr;
    }
    if (!value)
        return nullptr;

    source.crntDebugLine = oldDebugLine;
    source.crntDebugChar = oldDebugChar;
    
    if (expression->getRequiredType() && !expression->getType()->equals(expression->getRequiredType()))
        return new CodeValue{getTypeName(expression->getRequiredType()) + "(" + value->code + ")"};
    
    return value;
}

CodeValue* CodeWriter::codegenNumberExpression(const NumberExpressionAST* expression) {
    std::string code;
    switch (expression->getType()->getTypeID()) {
    case irb::TypeID::Bool:
        code = (expression->valueU() ? "true" : "false");
        break;
    case irb::TypeID::Integer:
        if (expression->getType()->getIsSigned())
            code = std::to_string(expression->valueL());
        else
            code = std::to_string(expression->valueU());
        break;
    case irb::TypeID::Float:
        code = std::to_string(expression->valueD());
        break;
    default:
        return nullptr;
    }

    return new CodeValue{code};
}

CodeValue* CodeWriter::codegenVariableExpression(const VariableExpressionAST* expression) {
    return new CodeValue{expression->getVariable()->value->getRawName()};
}

CodeValue* CodeWriter::codegenBinaryExpression(const BinaryExpressionAST* expression) {
    CodeValue* l = codegenExpression(expression->getLHS());
    if (!l)
        return nullptr;
    CodeValue* r = codegenExpression(expression->getRHS());
    if (!r)
        return nullptr;

    if (expression->getOp() == "=")
        return new CodeValue{l->code + " = " + r->code};

    return new CodeValue{"(" + l->code + " " + expression->getOp() + " " + r->code + ")"};
}

CodeValue* CodeWriter::codegenBlockExpression(const BlockExpressionAST* expression) {
    std::string codeStr = "{\n";

    currentIndentation += 1;

    for (auto expr : expression->getExpressions()) {
        CodeValue* value = codegenExpression(expr);
        if (!value)
            return nullptr;
        for (uint16_t i = 0; i < currentIndentation; i++)
            codeStr += "\t";
        codeStr += value->code + ";\n";
    }

    currentIndentation -= 1;

    for (uint16_t i = 0; i < currentIndentation; i++)
        codeStr += "\t";
    codeStr += "}";
    
    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenFunctionPrototype(const FunctionPrototypeAST* expression) {
    if (expression->getIsSTDFunction())
        return new CodeValue{""};
        
    std::string codeStr;
    std::string argsStr;
    std::string entryPointStr;
    for (uint32_t i = 0; i < expression->arguments().size(); i++) {
        const irb::Argument& arg = expression->arguments()[i];
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
            if (expression->getFunctionRole() != irb::FunctionRole::Normal) {
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
            if (expression->getFunctionRole() != irb::FunctionRole::Normal) {
                std::string typeName;
                if (attr.isInput) {
                    switch (expression->getFunctionRole()) {
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

    if (expression->getFunctionRole() != irb::FunctionRole::Normal) {
        if (irb::target == irb::Target::Metal) {
            switch (expression->getFunctionRole()) {
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
            if (expression->getReturnType()->getTypeID() != irb::TypeID::Void) {
                entryPointStr += "struct " + getTypeName(expression->getReturnType()) + "_Output {\n\t" + getTypeName(expression->getReturnType()) + " output : TEXCOORD0;\n";
                if (expression->getFunctionRole() == irb::FunctionRole::Vertex)
                    entryPointStr += "\tfloat4 position : SV_Position;\n";
                entryPointStr += "};\n\n";
            }

            //Entry point
            std::string argsStr;
            for (const auto& argument : expression->arguments()) {
                if (argument.attributes.isInput) {
                    argsStr += getTypeName(argument.type) + " " + argument.name;
                    break;
                }
            }
            entryPointStr += getTypeName(expression->getReturnType()) + "_Output _" + expression->name() + "(" + argsStr + ") {\n";

            //-------- Entry point call --------
            entryPointStr += "\t//Entry point call\n";
            std::string outputVarName = "_entryPointOutput";
            entryPointStr += "\t" + (expression->getReturnType()->getTypeID() == irb::TypeID::Void ? "" : getTypeName(expression->getReturnType()) + " " + outputVarName + " = ") + expression->name() + "(";
            for (uint32_t i = 0; i < expression->arguments().size(); i++) {
                if (i != 0)
                    entryPointStr += ", ";
                entryPointStr += expression->arguments()[i].name;
            }
            entryPointStr += ");\n";

            //-------- Output --------
            if (expression->getReturnType()->getTypeID() != irb::TypeID::Void) {
                entryPointStr += "\n\t//Output\n\t" + getTypeName(expression->getReturnType()) + "_Output __output;\n\t__output.output = " + outputVarName + ";\n";
                if (expression->getFunctionRole() == irb::FunctionRole::Vertex) {
                    //TODO: support non-structure types as well
                    if (!expression->getReturnType()->isStructure()) {
                        logError("Entry point output must have a structure type");
                        return nullptr;
                    }
                    irb::Structure* structure = static_cast<irb::StructureType*>(expression->getReturnType())->getStructure();
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
            switch (expression->getFunctionRole()) {
            case irb::FunctionRole::Vertex:
                entryPointStr += "layout (location = 0) out " + getTypeName(expression->getReturnType()) + "_Output {\n\t" + getTypeName(expression->getReturnType()) + " _output;\n} _output;\n\n";
                break;
            case irb::FunctionRole::Fragment:
                //TODO: do this error check for every backend?
                if (!expression->getReturnType()->isStructure()) {
                    logError("Entry point argument declared with the 'input' attribute must have a structure type");
                    return nullptr;
                }
                for (const auto& member : static_cast<irb::StructureType*>(expression->getReturnType())->getStructure()->members)
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
            for (uint32_t i = 0; i < expression->arguments().size(); i++) {
                if (expression->getFunctionRole() == irb::FunctionRole::Vertex && expression->arguments()[i].attributes.isInput) {
                    //TODO: throw an error if not structure?
                    irb::StructureType* structureType = dynamic_cast<irb::StructureType*>(expression->arguments()[i].type);
                    //HACK: just assemble the input structure
                    entryPointStr += "\t" + getTypeName(structureType) + " " + expression->arguments()[i].name + ";\n";
                    for (const auto& member : structureType->getStructure()->members)
                        entryPointStr += "\t" + expression->arguments()[i].name + "." + member.name + " = " + member.name + ";\n";
                }
            }
            entryPointStr += "\n";

            //-------- Entry point call --------
            entryPointStr += "\t//Entry point call\n";
            std::string outputVarName = "_entryPointOutput";
            entryPointStr += "\t" + (expression->getReturnType()->getTypeID() == irb::TypeID::Void ? "" : getTypeName(expression->getReturnType()) + " " + outputVarName + " = ") + expression->name() + "(";
            for (uint32_t i = 0; i < expression->arguments().size(); i++) {
                if (i != 0)
                    entryPointStr += ", ";
                entryPointStr += expression->arguments()[i].name;
            }

            //-------- Output --------
            if (expression->getReturnType()->getTypeID() != irb::TypeID::Void) {
                entryPointStr += ");\n\n\t//Output\n";

                //TODO: support other types besides structure
                if (!expression->getReturnType()->isStructure()) {
                    logError("Only structures can be returned from an entry point function");
                    return nullptr;
                }
                irb::StructureType* structType = static_cast<irb::StructureType*>(expression->getReturnType());
                irb::Structure* structure = structType->getStructure();

                for (uint32_t i = 0; i < structure->members.size(); i++) {
                    const irb::StructureMember& member = structure->members[i];
                    std::string memberStr = outputVarName + "." + member.name;
                    entryPointStr += "\t";
                    if (member.attributes.isPosition) {
                        entryPointStr += "gl_Position = " + memberStr + ";\n\t";
                    }
                    switch (expression->getFunctionRole()) {
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
    codeStr += getTypeName(expression->getReturnType()) + " " + expression->name() + "(" + argsStr + ")";
    if ((irb::target == irb::Target::GLSL || irb::target == irb::Target::HLSL) && expression->getFunctionRole() != irb::FunctionRole::Normal)
        codeStr += ";\n\n" + entryPointStr + codeStr;
    if (!expression->getIsDefined())
        codeStr += ";";
    
    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenFunctionDefinition(const FunctionDefinitionAST* expression) {
    CodeValue* value = codegenExpression(expression->getPrototype());
    if (!value)
        return nullptr;

    for (uint32_t i = 0; i < expression->getPrototype()->arguments().size(); i++) {
        auto& arg = expression->getPrototype()->arguments()[i];
        if (arg.name != "")
            variables[arg.name].value = new irb::Value(context, new irb::PointerType(context, arg.type, irb::StorageClass::Function), arg.name);
    }
    
    CodeValue* bodyV = codegenExpression(expression->getBody());
    if (!bodyV)
        return nullptr;
    
    std::string bodyStr = bodyV->code;
    std::string codeStr = value->code + " " + bodyStr;

    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenFunctionCall(const CallExpressionAST* expression) {
    std::string argsStr;
    std::vector<CodeValue*> argVs(expression->getArguments().size());
    for (uint32_t i = 0; i < expression->getArguments().size(); i++) {
        ExpressionAST* arg = expression->getArguments()[i];
        argVs[i] = codegenExpression(arg);
        if (!argVs[i])
            return nullptr;
        if (i != 0)
            argsStr += ", ";
        argsStr += argVs[i]->code;
    }

    std::string code;
    if (expression->getCallee() == "sample") {
        switch (irb::target) {
        case irb::Target::Metal:
            code = argVs[0]->code + ".sample(" + argVs[1]->code + ", " + argVs[2]->code + ")";
            break;
        case irb::Target::HLSL:
            code = argVs[0]->code + ".SampleLevel(" + argVs[1]->code + ", " + argVs[2]->code + ", 0.0f)";
            break;
        case irb::Target::GLSL:
            code = "texture(sampler2D(" + argVs[0]->code + ", " + argVs[1]->code + "), " + argVs[2]->code + ")"; //TODO: support other samplers + textures as well
            break;
        default:
            break;
        }
    } else {
        code = expression->getCallee() + "(" + argsStr + ")";
    }

    return new CodeValue{code};
}

CodeValue* CodeWriter::codegenReturnExpression(const ReturnExpressionAST* expression) {
    CodeValue* returnV = nullptr;
    if (expression) {
        returnV = codegenExpression(expression->getExpression());
        if (!returnV)
            return nullptr;
    }

    return new CodeValue{"return" + (returnV ? " " + returnV->code : "")};
}

CodeValue* CodeWriter::codegenIfExpression(const IfExpressionAST* expression) {
    std::string codeStr;
    for (uint32_t i = 0; i < expression->getIfThenBlocks().size(); i++) {
        if (i != 0)
            codeStr += " else ";
        codeStr += "if (";
        CodeValue* condV = codegenExpression(expression->getIfThenBlocks()[i]->condition);
        if (!condV)
            return nullptr;
        CodeValue* blockV = codegenExpression(expression->getIfThenBlocks()[i]->block);
        if (!blockV)
            return nullptr;
        codeStr += condV->code + ") " + blockV->code;
    }

    if (expression->getElseBlock()) {
        codeStr += " else ";
        CodeValue* blockV = codegenExpression(expression->getElseBlock());
        if (!blockV)
            return nullptr;
        codeStr += blockV->code;
    }

    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenWhileExpression(const WhileExpressionAST* expression) {
    CodeValue* condV = codegenExpression(expression->getCondition());
    if (!condV)
        return nullptr;

    CodeValue* blockV = codegenExpression(expression->getBlock());
    if (!blockV)
        return nullptr;

    std::string codeStr;
    if (expression->getIsDoWhile())
        codeStr += "do (";
    else
        codeStr += "while (";
    codeStr += condV->code + ")";
    codeStr += blockV->code;

    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenVariableDeclaration(const VariableDeclarationExpressionAST* expression) {
    std::string codeStr;
    for (uint32_t i = 0; i < expression->getVariableDeclarations().size(); i++) {
        const std::string& varName = expression->getVariableDeclarations()[i].name;
        irb::Type* type = expression->getVariableDeclarations()[i].type;
        ExpressionAST* initExpression = expression->getVariableDeclarations()[i].expression;

        CodeValue* initV = nullptr;
        if (initExpression) {
            initV = codegenExpression(initExpression);
            if (!initV)
                return nullptr;
        }
        if (!type)
            type = initExpression->getType();
        
        irb::PointerType* varType = new irb::PointerType(context, type, irb::StorageClass::Function);
        if (expression->getIsConstant()) {
            if (irb::target == irb::Target::Metal && expression->getIsGlobal())
                codeStr += "constant ";
            else
                codeStr += "const ";
        }

        codeStr += getTypeNameBegin(type) + " " + varName + getTypeNameEnd(type);
        if (initExpression)
            codeStr += " = " + initV->code;
        if (expression->getIsGlobal())
            codeStr += ";";

        variables[varName].value = new irb::Value(context, varType, varName);
    }

    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenSubscriptExpression(const SubscriptExpressionAST* expression) {
    CodeValue* ptrV = codegenExpression(expression->getPtr());
    CodeValue* indexV = codegenExpression(expression->getIndex());
    if (!ptrV || !indexV)
        return nullptr;

    return new CodeValue{ptrV->code + "[" + indexV->code + "]"};
}

CodeValue* CodeWriter::codegenMemberAccessExpression(const MemberAccessExpressionAST* expression) {
    CodeValue* exprV = codegenExpression(expression->getExpression());
    if (!exprV)
        return nullptr;
    irb::PointerType* exprType = static_cast<irb::PointerType*>(expression->getExpression()->getType());
    irb::Type* elementExprType = exprType->getElementType();
    if (target == irb::Target::Metal && expression->getExprShouldBeLoadedBeforeAccessingMember()) {
        exprV = new CodeValue{"(*" + exprV->code + ")"};
        elementExprType = elementExprType->getElementType();
    }
    if (elementExprType->isStructure()) {
        return new CodeValue{exprV->code + "." + expression->getMemberName()};
    } else if (elementExprType->isVector()) {
        irb::Type* type;
        if (expression->getMemberName().size() == 1)
            type = elementExprType->getBaseType();
        else
            type = new irb::VectorType(context, elementExprType->getBaseType(), expression->getMemberName().size());
        irb::Type* trueType = type;
        //HACK: get the pointer type
        if (!expression->getLoadOnCodegen())
            trueType = new irb::PointerType(context, type, irb::StorageClass::Function);
        return new CodeValue{exprV->code + "." + expression->getMemberName()};
    } else {
        logError("the '.' operator only operates on structures and vectors, got '" + elementExprType->getDebugName() + "' instead");
        return nullptr;
    }
}

CodeValue* CodeWriter::codegenStructureDefinition(const StructureDefinitionAST* expression) {
    std::string codeStr = "struct " + expression->getName() + " {\n";
    for (auto& member : expression->getMembers()) {
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

    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenEnumDefinition(const EnumDefinitionAST* expression) {
    std::string codeStr;
    if (irb::target == irb::Target::Metal || irb::target == irb::Target::HLSL) {
        codeStr = "enum " + expression->getName() + " {\n";
        for (auto& value : expression->getValues())
            codeStr += "\t" + value.name + " = " + std::to_string(value.value) + ",\n";
        codeStr += "};";
    } else {
        codeStr = "//Enum '" + expression->getName() + "'";
    }

    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenEnumValueExpression(const EnumValueExpressionAST* expression) {
    if (target == irb::Target::Metal || target == irb::Target::HLSL)
        return new CodeValue{expression->getValue().name};
    else
        return new CodeValue{std::to_string(expression->getValue().value)};
}

CodeValue* CodeWriter::codegenInitializerListExpression(const InitializerListExpressionAST* expression) {
    std::string codeStr = getTypeName(expression->getType()) + "(";
    for (uint32_t i = 0; i < expression->getExpressions().size(); i++) {
        CodeValue* component = codegenExpression(expression->getExpressions()[i]);
        if (!component)
            return nullptr;
        if (i != 0)
            codeStr += ", ";
        codeStr += component->code;
    }

    return new CodeValue{codeStr + ")"};
}

} //namespace lvslang
