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

The code can be compiled with `lvslang --[desired output] /path/to/your/shader.[metal or lvsl] -o output.[output extension]`. This would emit SPIRV, but there are other viable backends as well. Use `--help` or `-h` to display all options. Here is an example code:
```c++
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
; Version: 1.6
; Generator: Khronos SPIR-V Tools Assembler; 0
; Bound: 186
; Schema: 0
               OpCapability Shader
               OpCapability Float16
               OpCapability Int8
               OpCapability Int16
               OpExtension "SPV_KHR_8bit_storage"
               OpExtension "SPV_KHR_16bit_storage"
               OpExtension "SPV_AMD_gpu_shader_int16"
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %2 "vertexMain" %3 %4 %5 %gl_Position
               OpEntryPoint Fragment %7 "fragmentMain" %8 %9 %10 %11
               OpExecutionMode %7 OriginUpperLeft

               ; Annotations
               OpMemberDecorate %_struct_12 0 Location 0
               OpMemberDecorate %_struct_12 1 Location 1
               OpMemberDecorate %_struct_12 0 Offset 0
               OpMemberDecorate %_struct_12 1 Offset 8
               OpDecorate %_struct_12 Block
               OpDecorate %4 DescriptorSet 0
               OpDecorate %4 Binding 0
               OpMemberDecorate %_struct_13 0 Offset 0
               OpMemberDecorate %_struct_13 1 Offset 8
               OpDecorate %_struct_13 Block
               OpDecorate %_struct_14 Block
               OpDecorate %5 Location 0
               OpDecorate %gl_Position BuiltIn Position
               OpDecorate %8 Location 0
               OpDecorate %9 DescriptorSet 0
               OpDecorate %9 Binding 1
               OpDecorate %10 DescriptorSet 1
               OpDecorate %10 Binding 0
               OpDecorate %_struct_15 Block
               OpMemberDecorate %_struct_15 0 Location 0

               ; Types, variables and constants
        %int = OpTypeInt 32 1
       %half = OpTypeFloat 16
     %v4half = OpTypeVector %half 4
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
    %v4float = OpTypeVector %float 4
 %_struct_14 = OpTypeStruct %v4float %v2float
 %_struct_12 = OpTypeStruct %v2float %v2float
 %_struct_13 = OpTypeStruct %v2float %v2float
       %void = OpTypeVoid
         %44 = OpTypeFunction %void
%_ptr_Input__struct_12 = OpTypePointer Input %_struct_12
          %3 = OpVariable %_ptr_Input__struct_12 Input
%_ptr_Uniform__struct_13 = OpTypePointer Uniform %_struct_13
          %4 = OpVariable %_ptr_Uniform__struct_13 Uniform
%_ptr_Output__struct_14 = OpTypePointer Output %_struct_14
          %5 = OpVariable %_ptr_Output__struct_14 Output
%_ptr_Output_v4float = OpTypePointer Output %v4float
%gl_Position = OpVariable %_ptr_Output_v4float Output
      %int_0 = OpConstant %int 0
    %float_0 = OpConstant %float 0
    %float_1 = OpConstant %float 1
 %_struct_15 = OpTypeStruct %v4float
         %56 = OpTypeImage %half 2D 0 0 0 1 Unknown
         %58 = OpTypeSampler
%_ptr_Input__struct_14 = OpTypePointer Input %_struct_14
          %8 = OpVariable %_ptr_Input__struct_14 Input
%_ptr_UniformConstant_56 = OpTypePointer UniformConstant %56
          %9 = OpVariable %_ptr_UniformConstant_56 UniformConstant
%_ptr_UniformConstant_58 = OpTypePointer UniformConstant %58
         %10 = OpVariable %_ptr_UniformConstant_58 UniformConstant
%_ptr_Output__struct_15 = OpTypePointer Output %_struct_15
         %11 = OpVariable %_ptr_Output__struct_15 Output
         %66 = OpTypeSampledImage %56
%_ptr_Input_v2float = OpTypePointer Input %v2float
       %uint = OpTypeInt 32 0
     %uint_1 = OpConstant %uint 1

               ; Function 2
          %2 = OpFunction %void None %44
         %67 = OpLabel
         %70 = OpLoad %_struct_12 %3
         %71 = OpLoad %_struct_13 %4
        %132 = OpCompositeExtract %v2float %71 0
        %134 = OpCompositeExtract %v2float %70 0
        %136 = OpCompositeExtract %v2float %71 1
        %138 = OpExtInst %v2float %1 Fma %134 %136 %132
        %139 = OpCompositeExtract %float %138 0
        %140 = OpCompositeExtract %float %138 1
        %141 = OpCompositeConstruct %v4float %139 %140 %float_0 %float_1
        %144 = OpCompositeExtract %v2float %70 1
        %179 = OpCompositeConstruct %_struct_14 %141 %144
               OpStore %5 %179
         %74 = OpAccessChain %_ptr_Output_v4float %5 %int_0
         %75 = OpLoad %v4float %74
               OpStore %gl_Position %75
               OpReturn
               OpFunctionEnd

               ; Function 7
          %7 = OpFunction %void None %44
         %96 = OpLabel
        %184 = OpAccessChain %_ptr_Input_v2float %8 %uint_1
        %185 = OpLoad %v2float %184
        %101 = OpLoad %56 %9
        %102 = OpLoad %58 %10
        %154 = OpSampledImage %66 %101 %102
        %155 = OpImageSampleExplicitLod %v4half %154 %185 Lod %float_0
        %156 = OpCompositeExtract %half %155 0
        %157 = OpFConvert %float %156
        %158 = OpCompositeExtract %half %155 1
        %159 = OpFConvert %float %158
        %160 = OpCompositeExtract %half %155 2
        %161 = OpFConvert %float %160
        %162 = OpCompositeExtract %half %155 3
        %163 = OpFConvert %float %162
        %164 = OpCompositeConstruct %v4float %157 %159 %161 %163
        %180 = OpCompositeConstruct %_struct_15 %164
               OpStore %11 %180
               OpReturn
               OpFunctionEnd
```

