target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%FragmentOut = type { <4 x float> }

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define %FragmentOut @testMatrices() local_unnamed_addr #0 {
entry:
  ret %FragmentOut { <4 x float> <float 0.000000e+00, float 0.000000e+00, float 0.000000e+00, float 1.000000e+00> }
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn }

!llvm.module.flags = !{!288, !289, !290, !291, !292, !293, !294, !295, !296}
!air.fragment = !{!297}
!air.compile_options = !{!301, !302, !303}
!air.version = !{!304}

!288 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!289 = !{i32 1, !"wchar_size", i32 4}
!290 = !{i32 7, !"frame-pointer", i32 2}
!291 = !{i32 7, !"air.max_device_buffers", i32 31}
!292 = !{i32 7, !"air.max_constant_buffers", i32 31}
!293 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!294 = !{i32 7, !"air.max_textures", i32 128}
!295 = !{i32 7, !"air.max_read_write_textures", i32 8}
!296 = !{i32 7, !"air.max_samplers", i32 16}
!297 = !{ptr @testMatrices, !298, !299}
!298 = !{!300}
!299 = !{}
!300 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"outColor"}
!301 = !{!"air.compile.denorms_disable"}
!302 = !{!"air.compile.fast_math_disable"}
!303 = !{!"air.compile.framebuffer_fetch_enable"}
!304 = !{i32 2, i32 6, i32 0}
