## About The Project

This is a compiler for the Lava Shading Language (LVSL). It compiles into other shading languages (GLSL, Metal Shading Language) and bytecodes (SPIRV, AIR).

### Backend status

| SPIRV | Metal AIR | HLSL bytecode | Metal Shading Language | HLSL | GLSL |
| :---: | :-------: | :-----------: | :--------------------: | :--: | :--: |
|  ✅   |    ❔     |      ❌       |           ✅            |  ❌  |  ✅  |

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

The code can be compiled with `lvslang --spirv /path/to/your/shader.lvsl -o output.spvasm`. This would emit SPIRV, but there are other viable backends as well. Use `--help` to display all options (not working right now). Here is an example code:
```rs
struct BufferContents {
    member cameraPos: float3
    member color: half4
}

struct VertexOut {
    member pos: float4 [[position]]
    member color: float3
}

entry_point vertexMain(myBuffer: constant buffer struct BufferContents* [[descriptor_set(0, 0)]],
                       myTexture: texture2D<float> [[descriptor_set(0, 1)]],
                       mySampler: sampler [[descriptor_set(1, 0)]]) -> struct VertexOut [[output]] {
    var coords: float2
    var sampled = sample(myTexture, mySampler, coords)
    
    var vertexOut: struct VertexOut
    vertexOut.pos = sampled
    vertexOut.color = sampled.xxw

    return vertexOut
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
           %_import = OpExtInstImport "GLSL.std.450"
                      OpMemoryModel Logical GLSL450
                      OpEntryPoint Vertex %_vertexMain "vertexMain" %_vertexMain_output %_position %_vertexIn %_model
                      OpEntryPoint Fragment %_fragmentMain "fragmentMain" %_fragmentMain_output %_fragmentIn %_colorTexture %_colorSampler
                      OpExecutionMode %_fragmentMain OriginLowerLeft

; Debug information
                      OpName %_vertexMain "vertexMain("
                      OpName %_fragmentMain "fragmentMain("

; Annotations (non-debug)
                      OpMemberDecorate %_struct_VertexOut 0 Offset 0
                      OpMemberDecorate %_struct_VertexOut 1 Offset 16
                      OpDecorate %_struct_VertexOut Block
                      OpDecorate %_vertexMain_output Location 0
                      OpDecorate %_position BuiltIn Position
                      OpMemberDecorate %_struct_VertexIn 0 Location 0
                      OpMemberDecorate %_struct_VertexIn 1 Location 1
                      OpMemberDecorate %_struct_VertexIn 0 Offset 0
                      OpMemberDecorate %_struct_VertexIn 0 Location 0
                      OpMemberDecorate %_struct_VertexIn 1 Offset 8
                      OpMemberDecorate %_struct_VertexIn 1 Location 1
                      OpDecorate %_struct_VertexIn Block
                      OpDecorate %_model DescriptorSet 0
                      OpDecorate %_model Binding 0
                      OpMemberDecorate %_struct_VertexIn 0 Offset 0
                      OpMemberDecorate %_struct_VertexIn 1 Offset 8
                      OpDecorate %_struct_VertexIn Block
                      OpMemberDecorate %_struct_FragmentOut 0 Offset 0
                      OpDecorate %_struct_FragmentOut Block
                      OpDecorate %_fragmentIn Location 0
                      OpDecorate %_colorTexture DescriptorSet 0
                      OpDecorate %_colorTexture Binding 1
                      OpDecorate %_colorSampler DescriptorSet 1
                      OpDecorate %_colorSampler Binding 0
                      OpMemberDecorate %_struct_FragmentOut 0 Location 0

; All types, variables, and constants
          %_float32 = OpTypeFloat 32                  ; 32-bit float32
    %_vec_float32_4 = OpTypeVector %_float32 4        ; vector(4) of float32
    %_vec_float32_2 = OpTypeVector %_float32 2        ; vector(2) of float32
 %_struct_VertexOut = OpTypeStruct %_vec_float32_4 %_vec_float32_2; VertexOut
%_ptr_Output_struct_VertexOut = OpTypePointer Output %_struct_VertexOut; struct_VertexOut*
%_vertexMain_output = OpVariable %_ptr_Output_struct_VertexOut Output
%_ptr_Output_vec_float32_4 = OpTypePointer Output %_vec_float32_4; vec_float32_4*
         %_position = OpVariable %_ptr_Output_vec_float32_4 Output
             %_void = OpTypeVoid                      ; 0-bit void, sign-less
        %_func_void = OpTypeFunction %_void           ; void ()
  %_struct_VertexIn = OpTypeStruct %_vec_float32_2 %_vec_float32_2; VertexIn
%_ptr_Input_struct_VertexIn = OpTypePointer Input %_struct_VertexIn; struct_VertexIn*
         %_vertexIn = OpVariable %_ptr_Input_struct_VertexIn Input
%_ptr_Uniform_struct_Model = OpTypePointer Uniform %_struct_VertexIn; struct_Model*
            %_model = OpVariable %_ptr_Uniform_struct_Model Uniform
%_ptr_Function_struct_VertexOut = OpTypePointer Function %_struct_VertexOut; struct_VertexOut*
            %_int32 = OpTypeInt 32 1                  ; 32-bit int32
               %_14 = OpConstant %_int32 0
%_ptr_Function_vec_float32_4 = OpTypePointer Function %_vec_float32_4; vec_float32_4*
%_ptr_Uniform_vec_float32_2 = OpTypePointer Uniform %_vec_float32_2; vec_float32_2*
%_ptr_Input_vec_float32_2 = OpTypePointer Input %_vec_float32_2; vec_float32_2*
               %_27 = OpConstant %_int32 1
            %_const = OpConstant %_float32 0.000000
           %_const0 = OpConstant %_float32 1.000000
%_ptr_Function_vec_float32_2 = OpTypePointer Function %_vec_float32_2; vec_float32_2*
%_struct_FragmentOut = OpTypeStruct %_vec_float32_4   ; FragmentOut
%_ptr_Output_struct_FragmentOut = OpTypePointer Output %_struct_FragmentOut; struct_FragmentOut*
%_fragmentMain_output = OpVariable %_ptr_Output_struct_FragmentOut Output
%_ptr_Input_struct_VertexOut = OpTypePointer Input %_struct_VertexOut; struct_VertexOut*
       %_fragmentIn = OpVariable %_ptr_Input_struct_VertexOut Input
%_texture_1_float32 = OpTypeImage %_float32 2D 0 0 0 1 Unknown; image
%_ptr_UniformConstant_texture_1_float32 = OpTypePointer UniformConstant %_texture_1_float32; texture_1_float32*
     %_colorTexture = OpVariable %_ptr_UniformConstant_texture_1_float32 UniformConstant
          %_sampler = OpTypeSampler                   ; sampler
%_ptr_UniformConstant_sampler = OpTypePointer UniformConstant %_sampler; sampler*
     %_colorSampler = OpVariable %_ptr_UniformConstant_sampler UniformConstant
%_ptr_Function_struct_FragmentOut = OpTypePointer Function %_struct_FragmentOut; struct_FragmentOut*
 %_sampledImageType = OpTypeSampledImage %_texture_1_float32

; All functions
       %_vertexMain = OpFunction %_void None %_func_void; %_vertexMain

               %_12 = OpLabel
        %_vertexOut = OpVariable %_ptr_Function_struct_VertexOut Function
               %_15 = OpAccessChain %_ptr_Function_vec_float32_4 %_vertexOut %_14
               %_17 = OpAccessChain %_ptr_Uniform_vec_float32_2 %_model %_14
               %_18 = OpLoad %_vec_float32_2 %_17
               %_20 = OpCompositeExtract %_float32 %_18 0
               %_22 = OpAccessChain %_ptr_Input_vec_float32_2 %_vertexIn %_14
               %_23 = OpLoad %_vec_float32_2 %_22
               %_25 = OpCompositeExtract %_float32 %_23 0
               %_28 = OpAccessChain %_ptr_Uniform_vec_float32_2 %_model %_27
               %_29 = OpLoad %_vec_float32_2 %_28
               %_31 = OpCompositeExtract %_float32 %_29 0
               %_32 = OpFMul %_float32 %_25 %_31
               %_33 = OpFAdd %_float32 %_20 %_32
               %_35 = OpAccessChain %_ptr_Uniform_vec_float32_2 %_model %_14
               %_36 = OpLoad %_vec_float32_2 %_35
               %_38 = OpCompositeExtract %_float32 %_36 1
               %_40 = OpAccessChain %_ptr_Input_vec_float32_2 %_vertexIn %_14
               %_41 = OpLoad %_vec_float32_2 %_40
               %_43 = OpCompositeExtract %_float32 %_41 1
               %_45 = OpAccessChain %_ptr_Uniform_vec_float32_2 %_model %_27
               %_46 = OpLoad %_vec_float32_2 %_45
               %_48 = OpCompositeExtract %_float32 %_46 1
               %_49 = OpFMul %_float32 %_43 %_48
               %_50 = OpFAdd %_float32 %_38 %_49
     %_const_vector = OpCompositeConstruct %_vec_float32_4 %_33 %_50 %_const %_const0
                      OpStore %_15 %_const_vector
               %_54 = OpAccessChain %_ptr_Function_vec_float32_2 %_vertexOut %_27
               %_56 = OpAccessChain %_ptr_Input_vec_float32_2 %_vertexIn %_27
               %_57 = OpLoad %_vec_float32_2 %_56
                      OpStore %_54 %_57
               %_58 = OpLoad %_struct_VertexOut %_vertexOut
               %_60 = OpAccessChain %_ptr_Function_vec_float32_4 %_vertexOut %_14
               %_61 = OpLoad %_vec_float32_4 %_60
                      OpStore %_position %_61
                      OpStore %_vertexMain_output %_58
                      OpReturn

                      OpFunctionEnd


     %_fragmentMain = OpFunction %_void None %_func_void; %_fragmentMain

               %_66 = OpLabel
      %_fragmentOut = OpVariable %_ptr_Function_struct_FragmentOut Function
               %_68 = OpAccessChain %_ptr_Function_vec_float32_4 %_fragmentOut %_14
               %_69 = OpLoad %_texture_1_float32 %_colorTexture
               %_70 = OpLoad %_sampler %_colorSampler
               %_72 = OpAccessChain %_ptr_Input_vec_float32_2 %_fragmentIn %_27
               %_73 = OpLoad %_vec_float32_2 %_72
    %_samplerTexTmp = OpSampledImage %_sampledImageType %_69 %_70
               %_75 = OpImageSampleExplicitLod %_vec_float32_4 %_samplerTexTmp %_73 Lod %_const
                      OpStore %_68 %_75
               %_76 = OpLoad %_struct_FragmentOut %_fragmentOut
                      OpStore %_fragmentMain_output %_76
                      OpReturn

                      OpFunctionEnd
```

