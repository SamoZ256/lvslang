target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%VertexOut = type { <4 x float>, <2 x float> }

; Function Attrs: convergent mustprogress nofree nounwind willreturn
declare <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) nocapture readonly, ptr addrspace(2) nocapture readonly, <2 x float>, i1, <2 x i32>, i1, float, float, i32) local_unnamed_addr #0

; Function Attrs: mustprogress nofree nounwind willreturn
define <4 x float> @fragmentMain.sVertexOut.t1f32.sm(%VertexOut %fragmentIn, ptr addrspace(1) nocapture readonly %tex, ptr addrspace(2) nocapture readonly %smp) local_unnamed_addr #1 {
entry:
  %fragmentIn.fca.1.extract = extractvalue %VertexOut %fragmentIn, 1
  %0 = tail call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) %tex, ptr addrspace(2) %smp, <2 x float> %fragmentIn.fca.1.extract, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  ret <4 x float> %0
}

attributes #0 = { convergent mustprogress nofree nounwind willreturn }
attributes #1 = { mustprogress nofree nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.fragment = !{!9}
!air.compile_options = !{!17, !18, !19}
!air.version = !{!20}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @fragmentMain.sVertexOut.t1f32.sm, !10, !11}
!10 = !{!12}
!11 = !{!13, !14, !15, !16}
!12 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"output"}
!13 = !{i32 0, !"air.position", !"air.center", !"air.no_perspective", !"air.arg_type_name", !"float4", !"air.arg_name", !"pos"}
!14 = !{i32 1, !"air.fragment_input", !"generated(randomstuff)", !"air.center", !"air.perspective", !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!15 = !{i32 2, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"texture2d<float>", !"air.arg_name", !"tex"}
!16 = !{i32 3, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"sampler", !"air.arg_name", !"smp"}
!17 = !{!"air.compile.denorms_disable"}
!18 = !{!"air.compile.fast_math_disable"}
!19 = !{!"air.compile.framebuffer_fetch_enable"}
!20 = !{i32 2, i32 6, i32 0}
