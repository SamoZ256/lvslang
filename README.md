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
   git clone https:// github.com/SamoZ256/lvslang.git
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
    float2 pos [[attribute(0)]];
    float2 texCoord [[attribute(1)]];
};

struct VertexOut {
    float4 pos [[position]];
    float2 texCoord;
};

vertex struct VertexOut vertexMain(struct VertexIn vertexIn [[stage_in]],
                                   constant struct Model* model [[descriptor_set(0, 0)]]) {
    struct VertexOut vertexOut;
    vertexOut.pos = float4(model->pos + vertexIn.pos * model->scale, 0.0, 1.0);
    vertexOut.texCoord = vertexIn.texCoord;

    return vertexOut;
};

struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut fragmentMain(struct VertexOut fragmentIn [[stage_in]],
                                         texture2d<half> colorTexture [[descriptor_set(0, 1)]],
                                         sampler colorSampler [[descriptor_set(1, 0)]]) {
    struct FragmentOut fragmentOut;
    fragmentOut.outColor = float4(sample(colorTexture, colorSampler, fragmentIn.texCoord));

    return fragmentOut;
}
```

Here are the outputs for each backend:
<details>
<summary>SPIRV</summary>

```assembly
; SPIR-V
; Version: 1.6
; Generator: Khronos SPIR-V Tools Assembler; 0
; Bound: 197
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
               OpEntryPoint Vertex %2 "vertexMain" %3 %4 %5 %6 %gl_Position
               OpEntryPoint Fragment %8 "fragmentMain" %9 %10 %11 %12
               OpExecutionMode %8 OriginUpperLeft

               ; Annotations
               OpMemberDecorate %_struct_15 0 Location 0
               OpMemberDecorate %_struct_15 1 Location 1
               OpMemberDecorate %_struct_15 0 Offset 0
               OpMemberDecorate %_struct_15 1 Offset 8
               OpDecorate %_struct_15 Block
               OpDecorate %4 DescriptorSet 0
               OpDecorate %4 Binding 0
               OpMemberDecorate %_struct_16 0 Offset 0
               OpMemberDecorate %_struct_16 0 ColMajor
               OpMemberDecorate %_struct_16 0 MatrixStride 16
               OpMemberDecorate %_struct_16 1 Offset 64
               OpMemberDecorate %_struct_16 1 ColMajor
               OpMemberDecorate %_struct_16 1 MatrixStride 16
               OpDecorate %_struct_16 Block
               OpDecorate %5 DescriptorSet 1
               OpDecorate %5 Binding 0
               OpDecorate %_struct_17 Block
               OpDecorate %6 Location 0
               OpDecorate %gl_Position BuiltIn Position
               OpDecorate %9 Location 0
               OpDecorate %10 DescriptorSet 0
               OpDecorate %10 Binding 1
               OpDecorate %11 DescriptorSet 1
               OpDecorate %11 Binding 0
               OpDecorate %_struct_18 Block
               OpMemberDecorate %_struct_18 0 Location 0

               ; Types, variables and constants
        %int = OpTypeInt 32 1
       %half = OpTypeFloat 16
     %v4half = OpTypeVector %half 4
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
    %v4float = OpTypeVector %float 4
 %_struct_15 = OpTypeStruct %v2float %v2float
%_ptr_Input__struct_15 = OpTypePointer Input %_struct_15
          %3 = OpVariable %_ptr_Input__struct_15 Input
%mat4v4float = OpTypeMatrix %v4float 4
 %_struct_16 = OpTypeStruct %mat4v4float %mat4v4float
%_ptr_Uniform__struct_16 = OpTypePointer Uniform %_struct_16
          %4 = OpVariable %_ptr_Uniform__struct_16 Uniform
%_ptr_Uniform_mat4v4float = OpTypePointer Uniform %mat4v4float
          %5 = OpVariable %_ptr_Uniform_mat4v4float Uniform
 %_struct_17 = OpTypeStruct %v4float %v2float
%_ptr_Output__struct_17 = OpTypePointer Output %_struct_17
          %6 = OpVariable %_ptr_Output__struct_17 Output
%_ptr_Output_v4float = OpTypePointer Output %v4float
%gl_Position = OpVariable %_ptr_Output_v4float Output
      %int_0 = OpConstant %int 0
       %void = OpTypeVoid
         %54 = OpTypeFunction %void
    %float_0 = OpConstant %float 0
    %float_1 = OpConstant %float 1
