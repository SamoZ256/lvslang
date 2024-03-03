#ifndef LVSLANG_IR_WRITER_H
#define LVSLANG_IR_WRITER_H

#include "ast.hpp"

namespace lvslang {

class IRWriter {
public:
    IRWriter(Target aTarget, const AST& aAST, irb::OptimizationLevel aOptimizationLevel, bool aOutputAssembly, bool aIncludeDebugInformation, std::string aSourceFilename, irb::SPIRVVersion aSpirvVersion, std::string aLanguageName, uint32_t aLanguageVersionMajor, uint32_t aLanguageVersionMinor, uint32_t aLanguageVersionPatch) : target(aTarget), ast(aAST), optimizationLevel(aOptimizationLevel), outputAssembly(aOutputAssembly), includeDebugInformation(aIncludeDebugInformation), sourceFilename(aSourceFilename), spirvVersion(aSpirvVersion), languageName(aLanguageName), languageVersionMajor(aLanguageVersionMajor), languageVersionMinor(aLanguageVersionMinor), languageVersionPatch(aLanguageVersionPatch) {}

    bool write(std::string& outputCode) {
        switch (target) {
        case Target::None:
            IRB_ERROR("No target specified");
            break;
        case Target::SPIRV:
            builder = new irb::SPIRVBuilder(context, spirvVersion, includeDebugInformation);
            break;
        case Target::AIR:
            builder = new irb::AIRBuilder(context, "Lvslang", sourceFilename, includeDebugInformation);
            break;
        default:
            LVSLANG_ERROR_UNSUPPORTED_TARGET("[Code target]");
            break;
        }
        
        // TODO: enable them only if needed
        if (target == Target::SPIRV) {
            builder->opExtension(irb::Extension::_8bit_storage);
            builder->opExtension(irb::Extension::_16bit_storage);
            builder->opExtension(irb::Extension::explicit_arithmetic_types);
            
            builder->opImportSTD_EXT("GLSL.std.450");
            builder->opMemoryModel();
        }
        
        std::string code;
        for (auto* expression : ast.getExpressions()) {
            if (!codegenExpression(expression))
                return false;
        }
        bool success = builder->getCode(code, (irb::OptimizationLevel)optimizationLevel, outputAssembly, spirvVersion);
        if (!success)
            return false;

        if (target == Target::AIR)
            code += static_cast<irb::AIRBuilder*>(builder)->createMetadata(languageName, languageVersionMajor, languageVersionMinor, languageVersionPatch);
        outputCode = code;

        return true;
    }

private:
    Target target;
    const AST& ast;

    irb::OptimizationLevel optimizationLevel;
    bool outputAssembly;
    bool includeDebugInformation;
    std::string sourceFilename;
    irb::SPIRVVersion spirvVersion;
    std::string languageName;
    uint32_t languageVersionMajor, languageVersionMinor, languageVersionPatch;

    // Codegen
    irb::Value* codegenExpression(const ExpressionAST* expression);

    irb::Value* codegenNumberExpression(const NumberExpressionAST* expression);

    irb::Value* codegenVariableExpression(const VariableExpressionAST* expression);

    irb::Value* codegenBinaryExpression(const BinaryExpressionAST* expression);

    irb::Value* codegenBlockExpression(const BlockExpressionAST* expression);

    irb::Value* codegenFunctionPrototype(const FunctionPrototypeAST* expression);

    irb::Value* codegenFunctionDefinition(const FunctionDefinitionAST* expression);

    irb::Value* codegenFunctionCall(const CallExpressionAST* expression);

    irb::Value* codegenReturnExpression(const ReturnExpressionAST* expression);

    irb::Value* codegenIfExpression(const IfExpressionAST* expression);

    irb::Value* codegenWhileExpression(const WhileExpressionAST* expression);

    irb::Value* codegenVariableDeclaration(const VariableDeclarationExpressionAST* expression);

    irb::Value* codegenSubscriptExpression(const SubscriptExpressionAST* expression);

    irb::Value* codegenMemberAccessExpression(const MemberAccessExpressionAST* expression);

    irb::Value* codegenStructureDefinition(const StructureDefinitionAST* expression);

    irb::Value* codegenEnumDefinition(const EnumDefinitionAST* expression);

    irb::Value* codegenEnumValueExpression(const EnumValueExpressionAST* expression);

    irb::Value* codegenInitializerListExpression(const InitializerListExpressionAST* expression);

    irb::Value* codegenDereferenceExpression(const DereferenceExpressionAST* expression);
};

} // namespace lvslang

#endif
