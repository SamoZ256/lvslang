## About The Project

This is a compiler for the Lava Shading Language (LVSL). It compiles into other shading languages (GLSL, Metal Shading Language) and bytecodes (SPIRV, AIR).

## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/SamoZ256/lvslang.git
   ```
2. Build the project
   ```
   cd /path/to/lvslang
   mkdir build
   cd build
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
   %_float32 = OpTypeFloat 32                         ; 32-bit float32
%_vec_float32_4 = OpTypeVector %_float32 4            ; vector(4) of float32
%_vec_float32_3 = OpTypeVector %_float32 3            ; vector(3) of float32
%_struct_VertexOut = OpTypeStruct %_vec_float32_4 %_vec_float32_3; VertexOut
%_func_struct_VertexOut = OpTypeFunction %_struct_VertexOut; struct_VertexOut ()
   %_float16 = OpTypeFloat 16                         ; 16-bit float16
%_vec_float16_4 = OpTypeVector %_float16 4            ; vector(4) of float16
%_struct_BufferContents = OpTypeStruct %_vec_float32_3 %_vec_float16_4; BufferContents
%_ptr_Uniform_struct_BufferContents = OpTypePointer Uniform %_struct_BufferContents; struct_BufferContents*
  %_myBuffer = OpVariable %_ptr_Uniform_struct_BufferContents Uniform
%_texture_1_float32 = OpTypeImage %_float32 2D 0 0 0 1 Unknown; image
%_ptr_UniformConstant_texture_1_float32 = OpTypePointer UniformConstant %_texture_1_float32; texture_1_float32*
 %_myTexture = OpVariable %_ptr_UniformConstant_texture_1_float32 UniformConstant
   %_sampler = OpTypeSampler                          ; sampler
%_ptr_UniformConstant_sampler = OpTypePointer UniformConstant %_sampler; sampler*
 %_mySampler = OpVariable %_ptr_UniformConstant_sampler UniformConstant
%_vec_float32_2 = OpTypeVector %_float32 2            ; vector(2) of float32
%_ptr_Function_vec_float32_2 = OpTypePointer Function %_vec_float32_2; vec_float32_2*
%_sampledImageType = OpTypeSampledImage %_texture_1_float32
        %_17 = OpConstant %_float32 0.000000
%_ptr_Function_vec_float32_4 = OpTypePointer Function %_vec_float32_4; vec_float32_4*
%_ptr_Function_struct_VertexOut = OpTypePointer Function %_struct_VertexOut; struct_VertexOut*
     %_int32 = OpTypeInt 32 1                         ; 32-bit int32
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

## Roadmap

- [ ] Attributes for AIR backend
- [ ] Shader output for SPIRV and GLSL backends
- [ ] Fragment shaders
- [ ] Shader input
- [ ] Vectors
    - [ ] Operators
    - [ ] Swizzling
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
