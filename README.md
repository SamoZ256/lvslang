## About The Project

This is a compiler for various shading languages. It compiles into other shading languages (Metal Shading Language, HLSL, GLSL) and bytecodes (SPIRV, AIR).

### Backend status

| SPIRV | Metal AIR | HLSL bytecode | Metal Shading Language | HLSL | GLSL |
| :---: | :-------: | :-----------: | :--------------------: | :--: | :--: |
|  ✅   |    ❔     |      ❌       |           ✅            |  ✅  |  ✅  |

## Getting Started

### Installation

1. Clone the repo
   ```console
   git clone https://github.com/SamoZ256/lvslang.git
   ```
2. Build the project
   ```console
   cd /path/to/lvslang
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

## Usage

The code can be compiled with `lvslang --[desired output] /path/to/your/shader.[metal or lvsl] -o output.[output extension]`. This would emit SPIRV, but there are other viable backends as well. Use `--help`o r `-h` to display all options. Here is an example code:
```rs
struct Model {
    float2 pos;
    float2 scale;
};

struct VertexIn {
    float2 pos [[location(0)]];
    float2 texCoord [[location(1)]];
};

struct VertexOut {
    float4 pos [[position]];
    float2 texCoord;
};

vertex struct VertexOut vertexMain(struct VertexIn vertexIn [[input]],
                                   constant struct Model* model [[descriptor_set(0, 0)]]) {
    struct VertexOut vertexOut;
    vertexOut.pos = float4(model->pos + vertexIn.pos * model->scale, 0.0, 1.0);
    vertexOut.texCoord = vertexIn.texCoord;

    return vertexOut;
};

struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut fragmentMain(struct VertexOut fragmentIn [[input]],
                                         texture2d<half> colorTexture [[descriptor_set(0, 1)]],
                                         sampler colorSampler [[descriptor_set(1, 0)]]) {
    struct FragmentOut fragmentOut;
    fragmentOut.outColor = float4(sample(colorTexture, colorSampler, fragmentIn.texCoord));

    return fragmentOut;
}
```

Here are the outputs for each backend:

SPIRV:
```assembly


; SPIR-V
; Version:   1.0
; Generator: Lvslang; 11
; Bound:     385
; Schema:    0

                      OpCapability Shader
                      OpCapability Float16
                      OpCapability Int8
                      OpCapability Int16
                      OpExtension "SPV_KHR_8bit_storage"
                      OpExtension "SPV_KHR_16bit_storage"
                      OpExtension "SPV_AMD_gpu_shader_int16"
            %import = OpExtInstImport "GLSL.std.450"
                      OpMemoryModel Logical GLSL450
                      OpEntryPoint Vertex %vertexMain0 "vertexMain" %13 %16 %vertexMain_output %position
                      OpEntryPoint Fragment %fragmentMain0 "fragmentMain" %47 %50 %53 %fragmentMain_output
                      OpExecutionMode %fragmentMain0 OriginLowerLeft

; Debug information
                      OpName %vertexMain "vertexMain("
                      OpName %fragmentMain "fragmentMain("

; Annotations (non-debug)
                      OpMemberDecorate %struct_VertexIn 0 Location 0
                      OpMemberDecorate %struct_VertexIn 1 Location 1
                      OpMemberDecorate %struct_VertexIn 0 Offset 0
                      OpMemberDecorate %struct_VertexIn 1 Offset 8
                      OpDecorate %struct_VertexIn Block
                      OpDecorate %16 DescriptorSet 0
                      OpDecorate %16 Binding 0
                      OpMemberDecorate %struct_Model 0 Offset 0
                      OpMemberDecorate %struct_Model 1 Offset 8
                      OpDecorate %struct_Model Block
                      OpDecorate %struct_VertexOut Block
                      OpDecorate %vertexMain_output Location 0
                      OpDecorate %position BuiltIn Position
                      OpDecorate %47 Location 0
                      OpDecorate %50 DescriptorSet 0
                      OpDecorate %50 Binding 1
                      OpDecorate %53 DescriptorSet 1
                      OpDecorate %53 Binding 0
                      OpDecorate %struct_FragmentOut Block
                      OpMemberDecorate %struct_FragmentOut 0 Location 0

