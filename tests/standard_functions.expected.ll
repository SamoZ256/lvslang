target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%FragmentOut = type { <4 x float> }

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn
define %FragmentOut @testStandardFunctions.t1f32.sm(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler) local_unnamed_addr #0 {
entry:
  ret %FragmentOut { <4 x float> <float 0.000000e+00, float 0.000000e+00, float 0.000000e+00, float 1.000000e+00> }
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn }

!llvm.module.flags = !{!1462, !1463, !1464, !1465, !1466, !1467, !1468, !1469, !1470}
!air.fragment = !{!1471}
!air.compile_options = !{!1477, !1478, !1479}
!air.version = !{!1480}

!1462 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1463 = !{i32 1, !"wchar_size", i32 4}
!1464 = !{i32 7, !"frame-pointer", i32 2}
!1465 = !{i32 7, !"air.max_device_buffers", i32 31}
!1466 = !{i32 7, !"air.max_constant_buffers", i32 31}
!1467 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!1468 = !{i32 7, !"air.max_textures", i32 128}
!1469 = !{i32 7, !"air.max_read_write_textures", i32 8}
!1470 = !{i32 7, !"air.max_samplers", i32 16}
!1471 = !{ptr @testStandardFunctions.t1f32.sm, !1472, !1473}
!1472 = !{!1474}
!1473 = !{!1475, !1476}
!1474 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"float4", !"air.arg_name", !"outColor"}
!1475 = !{i32 0, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"texture2d<float>", !"air.arg_name", !"testTexture"}
!1476 = !{i32 1, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"sampler", !"air.arg_name", !"testSampler"}
!1477 = !{!"air.compile.denorms_disable"}
!1478 = !{!"air.compile.fast_math_disable"}
!1479 = !{!"air.compile.framebuffer_fetch_enable"}
!1480 = !{i32 2, i32 6, i32 0}
