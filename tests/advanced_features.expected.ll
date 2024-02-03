target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%FragmentOut = type { <4 x float> }

declare i1 @forwardDeclaredFunction.i32.v3i32(i32, <3 x i32>) local_unnamed_addr

define %FragmentOut @testAdvancedFeatures() local_unnamed_addr {
entry:
  %_279 = tail call i1 @forwardDeclaredFunction.i32.v3i32(i32 1, <3 x i32> <i32 1, i32 2, i32 3>)
  ret %FragmentOut undef
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define i1 @forwardDeclaredFunction.i32.v3i32.1(i32 %a0, <3 x i32> %b) local_unnamed_addr #0 {
entry:
  %_287 = extractelement <3 x i32> %b, i64 0
  %op = icmp eq i32 %_287, %a0
  %_290 = extractelement <3 x i32> %b, i64 1
  %op0 = icmp eq i32 %_290, %a0
  %op1 = or i1 %op, %op0
  %_293 = extractelement <3 x i32> %b, i64 2
  %op2 = icmp eq i32 %_293, %a0
  %op3 = or i1 %op2, %op1
  ret i1 %op3
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn }

!llvm.module.flags = !{!295, !296, !297, !298, !299, !300, !301, !302, !303}
!air.fragment = !{!304}
!air.compile_options = !{!308, !309, !310}
!air.version = !{!311}

!295 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!296 = !{i32 1, !"wchar_size", i32 4}
!297 = !{i32 7, !"frame-pointer", i32 2}
!298 = !{i32 7, !"air.max_device_buffers", i32 31}
!299 = !{i32 7, !"air.max_constant_buffers", i32 31}
!300 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!301 = !{i32 7, !"air.max_textures", i32 128}
!302 = !{i32 7, !"air.max_read_write_textures", i32 8}
!303 = !{i32 7, !"air.max_samplers", i32 16}
!304 = !{ptr @testAdvancedFeatures, !305, !306}
!305 = !{!307}
!306 = !{}
!307 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"outColor"}
!308 = !{!"air.compile.denorms_disable"}
!309 = !{!"air.compile.fast_math_disable"}
!310 = !{!"air.compile.framebuffer_fetch_enable"}
!311 = !{i32 2, i32 6, i32 0}