; All types, variables, and constants
           %float32 = OpTypeFloat 32                  ; 32-bit float32
     %vec_float32_4 = OpTypeVector %float32 4         ; vector(4) of float32
     %vec_float32_2 = OpTypeVector %float32 2         ; vector(2) of float32
  %struct_VertexOut = OpTypeStruct %vec_float32_4 %vec_float32_2; VertexOut
   %struct_VertexIn = OpTypeStruct %vec_float32_2 %vec_float32_2; VertexIn
%ptr_Function_struct_VertexIn = OpTypePointer Function %struct_VertexIn; struct_VertexIn*
      %struct_Model = OpTypeStruct %vec_float32_2 %vec_float32_2; Model
%ptr_Function_struct_Model = OpTypePointer Function %struct_Model; struct_Model*
%func_struct_VertexOut_ptr_Function_struct_VertexIn_ptr_Function_struct_Model = OpTypeFunction %struct_VertexOut %ptr_Function_struct_VertexIn %ptr_Function_struct_Model; struct_VertexOut (ptr_Function_struct_VertexIn, ptr_Function_struct_Model)
              %void = OpTypeVoid                      ; 0-bit void
         %func_void = OpTypeFunction %void            ; void ()
%ptr_Input_struct_VertexIn = OpTypePointer Input %struct_VertexIn; struct_VertexIn*
                %13 = OpVariable %ptr_Input_struct_VertexIn Input
%ptr_Uniform_struct_Model = OpTypePointer Uniform %struct_Model; struct_Model*
                %16 = OpVariable %ptr_Uniform_struct_Model Uniform
%ptr_Output_struct_VertexOut = OpTypePointer Output %struct_VertexOut; struct_VertexOut*
 %vertexMain_output = OpVariable %ptr_Output_struct_VertexOut Output
%ptr_Output_vec_float32_4 = OpTypePointer Output %vec_float32_4; vec_float32_4*
          %position = OpVariable %ptr_Output_vec_float32_4 Output
             %int32 = OpTypeInt 32 1                  ; 32-bit int32
                %21 = OpConstant %int32 0
%ptr_Function_struct_VertexOut = OpTypePointer Function %struct_VertexOut; struct_VertexOut*
%ptr_Function_vec_float32_4 = OpTypePointer Function %vec_float32_4; vec_float32_4*
%ptr_Function_vec_float32_2 = OpTypePointer Function %vec_float32_2; vec_float32_2*
                %31 = OpConstant %int32 1
            %const5 = OpConstant %float32 0.000000
            %const7 = OpConstant %float32 1.000000
%struct_FragmentOut = OpTypeStruct %vec_float32_4     ; FragmentOut
 %texture_1_float32 = OpTypeImage %float32 2D 0 0 0 1 Unknown; image
%ptr_Function_texture_1_float32 = OpTypePointer Function %texture_1_float32; texture_1_float32*
           %sampler = OpTypeSampler                   ; sampler
%ptr_Function_sampler = OpTypePointer Function %sampler; sampler*
%func_struct_FragmentOut_ptr_Function_struct_VertexOut_ptr_Function_texture_1_float32_ptr_Function_sampler = OpTypeFunction %struct_FragmentOut %ptr_Function_struct_VertexOut %ptr_Function_texture_1_float32 %ptr_Function_sampler; struct_FragmentOut (ptr_Function_struct_VertexOut, ptr_Function_texture_1_float32, ptr_Function_sampler)
%ptr_Input_struct_VertexOut = OpTypePointer Input %struct_VertexOut; struct_VertexOut*
                %47 = OpVariable %ptr_Input_struct_VertexOut Input
%ptr_UniformConstant_texture_1_float32 = OpTypePointer UniformConstant %texture_1_float32; texture_1_float32*
                %50 = OpVariable %ptr_UniformConstant_texture_1_float32 UniformConstant
%ptr_UniformConstant_sampler = OpTypePointer UniformConstant %sampler; sampler*
                %53 = OpVariable %ptr_UniformConstant_sampler UniformConstant
%ptr_Output_struct_FragmentOut = OpTypePointer Output %struct_FragmentOut; struct_FragmentOut*
%fragmentMain_output = OpVariable %ptr_Output_struct_FragmentOut Output
%ptr_Function_struct_FragmentOut = OpTypePointer Function %struct_FragmentOut; struct_FragmentOut*
  %sampledImageType = OpTypeSampledImage %texture_1_float32

