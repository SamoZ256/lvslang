source_filename = "/Users/samuliak/Desktop/lvslang/build/../tests/standard_functions.metal"
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%FragmentOut = type { <4 x float> }

declare i32 @air.abs.i32(i32) local_unnamed_addr

declare float @air.acos.f32(float) local_unnamed_addr

declare float @air.acosh.f32(float) local_unnamed_addr

declare float @air.asin.f32(float) local_unnamed_addr

declare float @air.asinh.f32(float) local_unnamed_addr

declare float @air.atan.f32(float) local_unnamed_addr

declare float @air.atanh.f32(float) local_unnamed_addr

declare float @air.ceil.f32(float) local_unnamed_addr

declare float @air.clamp.f32(float, float, float) local_unnamed_addr

declare float @air.cos.f32(float) local_unnamed_addr

declare float @air.cosh.f32(float) local_unnamed_addr

declare <3 x float> @air.cross.f32(<3 x float>, <3 x float>) local_unnamed_addr

declare float @air.distance.f32(<3 x float>, <3 x float>) local_unnamed_addr

declare float @air.dot.f32(<3 x float>, <3 x float>) local_unnamed_addr

declare float @air.exp.f32(float) local_unnamed_addr

declare float @air.exp2.f32(float) local_unnamed_addr

declare float @air.floor.f32(float) local_unnamed_addr

declare float @air.fract.f32(float) local_unnamed_addr

declare i1 @air.isinf.f32(float) local_unnamed_addr

declare i1 @air.isnan.f32(float) local_unnamed_addr

declare float @air.length.f32(<3 x float>) local_unnamed_addr

declare float @air.log.f32(float) local_unnamed_addr

declare float @air.log2.f32(float) local_unnamed_addr

declare float @air.max.f32(float, float) local_unnamed_addr

declare float @air.min.f32(float, float) local_unnamed_addr

declare float @air.mix.f32(float, float, float) local_unnamed_addr

declare <3 x float> @air.normalize.f32(<3 x float>) local_unnamed_addr

declare float @air.pow.f32(float, float) local_unnamed_addr

declare <3 x float> @air.reflect.f32(<3 x float>, <3 x float>) local_unnamed_addr

declare <3 x float> @air.refract.f32(<3 x float>, <3 x float>, float) local_unnamed_addr

declare float @air.round.f32(float) local_unnamed_addr

declare <4 x float> @air.sample_texture_2d.f32(ptr addrspace(1) nocapture readonly, ptr addrspace(2) nocapture readonly, <2 x float>, i1, <2 x i32>, i1, float, float, i32) local_unnamed_addr

declare float @air.sign.f32(float) local_unnamed_addr

declare float @air.sin.f32(float) local_unnamed_addr

declare float @air.sinh.f32(float) local_unnamed_addr

declare float @air.smoothstep.f32(float, float, float) local_unnamed_addr

declare float @air.sqrt.f32(float) local_unnamed_addr

declare float @air.step.f32(float, float) local_unnamed_addr

declare float @air.tan.f32(float) local_unnamed_addr

declare float @air.tanh.f32(float) local_unnamed_addr

define %FragmentOut @testStandardFunctions(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler) local_unnamed_addr {
  %_45 = tail call i32 @air.abs.i32(i32 0)
  %_46 = tail call float @air.acos.f32(float 0.000000e+00)
  %_47 = tail call float @air.acosh.f32(float 0.000000e+00)
  %_48 = tail call float @air.asin.f32(float 0.000000e+00)
  %_49 = tail call float @air.asinh.f32(float 0.000000e+00)
  %_50 = tail call float @air.atan.f32(float 0.000000e+00)
  %_51 = tail call float @air.atanh.f32(float 0.000000e+00)
  %_52 = tail call float @air.ceil.f32(float 0.000000e+00)
  %_53 = tail call float @air.clamp.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_54 = tail call float @air.cos.f32(float 0.000000e+00)
  %_55 = tail call float @air.cosh.f32(float 0.000000e+00)
  %_56 = tail call <3 x float> @air.cross.f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_57 = tail call float @air.distance.f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_58 = tail call float @air.dot.f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_59 = tail call float @air.exp.f32(float 0.000000e+00)
  %_60 = tail call float @air.exp2.f32(float 0.000000e+00)
  %_61 = tail call float @air.floor.f32(float 0.000000e+00)
  %_62 = tail call float @air.fract.f32(float 0.000000e+00)
  %_63 = tail call i1 @air.isinf.f32(float 0.000000e+00)
  %_64 = tail call i1 @air.isnan.f32(float 0.000000e+00)
  %_65 = tail call float @air.length.f32(<3 x float> zeroinitializer)
  %_66 = tail call float @air.log.f32(float 0.000000e+00)
  %_67 = tail call float @air.log2.f32(float 0.000000e+00)
  %_68 = tail call float @air.max.f32(float 0.000000e+00, float 0.000000e+00)
  %_69 = tail call float @air.min.f32(float 0.000000e+00, float 0.000000e+00)
  %_70 = tail call float @air.mix.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_71 = tail call <3 x float> @air.normalize.f32(<3 x float> zeroinitializer)
  %_72 = tail call float @air.pow.f32(float 0.000000e+00, float 0.000000e+00)
  %_73 = tail call <3 x float> @air.reflect.f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_74 = tail call <3 x float> @air.refract.f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, float 0.000000e+00)
  %_75 = tail call float @air.round.f32(float 0.000000e+00)
  %_78 = tail call <4 x float> @air.sample_texture_2d.f32(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler, <2 x float> zeroinitializer, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %_79 = tail call float @air.sign.f32(float 0.000000e+00)
  %_80 = tail call float @air.sin.f32(float 0.000000e+00)
  %_81 = tail call float @air.sinh.f32(float 0.000000e+00)
  %_82 = tail call float @air.smoothstep.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_83 = tail call float @air.sqrt.f32(float 0.000000e+00)
  %_84 = tail call float @air.step.f32(float 0.000000e+00, float 0.000000e+00)
  %_85 = tail call float @air.tan.f32(float 0.000000e+00)
  %_86 = tail call float @air.tanh.f32(float 0.000000e+00)
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
!13 = !{i32 0, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"ptr addrspace(1)", !"air.arg_name", !"testTexture"}
!14 = !{i32 1, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"ptr addrspace(2)", !"air.arg_name", !"testSampler"}
!15 = !{!"air.compile.denorms_disable"}
!16 = !{!"air.compile.fast_math_disable"}
!17 = !{!"air.compile.framebuffer_fetch_enable"}
!18 = !{!"Lvslang"}
!19 = !{i32 2, i32 6, i32 0}
!20 = !{!"LVSL", i32 0, i32 7, i32 0}
!21 = !{!"/Users/samuliak/Desktop/lvslang/test.lvsl"}