AIR:
```ll
source_filename = "test.lvsl"
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%_Model = type { <2 x float>, <2 x float> }

%_VertexIn = type { <2 x float>, <2 x float> }

%_VertexOut = type { <4 x float>, <2 x float> }

define %_VertexOut @vertexMain(%_VertexIn noundef %_vertexIn, ptr addrspace(2) noundef %_model) {
	%_6 = alloca %_VertexIn, align 4
	store %_VertexIn %_vertexIn, ptr %_6, align 4
	%_7 = alloca ptr addrspace(2), align 4
	store ptr addrspace(2) %_model, ptr %_7, align 4
	%_vertexOut = alloca %_VertexOut, align 4

	%_10 = getelementptr inbounds %_VertexOut, ptr %_vertexOut, i32 0
	%_11 = load ptr addrspace(2), ptr %_7, align 4
	%_13 = getelementptr inbounds %_Model, ptr addrspace(2) %_11, i32 0
	%_14 = load <2 x float>, ptr %_13, align 4
	%_16 = extractelement <2 x float> %_14, i32 0
	%_18 = getelementptr inbounds %_VertexIn, ptr %_6, i32 0
	%_19 = load <2 x float>, ptr %_18, align 4
	%_21 = extractelement <2 x float> %_19, i32 0
	%_22 = load ptr addrspace(2), ptr %_7, align 4
	%_24 = getelementptr inbounds %_Model, ptr addrspace(2) %_22, i32 1
	%_25 = load <2 x float>, ptr %_24, align 4
	%_27 = extractelement <2 x float> %_25, i32 0
	%_28 = fmul float %_21, %_27
	%_29 = fadd float %_16, %_28
	%_30 = load ptr addrspace(2), ptr %_7, align 4
	%_32 = getelementptr inbounds %_Model, ptr addrspace(2) %_30, i32 0
	%_33 = load <2 x float>, ptr %_32, align 4
	%_35 = extractelement <2 x float> %_33, i32 1
	%_37 = getelementptr inbounds %_VertexIn, ptr %_6, i32 0
	%_38 = load <2 x float>, ptr %_37, align 4
	%_40 = extractelement <2 x float> %_38, i32 1
	%_41 = load ptr addrspace(2), ptr %_7, align 4
	%_43 = getelementptr inbounds %_Model, ptr addrspace(2) %_41, i32 1
	%_44 = load <2 x float>, ptr %_43, align 4
	%_46 = extractelement <2 x float> %_44, i32 1
	%_47 = fmul float %_40, %_46
	%_48 = fadd float %_35, %_47
	%_52 = insertelement <4 x float> undef, float %_29, i32 0
	%_54 = insertelement <4 x float> %_52, float %_48, i32 1
	%_56 = insertelement <4 x float> %_54, float 0x0, i32 2
	%_58 = insertelement <4 x float> %_56, float 0x3ff0000000000000, i32 3
	store <4 x float> %_58, ptr %_10, align 4
	%_60 = getelementptr inbounds %_VertexOut, ptr %_vertexOut, i32 1
	%_62 = getelementptr inbounds %_VertexIn, ptr %_6, i32 1
	%_63 = load <2 x float>, ptr %_62, align 4
	store <2 x float> %_63, ptr %_60, align 4
	%_64 = load %_VertexOut, ptr %_vertexOut, align 4
	ret %_VertexOut %_64
}

%_FragmentOut = type { <4 x float> }

declare <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1), ptr addrspace(2), <2 x float>, i1, <2 x i32>, i1, float, float, i32);

define %_FragmentOut @fragmentMain(%_VertexOut noundef %_fragmentIn, ptr addrspace(1) %_colorTexture, ptr addrspace(2) %_colorSampler) {
	%_67 = alloca %_VertexOut, align 4
	store %_VertexOut %_fragmentIn, ptr %_67, align 4
	%_68 = alloca ptr addrspace(1), align 4
	store ptr addrspace(1) %_colorTexture, ptr %_68, align 4
	%_69 = alloca ptr addrspace(2), align 4
	store ptr addrspace(2) %_colorSampler, ptr %_69, align 4
	%_fragmentOut = alloca %_FragmentOut, align 4

	%_72 = getelementptr inbounds %_FragmentOut, ptr %_fragmentOut, i32 0
	%_73 = load ptr addrspace(1), ptr %_68, align 4
	%_74 = load ptr addrspace(2), ptr %_69, align 4
	%_76 = getelementptr inbounds %_VertexOut, ptr %_67, i32 1
	%_77 = load <2 x float>, ptr %_76, align 4
	%_85 = call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) %_73, ptr addrspace(2) %_74, <2 x float> %_77, i1 1, <2 x i32> <i32 0, i32 0>, i1 0, float 0x0, float 0x0, i32 0)
	store <4 x float> %_85, ptr %_72, align 4
	%_86 = load %_FragmentOut, ptr %_fragmentOut, align 4
	ret %_FragmentOut %_86
}

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.vertex = !{!9}
!air.compile_options = !{!11, !12, !13}
!llvm.ident = !{!14}
!air.version = !{!15}
!air.language_version = !{!16}
!air.source_file_name = !{!17}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @vertexMain, !10, !10}
!10 = !{}
!11 = !{!"air.compile.denorms_disable"}
!12 = !{!"air.compile.fast_math_enable"}
!13 = !{!"air.compile.framebuffer_fetch_enable"}
!14 = !{!"Apple metal version 32023.35 (metalfe-32023.35)"}
!15 = !{i32 2, i32 6, i32 0}
!16 = !{!"Metal", i32 3, i32 1, i32 0}
!17 = !{!"/Users/samuliak/Desktop/lvslang/test.metal"}
!18 = distinct !{!18, !19}
!19 = !{!"llvm.loop.mustprogress"}
```