AIR:
```ll
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%VertexOut = type { <4 x float>, <2 x float> }
%VertexIn = type { <2 x float>, <2 x float> }
%Model = type { <2 x float>, <2 x float> }
%FragmentOut = type { <4 x float> }

; Function Attrs: convergent mustprogress nofree nounwind willreturn
declare <4 x half> @air.sample_texture_2d.v4f16(ptr addrspace(1) nocapture readonly, ptr addrspace(2) nocapture readonly, <2 x float>, i1, <2 x i32>, i1, float, float, i32) local_unnamed_addr #0

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define %VertexOut @vertexMain.sVertexIn.psModel(%VertexIn %vertexIn, ptr addrspace(2) nocapture noundef readonly "air-buffer-no-alias" %model) local_unnamed_addr #1 {
  %vertexIn.fca.0.extract = extractvalue %VertexIn %vertexIn, 0
  %vertexIn.fca.1.extract = extractvalue %VertexIn %vertexIn, 1
  %_283 = load <2 x float>, ptr addrspace(2) %model, align 4
  %_287 = getelementptr inbounds %Model, ptr addrspace(2) %model, i64 0, i32 1
  %_288 = load <2 x float>, ptr addrspace(2) %_287, align 4
  %op = fmul <2 x float> %vertexIn.fca.0.extract, %_288
  %op0 = fadd <2 x float> %_283, %op
  %1 = shufflevector <2 x float> %op0, <2 x float> poison, <4 x i32> <i32 0, i32 1, i32 poison, i32 poison>
  %_294 = shufflevector <4 x float> %1, <4 x float> <float poison, float poison, float 0.000000e+00, float 1.000000e+00>, <4 x i32> <i32 0, i32 1, i32 6, i32 7>
  %_298.fca.0.insert = insertvalue %VertexOut poison, <4 x float> %_294, 0
  %_298.fca.1.insert = insertvalue %VertexOut %_298.fca.0.insert, <2 x float> %vertexIn.fca.1.extract, 1
  ret %VertexOut %_298.fca.1.insert
}

; Function Attrs: mustprogress nofree nounwind willreturn
define %FragmentOut @fragmentMain.sVertexOut.t1f16.sm(%VertexOut %fragmentIn, ptr addrspace(1) nocapture readonly %colorTexture, ptr addrspace(2) nocapture readonly %colorSampler) local_unnamed_addr #2 {
  %fragmentIn.fca.1.extract = extractvalue %VertexOut %fragmentIn, 1
  %_310 = tail call <4 x half> @air.sample_texture_2d.v4f16(ptr addrspace(1) nocapture readonly %colorTexture, ptr addrspace(2) nocapture readonly %colorSampler, <2 x float> %fragmentIn.fca.1.extract, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %_311 = extractelement <4 x half> %_310, i64 0
  %_312 = fpext half %_311 to float
  %_313 = extractelement <4 x half> %_310, i64 1
  %_314 = fpext half %_313 to float
  %_315 = extractelement <4 x half> %_310, i64 2
  %_316 = fpext half %_315 to float
  %_317 = extractelement <4 x half> %_310, i64 3
  %_318 = fpext half %_317 to float
  %_319 = insertelement <4 x float> undef, float %_312, i64 0
  %_320 = insertelement <4 x float> %_319, float %_314, i64 1
  %_321 = insertelement <4 x float> %_320, float %_316, i64 2
  %_322 = insertelement <4 x float> %_321, float %_318, i64 3
  %_323.fca.0.insert = insertvalue %FragmentOut poison, <4 x float> %_322, 0
  ret %FragmentOut %_323.fca.0.insert
}

attributes #0 = { convergent mustprogress nofree nounwind willreturn }
attributes #1 = { mustprogress nofree norecurse nosync nounwind willreturn }
attributes #2 = { mustprogress nofree nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.vertex = !{!9}
!air.fragment = !{!18}
!air.compile_options = !{!26, !27, !28}
!air.version = !{!29}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @vertexMain.sVertexIn.psModel, !10, !13}
!10 = !{!11, !12}
!11 = !{!"air.position", !"air.arg_type_name", !"<4 x float>", !"air.arg_name", !"pos"}
!12 = !{!"air.vertex_output", !"generated(randomstuff)", !"air.arg_type_name", !"<2 x float>", !"air.arg_name", !"texCoord"}
!13 = !{!14, !15, !16}
!14 = !{i32 0, !"air.vertex_input", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"<2 x float>", !"air.arg_name", !"pos"}
!15 = !{i32 1, !"air.vertex_input", !"air.location_index", i32 1, i32 1, !"air.arg_type_name", !"<2 x float>", !"air.arg_name", !"texCoord"}
!16 = !{i32 2, !"air.buffer", !"air.location_index", i32 0, i32 1, !"air.read", !"air.address_space", i32 2, !"air.struct_type_info", !17, !"air.arg_type_size", i32 16, !"air.arg_type_align_size", i32 8, !"air.arg_type_name", !"ptr addrspace(2)", !"air.arg_name", !"model"}
!17 = !{i32 0, i32 8, i32 0, !"<2 x float>", !"pos", i32 8, i32 8, i32 0, !"<2 x float>", !"scale"}
!18 = !{ptr @fragmentMain.sVertexOut.t1f16.sm, !19, !21}
!19 = !{!20}
!20 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"<4 x float>", !"air.arg_name", !"outColor"}
!21 = !{!22, !23, !24, !25}
!22 = !{i32 0, !"air.position", !"air.center", !"air.no_perspective", !"air.arg_type_name", !"<4 x float>", !"air.arg_name", !"pos"}
!23 = !{i32 1, !"air.fragment_input", !"generated(randomstuff)", !"air.center", !"air.perspective", !"air.arg_type_name", !"<2 x float>", !"air.arg_name", !"texCoord"}
!24 = !{i32 2, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"ptr addrspace(1)", !"air.arg_name", !"colorTexture"}
!25 = !{i32 3, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"ptr addrspace(2)", !"air.arg_name", !"colorSampler"}
!26 = !{!"air.compile.denorms_disable"}
!27 = !{!"air.compile.fast_math_disable"}
!28 = !{!"air.compile.framebuffer_fetch_enable"}
!29 = !{i32 2, i32 6, i32 0}
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

fragment FragmentOut fragmentMain(VertexOut fragmentIn [[stage_in]], texture2d<half> colorTexture [[texture(0)]], sampler colorSampler [[sampler(0)]]) {
	FragmentOut fragmentOut;
	fragmentOut.outColor = float4(colorTexture.sample(colorSampler, fragmentIn.texCoord));
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

FragmentOut fragmentMain(VertexOut fragmentIn, Texture2D<min16float> colorTexture, SamplerState colorSampler);

Texture2D<min16float> colorTexture : register(t0);

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

FragmentOut fragmentMain(VertexOut fragmentIn, Texture2D<min16float> colorTexture, SamplerState colorSampler) {
	FragmentOut fragmentOut;
	fragmentOut.outColor = float4(colorTexture.SampleLevel(colorSampler, fragmentIn.texCoord, 0.0f));
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
	fragmentOut.outColor = vec4(texture(sampler2D(colorTexture, colorSampler), fragmentIn.texCoord));
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
