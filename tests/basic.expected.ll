target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%VertexOut = type { <4 x float>, <2 x float> }
%VertexIn = type { <2 x float>, <2 x float> }
%Model = type { <2 x float>, <2 x float> }
%FragmentOut = type { <4 x float> }

; Function Attrs: convergent mustprogress nofree nounwind willreturn
declare <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) nocapture readonly, ptr addrspace(2) nocapture readonly, <2 x float>, i1, <2 x i32>, i1, float, float, i32) local_unnamed_addr #0

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define %VertexOut @vertexMain.sVertexIn.psModel(%VertexIn %vertexIn, ptr nocapture readonly %model) local_unnamed_addr #1 {
entry:
  %vertexIn.fca.0.extract = extractvalue %VertexIn %vertexIn, 0
  %vertexIn.fca.1.extract = extractvalue %VertexIn %vertexIn, 1
  %_282 = load <2 x float>, ptr %model, align 8
  %_286 = getelementptr inbounds %Model, ptr %model, i64 0, i32 1
  %_287 = load <2 x float>, ptr %_286, align 8
  %op = fmul <2 x float> %vertexIn.fca.0.extract, %_287
  %op0 = fadd <2 x float> %_282, %op
  %0 = shufflevector <2 x float> %op0, <2 x float> poison, <4 x i32> <i32 0, i32 1, i32 poison, i32 poison>
  %_293 = shufflevector <4 x float> %0, <4 x float> <float poison, float poison, float 0.000000e+00, float 1.000000e+00>, <4 x i32> <i32 0, i32 1, i32 6, i32 7>
  %_297.fca.0.insert = insertvalue %VertexOut poison, <4 x float> %_293, 0
  %_297.fca.1.insert = insertvalue %VertexOut %_297.fca.0.insert, <2 x float> %vertexIn.fca.1.extract, 1
  ret %VertexOut %_297.fca.1.insert
}

; Function Attrs: mustprogress nofree nounwind willreturn
define %FragmentOut @fragmentMain.sVertexOut.t1f32.sm(%VertexOut %fragmentIn, ptr addrspace(1) nocapture readonly %colorTexture, ptr addrspace(2) nocapture readonly %colorSampler) local_unnamed_addr #2 {
entry:
  %fragmentIn.fca.1.extract = extractvalue %VertexOut %fragmentIn, 1
  %_309 = tail call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) %colorTexture, ptr addrspace(2) %colorSampler, <2 x float> %fragmentIn.fca.1.extract, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %_310.fca.0.insert = insertvalue %FragmentOut poison, <4 x float> %_309, 0
  ret %FragmentOut %_310.fca.0.insert
}

attributes #0 = { convergent mustprogress nofree nounwind willreturn }
attributes #1 = { mustprogress nofree norecurse nosync nounwind willreturn }
attributes #2 = { mustprogress nofree nounwind willreturn }

!llvm.module.flags = !{!312, !313, !314, !315, !316, !317, !318, !319, !320}
!air.vertex = !{!321}
!air.fragment = !{!330}
!air.compile_options = !{!338, !339, !340}
!air.version = !{!341}

!312 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!313 = !{i32 1, !"wchar_size", i32 4}
!314 = !{i32 7, !"frame-pointer", i32 2}
!315 = !{i32 7, !"air.max_device_buffers", i32 31}
!316 = !{i32 7, !"air.max_constant_buffers", i32 31}
!317 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!318 = !{i32 7, !"air.max_textures", i32 128}
!319 = !{i32 7, !"air.max_read_write_textures", i32 8}
!320 = !{i32 7, !"air.max_samplers", i32 16}
!321 = !{ptr @vertexMain.sVertexIn.psModel, !322, !323}
!322 = !{!324, !325}
!323 = !{!326, !327, !328}
!324 = !{!"air.position", !"air.arg_type_name", !"float4", !"air.arg_name", !"pos"}
!325 = !{!"air.vertex_output", !"generated(randomstuff)", !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!326 = !{i32 0, !"air.vertex_input", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"float2", !"air.arg_name", !"pos"}
!327 = !{i32 1, !"air.vertex_input", !"air.location_index", i32 1, i32 1, !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!328 = !{i32 2, !"air.buffer", !"air.location_index", i32 0, i32 1, !"air.read", !"air.address_space", i32 2, !"air.struct_type_info", !329, !"air.arg_type_size", i32 16, !"air.arg_type_align_size", i32 8, !"air.arg_type_name", !"struct Model*", !"air.arg_name", !"model"}
!329 = !{i32 0, i32 8, i32 0, !"float2", !"pos", i32 8, i32 8, i32 0, !"float2", !"scale"}
!330 = !{ptr @fragmentMain.sVertexOut.t1f32.sm, !331, !332}
!331 = !{!333}
!332 = !{!334, !335, !336, !337}
!333 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"outColor"}
!334 = !{i32 0, !"air.position", !"air.center", !"air.no_perspective", !"air.arg_type_name", !"float4", !"air.arg_name", !"pos"}
!335 = !{i32 1, !"air.fragment_input", !"generated(randomstuff)", !"air.center", !"air.perspective", !"air.arg_type_name", !"float2", !"air.arg_name", !"texCoord"}
!336 = !{i32 2, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"texture2d<float>", !"air.arg_name", !"colorTexture"}
!337 = !{i32 3, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"sampler", !"air.arg_name", !"colorSampler"}
!338 = !{!"air.compile.denorms_disable"}
!339 = !{!"air.compile.fast_math_disable"}
!340 = !{!"air.compile.framebuffer_fetch_enable"}
!341 = !{i32 2, i32 6, i32 0}