GLSL:
```c
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

layout (location = 0) in vec2 pos;

layout (location = 1) in vec2 texCoord;

layout (set = 0, binding = 0) uniform Model_Uniform {
	Model model;
};

layout (location = 0) out VertexOut_Output {
	VertexOut _output;
} _output;

void main() {
	VertexIn vertexIn;
	vertexIn.pos = pos;
	vertexIn.texCoord = texCoord;
	VertexOut vertexOut;
	vertexOut.pos = vec4((model.pos.x + (vertexIn.pos.x * model.scale.x)), (model.pos.y + (vertexIn.pos.y * model.scale.y)), 0.000000, 1.000000);
	vertexOut.texCoord = vertexIn.texCoord;
	
	//Return
	gl_Position = vertexOut.pos;
	_output._output.texCoord = vertexOut.texCoord;
}

struct FragmentOut {
	vec4 color;
};

layout (location = 0) in VertexOut_Input {
	VertexOut fragmentIn;
};

layout (set = 0, binding = 1) uniform texture2D colorTexture;

layout (set = 1, binding = 0) uniform sampler colorSampler;

layout (location = 0) out vec4 color;

void main() {
	FragmentOut fragmentOut;
	fragmentOut.color = texture(sampler2D(colorTexture, colorSampler), fragmentIn.texCoord);
	
	//Return
	color = fragmentOut.color;
}
```

