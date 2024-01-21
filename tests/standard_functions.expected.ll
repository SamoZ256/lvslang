source_filename = "/Users/samuliak/Desktop/lvslang/build/../tests/standard_functions.metal"
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%FragmentOut = type { <4 x float> }

declare i32 @air.abs.i32(i32) local_unnamed_addr

declare float @air.acos(float) local_unnamed_addr

declare float @air.acosh(float) local_unnamed_addr

declare float @air.asin(float) local_unnamed_addr

declare float @air.asinh(float) local_unnamed_addr

declare float @air.atan(float) local_unnamed_addr

declare float @air.atanh(float) local_unnamed_addr

declare float @air.ceil(float) local_unnamed_addr

declare float @air.clamp.f32(float, float, float) local_unnamed_addr

declare float @air.cos(float) local_unnamed_addr

declare float @air.cosh(float) local_unnamed_addr

declare <3 x float> @air.cross(<3 x float>, <3 x float>) local_unnamed_addr

declare float @air.distance(<3 x float>, <3 x float>) local_unnamed_addr

declare float @air.dot(<3 x float>, <3 x float>) local_unnamed_addr

declare float @air.exp(float) local_unnamed_addr

declare float @air.exp2(float) local_unnamed_addr

declare float @air.floor(float) local_unnamed_addr

declare float @air.fract(float) local_unnamed_addr

declare i1 @air.isinf.f32(float) local_unnamed_addr

declare i1 @air.isnan.f32(float) local_unnamed_addr

declare float @air.length(<3 x float>) local_unnamed_addr

declare float @air.log(float) local_unnamed_addr

declare float @air.log2(float) local_unnamed_addr

declare float @air.max.f32(float, float) local_unnamed_addr

declare float @air.min.f32(float, float) local_unnamed_addr

declare float @air.mix.f32(float, float, float) local_unnamed_addr

declare <3 x float> @air.normalize(<3 x float>) local_unnamed_addr

declare float @air.pow(float, float) local_unnamed_addr

declare <3 x float> @air.reflect(<3 x float>, <3 x float>) local_unnamed_addr

declare <3 x float> @air.refract(<3 x float>, <3 x float>, float) local_unnamed_addr

declare float @air.round(float) local_unnamed_addr

declare <4 x float> @air.sample_texture_2d.f32(ptr addrspace(2) nocapture readonly, ptr addrspace(2) nocapture readonly, <2 x float>, i1, <2 x i32>, i1, float, float, i32) local_unnamed_addr

declare float @air.sign.f32(float) local_unnamed_addr

declare float @air.sin(float) local_unnamed_addr

declare float @air.sinh(float) local_unnamed_addr

declare float @air.smoothstep(float, float, float) local_unnamed_addr

declare float @air.sqrt(float) local_unnamed_addr

declare float @air.step(float, float) local_unnamed_addr

declare float @air.tan(float) local_unnamed_addr

declare float @air.tanh(float) local_unnamed_addr

define %FragmentOut @testStandardFunctions(ptr addrspace(2) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler) local_unnamed_addr {
  %_5 = tail call i32 @air.abs.i32(i32 0)
  %_6 = tail call float @air.acos(float 0.000000e+00)
  %_7 = tail call float @air.acosh(float 0.000000e+00)
  %_8 = tail call float @air.asin(float 0.000000e+00)
  %_9 = tail call float @air.asinh(float 0.000000e+00)
  %_10 = tail call float @air.atan(float 0.000000e+00)
  %_11 = tail call float @air.atanh(float 0.000000e+00)
  %_12 = tail call float @air.ceil(float 0.000000e+00)
  %_13 = tail call float @air.clamp.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_14 = tail call float @air.cos(float 0.000000e+00)
  %_15 = tail call float @air.cosh(float 0.000000e+00)
  %_16 = tail call <3 x float> @air.cross(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_17 = tail call float @air.distance(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_18 = tail call float @air.dot(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_19 = tail call float @air.exp(float 0.000000e+00)
  %_20 = tail call float @air.exp2(float 0.000000e+00)
  %_21 = tail call float @air.floor(float 0.000000e+00)
  %_22 = tail call float @air.fract(float 0.000000e+00)
  %_23 = tail call i1 @air.isinf.f32(float 0.000000e+00)
  %_24 = tail call i1 @air.isnan.f32(float 0.000000e+00)
  %_25 = tail call float @air.length(<3 x float> zeroinitializer)
  %_26 = tail call float @air.log(float 0.000000e+00)
  %_27 = tail call float @air.log2(float 0.000000e+00)
  %_28 = tail call float @air.max.f32(float 0.000000e+00, float 0.000000e+00)
  %_29 = tail call float @air.min.f32(float 0.000000e+00, float 0.000000e+00)
  %_30 = tail call float @air.mix.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_31 = tail call <3 x float> @air.normalize(<3 x float> zeroinitializer)
  %_32 = tail call float @air.pow(float 0.000000e+00, float 0.000000e+00)
  %_33 = tail call <3 x float> @air.reflect(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_34 = tail call <3 x float> @air.refract(<3 x float> zeroinitializer, <3 x float> zeroinitializer, float 0.000000e+00)
  %_35 = tail call float @air.round(float 0.000000e+00)
  %_38 = tail call <4 x float> @air.sample_texture_2d.f32(ptr addrspace(2) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler, <2 x float> zeroinitializer, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %_39 = tail call float @air.sign.f32(float 0.000000e+00)
  %_40 = tail call float @air.sin(float 0.000000e+00)
  %_41 = tail call float @air.sinh(float 0.000000e+00)
  %_42 = tail call float @air.smoothstep(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_43 = tail call float @air.sqrt(float 0.000000e+00)
  %_44 = tail call float @air.step(float 0.000000e+00, float 0.000000e+00)
  %_45 = tail call float @air.tan(float 0.000000e+00)
  %_46 = tail call float @air.tanh(float 0.000000e+00)
  ret %FragmentOut { <4 x float> <float 0.000000e+00, float 0.000000e+00, float 0.000000e+00, float 1.000000e+00> }
}

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.fragment = !{!9}
!air.compile_options = !{!15, !16, !17}
!llvm.ident = !{!18}
!air.version = !{!19}
!air.language_version = !{!20}
!air.source_file_name = !{!21}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @testStandardFunctions, !10, !12}
!10 = !{!11}
!11 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"<4 x float>", !"air.arg_name", !"outColor"}
!12 = !{!13, !14}
!13 = !{i32 0, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"ptr addrspace(2)", !"air.arg_name", !"testTexture"}
!14 = !{i32 1, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"ptr addrspace(2)", !"air.arg_name", !"testSampler"}
!15 = !{!"air.compile.denorms_disable"}
!16 = !{!"air.compile.fast_math_disable"}
!17 = !{!"air.compile.framebuffer_fetch_enable"}
!18 = !{!"Lvslang"}
!19 = !{i32 2, i32 6, i32 0}
!20 = !{!"LVSL", i32 0, i32 7, i32 0}
!21 = !{!"/Users/samuliak/Desktop/lvslang/test.lvsl"}
