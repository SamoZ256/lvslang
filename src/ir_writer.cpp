#include "ir_writer.hpp"

namespace lvslang {

irb::Value* IRWriter::codegenExpression(const ExpressionAST* expression) {
    uint32_t oldDebugLine = source.crntDebugLine;
    uint32_t oldDebugChar = source.crntDebugChar;
    expression->setDebugInfo();
    
    irb::Value* value;
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
    
    if (expression->getRequiredType())
        return builder->opCast(value, expression->getRequiredType());
    
    return value;
}

irb::Value* IRWriter::codegenNumberExpression(const NumberExpressionAST* expression) {
    irb::ConstantValue* value;
    switch (expression->getType()->getTypeID()) {
    case irb::TypeID::Bool:
        value = new irb::ConstantBool(context, expression->valueU());
        break;
    case irb::TypeID::Integer:
        if (expression->getType()->getIsSigned())
            value = new irb::ConstantInt(context, expression->valueL(), expression->getType()->getBitCount(), true);
        else
            value = new irb::ConstantInt(context, expression->valueU(), expression->getType()->getBitCount(), false);
        break;
    case irb::TypeID::Float:
        value = new irb::ConstantFloat(context, expression->valueD(), expression->getType()->getBitCount());
        break;
    default:
        break;
    }
    
    // TODO: find out why I do this
    if (!context.pushedRegisterName())
        context.pushRegisterName("const");

    return builder->opConstant(value);

    return value;
}

irb::Value* IRWriter::codegenVariableExpression(const VariableExpressionAST* expression) {
    irb::Value* value = expression->getVariable()->value;
    if (expression->getLoadOnCodegen() && expression->getVariable()->shouldBeLoaded)
        value = builder->opLoad(value);

    return value;
}

irb::Value* IRWriter::codegenBinaryExpression(const BinaryExpressionAST* expression) {
    irb::Value* l = codegenExpression(expression->getLHS());
    if (!l)
        return nullptr;
    irb::Value* r = codegenExpression(expression->getRHS());
    if (!r)
        return nullptr;

    if (expression->getOp() == "=") {
        if (auto* unloadedVector = dynamic_cast<UnloadedSwizzledVectorValue*>(l)) {
            irb::Value* loadedVector = builder->opLoad(unloadedVector->getUnloadedVector());
            if (r->getType()->isScalar()) {
                for (auto index : unloadedVector->getIndices())
                    loadedVector = builder->opInsert(loadedVector, r, new irb::ConstantInt(context, index, 32, true)); // TODO: should it be signed?
            } else if (r->getType()->isVector()) {
                // TODO: check if component count matches and if we are not accessing out of bounds
                for (uint8_t i = 0; i < unloadedVector->getIndices().size(); i++)
                    loadedVector = builder->opInsert(loadedVector, builder->opExtract(r, new irb::ConstantInt(context, i, 32, true)), new irb::ConstantInt(context, unloadedVector->getIndices()[i], 32, true));
            } else {
                logError("cannot assign to vector from type other than scalar and vector");
                return nullptr;
            }
            builder->opStore(unloadedVector->getUnloadedVector(), loadedVector);
        } else {
            builder->opStore(l, r);
        }

        return l;
    }

    // TODO: don't always cast?
    l = builder->opCast(l, expression->getPromotedType());
    r = builder->opCast(r, expression->getPromotedType());

    context.pushRegisterName("op");
    irb::Value* value = builder->opOperation(l, r, expression->getType(), expression->getOperation());

    return value;
}

irb::Value* IRWriter::codegenBlockExpression(const BlockExpressionAST* expression) {
    for (auto expr : expression->getExpressions()) {
        irb::Value* value = codegenExpression(expr);
        if (!value)
            return nullptr;
    }
    
    return new irb::Value(context, expression->getType());
}

irb::Value* IRWriter::codegenFunctionPrototype(const FunctionPrototypeAST* expression) {
    irb::Value* value;
    if (expression->getPreviousDeclaration()) {
        value = expression->getPreviousDeclaration()->getValue();
    } else {
        if (expression->getIsSTDFunction()) {
            value = builder->opStandardFunctionDeclaration(static_cast<irb::FunctionType*>(expression->getType()), expression->name());
        } else {
            value = builder->opFunction(static_cast<irb::FunctionType*>(expression->getType()), expression->name());
            // TODO: name the function properly
            builder->opName(value, expression->name() + "(");
        }
    }

    // HACK: set the value
    const_cast<FunctionPrototypeAST*>(expression)->setValue(static_cast<irb::Function*>(value));

    return value;
}

irb::Value* IRWriter::codegenFunctionDefinition(const FunctionDefinitionAST* expression) {
    irb::Value* value = codegenExpression(expression->getPrototype());
    if (!value)
        return nullptr;
    
    irb::FunctionType* functionType = static_cast<irb::FunctionType*>(value->getType());
    builder->setActiveFunction(expression->getPrototype()->getValue());
    if (expression->getPrototype()->getFunctionRole() != irb::FunctionRole::Normal)
        builder->opEntryPoint(value, expression->getPrototype()->getFunctionRole(), expression->getPrototype()->name(), static_cast<irb::FunctionType*>(expression->getPrototype()->getType())->getReturnType(), expression->getPrototype()->arguments());

    context.pushRegisterName("entry");
    irb::Block* block = builder->opBlock(expression->getPrototype()->getValue());
    builder->setInsertBlock(block);

    for (uint32_t i = 0; i < expression->getPrototype()->arguments().size(); i++) {
        auto& arg = expression->getPrototype()->arguments()[i];
        if (arg.name != "") {
            auto& attr = expression->getPrototype()->getArgumentAttributes(i);
            context.pushRegisterName(arg.name);
            irb::Type* type = arg.type;
            irb::Value* argValue = builder->opFunctionParameter(expression->getPrototype()->getValue(), type);
            variables[arg.name].value = argValue;
        }
    }
    
    irb::Value* bodyV = codegenExpression(expression->getBody());
    if (!bodyV)
        return nullptr;
    
    if (!builder->getInsertBlock()->hasReturned()) {
        if (static_cast<irb::FunctionType*>(expression->getPrototype()->getType())->getReturnType()->getTypeID() == irb::TypeID::Void)
            builder->opReturn();
        else
            builder->opUnreachable();
    }
    builder->opFunctionEnd(expression->getPrototype()->getValue());

    return value;
}

irb::Value* IRWriter::codegenFunctionCall(const CallExpressionAST* expression) {
    std::vector<irb::Value*> argVs;
    argVs.reserve(expression->getArguments().size());
    for (const auto& arg : expression->getArguments()) {
        irb::Value* argV = codegenExpression(arg);
        if (!argV)
            return nullptr;
        argVs.push_back(argV);
    }

    if (target == Target::SPIRV && !expression->getPrototype()->getIsSTDFunction()) {
        for (uint32_t i = 0; i < expression->getArguments().size(); i++) {
            context.pushRegisterName("param");
            argVs[i] = builder->opVariable(new irb::PointerType(context, argVs[i]->getType(), irb::StorageClass::Function), argVs[i]);
        }
    }

    if (expression->getCallee() == "sample")
        return builder->opSample(expression->getPrototype()->getValue(), argVs[0], argVs[1], argVs[2]);

    return builder->opFunctionCall(expression->getPrototype()->getValue(), argVs);
}

irb::Value* IRWriter::codegenReturnExpression(const ReturnExpressionAST* expression) {
    irb::Value* returnV = nullptr;
    if (expression) {
        returnV = codegenExpression(expression->getExpression());
        if (!returnV)
            return nullptr;
    }

    builder->opReturn(returnV);

    return returnV;
}

irb::Value* IRWriter::codegenIfExpression(const IfExpressionAST* expression) {
    std::vector<irb::Block*> elseBs(expression->getIfThenBlocks().size()); // Serve as conditions except for the else block
    std::vector<irb::Block*> thenBs(expression->getIfThenBlocks().size());
    std::vector<irb::Block*> mergeBs(expression->getIfThenBlocks().size());
    for (uint32_t i = 0; i < expression->getIfThenBlocks().size(); i++) {
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
    if (expression->getElseBlock()) {
        context.pushRegisterName("else");
        elseBs[elseBs.size() - 1] = builder->opBlock(builder->getActiveFunction());
    } else {
        elseBs[elseBs.size() - 1] = endB;
    }
    for (uint32_t i = 0; i < expression->getIfThenBlocks().size(); i++) {
        irb::Value* condV = codegenExpression(expression->getIfThenBlocks()[i]->condition);
        builder->opBlockMerge(mergeBs[i]);
        builder->opBranchCond(condV, thenBs[i], elseBs[i]);

        // Current body
        builder->setInsertBlock(thenBs[i]);
        irb::Value* blockV = codegenExpression(expression->getIfThenBlocks()[i]->block);
        builder->opBranch(mergeBs[i]);

        // Next condition or else block
        builder->setInsertBlock(elseBs[i]);
    }
    if (expression->getElseBlock()) {
        irb::Value* blockV = codegenExpression(expression->getElseBlock());
        builder->opBranch(mergeBs[mergeBs.size() - 1]);
    }
    for (uint32_t i = mergeBs.size() - 1; i > 0; i--) {
        builder->setInsertBlock(mergeBs[i]);
        builder->opBranch(mergeBs[i - 1]);
    }

    // End
    builder->setInsertBlock(endB);

    // TODO: return something else
    return endB;
}

irb::Value* IRWriter::codegenWhileExpression(const WhileExpressionAST* expression) {
    irb::Block* mergeB;
    irb::Block* condB;
    irb::Block* thenB;
    irb::Block* afterThenB;
    irb::Block* endB;

    if (target == Target::SPIRV) {
        context.pushRegisterName("loop_merge");
        mergeB = builder->opBlock(builder->getActiveFunction());
    }
    context.pushRegisterName("loop_cond");
    condB = builder->opBlock(builder->getActiveFunction());
    context.pushRegisterName("loop");
    thenB = builder->opBlock(builder->getActiveFunction());
    if (target == Target::SPIRV) {
        context.pushRegisterName("after_loop");
        afterThenB = builder->opBlock(builder->getActiveFunction());
    } else {
        mergeB = condB;
        afterThenB = condB;
    }
    context.pushRegisterName("end");
    endB = builder->opBlock(builder->getActiveFunction());

    builder->opBranch(expression->getIsDoWhile() ? thenB : mergeB);

    // Merge
    if (target == Target::SPIRV) {
        builder->setInsertBlock(mergeB);
        builder->opLoopMerge(endB, afterThenB);
        builder->opBranch(condB);
    }

    // Condition
    builder->setInsertBlock(condB);
    
    irb::Value* condV = codegenExpression(expression->getCondition());
    if (!condV)
        return nullptr;

    builder->opBranchCond(condV, thenB, endB);

    // Then
    builder->setInsertBlock(thenB);
    irb::Value* blockV = codegenExpression(expression->getBlock());
    if (!blockV)
        return nullptr;
    builder->opBranch(afterThenB);

    // After then
    if (target == Target::SPIRV) {
        builder->setInsertBlock(afterThenB);
        builder->opBranch(mergeB);
    }

    // End
    builder->setInsertBlock(endB);

    return endB;
}

irb::Value* IRWriter::codegenVariableDeclaration(const VariableDeclarationExpressionAST* expression) {
    irb::Value* value = nullptr;
    for (uint32_t i = 0; i < expression->getVariableDeclarations().size(); i++) {
        const std::string& varName = expression->getVariableDeclarations()[i].name;
        irb::Type* type = expression->getVariableDeclarations()[i].type;
        ExpressionAST* initExpression = expression->getVariableDeclarations()[i].expression;

        irb::Value* initV = nullptr;
        if (initExpression) {
            // TODO: uncomment?
            // context.pushRegisterName(varName + "_init");
            initV = codegenExpression(initExpression);
            if (!initV)
                return nullptr;
        }
        if (!type)
            type = initV->getType();
        
        irb::PointerType* varType = new irb::PointerType(context, type, irb::StorageClass::Function);
        context.pushRegisterName(varName);
        if (expression->getIsConstant() && expression->getIsGlobal())
            value = initV;
        else
            value = builder->opVariable(varType, (initExpression && initExpression->isConstant() ? initV : nullptr));
        if (initExpression && !initExpression->isConstant())
            builder->opStore(value, initV);
        variables[varName].value = value;
    }

    return value;
}

irb::Value* IRWriter::codegenSubscriptExpression(const SubscriptExpressionAST* expression) {
    irb::Value* ptrV = codegenExpression(expression->getPtr());
    irb::Value* indexV = codegenExpression(expression->getIndex());
    if (!ptrV || !indexV)
        return nullptr;

    irb::Value* value = builder->opGetElementPtr(static_cast<irb::PointerType*>(expression->getType()), ptrV, {indexV});
    if (expression->getLoadOnCodegen())
        value = builder->opLoad(value);

    return value;
}

// TODO: support chained unloaded vector swizzle
irb::Value* IRWriter::codegenMemberAccessExpression(const MemberAccessExpressionAST* expression) {
    irb::Value* exprV = codegenExpression(expression->getExpression());
    if (!exprV)
        return nullptr;
    // TODO: load the value in SPIRV backend if it isn't input/buffer
    if (target == Target::AIR && expression->getExprShouldBeLoadedBeforeAccessingMember())
        exprV = builder->opLoad(exprV);
    irb::PointerType* exprType = static_cast<irb::PointerType*>(exprV->getType());
    irb::Type* elementExprType = exprType->getElementType();
    if (elementExprType->isStructure()) {
        irb::PointerType* type = (expression->getLoadOnCodegen() ? new irb::PointerType(context, expression->getType(), irb::StorageClass::Function) : static_cast<irb::PointerType*>(expression->getType()));
        irb::Value* indexV = builder->opConstant(new irb::ConstantInt(context, expression->getMemberIndex(), 32, true));
        irb::Value* elementV = builder->opGetElementPtr(type, exprV, {indexV});
        if (expression->getLoadOnCodegen())
            elementV = builder->opLoad(elementV);

        return elementV;
    } else if (elementExprType->isVector()) {
        irb::Type* type;
        if (expression->getMemberName().size() == 1)
            type = elementExprType->getBaseType();
        else
            type = new irb::VectorType(context, elementExprType->getBaseType(), expression->getMemberName().size());
        irb::Value* loadedVector;
        std::vector<irb::Value*> components;
        std::vector<uint8_t> indices;
        if (expression->getLoadOnCodegen()) {
            loadedVector = builder->opLoad(exprV);
            components.reserve(expression->getMemberName().size());
        } else {
            indices.reserve(expression->getMemberName().size());
        }
        for (uint8_t i = 0; i < expression->getMemberName().size(); i++) {
            int8_t index;
            switch (expression->getMemberName()[i]) {
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
            if (expression->getLoadOnCodegen())
                components.push_back(builder->opExtract(loadedVector, new irb::ConstantInt(context, index, 32, false)));
            else
                indices.push_back(index);
        }
        
        if (expression->getLoadOnCodegen()) {
            if (components.size() == 1)
                return components[0];
            return builder->opConstruct(static_cast<irb::VectorType*>(type), components);
        } else {
            return new UnloadedSwizzledVectorValue(context, exprV, indices);
        }
    } else {
        logError("the '.' operator only operates on structures and vectors, got '" + elementExprType->getDebugName() + "' instead");
        return nullptr;
    }
}

irb::Value* IRWriter::codegenStructureDefinition(const StructureDefinitionAST* expression) {
    context.pushRegisterName(expression->getName());

    return builder->opStructureDefinition(static_cast<irb::StructureType*>(expression->getType()));
}

irb::Value* IRWriter::codegenEnumDefinition(const EnumDefinitionAST* expression) {
    return new irb::Value(context, expression->getType());
}

irb::Value* IRWriter::codegenEnumValueExpression(const EnumValueExpressionAST* expression) {
    return builder->opConstant(new irb::ConstantInt(context, expression->getValue().value, expression->getType()->getBitCount(), expression->getType()->getIsSigned()));
}

irb::Value* IRWriter::codegenInitializerListExpression(const InitializerListExpressionAST* expression) {
    std::vector<irb::Value*> components;
    components.reserve(expression->getExpressions().size());
    for (auto* expr : expression->getExpressions()) {
        irb::Value* component = codegenExpression(expr);
        if (!component)
            return nullptr;
        if (component->getType()->isScalar())
            component = builder->opCast(component, (expression->getType()->isScalar() ? expression->getType() : expression->getType()->getBaseType()));
        components.push_back(component);
    }
    
    // "Unpack" the vectors
    if (expression->getType()->isVector()) {
        for (uint32_t i = 0; i < components.size(); i++) {
            irb::Value* component = components[i];
            if (auto vectorType = dynamic_cast<irb::VectorType*>(component->getType())) {
                components.erase(components.begin() + i);
                for (uint8_t j = 0; j < vectorType->getComponentCount(); j++) {
                    irb::Value* vectorComponent = builder->opCast(builder->opExtract(component, new irb::ConstantInt(context, j, 32, true)), expression->getType()->getBaseType());
                    components.insert(components.begin() + i + j, vectorComponent);
                }
                i += vectorType->getComponentCount() - 1;
            }
        }
    }

    if (expression->getType()->isScalar())
        return builder->opCast(components[0], expression->getType());
    if (expression->getType()->isArray()) {
        // TODO: implement this
        logError("array initializer lists are not supported for IR backends yet");
        return nullptr;
    }
    if (expression->getType()->isVector()) {
        irb::VectorType* vectorType = static_cast<irb::VectorType*>(expression->getType());
        // Fill the list in case it is just a one value initializer
        if (components.size() == 1) {
            components.reserve(vectorType->getComponentCount());
            for (uint8_t i = 1; i < vectorType->getComponentCount(); i++)
                components.push_back(components[0]);
        }
        context.pushRegisterName("constructed_vector");

        return builder->opConstruct(vectorType, components);
    }
    if (expression->getType()->isMatrix()) {
        irb::MatrixType* matrixType = static_cast<irb::MatrixType*>(expression->getType());
        // Fill the list in case it is just a one value initializer
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
}

irb::Value* IRWriter::codegenDereferenceExpression(const DereferenceExpressionAST* expression) {
    irb::Value* value = codegenExpression(expression->getExpression());
    if (!value)
        return nullptr;
    
    // TODO: load the value in SPIRV backend if it isn't input/buffer
    if (target == Target::AIR)
        value = builder->opLoad(value);

    return value;
}

} // namespace lvslang
