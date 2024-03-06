#include "ast.hpp"

namespace lvslang {

irb::Context context;

irb::Type* crntFunctionReturnType = nullptr;

std::map<std::string, Variable> variables;
std::map<std::string, std::vector<FunctionPrototypeAST*> > functionDeclarations;
std::map<std::string, Enumeration*> enumerations;

irb::Type* NumberExpressionAST::_initialize() {
    if (requiredType) {
        if (requiredType->isScalar()) {
            scalarType = requiredType;
        } else if (requiredType->isVector()) {
            scalarType = requiredType->getBaseType();
        } else if (requiredType->isMatrix()) {
            scalarType = requiredType->getBaseType()->getBaseType();
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

irb::Type* BinaryExpressionAST::_initialize() {
    if (op == "=")
        lhs->setLoadOnCodegen(false);
    
    irb::Type* lType = lhs->initialize();
    if (!lType)
        return nullptr;
    irb::Type* rType = rhs->initialize(op == "=" ? lType->getElementType() : nullptr);
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

    promotedType = findPromotedType(lType, rType);
    irb::Type* type = promotedType;

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

irb::Type* BlockExpressionAST::_initialize() {
    for (auto expr : expressions) {
        irb::Type* type = expr->initialize();
        if (!type)
            return nullptr;
    }
    
    // TODO: return something else?
    return new irb::ScalarType(context, irb::TypeID::Void, 0);
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
            // pointerType->setAddressSpace(attr.addressSpace);
        }
        if (functionRole != irb::FunctionRole::Normal) {
            // TDOO: save the bindings for reflection
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
                //if ((irb::target == Target::SPIRV || irb::target == Target::GLSL || irb::target == Target::HLSL) && functionRole != irb::FunctionRole::Normal)
                //    arg.type = arg.type->getElementType();
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

    // Check for redefinition
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

irb::Type* FunctionDefinitionAST::_initialize() {
    irb::Type* type = declaration->initialize();
    if (!type)
        return nullptr;

    // HACK: register the arguments as variables
    for (uint32_t i = 0; i < declaration->arguments().size(); i++) {
        auto& arg = declaration->arguments()[i];
        if (arg.name != "")
            variables[arg.name] = {new irb::PointerType(context, arg.type, irb::StorageClass::Function), nullptr, true};
    }
    
    if (!body->initialize())
        return nullptr;
    
    return type;
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
        // TODO: move this to a separate function?
        for (auto* argType : argTypes)
            identifier += "." + argType->getTemplateName();

        // Find suitable function overload
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

irb::Type* ReturnExpressionAST::_initialize() {
    irb::Type* type;
    if (expression)
        type = expression->initialize(crntFunctionReturnType);
    else
        type = new irb::ScalarType(context, irb::TypeID::Void, 0);

    return type;
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

    // TODO: return something else?
    return new irb::ScalarType(context, irb::TypeID::Void, 0);
}

irb::Type* WhileExpressionAST::_initialize() {
    if (!condition->initialize(new irb::ScalarType(context, irb::TypeID::Bool, 8, false)))
        return nullptr;

    if (!block->initialize())
        return nullptr;
    
    // TODO: return something else?
    return new irb::ScalarType(context, irb::TypeID::Void, 0);
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
    irb::PointerType* pointerType = dynamic_cast<irb::PointerType*>(ptrType);
    if (!pointerType) {
        logError("cannot index into a non-pointer value");
        return nullptr;
    }

    irb::Type* type = pointerType->getElementType()->getBaseType();
    if (!loadOnCodegen)
        type = new irb::PointerType(context, type, pointerType->getStorageClass());

    return type;
}

irb::Type* MemberAccessExpressionAST::_initialize() {
    expression->setLoadOnCodegen(false);
    irb::Type* exprType = expression->initialize();
    if (!exprType)
        return nullptr;
    if (exprShouldBeLoadedBeforeAccessingMember)
        exprType = exprType->getElementType();
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

        // TODO: check if the components are correct

        if (loadOnCodegen)
            return type;
        else
            return new irb::PointerType(context, type, irb::StorageClass::Function);
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

    // Check if none of the members have structure type and were declared with the location attribute at the same time
    for (const auto member : members) {
        if (member.attributes.locationIndex != -1) {
            if (member.type->isArray() || member.type->isStructure()) {
                logError("arrays and structures cannot have the 'location' attribute");
                return nullptr;
            }
        }
    }

    irb::Structure* structure = new irb::Structure;
    structure->members = members;
    context.structures[name] = structure;

    return new irb::StructureType(context, name);
}

irb::Type* EnumDefinitionAST::_initialize() {
    if (enumerations[name]) {
        logError("redefinition of enum '" + name + "'");
        return nullptr;
    }

    Enumeration* enumeration = new Enumeration(values, isClass);
    enumerations[name] = enumeration;

    return enumeration->getType();
}

irb::Type* EnumValueExpressionAST::_initialize() {
    return enumeration->getType();
}

irb::Type* InitializerListExpressionAST::_initialize() {
    std::vector<irb::Type*> components;
    components.reserve(expressions.size());
    for (auto* expression : expressions) {
        // Provide required type in case of a number expression
        irb::Type* component = expression->initialize((listType->isVector() && dynamic_cast<NumberExpressionAST*>(expression)) ? listType->getBaseType() : nullptr);
        if (!component)
            return nullptr;
        components.push_back(component);
    }
    
    // "Unpack" the vectors
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

irb::Type* DereferenceExpressionAST::_initialize() {
    irb::Type* type = expression->initialize();
    if (!type)
        return nullptr;

    if (!type->isPointer()) {
        logError("cannot dereference a non-pointer value");
        return nullptr;
    }

    return type->getElementType();
}

} // namespace lvslang
