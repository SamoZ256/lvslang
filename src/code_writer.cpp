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
    } else if (auto* e = dynamic_cast<const DereferenceExpressionAST*>(expression)) {
        value = codegenDereferenceExpression(e);
    } else {
        LVSLANG_ERROR("unknown expression type");
        return nullptr;
    }
    if (!value)
        return nullptr;

    source.crntDebugLine = oldDebugLine;
    source.crntDebugChar = oldDebugChar;
    
    if (expression->getRequiredType() && !expression->getType()->equals(expression->getRequiredType()))
        return new CodeValue{getTypeName(target, expression->getRequiredType()) + "(" + value->code + ")"};
    
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
    return new CodeValue{expression->getName()};
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
    
    // HLSL matrix multiplication
    if (target == Target::HLSL && expression->getOp() == "*" && (expression->getLHS()->getType()->isMatrix() || expression->getRHS()->getType()->isMatrix()))
        return new CodeValue{"mul(" + l->code + ", " + r->code + ")"};

    // TODO: cast in some cases?
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
        auto& attrs = arg.attributes;
        if (target == Target::Metal) {
            if (i != 0)
                argsStr += ", ";
            std::string addressSpace;
            if (attrs.addressSpace == 2)
                addressSpace = "constant ";
            else if (attrs.addressSpace == 1)
                addressSpace = "device ";
            
            std::string attributesEnd;
            if (attrs.isBuffer)
                attributesEnd = " [[buffer(" + std::to_string(attrs.bindings.buffer) + ")]]";
            if (attrs.isTexture)
                attributesEnd = " [[texture(" + std::to_string(attrs.bindings.texture) + ")]]";
            if (attrs.isSampler)
                attributesEnd = " [[sampler(" + std::to_string(attrs.bindings.sampler) + ")]]";
            if (attrs.isInput)
                attributesEnd = " [[stage_in]]";
            if (attrs.isPosition)
                attributesEnd += " [[position]]";
            if (attrs.locationIndex != -1)
                attributesEnd += " [[attribute(" + std::to_string(attrs.locationIndex) + ")]]";
            if (attrs.colorIndex != -1)
                attributesEnd += " [[color(" + std::to_string(attrs.colorIndex) + ")]]";

            argsStr += addressSpace + getTypeName(target, arg.type) + " " + arg.name + attributesEnd;
        } else if (target == Target::HLSL) {
            if (i != 0)
                argsStr += ", ";
            argsStr += getTypeName(target, (attrs.isBuffer ? arg.type->getElementType() : arg.type)) + " " + arg.name;

            // Entry point
            if (expression->getFunctionRole() != irb::FunctionRole::Normal) {
                if (!attrs.isInput) {
                    if (attrs.isBuffer) {
                        entryPointStr += "cbuffer "; // TODO: support other types of buffer as well
                        // We need to get element type, since HLSL treats it without pointer
                        entryPointStr += arg.name + "_Uniform : register(b" + std::to_string(attrs.bindings.buffer) + ") {\n\t" + getTypeName(target, arg.type->getElementType()) + " " + arg.name + ";\n}";
                    } else if (attrs.isTexture) {
                        entryPointStr += getTypeName(target, arg.type) + " " + arg.name + " : register(t" + std::to_string(attrs.bindings.texture) + ")";
                    } else if (attrs.isSampler) {
                        entryPointStr += getTypeName(target, arg.type) + " " + arg.name + " : register(s" + std::to_string(attrs.bindings.sampler) + ")";
                    }
                    entryPointStr += ";\n\n";
                }
            }
        } else {
            // TODO: check if this applies to all images
            // HACK: Image types cannot be passed as arguments
            if (!arg.type->isTexture() || static_cast<irb::TextureType*>(arg.type)->getAccess() == irb::TextureAccess::Sample) {
                if (i != 0)
                    argsStr += ", ";
                argsStr += getTypeName(target, (attrs.isBuffer ? arg.type->getElementType() : arg.type)) + " " + arg.name;
            }

            // Entry point
            if (expression->getFunctionRole() != irb::FunctionRole::Normal) {
                std::string typeName;
                if (attrs.isInput) {
                    switch (expression->getFunctionRole()) {
                    case irb::FunctionRole::Vertex:
                        if (auto* structureType = dynamic_cast<irb::StructureType*>(arg.type)) {
                            for (const auto& member : structureType->getStructure()->members)
                                entryPointStr += "layout (location = " + std::to_string(member.attributes.locationIndex) + ") in " + getTypeName(target, member.type) + " " + member.name + ";\n\n";
                        } else {
                            entryPointStr += "layout (location = " + std::to_string(attrs.locationIndex) + ") in " + getTypeName(target, arg.type) + " " + arg.name + ";\n\n";
                        }
                        break;
                    case irb::FunctionRole::Fragment:
                        entryPointStr += "layout (location = 0) in " + getTypeName(target, arg.type) + "_Input {\n\t" + getTypeName(target, arg.type) + " " + arg.name + ";\n};\n\n";
                        break;
                    default:
                        logError("cannot use the 'input' attribute for kernel function");
                        return nullptr;
                    }
                } else {
                    if (attrs.isBuffer) {
                        if (attrs.addressSpace == 2)
                            typeName = "uniform ";
                        else
                            typeName = "readonly buffer "; // TODO: support other types of buffer as well
                        // We need to get element type, since GLSL treats it without pointer
                        typeName += arg.name + "_Uniform {\n\t" + getTypeName(target, arg.type->getElementType()) + " " + arg.name + ";\n}";
                    } else {
                        typeName = "uniform " + getTypeName(target, arg.type);
                    }
                    entryPointStr += "layout (set = " + std::to_string(attrs.bindings.set) + ", binding = " + std::to_string(attrs.bindings.binding);
                    if (auto* textureType = dynamic_cast<irb::TextureType*>(arg.type)) {
                        if (textureType->getAccess() != irb::TextureAccess::Sample)
                            entryPointStr += ", rgba8"; // TODO: do not hardcode this
                    }
                    entryPointStr += ") " + typeName;
                    if (!attrs.isBuffer)
                        entryPointStr += " " + arg.name;
                    entryPointStr += ";\n\n";
                }
            }
        }
    }

    if (expression->getFunctionRole() != irb::FunctionRole::Normal) {
        if (target == Target::Metal) {
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
        } else if (target == Target::HLSL) {
            if (expression->getReturnType()->getTypeID() != irb::TypeID::Void) {
                entryPointStr += "struct " + getTypeName(target, expression->getReturnType()) + "_Output {\n\t" + getTypeName(target, expression->getReturnType()) + " output : TEXCOORD0;\n";
                if (expression->getFunctionRole() == irb::FunctionRole::Vertex)
                    entryPointStr += "\tfloat4 position : SV_Position;\n";
                entryPointStr += "};\n\n";
            }

            // Entry point
            std::string argsStr;
            for (const auto& argument : expression->arguments()) {
                if (argument.attributes.isInput) {
                    argsStr += getTypeName(target, argument.type) + " " + argument.name;
                    break;
                }
            }
            entryPointStr += getTypeName(target, expression->getReturnType()) + "_Output _" + expression->name() + "(" + argsStr + ") {\n";

            // -------- Entry point call --------
            entryPointStr += "\t// Entry point call\n";
            std::string outputVarName = "_entryPointOutput";
            entryPointStr += "\t" + (expression->getReturnType()->getTypeID() == irb::TypeID::Void ? "" : getTypeName(target, expression->getReturnType()) + " " + outputVarName + " = ") + expression->name() + "(";
            for (uint32_t i = 0; i < expression->arguments().size(); i++) {
                if (i != 0)
                    entryPointStr += ", ";
                entryPointStr += expression->arguments()[i].name;
            }
            entryPointStr += ");\n";

            // -------- Output --------
            if (expression->getReturnType()->getTypeID() != irb::TypeID::Void) {
                entryPointStr += "\n\t// Output\n\t" + getTypeName(target, expression->getReturnType()) + "_Output __output;\n\t__output.output = " + outputVarName + ";\n";
                if (expression->getFunctionRole() == irb::FunctionRole::Vertex) {
                    if (auto* structureType = dynamic_cast<irb::StructureType*>(expression->getReturnType())) {
                        for (const auto& member : structureType->getStructure()->members) {
                            if (member.attributes.isPosition) {
                                entryPointStr += "\t__output.position = " + outputVarName + "." + member.name + ";\n";
                                break;
                            }
                        }
                    } else {
                        entryPointStr += "\t__output.position = " + outputVarName + ";\n";
                    }
                }
                entryPointStr += "\n\treturn __output;\n";
            }

            entryPointStr += "}\n\n";
        } else if (target == Target::GLSL) {
            switch (expression->getFunctionRole()) {
            case irb::FunctionRole::Vertex:
                entryPointStr += "layout (location = 0) out " + getTypeName(target, expression->getReturnType()) + "_Output {\n\t" + getTypeName(target, expression->getReturnType()) + " _output;\n} _output;\n\n";
                break;
            case irb::FunctionRole::Fragment:
                if (auto* structureType = dynamic_cast<irb::StructureType*>(expression->getReturnType())) {
                    for (const auto& member : structureType->getStructure()->members)
                        entryPointStr += "layout (location = " + std::to_string(member.attributes.colorIndex) + ") out " + getTypeName(target, member.type) + " " + member.name + ";\n\n";
                } else {
                    entryPointStr += "layout (location = 0) out " + getTypeName(target, expression->getReturnType()) + " _outputColor;\n\n";
                }
                break;
            default:
                logError("cannot use the 'output' attribute for kernel function");
                return nullptr;
            }

            // Entry point
            entryPointStr += "void main() {";

            // -------- Input --------
            bool hasInput = false;
            for (uint32_t i = 0; i < expression->arguments().size(); i++) {
                if (expression->getFunctionRole() == irb::FunctionRole::Vertex && expression->arguments()[i].attributes.isInput) {
                    if (auto* structureType = dynamic_cast<irb::StructureType*>(expression->arguments()[i].type)) {
                        if (!hasInput) {
                            entryPointStr += "\n\t// Input\n";
                            hasInput = true;
                        }
                        // Assemble the input structure
                        entryPointStr += "\t" + getTypeName(target, structureType) + " " + expression->arguments()[i].name + ";\n";
                        for (const auto& member : structureType->getStructure()->members)
                            entryPointStr += "\t" + expression->arguments()[i].name + "." + member.name + " = " + member.name + ";\n";
                    }
                }
            }
            entryPointStr += "\n";

            // -------- Entry point call --------
            entryPointStr += "\t// Entry point call\n";
            std::string outputVarName = "_entryPointOutput";
            entryPointStr += "\t" + (expression->getReturnType()->getTypeID() == irb::TypeID::Void ? "" : getTypeName(target, expression->getReturnType()) + " " + outputVarName + " = ") + expression->name() + "(";
            for (uint32_t i = 0; i < expression->arguments().size(); i++) {
                if (!expression->arguments()[i].type->isTexture() || static_cast<irb::TextureType*>(expression->arguments()[i].type)->getAccess() == irb::TextureAccess::Sample) {
                    if (i != 0)
                        entryPointStr += ", ";
                    entryPointStr += expression->arguments()[i].name;
                }
            }
            entryPointStr += ");\n";

            // -------- Output --------
            if (expression->getReturnType()->getTypeID() != irb::TypeID::Void) {
                entryPointStr += "\n\t// Output\n";

                if (auto* structType = dynamic_cast<irb::StructureType*>(expression->getReturnType())) {
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
                } else {
                    if (expression->getFunctionRole() == irb::FunctionRole::Vertex)
                        entryPointStr += "\tgl_Position = " + outputVarName + ";\n";
                    else if (expression->getFunctionRole() == irb::FunctionRole::Fragment)
                        entryPointStr += "\t_outputColor = " + outputVarName + ";\n";
                }
            }
            
            entryPointStr += "}\n\n";
        }
    }
    codeStr += getTypeName(target, expression->getReturnType()) + " " + expression->name() + "(" + argsStr + ")";
    if ((target == Target::GLSL || target == Target::HLSL) && expression->getFunctionRole() != irb::FunctionRole::Normal)
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
    std::vector<CodeValue*> argVs(expression->getPrototype()->arguments().size());
    for (uint32_t i = 0; i < expression->getArguments().size(); i++)
        argVs[i] = codegenExpression(expression->getArguments()[i]);
    
    // Default arguments
    for (uint32_t i = expression->getArguments().size(); i < expression->getPrototype()->arguments().size(); i++)
        argVs[i] = codegenExpression(expression->getPrototype()->getDefaultValues()[i]);

    for (uint32_t i = 0; i < argVs.size(); i++) {
        if (!argVs[i])
            return nullptr;
        if (i != 0)
            argsStr += ", ";
        argsStr += argVs[i]->code;
    }

    std::string code;
    // TODO: add more argument options
    if (expression->getCallee() == "sample") {
        switch (target) {
        case Target::Metal:
            code = argVs[0]->code + ".sample(" + argVs[1]->code + ", " + argVs[2]->code + ")";
            break;
        case Target::HLSL:
            code = argVs[0]->code + ".SampleLevel(" + argVs[1]->code + ", " + argVs[2]->code + ", 0.0f)";
            break;
        case Target::GLSL:
            code = "texture(sampler2D(" + argVs[0]->code + ", " + argVs[1]->code + "), " + argVs[2]->code + ")"; // TODO: support other samplers + textures as well
            break;
        default:
            break;
        }
    } else if (expression->getCallee() == "read") {
        switch (target) {
        case Target::Metal:
            code = argVs[0]->code + ".read(" + argVs[1]->code + ")";
            break;
        case Target::HLSL:
            code = argVs[0]->code + ".Load(int2(" + argVs[1]->code + "))";
            break;
        case Target::GLSL:
            code = "imageLoad(" + argVs[0]->code + ", " + argVs[1]->code + ")";
            break;
        default:
            break;
        }
    } else if (expression->getCallee() == "write") {
        switch (target) {
        case Target::Metal:
            code = argVs[0]->code + ".write(" + argVs[1]->code + ", " + argVs[2]->code + ")";
            break;
        case Target::HLSL:
            code = argVs[0]->code + ".Store(" + argVs[1]->code + ", " + argVs[2]->code + ")"; // TODO: check if this is correct
            break;
        case Target::GLSL:
            code = "imageStore(" + argVs[0]->code + ", " + argVs[1]->code + ", " + argVs[2]->code + ")";
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
    codeStr += condV->code + ") ";
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
            if (target == Target::Metal && expression->getIsGlobal())
                codeStr += "constant ";
            else
                codeStr += "const ";
        }

        codeStr += getTypeNameBegin(target, type) + " " + varName + getTypeNameEnd(type);
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
    std::string accessOperator = ".";
    if (expression->getExprShouldBeLoadedBeforeAccessingMember()) {
        // TODO: do this in HLSL/GLSL backend as well if it isn't input/buffer
        if (target == Target::Metal)
            accessOperator = "->";
        elementExprType = elementExprType->getElementType();
    }
    if (elementExprType->isStructure()) {
        return new CodeValue{exprV->code + accessOperator + expression->getMemberName()};
    } else if (elementExprType->isVector()) {
        irb::Type* type;
        if (expression->getMemberName().size() == 1)
            type = elementExprType->getBaseType();
        else
            type = new irb::VectorType(context, elementExprType->getBaseType(), expression->getMemberName().size());
        irb::Type* trueType = type;
        // HACK: get the pointer type
        if (!expression->getLoadOnCodegen())
            trueType = new irb::PointerType(context, type, irb::StorageClass::Function);
        return new CodeValue{exprV->code + "." + expression->getMemberName()};
    } else {
        logError("the '.' operator only operates on structures and vectors, got '" + elementExprType->getDebugName() + "' instead");
        return nullptr;
    }
}