; All functions
       %vertexMain0 = OpFunction %void None %func_void; %vertexMain0

                %12 = OpLabel
                %14 = OpVariable %ptr_Function_struct_VertexIn Function
                %17 = OpVariable %ptr_Function_struct_Model Function
                %15 = OpLoad %struct_VertexIn %13
                      OpStore %14 %15
                %18 = OpLoad %struct_Model %16
                      OpStore %17 %18
                %20 = OpFunctionCall %struct_VertexOut %vertexMain %14 %17
                      OpStore %vertexMain_output %20
                %22 = OpAccessChain %ptr_Output_vec_float32_4 %vertexMain_output %21
                %23 = OpLoad %vec_float32_4 %22
                      OpStore %position %23
                      OpReturn

                      OpFunctionEnd


        %vertexMain = OpFunction %struct_VertexOut None %func_struct_VertexOut_ptr_Function_struct_VertexIn_ptr_Function_struct_Model; %vertexMain
          %vertexIn = OpFunctionParameter %ptr_Function_struct_VertexIn
             %model = OpFunctionParameter %ptr_Function_struct_Model

                %25 = OpLabel
         %vertexOut = OpVariable %ptr_Function_struct_VertexOut Function
                %26 = OpAccessChain %ptr_Function_vec_float32_4 %vertexOut %21
                %27 = OpAccessChain %ptr_Function_vec_float32_2 %model %21
                %28 = OpLoad %vec_float32_2 %27
                %29 = OpAccessChain %ptr_Function_vec_float32_2 %vertexIn %21
                %30 = OpLoad %vec_float32_2 %29
                %32 = OpAccessChain %ptr_Function_vec_float32_2 %model %31
                %33 = OpLoad %vec_float32_2 %32
                %op = OpFMul %vec_float32_2 %30 %33
               %op0 = OpFAdd %vec_float32_2 %28 %op
                %34 = OpCompositeExtract %float32 %op0 0
                %35 = OpCompositeExtract %float32 %op0 1
      %const_vector = OpCompositeConstruct %vec_float32_4 %34 %35 %const5 %const7
                      OpStore %26 %const_vector
                %36 = OpAccessChain %ptr_Function_vec_float32_2 %vertexOut %31
                %37 = OpAccessChain %ptr_Function_vec_float32_2 %vertexIn %31
                %38 = OpLoad %vec_float32_2 %37
                      OpStore %36 %38
                %39 = OpLoad %struct_VertexOut %vertexOut
                      OpReturnValue %39

                      OpFunctionEnd


     %fragmentMain0 = OpFunction %void None %func_void; %fragmentMain0

                %46 = OpLabel
                %48 = OpVariable %ptr_Function_struct_VertexOut Function
                %51 = OpVariable %ptr_Function_texture_1_float32 Function
                %54 = OpVariable %ptr_Function_sampler Function
                %49 = OpLoad %struct_VertexOut %47
                      OpStore %48 %49
                %52 = OpLoad %texture_1_float32 %50
                      OpStore %51 %52
                %55 = OpLoad %sampler %53
                      OpStore %54 %55
                %57 = OpFunctionCall %struct_FragmentOut %fragmentMain %48 %51 %54
                      OpStore %fragmentMain_output %57
                      OpReturn

                      OpFunctionEnd


      %fragmentMain = OpFunction %struct_FragmentOut None %func_struct_FragmentOut_ptr_Function_struct_VertexOut_ptr_Function_texture_1_float32_ptr_Function_sampler; %fragmentMain
        %fragmentIn = OpFunctionParameter %ptr_Function_struct_VertexOut
      %colorTexture = OpFunctionParameter %ptr_Function_texture_1_float32
      %colorSampler = OpFunctionParameter %ptr_Function_sampler

                %59 = OpLabel
       %fragmentOut = OpVariable %ptr_Function_struct_FragmentOut Function
                %60 = OpAccessChain %ptr_Function_vec_float32_4 %fragmentOut %21
                %61 = OpLoad %texture_1_float32 %colorTexture
                %62 = OpLoad %sampler %colorSampler
                %63 = OpAccessChain %ptr_Function_vec_float32_2 %fragmentIn %31
                %64 = OpLoad %vec_float32_2 %63
     %samplerTexTmp = OpSampledImage %sampledImageType %61 %62
                %65 = OpImageSampleExplicitLod %vec_float32_4 %samplerTexTmp %64 Lod %const5
                      OpStore %60 %65
                %66 = OpLoad %struct_FragmentOut %fragmentOut
                      OpReturnValue %66

                      OpFunctionEnd