Metal Shading Language:
```c++
#include <metal_stdlib>
using namespace metal;

struct Model {
	vec<float, 2> pos;
	vec<float, 2> scale;
};

struct VertexIn {
	vec<float, 2> pos [[attribute(0)]];
	vec<float, 2> texCoord [[attribute(1)]];
};

struct VertexOut {
	vec<float, 4> pos [[position]];
	vec<float, 2> texCoord;
};

vertex VertexOut vertexMain(VertexIn vertexIn [[stage_in]], constant Model* model [[buffer(0)]]) {
	VertexOut vertexOut;
	vertexOut.pos = vec<float, 4>(((*model).pos.x + (vertexIn.pos.x * (*model).scale.x)), ((*model).pos.y + (vertexIn.pos.y * (*model).scale.y)), 0.000000, 1.000000);
	vertexOut.texCoord = vertexIn.texCoord;
	return vertexOut;
}

struct FragmentOut {
	vec<float, 4> color;
};

fragment FragmentOut fragmentMain(VertexOut fragmentIn [[stage_in]], texture2d<float> colorTexture [[texture(0)]], sampler colorSampler [[sampler(0)]]) {
	FragmentOut fragmentOut;
	fragmentOut.color = colorTexture.sample(colorSampler, fragmentIn.texCoord);
	return fragmentOut;
}
```