CodeValue* CodeWriter::codegenStructureDefinition(const StructureDefinitionAST* expression) {
    if (expression->getIsSTD())
        return new CodeValue{""};
    
    std::string codeStr = "struct " + expression->getName() + " {\n";
    for (auto& member : expression->getMembers()) {
        std::string attributesEnd;
        if (target == Target::Metal) {
            if (member.attributes.isPosition)
                attributesEnd += " [[position]]";
            if (member.attributes.locationIndex != -1)
                attributesEnd += " [[attribute(" + std::to_string(member.attributes.locationIndex) + ")]]";
            if (member.attributes.colorIndex != -1)
                attributesEnd += " [[color(" + std::to_string(member.attributes.colorIndex) + ")]]";
        } else if (target == Target::HLSL) {
            //TODO: add commas between attributes
            //TODO: uncomment?
            //if (member.attributes.isPosition)
            //    attributesEnd += " : SV_Position";
            if (member.attributes.locationIndex != -1)
                attributesEnd += " : TEXCOORD" + std::to_string(member.attributes.locationIndex); // TODO: don't always use texcoord?
            if (member.attributes.colorIndex != -1)
                attributesEnd += " : SV_Target" + std::to_string(member.attributes.colorIndex); // TODO: check if this is correct
        }
        codeStr += "\t" + getTypeNameBegin(target, member.type) + " " + member.name + getTypeNameEnd(member.type) + attributesEnd + ";\n";
    }
    codeStr += "};";

    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenEnumDefinition(const EnumDefinitionAST* expression) {
    // TODO: uncomment?
    /*
    std::string codeStr;
    if (target == Target::Metal || target == Target::HLSL) {
        codeStr = "enum " + expression->getName() + " {\n";
        for (auto& value : expression->getValues())
            codeStr += "\t" + value.name + " = " + std::to_string(value.value) + ",\n";
        codeStr += "};";
    } else {
        codeStr = "// Enum '" + expression->getName() + "'";
    }
    */

    return new CodeValue{};
}

CodeValue* CodeWriter::codegenEnumValueExpression(const EnumValueExpressionAST* expression) {
    // TODO: uncomment?
    /*
    if (target == Target::Metal || target == Target::HLSL)
        return new CodeValue{expression->getValue().name};
    else
    */
    return new CodeValue{std::to_string(expression->getValue().value)};
}

CodeValue* CodeWriter::codegenInitializerListExpression(const InitializerListExpressionAST* expression) {
    std::vector<CodeValue*> components;
    components.reserve(expression->getExpressions().size());
    for (auto expr : expression->getExpressions()) {
        CodeValue* component = codegenExpression(expr);
        if (!component)
            return nullptr;
        components.push_back(component);
    }

    // "Unpack" the vectors
    if (target == Target::HLSL) {
        if (expression->getType()->isVector()) {
            uint32_t exprIndex = 0;
            for (uint32_t i = 0; i < components.size(); i++) {
                CodeValue* component = components[i];
                if (auto vectorType = dynamic_cast<irb::VectorType*>(expression->getExpressions()[exprIndex]->getType())) {
                    components.erase(components.begin() + i);
                    for (uint8_t j = 0; j < vectorType->getComponentCount(); j++) {
                        CodeValue* vectorComponent = new CodeValue{"(" + component->code + ")[" + std::to_string(j) + "]"};
                        components.insert(components.begin() + i + j, vectorComponent);
                    }
                    i += vectorType->getComponentCount() - 1;
                }
                exprIndex++;
            }
            if (components.size() == 1) {
                irb::VectorType* vectorType = static_cast<irb::VectorType*>(expression->getType());
                components.reserve(vectorType->getComponentCount());
                for (uint8_t i = 1; i < vectorType->getComponentCount(); i++)
                    components.push_back(components[0]);
            }
        } else if (expression->getType()->isMatrix() && components.size() == 1) {
            // TODO: create a matrix with components[0] at the diagonal
        }
    }

    std::string codeStr = getTypeName(target, expression->getType()) + "(";
    for (uint32_t i = 0; i < components.size(); i++) {
        if (i != 0)
            codeStr += ", ";
        codeStr += components[i]->code;
    }
    codeStr += ")";

    return new CodeValue{codeStr};
}

CodeValue* CodeWriter::codegenDereferenceExpression(const DereferenceExpressionAST* expression) {
    std::string code = codegenExpression(expression->getExpression())->code;

    // TODO: load the value in HLSL/GLSL backend if it isn't input/buffer
    if (target == Target::Metal)
        code = "*(" + code + ")";

    return new CodeValue{code};
}

} // namespace lvslang