```

AIR:
```ll
source_filename = "example.metal"
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%Model = type { <2 x float>, <2 x float> }

%VertexIn = type { <2 x float>, <2 x float> }

%VertexOut = type { <4 x float>, <2 x float> }

define %VertexOut @vertexMain(%VertexIn noundef %vertexIn, ptr addrspace(2) noundef %model) {
	%_4 = alloca %VertexIn, align 4
	store %VertexIn %vertexIn, ptr %_4, align 4
	%_5 = alloca ptr addrspace(2), align 4
	store ptr addrspace(2) %model, ptr %_5, align 4
	%vertexOut = alloca %VertexOut, align 4

	%_7 = getelementptr inbounds %VertexOut, ptr %vertexOut, i32 0
	%_8 = load ptr addrspace(2), ptr %_5, align 4
	%_9 = getelementptr inbounds %Model, ptr addrspace(2) %_8, i32 0
	%_10 = load <2 x float>, ptr addrspace(2) %_9, align 4
	%_11 = getelementptr inbounds %VertexIn, ptr %_4, i32 0
	%_12 = load <2 x float>, ptr %_11, align 4
	%_13 = load ptr addrspace(2), ptr %_5, align 4
	%_14 = getelementptr inbounds %Model, ptr addrspace(2) %_13, i32 1
	%_15 = load <2 x float>, ptr addrspace(2) %_14, align 4
	%op = fmul <2 x float> %_12, %_15
	%op0 = fadd <2 x float> %_10, %op
	%_16 = extractelement <2 x float> %op0, i32 0
	%_17 = extractelement <2 x float> %op0, i32 1
	%_18 = insertelement <4 x float> undef, float %_16, i32 0
	%_19 = insertelement <4 x float> %_18, float %_17, i32 1
	%_20 = insertelement <4 x float> %_19, float 0x0, i32 2
	%_21 = insertelement <4 x float> %_20, float 0x3ff0000000000000, i32 3
	store <4 x float> %_21, ptr %_7, align 4
	%_22 = getelementptr inbounds %VertexOut, ptr %vertexOut, i32 1
	%_23 = getelementptr inbounds %VertexIn, ptr %_4, i32 1
	%_24 = load <2 x float>, ptr %_23, align 4
	store <2 x float> %_24, ptr %_22, align 4
	%_25 = load %VertexOut, ptr %vertexOut, align 4
	ret %VertexOut %_25
}

%FragmentOut = type { <4 x float> }

declare <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1), ptr addrspace(2), <2 x float>, i1, <2 x i32>, i1, float, float, i32);

define %FragmentOut @fragmentMain(%VertexOut noundef %fragmentIn, ptr addrspace(1) %colorTexture, ptr addrspace(2) %colorSampler) {
	%_28 = alloca %VertexOut, align 4
	store %VertexOut %fragmentIn, ptr %_28, align 4
	%_29 = alloca ptr addrspace(1), align 4
	store ptr addrspace(1) %colorTexture, ptr %_29, align 4
	%_30 = alloca ptr addrspace(2), align 4
	store ptr addrspace(2) %colorSampler, ptr %_30, align 4
	%fragmentOut = alloca %FragmentOut, align 4

	%_32 = getelementptr inbounds %FragmentOut, ptr %fragmentOut, i32 0
	%_33 = load ptr addrspace(1), ptr %_29, align 4
	%_34 = load ptr addrspace(2), ptr %_30, align 4
	%_35 = getelementptr inbounds %VertexOut, ptr %_28, i32 1
	%_36 = load <2 x float>, ptr %_35, align 4
	%_37 = call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) %_33, ptr addrspace(2) %_34, <2 x float> %_36, i1 1, <2 x i32> <i32 0, i32 0>, i1 0, float 0x0, float 0x0, i32 0)
	store <4 x float> %_37, ptr %_32, align 4
	%_38 = load %FragmentOut, ptr %fragmentOut, align 4
	ret %FragmentOut %_38
}


!llvm.module.flags = !{!40, !41, !42, !43, !44, !45, !46, !47, !48}
!air.vertex = !{!49}
!air.fragment = !{!58}
!air.compile_options = !{!66, !67, !68}
!llvm.ident = !{!69}
!air.version = !{!70}
!air.language_version = !{!71}
!air.source_file_name = !{!72}

