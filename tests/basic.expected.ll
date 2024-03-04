target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%VertexOut = type { <4 x float>, <2 x float> }
%VertexIn = type { <2 x float>, <2 x float> }
%Model = type { <2 x float>, <2 x float> }
%FragmentOut = type { <4 x float> }

; Function Attrs: convergent mustprogress nofree nounwind willreturn
declare <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) nocapture readonly, ptr addrspace(2) nocapture readonly, <2 x float>, i1, <2 x i32>, i1, float, float, i32) local_unnamed_addr #0

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define %VertexOut @vertexMain.sVertexIn.psModel(%VertexIn %vertexIn, ptr addrspace(2) nocapture noundef readonly "air-buffer-no-alias" %model) local_unnamed_addr #1 {
entry:
  %vertexIn.fca.0.extract = extractvalue %VertexIn %vertexIn, 0
  %vertexIn.fca.1.extract = extractvalue %VertexIn %vertexIn, 1
  %0 = load <2 x float>, ptr addrspace(2) %model, align 8
  %1 = getelementptr inbounds %Model, ptr addrspace(2) %model, i64 0, i32 1
  %2 = load <2 x float>, ptr addrspace(2) %1, align 8
  %op = fmul <2 x float> %vertexIn.fca.0.extract, %2
  %op1 = fadd <2 x float> %0, %op
  %3 = shufflevector <2 x float> %op1, <2 x float> poison, <4 x i32> <i32 0, i32 1, i32 poison, i32 poison>
  %4 = shufflevector <4 x float> %3, <4 x float> <float poison, float poison, float 0.000000e+00, float 1.000000e+00>, <4 x i32> <i32 0, i32 1, i32 6, i32 7>
  %.fca.0.insert = insertvalue %VertexOut poison, <4 x float> %4, 0
  %.fca.1.insert = insertvalue %VertexOut %.fca.0.insert, <2 x float> %vertexIn.fca.1.extract, 1
  ret %VertexOut %.fca.1.insert
}

; Function Attrs: mustprogress nofree nounwind willreturn
define %FragmentOut @fragmentMain.sVertexOut.t1f32.sm(%VertexOut %fragmentIn, ptr addrspace(1) nocapture readonly %colorTexture, ptr addrspace(2) nocapture readonly %colorSampler) local_unnamed_addr #2 {
entry0:
  %fragmentIn.fca.1.extract = extractvalue %VertexOut %fragmentIn, 1
  %0 = tail call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) %colorTexture, ptr addrspace(2) %colorSampler, <2 x float> %fragmentIn.fca.1.extract, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %.fca.0.insert = insertvalue %FragmentOut poison, <4 x float> %0, 0
  ret %FragmentOut %.fca.0.insert
}

attributes #0 = { convergent mustprogress nofree nounwind willreturn }
attributes #1 = { mustprogress nofree norecurse nosync nounwind willreturn }
attributes #2 = { mustprogress nofree nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.vertex = !{!9}
!air.fragment = !{!18}
!air.compile_options = !{!26, !27, !28}
!air.version = !{!29}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @vertexMain.sVertexIn.psModel, !10, !11}
!10 = !{!12, !13}
!11 = !{!14, !15, !16}
!12 = !{!"air.position", !"air.arg_type_name", !"float4", !"air.arg_name", !"pos"}
!13 = !{!"air.vertex_output", !"generated(randomstuff)", !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!14 = !{i32 0, !"air.vertex_input", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"float2", !"air.arg_name", !"pos"}
!15 = !{i32 1, !"air.vertex_input", !"air.location_index", i32 1, i32 1, !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!16 = !{i32 2, !"air.buffer", !"air.location_index", i32 0, i32 1, !"air.read", !"air.address_space", i32 2, !"air.struct_type_info", !17, !"air.arg_type_size", i32 16, !"air.arg_type_align_size", i32 8, !"air.arg_type_name", !"struct Model*", !"air.arg_name", !"model"}
!17 = !{i32 0, i32 8, i32 0, !"float2", !"pos", i32 8, i32 8, i32 0, !"float2", !"scale"}
!18 = !{ptr @fragmentMain.sVertexOut.t1f32.sm, !19, !20}
!19 = !{!21}
!20 = !{!22, !23, !24, !25}
!21 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"outColor"}
!22 = !{i32 0, !"air.position", !"air.center", !"air.no_perspective", !"air.arg_type_name", !"float4", !"air.arg_name", !"pos"}
!23 = !{i32 1, !"air.fragment_input", !"generated(randomstuff)", !"air.center", !"air.perspective", !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!24 = !{i32 2, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"texture2D<float>", !"air.arg_name", !"colorTexture"}
!25 = !{i32 3, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"sampler", !"air.arg_name", !"colorSampler"}
!26 = !{!"air.compile.denorms_disable"}
!27 = !{!"air.compile.fast_math_disable"}
!28 = !{!"air.compile.framebuffer_fetch_enable"}
!29 = !{i32 2, i32 6, i32 0}
