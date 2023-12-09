## About The Project

This is a compiler for the Lava Shading Language (LVSL). It compiles into other shading languages (GLSL, Metal Shading Language) and bytecodes (SPIRV, AIR).

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

The code can be compiled with `lvslang --spirv /path/to/your/shader.lvsl -o output.spvasm`. This would emit SPIRV, but there are other viable backends as well. Use `--help`` to display all options (not working right now). Here is an example code:
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


; Magic:     0x07230203 (SPIR-V)
; Version:   0x00010000 (Version: 1.0.0)
; Generator: 0x00080001 (Lvslang Front End; 1)
; Bound:     63
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
                      OpEntryPoint Vertex %_vertexMain "vertexMain"

; Debug information
                      OpName %_vertexMain "vertexMain("

; Annotations (non-debug)
                      OpMemberDecorate %_struct_BufferContents 0 Offset 0
                      OpMemberDecorate %_struct_BufferContents 1 Offset 16
                      OpDecorate %_myBuffer DescriptorSet 0
                      OpDecorate %_myBuffer Binding 0
                      OpDecorate %_struct_BufferContents Block
                      OpDecorate %_myTexture DescriptorSet 0
                      OpDecorate %_myTexture Binding 1
                      OpDecorate %_mySampler DescriptorSet 1
                      OpDecorate %_mySampler Binding 0

; All types, variables, and constants
          %_float32 = OpTypeFloat 32                  ; 32-bit float32
    %_vec_float32_4 = OpTypeVector %_float32 4        ; vector(4) of float32
    %_vec_float32_3 = OpTypeVector %_float32 3        ; vector(3) of float32
 %_struct_VertexOut = OpTypeStruct %_vec_float32_4 %_vec_float32_3; VertexOut
%_func_struct_VertexOut = OpTypeFunction %_struct_VertexOut; struct_VertexOut ()
          %_float16 = OpTypeFloat 16                  ; 16-bit float16
    %_vec_float16_4 = OpTypeVector %_float16 4        ; vector(4) of float16
%_struct_BufferContents = OpTypeStruct %_vec_float32_3 %_vec_float16_4; BufferContents
%_ptr_Uniform_struct_BufferContents = OpTypePointer Uniform %_struct_BufferContents; struct_BufferContents*
         %_myBuffer = OpVariable %_ptr_Uniform_struct_BufferContents Uniform
%_texture_1_float32 = OpTypeImage %_float32 2D 0 0 0 1 Unknown; image
%_ptr_UniformConstant_texture_1_float32 = OpTypePointer UniformConstant %_texture_1_float32; texture_1_float32*
        %_myTexture = OpVariable %_ptr_UniformConstant_texture_1_float32 UniformConstant
          %_sampler = OpTypeSampler                   ; sampler
%_ptr_UniformConstant_sampler = OpTypePointer UniformConstant %_sampler; sampler*
        %_mySampler = OpVariable %_ptr_UniformConstant_sampler UniformConstant
    %_vec_float32_2 = OpTypeVector %_float32 2        ; vector(2) of float32
%_ptr_Function_vec_float32_2 = OpTypePointer Function %_vec_float32_2; vec_float32_2*
 %_sampledImageType = OpTypeSampledImage %_texture_1_float32
               %_17 = OpConstant %_float32 0.000000
%_ptr_Function_vec_float32_4 = OpTypePointer Function %_vec_float32_4; vec_float32_4*
%_ptr_Function_struct_VertexOut = OpTypePointer Function %_struct_VertexOut; struct_VertexOut*
            %_int32 = OpTypeInt 32 1                  ; 32-bit int32
               %_20 = OpConstant %_int32 0
               %_24 = OpConstant %_int32 1
%_ptr_Function_vec_float32_3 = OpTypePointer Function %_vec_float32_3; vec_float32_3*

; All functions
       %_vertexMain = OpFunction %_struct_VertexOut DontInline %_func_struct_VertexOut; %_vertexMain

               %_12 = OpLabel
           %_coords = OpVariable %_ptr_Function_vec_float32_2 Function
          %_sampled = OpVariable %_ptr_Function_vec_float32_4 Function
        %_vertexOut = OpVariable %_ptr_Function_struct_VertexOut Function
               %_13 = OpLoad %_texture_1_float32 %_myTexture
               %_14 = OpLoad %_sampler %_mySampler
               %_15 = OpLoad %_vec_float32_2 %_coords
    %_samplerTexTmp = OpSampledImage %_sampledImageType %_13 %_14
               %_18 = OpImageSampleExplicitLod %_vec_float32_4 %_samplerTexTmp %_15 Lod %_17
                      OpStore %_sampled %_18
               %_21 = OpAccessChain %_ptr_Function_vec_float32_4 %_vertexOut %_20
               %_22 = OpLoad %_vec_float32_4 %_sampled
                      OpStore %_21 %_22
               %_25 = OpAccessChain %_ptr_Function_vec_float32_3 %_vertexOut %_24
               %_26 = OpLoad %_vec_float32_4 %_sampled
               %_28 = OpCompositeExtract %_float32 %_26 0
               %_30 = OpCompositeExtract %_float32 %_26 0
               %_32 = OpCompositeExtract %_float32 %_26 3
               %_33 = OpCompositeConstruct %_vec_float32_3 %_28 %_30 %_32
                      OpStore %_25 %_33
               %_34 = OpLoad %_struct_VertexOut %_vertexOut
                      OpUnreachable

                      OpFunctionEnd
```