## Roadmap

- [ ] Attributes for AIR backend
    - [x] Address space attribute
    - [x] Function declaration attributes
    - [ ] Function call attributes
    - [ ] Buffer attributes
- [x] Shader output for SPIRV and GLSL backends
- [ ] Support non-structure types as input and output for SPIRV and GLSL backends
- [x] Fragment shaders
    - [x] Basic support
    - [x] Specific input and output in GLSL
    - [x] Specific input and output in SPIRV
    - [x] Multiple entry points in SPIRV backend
- [x] Shader input
- [x] Vectors
    - [x] Operators
    - [x] Swizzling
    - [x] Assigning to individual components
    - [x] Initialization
- [ ] Proper alignment in AIR backend
- [ ] Make buffer it's own type
- [ ] Better error handling
- [ ] Reflection
- [ ] Multiple stages in one shader for GLSL
- [ ] More template arguments for texture and sampler
- [ ] Matrices
- [ ] Directly compiling to IR backneds (currently, the compiler emits an assembly, not bytecode, e.g. SPIRV assembly instead of SPIRV and LLVM IR instead of AIR)
- [ ] Other frontends
    - [ ] Metal Shading Language
    - [ ] GLSL

See the [open issues](https://github.com/SamoZ256/lvslang/issues) for a full list of proposed features (and known issues).

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

## Contact

Samuel Žúbor - samuliak77@gmail.com

Project Link: [https://github.com/SamoZ256/lvslang](https://github.com/SamoZ256/lvslang)