%_ptr_Input__struct_17 = OpTypePointer Input %_struct_17
          %9 = OpVariable %_ptr_Input__struct_17 Input
         %63 = OpTypeImage %half 2D 0 0 0 1 Unknown
%_ptr_UniformConstant_63 = OpTypePointer UniformConstant %63
         %10 = OpVariable %_ptr_UniformConstant_63 UniformConstant
         %66 = OpTypeSampler
%_ptr_UniformConstant_66 = OpTypePointer UniformConstant %66
         %11 = OpVariable %_ptr_UniformConstant_66 UniformConstant
 %_struct_18 = OpTypeStruct %v4float
%_ptr_Output__struct_18 = OpTypePointer Output %_struct_18
         %12 = OpVariable %_ptr_Output__struct_18 Output
         %71 = OpTypeSampledImage %63
%_ptr_Input_v2float = OpTypePointer Input %v2float
       %uint = OpTypeInt 32 0
     %uint_1 = OpConstant %uint 1

               ; Function 2
          %2 = OpFunction %void None %54
         %73 = OpLabel
         %77 = OpLoad %_struct_15 %3
         %78 = OpLoad %_struct_16 %4
         %79 = OpLoad %mat4v4float %5
        %141 = OpCompositeExtract %mat4v4float %78 0
        %143 = OpCompositeExtract %mat4v4float %78 1
        %144 = OpMatrixTimesMatrix %mat4v4float %141 %143
        %146 = OpMatrixTimesMatrix %mat4v4float %144 %79
        %148 = OpCompositeExtract %v2float %77 0
        %149 = OpCompositeExtract %float %148 0
        %150 = OpCompositeExtract %float %148 1
        %151 = OpCompositeConstruct %v4float %149 %150 %float_0 %float_1
        %152 = OpMatrixTimesVector %v4float %146 %151
        %155 = OpCompositeExtract %v2float %77 1
        %190 = OpCompositeConstruct %_struct_17 %152 %155
               OpStore %6 %190
         %81 = OpAccessChain %_ptr_Output_v4float %6 %int_0
         %82 = OpLoad %v4float %81
               OpStore %gl_Position %82
               OpReturn
               OpFunctionEnd

               ; Function 8
          %8 = OpFunction %void None %54
        %106 = OpLabel
        %195 = OpAccessChain %_ptr_Input_v2float %9 %uint_1
        %196 = OpLoad %v2float %195
        %111 = OpLoad %63 %10
        %112 = OpLoad %66 %11
        %165 = OpSampledImage %71 %111 %112
        %166 = OpImageSampleExplicitLod %v4half %165 %196 Lod %float_0
        %167 = OpCompositeExtract %half %166 0
        %168 = OpFConvert %float %167
        %169 = OpCompositeExtract %half %166 1
        %170 = OpFConvert %float %169
        %171 = OpCompositeExtract %half %166 2
        %172 = OpFConvert %float %171
        %173 = OpCompositeExtract %half %166 3
        %174 = OpFConvert %float %173
        %175 = OpCompositeConstruct %v4float %168 %170 %172 %174
        %191 = OpCompositeConstruct %_struct_18 %175
               OpStore %12 %191
               OpReturn
               OpFunctionEnd
```
</details>

<details>
<summary>AIR</summary>

```ll
; ModuleID = '/Users/samuliak/Desktop/lvslang/example.metal'
source_filename = "/Users/samuliak/Desktop/lvslang/example.metal"
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%VertexOut = type { <4 x float>, <2 x float> }
%VertexIn = type { <2 x float>, <2 x float> }
%ViewProj = type { [4 x <4 x float>], [4 x <4 x float>] }
%FragmentOut = type { <4 x float> }