AIR:
```ll
source_filename = "test.lvsl"
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%_BufferContents = type { <3 x float>, <4 x half> }

%_VertexOut = type { <4 x float>, <3 x float> }

declare <4 x float> @air.sample_texture_2d.v4f32(ptr, ptr, <2 x float>, i1, <2 x i32>, i1, float, float, i32);

define %_VertexOut @vertexMain(ptr %_myBuffer, ptr %_myTexture, ptr %_mySampler) {
	%_6 = alloca ptr, align 4
	store ptr %_myBuffer, ptr %_6, align 4
	%_7 = alloca ptr, align 4
	store ptr %_myTexture, ptr %_7, align 4
	%_8 = alloca ptr, align 4
	store ptr %_mySampler, ptr %_8, align 4
	%_coords = alloca <2 x float>, align 4
	%_sampled = alloca <4 x float>, align 4
	%_vertexOut = alloca %_VertexOut, align 4

	%_10 = load ptr, ptr %_7, align 4
	%_11 = load ptr, ptr %_8, align 4
	%_12 = load <2 x float>, ptr %_coords, align 4
	%_20 = call <4 x float> @air.sample_texture_2d.v4f32(ptr %_10, ptr %_11, <2 x float> %_12, i1 1, <2 x i32> <i32 0, i32 0>, i1 0, float 0x0, float 0x0, i32 0)
	store <4 x float> %_20, ptr %_sampled, align 4
	%_22 = getelementptr inbounds %_VertexOut, ptr %_vertexOut, i32 0
	%_23 = load <4 x float>, ptr %_sampled, align 4
	store <4 x float> %_23, ptr %_22, align 4
	%_25 = getelementptr inbounds %_VertexOut, ptr %_vertexOut, i32 1
	%_26 = load <4 x float>, ptr %_sampled, align 4
	%_28 = extractelement <4 x float> %_26, i32 0
	%_30 = extractelement <4 x float> %_26, i32 0
	%_32 = extractelement <4 x float> %_26, i32 3
	%_34 = insertelement <3 x float> undef, float %_28, i32 0
	%_36 = insertelement <3 x float> %_34, float %_30, i32 1
	%_38 = insertelement <3 x float> %_36, float %_32, i32 2
	store <3 x float> %_38, ptr %_25, align 4
	%_39 = load %_VertexOut, ptr %_vertexOut, align 4
	ret %_VertexOut %_39
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
#version 450 core

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct BufferContents {
	vec3 cameraPos;
	f16vec4 color;
};

struct VertexOut {
	vec4 pos;
	vec3 color;
};

layout(set = 0, binding = 0) uniform BufferContents_Uniform {
	BufferContents myBuffer;
} myBuffer;

layout(set = 0, binding = 1) uniform texture2D myTexture;

layout(set = 1, binding = 0) uniform sampler mySampler;

void main() {
	vec2 coords;
	vec4 sampled = texture(sampler2D(myTexture, mySampler), coords);
	VertexOut vertexOut;
	vertexOut.pos = sampled;
	vertexOut.color = sampled.xxw;
	gl_Position = vertexOut.pos;
;
}
```

Metal Shading Language:
```c++
#include <metal_stdlib>
using namespace metal;

struct BufferContents {
	vec<float, 3> cameraPos;
	vec<half, 4> color;
};

struct VertexOut {
	vec<float, 4> pos [[position]];
	vec<float, 3> color;
};

vertex VertexOut vertexMain(constant BufferContents* myBuffer [[buffer(0)]], texture2d<float> myTexture [[texture(0)]], sampler mySampler [[sampler(0)]]) {
	vec<float, 2> coords;
	vec<float, 4> sampled = myTexture.sample(mySampler, coords);
	VertexOut vertexOut;
	vertexOut.pos = sampled;
	vertexOut.color = sampled.xxw;
	return vertexOut;
}
```

## Roadmap

- [ ] Attributes for AIR backend
- [ ] Shader output for SPIRV and GLSL backends
- [ ] Fragment shaders
- [ ] Shader input
- [ ] Vectors
    - [x] Operators
    - [x] Swizzling
    - [ ] Assigning to individual components
    - [ ] Initialization
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