!40 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!41 = !{i32 1, !"wchar_size", i32 4}
!42 = !{i32 7, !"frame-pointer", i32 2}
!43 = !{i32 7, !"air.max_device_buffers", i32 31}
!44 = !{i32 7, !"air.max_constant_buffers", i32 31}
!45 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!46 = !{i32 7, !"air.max_textures", i32 128}
!47 = !{i32 7, !"air.max_read_write_textures", i32 8}
!48 = !{i32 7, !"air.max_samplers", i32 16}
!49 = !{ptr @vertexMain, !50, !51}
!50 = !{!52, !53}
!51 = !{!54, !55, !56}
!52 = !{!"air.position", !"air.arg_type_name", !"<4 x float>", !"air.arg_name", !"pos"}
!53 = !{!"air.vertex_output", !"generated(randomstuff)", !"air.arg_type_name", !"<2 x float>", !"air.arg_name", !"texCoord"}
!54 = !{i32 0, !"air.vertex_input", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"<2 x float>", !"air.arg_name", !"pos"}
!55 = !{i32 1, !"air.vertex_input", !"air.location_index", i32 1, i32 1, !"air.arg_type_name", !"<2 x float>", !"air.arg_name", !"texCoord"}
!56 = !{i32 2, !"air.buffer", !"air.location_index", i32 0, i32 1, !"air.read", !"air.address_space", i32 2, !"air.struct_type_info", !57, !"air.arg_type_size", i32 16, !"air.arg_type_align_size", i32 8, !"air.arg_type_name", !"ptr addrspace(2)", !"air.arg_name", !"model"}
!57 = !{i32 0, i32 8, i32 0, !"<2 x float>", !"pos", i32 8, i32 8, i32 0, !"<2 x float>", !"scale"}
!58 = !{ptr @fragmentMain, !59, !60}
!59 = !{!61}
!60 = !{!62, !63, !64, !65}
!61 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"<4 x float>", !"air.arg_name", !"outColor"}
!62 = !{i32 0, !"air.position", !"air.center", !"air.no_perspective", !"air.arg_type_name", !"<4 x float>", !"air.arg_name", !"pos"}
!63 = !{i32 1, !"air.fragment_input", !"generated(randomstuff)", !"air.center", !"air.perspective", !"air.arg_type_name", !"<2 x float>", !"air.arg_name", !"texCoord"}
!64 = !{i32 2, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"ptr addrspace(1)", !"air.arg_name", !"colorTexture"}
!65 = !{i32 3, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"ptr addrspace(2)", !"air.arg_name", !"colorSampler"}
!66 = !{!"air.compile.denorms_disable"}
!67 = !{!"air.compile.fast_math_disable"}
!68 = !{!"air.compile.framebuffer_fetch_enable"}
!69 = !{!"Lvslang"}
!70 = !{i32 2, i32 6, i32 0}
!71 = !{!"LVSL", i32 0, i32 7, i32 0}
!72 = !{!"/Users/samuliak/Desktop/lvslang/test.lvsl"}
```

Metal Shading Language:
```c++
#include <metal_stdlib>
using namespace metal;

struct Model {
	float2 pos;
	float2 scale;
};

struct VertexIn {
	float2 pos [[attribute(0)]];
	float2 texCoord [[attribute(1)]];
};

struct VertexOut {
	float4 pos [[position]];
	float2 texCoord;
};

vertex VertexOut vertexMain(VertexIn vertexIn [[stage_in]], constant Model* model [[buffer(0)]]) {
	VertexOut vertexOut;
	vertexOut.pos = float4(((*model).pos + (vertexIn.pos * (*model).scale)), 0.000000, 1.000000);
	vertexOut.texCoord = vertexIn.texCoord;
	return vertexOut;
}

struct FragmentOut {
	float4 outColor [[color(0)]];
};

fragment FragmentOut fragmentMain(VertexOut fragmentIn [[stage_in]], texture2d<float> colorTexture [[texture(0)]], sampler colorSampler [[sampler(0)]]) {
	FragmentOut fragmentOut;
	fragmentOut.outColor = colorTexture.sample(colorSampler, fragmentIn.texCoord);
	return fragmentOut;
}
```

HLSL:
```c++
struct Model {
	float2 pos;
	float2 scale;
};

struct VertexIn {
	float2 pos : TEXCOORD0;
	float2 texCoord : TEXCOORD1;
};

struct VertexOut {
	float4 pos;
	float2 texCoord;
};

VertexOut vertexMain(VertexIn vertexIn, Model model);

cbuffer model_Uniform : register(b0) {
	Model model;
};