; Function Attrs: convergent mustprogress nofree nounwind willreturn
declare <4 x half> @air.sample_texture_2d.v4f16(ptr addrspace(1) nocapture readonly, ptr addrspace(2) nocapture readonly, <2 x float>, i1, <2 x i32>, i1, float, float, i32) local_unnamed_addr #0

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define %VertexOut @vertexMain.sVertexIn.psViewProj.pm4v4f32(%VertexIn %vertexIn, ptr addrspace(2) nocapture noundef readonly "air-buffer-no-alias" %viewProj, ptr addrspace(2) nocapture noundef readonly "air-buffer-no-alias" %model) local_unnamed_addr #1 {
entry:
  %vertexIn.fca.0.extract = extractvalue %VertexIn %vertexIn, 0
  %0 = shufflevector <2 x float> %vertexIn.fca.0.extract, <2 x float> poison, <4 x i32> <i32 0, i32 1, i32 poison, i32 poison>
  %vertexIn.fca.1.extract = extractvalue %VertexIn %vertexIn, 1
  %.unpack = load <4 x float>, ptr addrspace(2) %viewProj, align 16
  %.elt4 = getelementptr inbounds [4 x <4 x float>], ptr addrspace(2) %viewProj, i64 0, i64 1
  %.unpack5 = load <4 x float>, ptr addrspace(2) %.elt4, align 16
  %.elt6 = getelementptr inbounds [4 x <4 x float>], ptr addrspace(2) %viewProj, i64 0, i64 2
  %.unpack7 = load <4 x float>, ptr addrspace(2) %.elt6, align 16
  %.elt8 = getelementptr inbounds [4 x <4 x float>], ptr addrspace(2) %viewProj, i64 0, i64 3
  %.unpack9 = load <4 x float>, ptr addrspace(2) %.elt8, align 16
  %1 = getelementptr inbounds %ViewProj, ptr addrspace(2) %viewProj, i64 0, i32 1
  %.unpack10 = load <4 x float>, ptr addrspace(2) %1, align 16
  %.elt11 = getelementptr inbounds %ViewProj, ptr addrspace(2) %viewProj, i64 0, i32 1, i64 1
  %.unpack12 = load <4 x float>, ptr addrspace(2) %.elt11, align 16
  %.elt13 = getelementptr inbounds %ViewProj, ptr addrspace(2) %viewProj, i64 0, i32 1, i64 2
  %.unpack14 = load <4 x float>, ptr addrspace(2) %.elt13, align 16
  %.elt15 = getelementptr inbounds %ViewProj, ptr addrspace(2) %viewProj, i64 0, i32 1, i64 3
  %.unpack16 = load <4 x float>, ptr addrspace(2) %.elt15, align 16
  %2 = extractelement <4 x float> %.unpack, i64 0
  %3 = extractelement <4 x float> %.unpack10, i64 0
  %4 = fmul float %2, %3
  %5 = fadd float %4, 0.000000e+00
  %6 = extractelement <4 x float> %.unpack5, i64 0
  %7 = extractelement <4 x float> %.unpack10, i64 1
  %8 = fmul float %6, %7
  %9 = fadd float %8, %5
  %10 = extractelement <4 x float> %.unpack7, i64 0
  %11 = extractelement <4 x float> %.unpack10, i64 2
  %12 = fmul float %10, %11
  %13 = fadd float %12, %9
  %14 = extractelement <4 x float> %.unpack9, i64 0
  %15 = extractelement <4 x float> %.unpack10, i64 3
  %16 = fmul float %14, %15
  %17 = fadd float %16, %13
  %18 = extractelement <4 x float> %.unpack12, i64 0
  %19 = fmul float %2, %18
  %20 = fadd float %19, 0.000000e+00
  %21 = extractelement <4 x float> %.unpack12, i64 1
  %22 = fmul float %6, %21
  %23 = fadd float %22, %20
  %24 = extractelement <4 x float> %.unpack12, i64 2
  %25 = fmul float %10, %24
  %26 = fadd float %25, %23
  %27 = extractelement <4 x float> %.unpack12, i64 3
  %28 = fmul float %14, %27
  %29 = fadd float %28, %26
  %30 = extractelement <4 x float> %.unpack14, i64 0
  %31 = fmul float %2, %30
  %32 = fadd float %31, 0.000000e+00
  %33 = extractelement <4 x float> %.unpack14, i64 1
  %34 = fmul float %6, %33
  %35 = fadd float %34, %32
  %36 = extractelement <4 x float> %.unpack14, i64 2
  %37 = fmul float %10, %36
  %38 = fadd float %37, %35
  %39 = extractelement <4 x float> %.unpack14, i64 3
  %40 = fmul float %14, %39
  %41 = fadd float %40, %38
  %42 = extractelement <4 x float> %.unpack16, i64 0
  %43 = fmul float %2, %42
  %44 = fadd float %43, 0.000000e+00
  %45 = extractelement <4 x float> %.unpack16, i64 1
  %46 = fmul float %6, %45
  %47 = fadd float %46, %44
  %48 = extractelement <4 x float> %.unpack16, i64 2
  %49 = fmul float %10, %48
  %50 = fadd float %49, %47
  %51 = extractelement <4 x float> %.unpack16, i64 3
  %52 = fmul float %14, %51
  %53 = fadd float %52, %50
  %54 = extractelement <4 x float> %.unpack, i64 1
  %55 = fmul float %54, %3
  %56 = fadd float %55, 0.000000e+00
  %57 = extractelement <4 x float> %.unpack5, i64 1
  %58 = fmul float %57, %7
  %59 = fadd float %58, %56
  %60 = extractelement <4 x float> %.unpack7, i64 1
  %61 = fmul float %60, %11
  %62 = fadd float %61, %59
  %63 = extractelement <4 x float> %.unpack9, i64 1
  %64 = fmul float %63, %15
  %65 = fadd float %64, %62
  %66 = fmul float %54, %18
  %67 = fadd float %66, 0.000000e+00
  %68 = fmul float %57, %21
  %69 = fadd float %68, %67
  %70 = fmul float %60, %24
  %71 = fadd float %70, %69
  %72 = fmul float %63, %27
  %73 = fadd float %72, %71
  %74 = fmul float %54, %30
  %75 = fadd float %74, 0.000000e+00
  %76 = fmul float %57, %33
  %77 = fadd float %76, %75
  %78 = fmul float %60, %36
  %79 = fadd float %78, %77
  %80 = fmul float %63, %39
  %81 = fadd float %80, %79
  %82 = fmul float %54, %42
  %83 = fadd float %82, 0.000000e+00
  %84 = fmul float %57, %45
  %85 = fadd float %84, %83
  %86 = fmul float %60, %48
  %87 = fadd float %86, %85
  %88 = fmul float %63, %51
  %89 = fadd float %88, %87
  %90 = extractelement <4 x float> %.unpack, i64 2
  %91 = fmul float %90, %3
  %92 = fadd float %91, 0.000000e+00
  %93 = extractelement <4 x float> %.unpack5, i64 2
  %94 = fmul float %93, %7
  %95 = fadd float %94, %92
  %96 = extractelement <4 x float> %.unpack7, i64 2
  %97 = fmul float %96, %11
  %98 = fadd float %97, %95
  %99 = extractelement <4 x float> %.unpack9, i64 2
  %100 = fmul float %99, %15
  %101 = fadd float %100, %98
  %102 = fmul float %90, %18
  %103 = fadd float %102, 0.000000e+00
  %104 = fmul float %93, %21
  %105 = fadd float %104, %103
  %106 = fmul float %96, %24
  %107 = fadd float %106, %105
  %108 = fmul float %99, %27
  %109 = fadd float %108, %107
  %110 = fmul float %90, %30
  %111 = fadd float %110, 0.000000e+00
  %112 = fmul float %93, %33
  %113 = fadd float %112, %111
  %114 = fmul float %96, %36
  %115 = fadd float %114, %113
  %116 = fmul float %99, %39
  %117 = fadd float %116, %115
  %118 = fmul float %90, %42
  %119 = fadd float %118, 0.000000e+00
  %120 = fmul float %93, %45
  %121 = fadd float %120, %119
  %122 = fmul float %96, %48
  %123 = fadd float %122, %121
  %124 = fmul float %99, %51
  %125 = fadd float %124, %123
  %126 = extractelement <4 x float> %.unpack, i64 3
  %127 = fmul float %126, %3
  %128 = fadd float %127, 0.000000e+00
  %129 = extractelement <4 x float> %.unpack5, i64 3
  %130 = fmul float %129, %7
  %131 = fadd float %130, %128
  %132 = extractelement <4 x float> %.unpack7, i64 3
  %133 = fmul float %132, %11
  %134 = fadd float %133, %131
  %135 = extractelement <4 x float> %.unpack9, i64 3
  %136 = fmul float %135, %15
  %137 = fadd float %136, %134
  %138 = fmul float %126, %18
  %139 = fadd float %138, 0.000000e+00
  %140 = fmul float %129, %21
  %141 = fadd float %140, %139
  %142 = fmul float %132, %24
  %143 = fadd float %142, %141
  %144 = fmul float %135, %27
  %145 = fadd float %144, %143
  %146 = fmul float %126, %30
  %147 = fadd float %146, 0.000000e+00
  %148 = fmul float %129, %33
  %149 = fadd float %148, %147
  %150 = fmul float %132, %36
  %151 = fadd float %150, %149
  %152 = fmul float %135, %39
  %153 = fadd float %152, %151
  %154 = fmul float %126, %42
  %155 = fadd float %154, 0.000000e+00
  %156 = fmul float %129, %45
  %157 = fadd float %156, %155
  %158 = fmul float %132, %48
  %159 = fadd float %158, %157
  %160 = fmul float %135, %51
  %161 = fadd float %160, %159
  %.unpack17 = load <4 x float>, ptr addrspace(2) %model, align 16
  %.elt18 = getelementptr inbounds [4 x <4 x float>], ptr addrspace(2) %model, i64 0, i64 1
  %.unpack19 = load <4 x float>, ptr addrspace(2) %.elt18, align 16
  %.elt20 = getelementptr inbounds [4 x <4 x float>], ptr addrspace(2) %model, i64 0, i64 2
  %.unpack21 = load <4 x float>, ptr addrspace(2) %.elt20, align 16
  %.elt22 = getelementptr inbounds [4 x <4 x float>], ptr addrspace(2) %model, i64 0, i64 3
  %.unpack23 = load <4 x float>, ptr addrspace(2) %.elt22, align 16
  %162 = extractelement <4 x float> %.unpack17, i64 0
  %163 = fmul float %162, %17
  %164 = fadd float %163, 0.000000e+00
  %165 = extractelement <4 x float> %.unpack17, i64 1
  %166 = fmul float %165, %65
  %167 = fadd float %166, %164
  %168 = extractelement <4 x float> %.unpack17, i64 2
  %169 = fmul float %168, %101
  %170 = fadd float %169, %167
  %171 = extractelement <4 x float> %.unpack17, i64 3
  %172 = fmul float %171, %137
  %173 = fadd float %172, %170
  %174 = insertelement <4 x float> undef, float %173, i64 0
  %175 = extractelement <4 x float> %.unpack19, i64 0
  %176 = fmul float %17, %175
  %177 = fadd float %176, 0.000000e+00
  %178 = extractelement <4 x float> %.unpack19, i64 1
  %179 = fmul float %65, %178
  %180 = fadd float %179, %177
  %181 = extractelement <4 x float> %.unpack19, i64 2
  %182 = fmul float %101, %181
  %183 = fadd float %182, %180
  %184 = extractelement <4 x float> %.unpack19, i64 3
  %185 = fmul float %137, %184
  %186 = fadd float %185, %183
  %187 = extractelement <4 x float> %.unpack21, i64 0
  %188 = fmul float %17, %187
  %189 = fadd float %188, 0.000000e+00
  %190 = extractelement <4 x float> %.unpack21, i64 1
  %191 = fmul float %65, %190
  %192 = fadd float %191, %189
  %193 = extractelement <4 x float> %.unpack21, i64 2
  %194 = fmul float %101, %193
  %195 = fadd float %194, %192
  %196 = extractelement <4 x float> %.unpack21, i64 3
  %197 = fmul float %137, %196
  %198 = fadd float %197, %195
  %199 = extractelement <4 x float> %.unpack23, i64 0
  %200 = fmul float %17, %199
  %201 = fadd float %200, 0.000000e+00
  %202 = extractelement <4 x float> %.unpack23, i64 1
  %203 = fmul float %65, %202
  %204 = fadd float %203, %201
  %205 = extractelement <4 x float> %.unpack23, i64 2
  %206 = fmul float %101, %205
  %207 = fadd float %206, %204
  %208 = extractelement <4 x float> %.unpack23, i64 3
  %209 = fmul float %137, %208
  %210 = fadd float %209, %207
  %211 = fmul float %162, %29
  %212 = fadd float %211, 0.000000e+00
  %213 = fmul float %165, %73
  %214 = fadd float %213, %212
  %215 = fmul float %168, %109
  %216 = fadd float %215, %214
  %217 = fmul float %171, %145
  %218 = fadd float %217, %216
  %219 = fmul float %175, %29
  %220 = fadd float %219, 0.000000e+00
  %221 = fmul float %178, %73
  %222 = fadd float %221, %220
  %223 = fmul float %181, %109
  %224 = fadd float %223, %222
  %225 = fmul float %184, %145
  %226 = fadd float %225, %224
  %227 = fmul float %29, %187
  %228 = fadd float %227, 0.000000e+00
  %229 = fmul float %73, %190
  %230 = fadd float %229, %228
  %231 = fmul float %109, %193
  %232 = fadd float %231, %230
  %233 = fmul float %145, %196
  %234 = fadd float %233, %232
  %235 = fmul float %29, %199
  %236 = fadd float %235, 0.000000e+00
  %237 = fmul float %73, %202
  %238 = fadd float %237, %236
  %239 = fmul float %109, %205
  %240 = fadd float %239, %238
  %241 = fmul float %145, %208
  %242 = fadd float %241, %240
  %243 = fmul float %162, %41
  %244 = fadd float %243, 0.000000e+00
  %245 = fmul float %165, %81
  %246 = fadd float %245, %244
  %247 = fmul float %168, %117
  %248 = fadd float %247, %246
  %249 = fmul float %171, %153
  %250 = fadd float %249, %248
  %251 = fmul float %175, %41
  %252 = fadd float %251, 0.000000e+00
  %253 = fmul float %178, %81
  %254 = fadd float %253, %252
  %255 = fmul float %181, %117
  %256 = fadd float %255, %254
  %257 = fmul float %184, %153
  %258 = fadd float %257, %256
  %259 = fmul float %187, %41
  %260 = fadd float %259, 0.000000e+00
  %261 = fmul float %190, %81
  %262 = fadd float %261, %260
  %263 = fmul float %193, %117
  %264 = fadd float %263, %262
  %265 = fmul float %196, %153
  %266 = fadd float %265, %264
  %267 = fmul float %41, %199
  %268 = fadd float %267, 0.000000e+00
  %269 = fmul float %81, %202
  %270 = fadd float %269, %268
  %271 = fmul float %117, %205
  %272 = fadd float %271, %270
  %273 = fmul float %153, %208
  %274 = fadd float %273, %272
  %275 = fmul float %162, %53
  %276 = fadd float %275, 0.000000e+00
  %277 = fmul float %165, %89
  %278 = fadd float %277, %276
  %279 = fmul float %168, %125
  %280 = fadd float %279, %278
  %281 = fmul float %171, %161
  %282 = fadd float %281, %280
  %283 = fmul float %175, %53
  %284 = fadd float %283, 0.000000e+00
  %285 = fmul float %178, %89
  %286 = fadd float %285, %284
  %287 = fmul float %181, %125
  %288 = fadd float %287, %286
  %289 = fmul float %184, %161
  %290 = fadd float %289, %288
  %291 = fmul float %187, %53
  %292 = fadd float %291, 0.000000e+00
  %293 = fmul float %190, %89
  %294 = fadd float %293, %292
  %295 = fmul float %193, %125
  %296 = fadd float %295, %294
  %297 = fmul float %196, %161
  %298 = fadd float %297, %296
  %299 = fmul float %199, %53
  %300 = fadd float %299, 0.000000e+00
  %301 = fmul float %202, %89
  %302 = fadd float %301, %300
  %303 = fmul float %205, %125
  %304 = fadd float %303, %302
  %305 = fmul float %208, %161
  %306 = fadd float %305, %304
  %307 = shufflevector <4 x float> %0, <4 x float> <float poison, float poison, float 0.000000e+00, float 1.000000e+00>, <4 x i32> <i32 0, i32 1, i32 6, i32 7>
  %308 = insertelement <4 x float> %174, float %218, i64 1
  %309 = insertelement <4 x float> %308, float %250, i64 2
  %310 = insertelement <4 x float> %309, float %282, i64 3
  %311 = fmul <4 x float> %307, %310
  %312 = fadd <4 x float> %311, zeroinitializer
  %313 = insertelement <4 x float> undef, float %186, i64 0
  %314 = insertelement <4 x float> %313, float %226, i64 1
  %315 = insertelement <4 x float> %314, float %258, i64 2
  %316 = insertelement <4 x float> %315, float %290, i64 3
  %317 = fmul <4 x float> %307, %316
  %318 = fadd <4 x float> %317, %312
  %319 = insertelement <4 x float> undef, float %198, i64 0
  %320 = insertelement <4 x float> %319, float %234, i64 1
  %321 = insertelement <4 x float> %320, float %266, i64 2
  %322 = insertelement <4 x float> %321, float %298, i64 3
  %323 = fmul <4 x float> %307, %322
  %324 = fadd <4 x float> %323, %318
  %325 = insertelement <4 x float> undef, float %210, i64 0
  %326 = insertelement <4 x float> %325, float %242, i64 1
  %327 = insertelement <4 x float> %326, float %274, i64 2
  %328 = insertelement <4 x float> %327, float %306, i64 3
  %329 = fmul <4 x float> %307, %328
  %330 = fadd <4 x float> %329, %324
  %.fca.0.insert = insertvalue %VertexOut poison, <4 x float> %330, 0
  %.fca.1.insert = insertvalue %VertexOut %.fca.0.insert, <2 x float> %vertexIn.fca.1.extract, 1
  ret %VertexOut %.fca.1.insert
}

