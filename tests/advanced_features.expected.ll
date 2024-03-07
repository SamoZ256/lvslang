target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define i1 @forwardDeclaredFunction.i32.v3i32(i32 %a, <3 x i32> %b) local_unnamed_addr #0 {
entry2:
  %0 = extractelement <3 x i32> %b, i64 0
  %op = icmp eq i32 %0, %a
  %1 = extractelement <3 x i32> %b, i64 1
  %op1 = icmp eq i32 %1, %a
  %op2 = or i1 %op, %op1
  %2 = extractelement <3 x i32> %b, i64 2
  %op3 = icmp eq i32 %2, %a
  %op4 = or i1 %op3, %op2
  ret i1 %op4
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define <2 x i32> @functionWithDefaultArguments.v2i32.v2i32(<2 x i32> %a, <2 x i32> %b) local_unnamed_addr #0 {
entry:
  %op = add <2 x i32> %b, %a
  ret <2 x i32> %op
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define <2 x float> @functionWithDefaultArguments.v2f32.v2f32(<2 x float> %a, <2 x float> %b) local_unnamed_addr #0 {
entry0:
  %op = fadd <2 x float> %a, %b
  ret <2 x float> %op
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define void @testAdvancedFeatures() local_unnamed_addr #0 {
entry1:
  ret void
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.fragment = !{!9}
!air.compile_options = !{!12, !13, !14}
!air.version = !{!15}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @testAdvancedFeatures, !10, !11}
!10 = !{}
!11 = !{}
!12 = !{!"air.compile.denorms_disable"}
!13 = !{!"air.compile.fast_math_disable"}
!14 = !{!"air.compile.framebuffer_fetch_enable"}
!15 = !{i32 2, i32 6, i32 0}
