target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define <4 x float> @testArrays.psMyBuffer(ptr addrspace(2) nocapture noundef readonly "air-buffer-no-alias" %myBuffer) local_unnamed_addr #0 {
entry:
  %0 = load float, ptr addrspace(2) %myBuffer, align 4
  %1 = insertelement <4 x float> <float poison, float 0.000000e+00, float 0.000000e+00, float 1.000000e+00>, float %0, i64 0
  ret <4 x float> %1
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.fragment = !{!9}
!air.compile_options = !{!15, !16, !17}
!air.version = !{!18}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @testArrays.psMyBuffer, !10, !11}
!10 = !{!12}
!11 = !{!13}
!12 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4"}
!13 = !{i32 0, !"air.buffer", !"air.location_index", i32 0, i32 1, !"air.read", !"air.address_space", i32 2, !"air.struct_type_info", !14, !"air.arg_type_size", i32 132, !"air.arg_type_align_size", i32 8, !"air.arg_type_name", !"struct MyBuffer*", !"air.arg_name", !"myBuffer"}
!14 = !{i32 0, i32 128, i32 0, !"float[32]", !"a", i32 128, i32 4, i32 0, !"int", !"i"}
!15 = !{!"air.compile.denorms_disable"}
!16 = !{!"air.compile.fast_math_disable"}
!17 = !{!"air.compile.framebuffer_fetch_enable"}
!18 = !{i32 2, i32 6, i32 0}
