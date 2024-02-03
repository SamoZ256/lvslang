target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%FragmentOut = type { <4 x float> }

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define %FragmentOut @testControlFlow.psMyBuffer(ptr nocapture readonly %myBuffer) local_unnamed_addr #0 {
entry:
  %_291 = load float, ptr %myBuffer, align 4
  %op3 = fcmp ogt float %_291, 0.000000e+00
  %op4 = fcmp olt float %_291, 0.000000e+00
  %. = select i1 %op4, <4 x float> <float 0.000000e+00, float 1.000000e+00, float 0.000000e+00, float 1.000000e+00>, <4 x float> <float 0.000000e+00, float 0.000000e+00, float 1.000000e+00, float 1.000000e+00>
  %outColor.0 = select i1 %op3, <4 x float> <float 1.000000e+00, float 0.000000e+00, float 0.000000e+00, float 1.000000e+00>, <4 x float> %.
  %_30219 = insertvalue %FragmentOut poison, <4 x float> %outColor.0, 0
  ret %FragmentOut %_30219
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn }

!llvm.module.flags = !{!304, !305, !306, !307, !308, !309, !310, !311, !312}
!air.fragment = !{!313}
!air.compile_options = !{!319, !320, !321}
!air.version = !{!322}

!304 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!305 = !{i32 1, !"wchar_size", i32 4}
!306 = !{i32 7, !"frame-pointer", i32 2}
!307 = !{i32 7, !"air.max_device_buffers", i32 31}
!308 = !{i32 7, !"air.max_constant_buffers", i32 31}
!309 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!310 = !{i32 7, !"air.max_textures", i32 128}
!311 = !{i32 7, !"air.max_read_write_textures", i32 8}
!312 = !{i32 7, !"air.max_samplers", i32 16}
!313 = !{ptr @testControlFlow.psMyBuffer, !314, !315}
!314 = !{!316}
!315 = !{!317}
!316 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"outColor"}
!317 = !{i32 0, !"air.buffer", !"air.location_index", i32 0, i32 1, !"air.read", !"air.address_space", i32 2, !"air.struct_type_info", !318, !"air.arg_type_size", i32 4, !"air.arg_type_align_size", i32 8, !"air.arg_type_name", !"struct MyBuffer*", !"air.arg_name", !"myBuffer"}
!318 = !{i32 0, i32 4, i32 0, !"float", !"a"}
!319 = !{!"air.compile.denorms_disable"}
!320 = !{!"air.compile.fast_math_disable"}
!321 = !{!"air.compile.framebuffer_fetch_enable"}
!322 = !{i32 2, i32 6, i32 0}