struct VertexOut_Output {
	VertexOut output : TEXCOORD0;
	float4 position : SV_Position;
};

VertexOut_Output _vertexMain(VertexIn vertexIn) {
	//Entry point call
	VertexOut _entryPointOutput = vertexMain(vertexIn, model);

	//Output
	VertexOut_Output __output;
	__output.output = _entryPointOutput;
	__output.position = _entryPointOutput.pos;

	return __output;
}

VertexOut vertexMain(VertexIn vertexIn, Model model) {
	VertexOut vertexOut;
	vertexOut.pos = float4((model.pos + (vertexIn.pos * model.scale)), 0.000000, 1.000000);
	vertexOut.texCoord = vertexIn.texCoord;
	return vertexOut;
}

struct FragmentOut {
	float4 outColor : SV_Target0;
};

FragmentOut fragmentMain(VertexOut fragmentIn, Texture2D colorTexture, SamplerState colorSampler);

Texture2D colorTexture : register(t0);

SamplerState colorSampler : register(s0);

struct FragmentOut_Output {
	FragmentOut output : TEXCOORD0;
};

FragmentOut_Output _fragmentMain(VertexOut fragmentIn) {
	//Entry point call
	FragmentOut _entryPointOutput = fragmentMain(fragmentIn, colorTexture, colorSampler);

	//Output
	FragmentOut_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

FragmentOut fragmentMain(VertexOut fragmentIn, Texture2D colorTexture, SamplerState colorSampler) {
	FragmentOut fragmentOut;
	fragmentOut.outColor = colorTexture.SampleLevel(colorSampler, fragmentIn.texCoord, 0.0f);
	return fragmentOut;
}
```

GLSL:
```c++
#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct Model {
	vec2 pos;
	vec2 scale;
};

struct VertexIn {
	vec2 pos;
	vec2 texCoord;
};

struct VertexOut {
	vec4 pos;
	vec2 texCoord;
};

VertexOut vertexMain(VertexIn vertexIn, Model model);

layout (location = 0) in vec2 pos;

layout (location = 1) in vec2 texCoord;

layout (set = 0, binding = 0) uniform model_Uniform {
	Model model;
};

layout (location = 0) out VertexOut_Output {
	VertexOut _output;
} _output;

void main() {
	//Input
	VertexIn vertexIn;
	vertexIn.pos = pos;
	vertexIn.texCoord = texCoord;

	//Entry point call
	VertexOut _entryPointOutput = vertexMain(vertexIn, model);

	//Output
	gl_Position = _entryPointOutput.pos;
	_output._output.pos = _entryPointOutput.pos;
	_output._output.texCoord = _entryPointOutput.texCoord;
}

VertexOut vertexMain(VertexIn vertexIn, Model model) {
	VertexOut vertexOut;
	vertexOut.pos = vec4((model.pos + (vertexIn.pos * model.scale)), 0.000000, 1.000000);
	vertexOut.texCoord = vertexIn.texCoord;
	return vertexOut;
}

struct FragmentOut {
	vec4 outColor;
};

FragmentOut fragmentMain(VertexOut fragmentIn, texture2D colorTexture, sampler colorSampler);

layout (location = 0) in VertexOut_Input {
	VertexOut fragmentIn;
};

layout (set = 0, binding = 1) uniform texture2D colorTexture;

layout (set = 1, binding = 0) uniform sampler colorSampler;

layout (location = 0) out vec4 outColor;

void main() {
	//Input

	//Entry point call
	FragmentOut _entryPointOutput = fragmentMain(fragmentIn, colorTexture, colorSampler);

	//Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut fragmentMain(VertexOut fragmentIn, texture2D colorTexture, sampler colorSampler) {
	FragmentOut fragmentOut;
	fragmentOut.outColor = texture(sampler2D(colorTexture, colorSampler), fragmentIn.texCoord);
	return fragmentOut;
}
```

Note that the GLSL output won't compile, since it contains more than one entry point.

## Features

* Metal frontend
* Vertex shaders
* Fragment shaders
* Buffers
* Textures
* Samplers (without template arguments)
* Shader inputs and outputs

See the [open issues](https://github.com/SamoZ256/lvslang/issues) for a full list of proposed features (and known issues).

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

## Contact

Samuel Žúbor - samuliak77@gmail.com

Project Link: [https://github.com/SamoZ256/lvslang](https://github.com/SamoZ256/lvslang)