; Function Attrs: mustprogress nofree nounwind willreturn
define %FragmentOut @fragmentMain.sVertexOut.t1f16.sm(%VertexOut %fragmentIn, ptr addrspace(1) nocapture readonly %colorTexture, ptr addrspace(2) nocapture readonly %colorSampler) local_unnamed_addr #2 {
entry0:
  %fragmentIn.fca.1.extract = extractvalue %VertexOut %fragmentIn, 1
  %0 = tail call <4 x half> @air.sample_texture_2d.v4f16(ptr addrspace(1) %colorTexture, ptr addrspace(2) %colorSampler, <2 x float> %fragmentIn.fca.1.extract, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %1 = extractelement <4 x half> %0, i64 0
  %2 = fpext half %1 to float
  %3 = extractelement <4 x half> %0, i64 1
  %4 = fpext half %3 to float
  %5 = extractelement <4 x half> %0, i64 2
  %6 = fpext half %5 to float
  %7 = extractelement <4 x half> %0, i64 3
  %8 = fpext half %7 to float
  %9 = insertelement <4 x float> undef, float %2, i64 0
  %10 = insertelement <4 x float> %9, float %4, i64 1
  %11 = insertelement <4 x float> %10, float %6, i64 2
  %12 = insertelement <4 x float> %11, float %8, i64 3
  %.fca.0.insert = insertvalue %FragmentOut poison, <4 x float> %12, 0
  ret %FragmentOut %.fca.0.insert
}

