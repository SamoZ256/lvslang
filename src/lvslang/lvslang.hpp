#ifndef LVSLANG_H
#define LVSLANG_H

#include "spirv-tools/libspirv.hpp"
#include "spirv-tools/optimizer.hpp"

#ifdef LVSLANG_USE_LLVM
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#endif

#include "frontends/lvsl/parser.hpp"
#include "frontends/metal/parser.hpp"

namespace lvslang {

enum class OptimizationLevel {
    None,
    O1,
    O2,
    O3,
    Os
};

struct CompileOptions {
    std::string source;
    std::string inputName;
    std::string outputName;
    irb::Target target = irb::Target::None;
    irb::SPIRVVersion spirvVersion = irb::SPIRVVersion::_1_4;
    GLSLVersion glslVersion = GLSLVersion::_3_30;
    bool outputAssembly = false;
    OptimizationLevel optimizationLevel = OptimizationLevel::O2;
};

bool compile(const CompileOptions& options, std::string& outputCode) {
    irb::target = options.target;
    irb::spirvVersion = options.spirvVersion;
    lvslang::glslVersion = options.glslVersion;

    setSource(options.source);

    switch (irb::target) {
    case irb::Target::None:
        IRB_ERROR("No target specified");
        break;
    case irb::Target::Metal:
        context.codeHeader = "#include <metal_stdlib>\nusing namespace metal;";
        break;
    case irb::Target::GLSL:
        context.codeHeader = "#version " + getGLSLVersionString()/* + " core"*/;
        break;
    case irb::Target::HLSL:
        //TODO: add something here?
        break;
    case irb::Target::SPIRV:
        builder = new irb::SPIRVBuilder(context, true);
        break;
    case irb::Target::AIR:
        //TODO: support other data layouts as well
        //TODO: target triple should be omitted so as to prevent llvm-opt errors
        context.codeHeader = \
        "source_filename = \"" + options.inputName + "\"\n" \
        "target datalayout = \"e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32\"\n" \
        "target triple = \"air64-apple-macosx14.0.0\"";
        builder = new irb::AIRBuilder(context, true);
        break;
    default:
        LVSLANG_ERROR_UNSUPPORTED_TARGET("Unknown");
        break;
    }

    //Extensions
    //TODO: enable them only if needed
    enableExtension(irb::Extension::_8bit_storage);
    enableExtension(irb::Extension::_16bit_storage);
    enableExtension(irb::Extension::explicit_arithmetic_types);

    if (irb::target == irb::Target::SPIRV) {
        builder->opImportSTD_EXT("GLSL.std.450");
        builder->opMemoryModel();
    }

    std::string extension = options.inputName.substr(options.inputName.find_last_of('.'));
    if (extension == ".lvsl")
        lvsl::compile();
    else if (extension == ".metal")
        metal::compile();
    else
        throw std::runtime_error("unsupported output file extension '" + extension + "'");

    if (irb::target == irb::Target::AIR)
        static_cast<irb::AIRBuilder*>(builder)->createMetadata();
    std::string code = context.codeHeader + "\n\n" + (TARGET_IS_IR(irb::target) ? builder->getCode() : context.codeMain);
    
    //Assemble and optimize
    if (irb::target == irb::Target::SPIRV) {
        //TODO: uncomment?
        //if (options.optimizationLevel == OptimizationLevel::None && options.outputAssembly) {
        //    outputCode = code;
        //} else {
        spv_target_env targetEnv;
        //TODO: use vulkan env?
        switch (options.spirvVersion) {
        case irb::SPIRVVersion::_1_0:
            targetEnv = SPV_ENV_UNIVERSAL_1_0;
            break;
        case irb::SPIRVVersion::_1_1:
            targetEnv = SPV_ENV_UNIVERSAL_1_1;
            break;
        case irb::SPIRVVersion::_1_2:
            targetEnv = SPV_ENV_UNIVERSAL_1_2;
            break;
        case irb::SPIRVVersion::_1_3:
            targetEnv = SPV_ENV_UNIVERSAL_1_3;
            break;
        case irb::SPIRVVersion::_1_4:
            targetEnv = SPV_ENV_UNIVERSAL_1_4;
            break;
        case irb::SPIRVVersion::_1_5:
            targetEnv = SPV_ENV_UNIVERSAL_1_5;
            break;
        case irb::SPIRVVersion::_1_6:
            targetEnv = SPV_ENV_UNIVERSAL_1_6;
            break;
        default:
            break;
        }

        spvtools::SpirvTools core(targetEnv);
        spvtools::Optimizer opt(targetEnv);

        auto printMsgToStderr = [](spv_message_level_t, const char*, const spv_position_t& pos, const char* m) {
            std::cerr << pos.line << ":" << pos.column << ": error: " << m << std::endl;
        };
        core.SetMessageConsumer(printMsgToStderr);
        opt.SetMessageConsumer(printMsgToStderr);

        std::vector<uint32_t> binary;
        if (!core.Assemble(code, &binary)) {
            LVSLANG_ERROR("spirv assembler failed");
            return false;
        }
        if (!core.Validate(binary)) {
            LVSLANG_ERROR("spirv validator failed");
            return false;
        }

        switch (options.optimizationLevel) {
        case OptimizationLevel::None:
            break;
        //TODO: differentiate between these?
        case OptimizationLevel::O1:
        case OptimizationLevel::O2:
        case OptimizationLevel::O3:
            opt.RegisterPerformancePasses();
            break;
        case OptimizationLevel::Os:
            opt.RegisterSizePasses();
            break;
        }
        if (!opt.Run(binary.data(), binary.size(), &binary)) {
            LVSLANG_ERROR("spirv optimizer failed");
            return false;
        }

        if (options.outputAssembly) {
            if (!core.Disassemble(binary, &outputCode, SPV_BINARY_TO_TEXT_OPTION_INDENT | SPV_BINARY_TO_TEXT_OPTION_FRIENDLY_NAMES | SPV_BINARY_TO_TEXT_OPTION_COMMENT)) {
                LVSLANG_ERROR("spirv disassembler failed");
                return false;
            }
        } else {
            outputCode = std::string((const char*)binary.data(), binary.size() * sizeof(binary[0]) / sizeof(char));
        }
        //}
    } else if (irb::target == irb::Target::AIR) {
#ifdef LVSLANG_USE_LLVM
        llvm::LLVMContext llvmContext;
        std::unique_ptr<llvm::MemoryBuffer> buffer = llvm::MemoryBuffer::getMemBuffer(llvm::StringRef(code));
        llvm::SMDiagnostic error;
        std::unique_ptr<llvm::Module> llvmModule = llvm::parseIR(buffer->getMemBufferRef(), error, llvmContext);

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
        switch (options.optimizationLevel) {
        case OptimizationLevel::None:
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

        //Remove the "memory(argmem: read)" attribute, since xcrun metallib would throw "LLVM ERROR: Invalid bitcode file!"
        for (auto &function : *llvmModule) {
            function.removeFnAttr(llvm::Attribute::AttrKind::Memory);
        }

        llvm::raw_string_ostream stream(outputCode);
        if (options.outputAssembly) {
            stream << *llvmModule;
            stream.flush();
        } else {
            llvm::WriteBitcodeToFile(*llvmModule, stream);
        }
#else
        if (!options.outputAssembly) {
            LVSLANG_ERROR("cannot output LLVM binary when lvslang wasn't build with LLVM enabled");
            return false;
        }
        if (options.optimizationLevel != OptimizationLevel::None) {
            LVSLANG_WARN("cannot optimize LLVM binary when lvslang wasn't build with LLVM enabled");
        }
        outputCode = code;
#endif
    } else {
        outputCode = code;
    }

    return true;
}

} //namespace lvslang

#endif
