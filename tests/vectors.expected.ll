target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%FragmentOut = type { <4 x float> }

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define %FragmentOut @testVectors() local_unnamed_addr #0 {
entry:
  ret %FragmentOut { <4 x float> <float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00> }
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn }

!llvm.module.flags = !{!336, !337, !338, !339, !340, !341, !342, !343, !344}
!air.fragment = !{!345}
!air.compile_options = !{!349, !350, !351}
!air.version = !{!352}

!336 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!337 = !{i32 1, !"wchar_size", i32 4}
!338 = !{i32 7, !"frame-pointer", i32 2}
!339 = !{i32 7, !"air.max_device_buffers", i32 31}
!340 = !{i32 7, !"air.max_constant_buffers", i32 31}
!341 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!342 = !{i32 7, !"air.max_textures", i32 128}
!343 = !{i32 7, !"air.max_read_write_textures", i32 8}
!344 = !{i32 7, !"air.max_samplers", i32 16}
!345 = !{ptr @testVectors, !346, !347}
!346 = !{!348}
!347 = !{}
!348 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"outColor"}
!349 = !{!"air.compile.denorms_disable"}
!350 = !{!"air.compile.fast_math_disable"}
!351 = !{!"air.compile.framebuffer_fetch_enable"}
!352 = !{i32 2, i32 6, i32 0}