attributes #0 = { convergent mustprogress nofree nounwind willreturn }
attributes #1 = { mustprogress nofree norecurse nosync nounwind willreturn }
attributes #2 = { mustprogress nofree nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.vertex = !{!9}
!air.fragment = !{!19}
!air.compile_options = !{!27, !28, !29}
!llvm.ident = !{!30}
!air.version = !{!31}
!air.language_version = !{!32}
!air.source_file_name = !{!33}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @vertexMain.sVertexIn.psViewProj.pm4v4f32, !10, !11}
!10 = !{!12, !13}
!11 = !{!14, !15, !16, !18}
!12 = !{!"air.position", !"air.arg_type_name", !"float4", !"air.arg_name", !"pos"}
!13 = !{!"air.vertex_output", !"generated(randomstuff)", !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!14 = !{i32 0, !"air.vertex_input", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"float2", !"air.arg_name", !"pos"}
!15 = !{i32 1, !"air.vertex_input", !"air.location_index", i32 1, i32 1, !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!16 = !{i32 2, !"air.buffer", !"air.location_index", i32 0, i32 1, !"air.read", !"air.address_space", i32 2, !"air.struct_type_info", !17, !"air.arg_type_size", i32 128, !"air.arg_type_align_size", i32 8, !"air.arg_type_name", !"struct ViewProj*", !"air.arg_name", !"viewProj"}
!17 = !{i32 0, i32 64, i32 0, !"float4x4", !"projection", i32 64, i32 64, i32 0, !"float4x4", !"view"}
!18 = !{i32 3, !"air.buffer", !"air.location_index", i32 1, i32 1, !"air.read", !"air.address_space", i32 2, !"air.arg_type_name", !"float4x4*", !"air.arg_name", !"model"}
!19 = !{ptr @fragmentMain.sVertexOut.t1f16.sm, !20, !21}
!20 = !{!22}
!21 = !{!23, !24, !25, !26}
!22 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"outColor"}
!23 = !{i32 0, !"air.position", !"air.center", !"air.no_perspective", !"air.arg_type_name", !"float4", !"air.arg_name", !"pos"}
!24 = !{i32 1, !"air.fragment_input", !"generated(randomstuff)", !"air.center", !"air.perspective", !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!25 = !{i32 2, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"texture2d<half>", !"air.arg_name", !"colorTexture"}
!26 = !{i32 3, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"sampler", !"air.arg_name", !"colorSampler"}
!27 = !{!"air.compile.denorms_disable"}
!28 = !{!"air.compile.fast_math_disable"}
!29 = !{!"air.compile.framebuffer_fetch_enable"}
!30 = !{!"Lvslang"}
!31 = !{i32 2, i32 6, i32 0}
!32 = !{!"Metal", i32 3, i32 1, i32 0}
!33 = !{!"/Users/samuliak/Desktop/lvslang/example.metal"}
```
</details>

<details>
<summary>Metal Shading Language</summary>

```c++
#include <metal_stdlib>
using namespace metal;

struct ViewProj {
	float4x4 projection;
	float4x4 view;
};

struct VertexIn {
	float2 pos [[attribute(0)]];
	float2 texCoord [[attribute(1)]];
};

struct VertexOut {
	float4 pos [[position]];
	float2 texCoord;
};

vertex VertexOut vertexMain(VertexIn vertexIn [[stage_in]], constant ViewProj* viewProj [[buffer(0)]], constant float4x4* model [[buffer(1)]]) {
	VertexOut vertexOut;
	vertexOut.pos = (((viewProj->projection * viewProj->view) * *(model)) * float4(vertexIn.pos, 0.000000, 1.000000));
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
</details>

<details>
<summary>HLSL</summary>

```c++
struct ViewProj {
	float4x4 projection;
	float4x4 view;
};

struct VertexIn {
	float2 pos : TEXCOORD0;
	float2 texCoord : TEXCOORD1;
};

struct VertexOut {
	float4 pos;
	float2 texCoord;
};

VertexOut vertexMain(VertexIn vertexIn, ViewProj viewProj, float4x4 model);

cbuffer viewProj_Uniform : register(b0) {
	ViewProj viewProj;
};

cbuffer model_Uniform : register(b1) {
	float4x4 model;
};

struct VertexOut_Output {
	VertexOut output : TEXCOORD0;
	float4 position : SV_Position;
};

VertexOut_Output _vertexMain(VertexIn vertexIn) {
	// Entry point call
	VertexOut _entryPointOutput = vertexMain(vertexIn, viewProj, model);

	// Output
	VertexOut_Output __output;
	__output.output = _entryPointOutput;
	__output.position = _entryPointOutput.pos;

	return __output;
}

VertexOut vertexMain(VertexIn vertexIn, ViewProj viewProj, float4x4 model) {
	VertexOut vertexOut;
	vertexOut.pos = mul(mul(mul(viewProj.projection, viewProj.view), model), float4(vertexIn.pos, 0.000000, 1.000000));
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
	// Entry point call
	FragmentOut _entryPointOutput = fragmentMain(fragmentIn, colorTexture, colorSampler);

	// Output
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
</details>

<details>
<summary>GLSL</summary>

```c++
#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct ViewProj {
	mat4 projection;
	mat4 view;
};

struct VertexIn {
	vec2 pos;
	vec2 texCoord;
};

struct VertexOut {
	vec4 pos;
	vec2 texCoord;
};

VertexOut vertexMain(VertexIn vertexIn, ViewProj viewProj, mat4 model);

layout (location = 0) in vec2 pos;

layout (location = 1) in vec2 texCoord;

layout (set = 0, binding = 0) uniform viewProj_Uniform {
	ViewProj viewProj;
};

layout (set = 1, binding = 0) uniform model_Uniform {
	mat4 model;
};

layout (location = 0) out VertexOut_Output {
	VertexOut _output;
} _output;

void main() {
	// Input
	VertexIn vertexIn;
	vertexIn.pos = pos;
	vertexIn.texCoord = texCoord;

	// Entry point call
	VertexOut _entryPointOutput = vertexMain(vertexIn, viewProj, model);

	// Output
	gl_Position = _entryPointOutput.pos;
	_output._output.pos = _entryPointOutput.pos;
	_output._output.texCoord = _entryPointOutput.texCoord;
}

VertexOut vertexMain(VertexIn vertexIn, ViewProj viewProj, mat4 model) {
	VertexOut vertexOut;
	vertexOut.pos = (((viewProj.projection * viewProj.view) * model) * vec4(vertexIn.pos, 0.000000, 1.000000));
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
	// Input

	// Entry point call
	FragmentOut _entryPointOutput = fragmentMain(fragmentIn, colorTexture, colorSampler);

	// Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut fragmentMain(VertexOut fragmentIn, texture2D colorTexture, sampler colorSampler) {
	FragmentOut fragmentOut;
	fragmentOut.outColor = vec4(texture(sampler2D(colorTexture, colorSampler), fragmentIn.texCoord));
	return fragmentOut;
}
```

Note that the this output won't compile, since it contains more than one entry point.
</details>

## Features

* Metal frontend
* Vertex shaders
* Fragment shaders
* Buffers
* Textures
* Samplers (without template arguments)
* Shader inputs and outputs

See the [open issues](https:// github.com/SamoZ256/lvslang/issues) for a full list of proposed features (and known issues).

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

## Contact

Samuel Žúbor - samuliak77@gmail.com

Project Link: [https:// github.com/SamoZ256/lvslang](https:// github.com/SamoZ256/lvslang)
