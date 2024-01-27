source_filename = "/Users/samuliak/Desktop/lvslang/build/../tests/standard_functions.metal"
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-n8:16:32"
target triple = "air64-apple-macosx14.0.0"

%FragmentOut = type { <4 x float> }

declare i8 @air.abs.i8(i8) local_unnamed_addr

declare <2 x i8> @air.abs.v2i8(<2 x i8>) local_unnamed_addr

declare <3 x i8> @air.abs.v3i8(<3 x i8>) local_unnamed_addr

declare <4 x i8> @air.abs.v4i8(<4 x i8>) local_unnamed_addr

declare i16 @air.abs.i16(i16) local_unnamed_addr

declare <2 x i16> @air.abs.v2i16(<2 x i16>) local_unnamed_addr

declare <3 x i16> @air.abs.v3i16(<3 x i16>) local_unnamed_addr

declare <4 x i16> @air.abs.v4i16(<4 x i16>) local_unnamed_addr

declare i32 @air.abs.i32(i32) local_unnamed_addr

declare <2 x i32> @air.abs.v2i32(<2 x i32>) local_unnamed_addr

declare <3 x i32> @air.abs.v3i32(<3 x i32>) local_unnamed_addr

declare <4 x i32> @air.abs.v4i32(<4 x i32>) local_unnamed_addr

declare half @air.abs.f16(half) local_unnamed_addr

declare <2 x half> @air.abs.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.abs.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.abs.v4f16(<4 x half>) local_unnamed_addr

declare float @air.abs.f32(float) local_unnamed_addr

declare <2 x float> @air.abs.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.abs.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.abs.v4f32(<4 x float>) local_unnamed_addr

declare float @air.acos.f32(float) local_unnamed_addr

declare float @air.acosh.f32(float) local_unnamed_addr

declare float @air.asin.f32(float) local_unnamed_addr

declare float @air.asinh.f32(float) local_unnamed_addr

declare float @air.atan.f32(float) local_unnamed_addr

declare float @air.atanh.f32(float) local_unnamed_addr

declare half @air.ceil.f16(half) local_unnamed_addr

declare <2 x half> @air.ceil.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.ceil.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.ceil.v4f16(<4 x half>) local_unnamed_addr

declare float @air.ceil.f32(float) local_unnamed_addr

declare <2 x float> @air.ceil.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.ceil.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.ceil.v4f32(<4 x float>) local_unnamed_addr

declare i8 @air.clamp.i8(i8, i8, i8) local_unnamed_addr

declare <2 x i8> @air.clamp.v2i8(<2 x i8>, <2 x i8>, <2 x i8>) local_unnamed_addr

declare <3 x i8> @air.clamp.v3i8(<3 x i8>, <3 x i8>, <3 x i8>) local_unnamed_addr

declare <4 x i8> @air.clamp.v4i8(<4 x i8>, <4 x i8>, <4 x i8>) local_unnamed_addr

declare i16 @air.clamp.i16(i16, i16, i16) local_unnamed_addr

declare <2 x i16> @air.clamp.v2i16(<2 x i16>, <2 x i16>, <2 x i16>) local_unnamed_addr

declare <3 x i16> @air.clamp.v3i16(<3 x i16>, <3 x i16>, <3 x i16>) local_unnamed_addr

declare <4 x i16> @air.clamp.v4i16(<4 x i16>, <4 x i16>, <4 x i16>) local_unnamed_addr

declare i32 @air.clamp.i32(i32, i32, i32) local_unnamed_addr

declare <2 x i32> @air.clamp.v2i32(<2 x i32>, <2 x i32>, <2 x i32>) local_unnamed_addr

declare <3 x i32> @air.clamp.v3i32(<3 x i32>, <3 x i32>, <3 x i32>) local_unnamed_addr

declare <4 x i32> @air.clamp.v4i32(<4 x i32>, <4 x i32>, <4 x i32>) local_unnamed_addr

declare half @air.clamp.f16(half, half, half) local_unnamed_addr

declare <2 x half> @air.clamp.v2f16(<2 x half>, <2 x half>, <2 x half>) local_unnamed_addr

declare <3 x half> @air.clamp.v3f16(<3 x half>, <3 x half>, <3 x half>) local_unnamed_addr

declare <4 x half> @air.clamp.v4f16(<4 x half>, <4 x half>, <4 x half>) local_unnamed_addr

declare float @air.clamp.f32(float, float, float) local_unnamed_addr

declare <2 x float> @air.clamp.v2f32(<2 x float>, <2 x float>, <2 x float>) local_unnamed_addr

declare <3 x float> @air.clamp.v3f32(<3 x float>, <3 x float>, <3 x float>) local_unnamed_addr

declare <4 x float> @air.clamp.v4f32(<4 x float>, <4 x float>, <4 x float>) local_unnamed_addr

declare float @air.cos.f32(float) local_unnamed_addr

declare float @air.cosh.f32(float) local_unnamed_addr

declare <3 x half> @air.cross.v3f16(<3 x half>, <3 x half>) local_unnamed_addr

declare <3 x float> @air.cross.v3f32(<3 x float>, <3 x float>) local_unnamed_addr

declare half @air.distance.v2f16(<2 x half>, <2 x half>) local_unnamed_addr

declare half @air.distance.v3f16(<3 x half>, <3 x half>) local_unnamed_addr

declare half @air.distance.v4f16(<4 x half>, <4 x half>) local_unnamed_addr

declare float @air.distance.v2f32(<2 x float>, <2 x float>) local_unnamed_addr

declare float @air.distance.v3f32(<3 x float>, <3 x float>) local_unnamed_addr

declare float @air.distance.v4f32(<4 x float>, <4 x float>) local_unnamed_addr

declare half @air.dot.v2f16(<2 x half>, <2 x half>) local_unnamed_addr

declare half @air.dot.v3f16(<3 x half>, <3 x half>) local_unnamed_addr

declare half @air.dot.v4f16(<4 x half>, <4 x half>) local_unnamed_addr

declare float @air.dot.v2f32(<2 x float>, <2 x float>) local_unnamed_addr

declare float @air.dot.v3f32(<3 x float>, <3 x float>) local_unnamed_addr

declare float @air.dot.v4f32(<4 x float>, <4 x float>) local_unnamed_addr

declare half @air.exp.f16(half) local_unnamed_addr

declare <2 x half> @air.exp.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.exp.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.exp.v4f16(<4 x half>) local_unnamed_addr

declare float @air.exp.f32(float) local_unnamed_addr

declare <2 x float> @air.exp.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.exp.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.exp.v4f32(<4 x float>) local_unnamed_addr

declare half @air.exp2.f16(half) local_unnamed_addr

declare <2 x half> @air.exp2.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.exp2.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.exp2.v4f16(<4 x half>) local_unnamed_addr

declare float @air.exp2.f32(float) local_unnamed_addr

declare <2 x float> @air.exp2.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.exp2.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.exp2.v4f32(<4 x float>) local_unnamed_addr

declare half @air.floor.f16(half) local_unnamed_addr

declare <2 x half> @air.floor.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.floor.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.floor.v4f16(<4 x half>) local_unnamed_addr

declare float @air.floor.f32(float) local_unnamed_addr

declare <2 x float> @air.floor.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.floor.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.floor.v4f32(<4 x float>) local_unnamed_addr

declare half @air.fract.f16(half) local_unnamed_addr

declare <2 x half> @air.fract.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.fract.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.fract.v4f16(<4 x half>) local_unnamed_addr

declare float @air.fract.f32(float) local_unnamed_addr

declare <2 x float> @air.fract.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.fract.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.fract.v4f32(<4 x float>) local_unnamed_addr

declare i1 @air.isinf.f16(half) local_unnamed_addr

declare <2 x i1> @air.isinf.v2f16(<2 x half>) local_unnamed_addr

declare <3 x i1> @air.isinf.v3f16(<3 x half>) local_unnamed_addr

declare <4 x i1> @air.isinf.v4f16(<4 x half>) local_unnamed_addr

declare i1 @air.isinf.f32(float) local_unnamed_addr

declare <2 x i1> @air.isinf.v2f32(<2 x float>) local_unnamed_addr

declare <3 x i1> @air.isinf.v3f32(<3 x float>) local_unnamed_addr

declare <4 x i1> @air.isinf.v4f32(<4 x float>) local_unnamed_addr

declare i1 @air.isnan.f16(half) local_unnamed_addr

declare <2 x i1> @air.isnan.v2f16(<2 x half>) local_unnamed_addr

declare <3 x i1> @air.isnan.v3f16(<3 x half>) local_unnamed_addr

declare <4 x i1> @air.isnan.v4f16(<4 x half>) local_unnamed_addr

declare i1 @air.isnan.f32(float) local_unnamed_addr

declare <2 x i1> @air.isnan.v2f32(<2 x float>) local_unnamed_addr

declare <3 x i1> @air.isnan.v3f32(<3 x float>) local_unnamed_addr

declare <4 x i1> @air.isnan.v4f32(<4 x float>) local_unnamed_addr

declare half @air.length.v2f16(<2 x half>) local_unnamed_addr

declare half @air.length.v3f16(<3 x half>) local_unnamed_addr

declare half @air.length.v4f16(<4 x half>) local_unnamed_addr

declare float @air.length.v2f32(<2 x float>) local_unnamed_addr

declare float @air.length.v3f32(<3 x float>) local_unnamed_addr

declare float @air.length.v4f32(<4 x float>) local_unnamed_addr

declare i8 @air.max.i8(i8, i8) local_unnamed_addr

declare <2 x i8> @air.max.v2i8(<2 x i8>, <2 x i8>) local_unnamed_addr

declare <3 x i8> @air.max.v3i8(<3 x i8>, <3 x i8>) local_unnamed_addr

declare <4 x i8> @air.max.v4i8(<4 x i8>, <4 x i8>) local_unnamed_addr

declare i16 @air.max.i16(i16, i16) local_unnamed_addr

declare <2 x i16> @air.max.v2i16(<2 x i16>, <2 x i16>) local_unnamed_addr

declare <3 x i16> @air.max.v3i16(<3 x i16>, <3 x i16>) local_unnamed_addr

declare <4 x i16> @air.max.v4i16(<4 x i16>, <4 x i16>) local_unnamed_addr

declare i32 @air.max.i32(i32, i32) local_unnamed_addr

declare <2 x i32> @air.max.v2i32(<2 x i32>, <2 x i32>) local_unnamed_addr

declare <3 x i32> @air.max.v3i32(<3 x i32>, <3 x i32>) local_unnamed_addr

declare <4 x i32> @air.max.v4i32(<4 x i32>, <4 x i32>) local_unnamed_addr

declare half @air.max.f16(half, half) local_unnamed_addr

declare <2 x half> @air.max.v2f16(<2 x half>, <2 x half>) local_unnamed_addr

declare <3 x half> @air.max.v3f16(<3 x half>, <3 x half>) local_unnamed_addr

declare <4 x half> @air.max.v4f16(<4 x half>, <4 x half>) local_unnamed_addr

declare float @air.max.f32(float, float) local_unnamed_addr

declare <2 x float> @air.max.v2f32(<2 x float>, <2 x float>) local_unnamed_addr

declare <3 x float> @air.max.v3f32(<3 x float>, <3 x float>) local_unnamed_addr

declare <4 x float> @air.max.v4f32(<4 x float>, <4 x float>) local_unnamed_addr

declare i8 @air.min.i8(i8, i8) local_unnamed_addr

declare <2 x i8> @air.min.v2i8(<2 x i8>, <2 x i8>) local_unnamed_addr

declare <3 x i8> @air.min.v3i8(<3 x i8>, <3 x i8>) local_unnamed_addr

declare <4 x i8> @air.min.v4i8(<4 x i8>, <4 x i8>) local_unnamed_addr

declare i16 @air.min.i16(i16, i16) local_unnamed_addr

declare <2 x i16> @air.min.v2i16(<2 x i16>, <2 x i16>) local_unnamed_addr

declare <3 x i16> @air.min.v3i16(<3 x i16>, <3 x i16>) local_unnamed_addr

declare <4 x i16> @air.min.v4i16(<4 x i16>, <4 x i16>) local_unnamed_addr

declare i32 @air.min.i32(i32, i32) local_unnamed_addr

declare <2 x i32> @air.min.v2i32(<2 x i32>, <2 x i32>) local_unnamed_addr

declare <3 x i32> @air.min.v3i32(<3 x i32>, <3 x i32>) local_unnamed_addr

declare <4 x i32> @air.min.v4i32(<4 x i32>, <4 x i32>) local_unnamed_addr

declare half @air.min.f16(half, half) local_unnamed_addr

declare <2 x half> @air.min.v2f16(<2 x half>, <2 x half>) local_unnamed_addr

declare <3 x half> @air.min.v3f16(<3 x half>, <3 x half>) local_unnamed_addr

declare <4 x half> @air.min.v4f16(<4 x half>, <4 x half>) local_unnamed_addr

declare float @air.min.f32(float, float) local_unnamed_addr

declare <2 x float> @air.min.v2f32(<2 x float>, <2 x float>) local_unnamed_addr

declare <3 x float> @air.min.v3f32(<3 x float>, <3 x float>) local_unnamed_addr

declare <4 x float> @air.min.v4f32(<4 x float>, <4 x float>) local_unnamed_addr

declare half @air.mix.f16(half, half, half) local_unnamed_addr

declare <2 x half> @air.mix.v2f16(<2 x half>, <2 x half>, <2 x half>) local_unnamed_addr

declare <3 x half> @air.mix.v3f16(<3 x half>, <3 x half>, <3 x half>) local_unnamed_addr

declare <4 x half> @air.mix.v4f16(<4 x half>, <4 x half>, <4 x half>) local_unnamed_addr

declare float @air.mix.f32(float, float, float) local_unnamed_addr

declare <2 x float> @air.mix.v2f32(<2 x float>, <2 x float>, <2 x float>) local_unnamed_addr

declare <3 x float> @air.mix.v3f32(<3 x float>, <3 x float>, <3 x float>) local_unnamed_addr

declare <4 x float> @air.mix.v4f32(<4 x float>, <4 x float>, <4 x float>) local_unnamed_addr

declare <2 x half> @air.normalize.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.normalize.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.normalize.v4f16(<4 x half>) local_unnamed_addr

declare <2 x float> @air.normalize.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.normalize.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.normalize.v4f32(<4 x float>) local_unnamed_addr

declare half @air.pow.f16(half, half) local_unnamed_addr

declare <2 x half> @air.pow.v2f16(<2 x half>, <2 x half>) local_unnamed_addr

declare <3 x half> @air.pow.v3f16(<3 x half>, <3 x half>) local_unnamed_addr

declare <4 x half> @air.pow.v4f16(<4 x half>, <4 x half>) local_unnamed_addr

declare float @air.pow.f32(float, float) local_unnamed_addr

declare <2 x float> @air.pow.v2f32(<2 x float>, <2 x float>) local_unnamed_addr

declare <3 x float> @air.pow.v3f32(<3 x float>, <3 x float>) local_unnamed_addr

declare <4 x float> @air.pow.v4f32(<4 x float>, <4 x float>) local_unnamed_addr

declare <2 x half> @air.reflect.v2f16(<2 x half>, <2 x half>) local_unnamed_addr

declare <3 x half> @air.reflect.v3f16(<3 x half>, <3 x half>) local_unnamed_addr

declare <4 x half> @air.reflect.v4f16(<4 x half>, <4 x half>) local_unnamed_addr

declare <2 x float> @air.reflect.v2f32(<2 x float>, <2 x float>) local_unnamed_addr

declare <3 x float> @air.reflect.v3f32(<3 x float>, <3 x float>) local_unnamed_addr

declare <4 x float> @air.reflect.v4f32(<4 x float>, <4 x float>) local_unnamed_addr

declare <2 x half> @air.refract.v2f16(<2 x half>, <2 x half>, half) local_unnamed_addr

declare <3 x half> @air.refract.v3f16(<3 x half>, <3 x half>, half) local_unnamed_addr

declare <4 x half> @air.refract.v4f16(<4 x half>, <4 x half>, half) local_unnamed_addr

declare <2 x float> @air.refract.v2f32(<2 x float>, <2 x float>, float) local_unnamed_addr

declare <3 x float> @air.refract.v3f32(<3 x float>, <3 x float>, float) local_unnamed_addr

declare <4 x float> @air.refract.v4f32(<4 x float>, <4 x float>, float) local_unnamed_addr

declare half @air.round.f16(half) local_unnamed_addr

declare <2 x half> @air.round.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.round.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.round.v4f16(<4 x half>) local_unnamed_addr

declare float @air.round.f32(float) local_unnamed_addr

declare <2 x float> @air.round.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.round.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.round.v4f32(<4 x float>) local_unnamed_addr

declare <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) nocapture readonly, ptr addrspace(2) nocapture readonly, <2 x float>, i1, <2 x i32>, i1, float, float, i32) local_unnamed_addr

declare i8 @air.sign.i8(i8) local_unnamed_addr

declare <2 x i8> @air.sign.v2i8(<2 x i8>) local_unnamed_addr

declare <3 x i8> @air.sign.v3i8(<3 x i8>) local_unnamed_addr

declare <4 x i8> @air.sign.v4i8(<4 x i8>) local_unnamed_addr

declare i16 @air.sign.i16(i16) local_unnamed_addr

declare <2 x i16> @air.sign.v2i16(<2 x i16>) local_unnamed_addr

declare <3 x i16> @air.sign.v3i16(<3 x i16>) local_unnamed_addr

declare <4 x i16> @air.sign.v4i16(<4 x i16>) local_unnamed_addr

declare i32 @air.sign.i32(i32) local_unnamed_addr

declare <2 x i32> @air.sign.v2i32(<2 x i32>) local_unnamed_addr

declare <3 x i32> @air.sign.v3i32(<3 x i32>) local_unnamed_addr

declare <4 x i32> @air.sign.v4i32(<4 x i32>) local_unnamed_addr

declare half @air.sign.f16(half) local_unnamed_addr

declare <2 x half> @air.sign.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.sign.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.sign.v4f16(<4 x half>) local_unnamed_addr

declare float @air.sign.f32(float) local_unnamed_addr

declare <2 x float> @air.sign.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.sign.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.sign.v4f32(<4 x float>) local_unnamed_addr

declare float @air.sin.f32(float) local_unnamed_addr

declare float @air.sinh.f32(float) local_unnamed_addr

declare half @air.smoothstep.f16(half, half, half) local_unnamed_addr

declare <2 x half> @air.smoothstep.v2f16(<2 x half>, <2 x half>, <2 x half>) local_unnamed_addr

declare <3 x half> @air.smoothstep.v3f16(<3 x half>, <3 x half>, <3 x half>) local_unnamed_addr

declare <4 x half> @air.smoothstep.v4f16(<4 x half>, <4 x half>, <4 x half>) local_unnamed_addr

declare float @air.smoothstep.f32(float, float, float) local_unnamed_addr

declare <2 x float> @air.smoothstep.v2f32(<2 x float>, <2 x float>, <2 x float>) local_unnamed_addr

declare <3 x float> @air.smoothstep.v3f32(<3 x float>, <3 x float>, <3 x float>) local_unnamed_addr

declare <4 x float> @air.smoothstep.v4f32(<4 x float>, <4 x float>, <4 x float>) local_unnamed_addr

declare half @air.sqrt.f16(half) local_unnamed_addr

declare <2 x half> @air.sqrt.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.sqrt.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.sqrt.v4f16(<4 x half>) local_unnamed_addr

declare float @air.sqrt.f32(float) local_unnamed_addr

declare <2 x float> @air.sqrt.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.sqrt.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.sqrt.v4f32(<4 x float>) local_unnamed_addr

declare half @air.step.f16(half, half) local_unnamed_addr

declare <2 x half> @air.step.v2f16(<2 x half>, <2 x half>) local_unnamed_addr

declare <3 x half> @air.step.v3f16(<3 x half>, <3 x half>) local_unnamed_addr

declare <4 x half> @air.step.v4f16(<4 x half>, <4 x half>) local_unnamed_addr

declare float @air.step.f32(float, float) local_unnamed_addr

declare <2 x float> @air.step.v2f32(<2 x float>, <2 x float>) local_unnamed_addr

declare <3 x float> @air.step.v3f32(<3 x float>, <3 x float>) local_unnamed_addr

declare <4 x float> @air.step.v4f32(<4 x float>, <4 x float>) local_unnamed_addr

declare float @air.tan.f32(float) local_unnamed_addr

declare float @air.tanh.f32(float) local_unnamed_addr

declare i8 @convert.s.i8.s.i32(i32) local_unnamed_addr

declare i16 @convert.s.i16.s.i32(i32) local_unnamed_addr

declare half @convert.f.f16.f.f32(float) local_unnamed_addr

define %FragmentOut @testStandardFunctions(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler) local_unnamed_addr {
  %_262 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_263 = tail call i8 @air.abs.i8(i8 %_262)
  %_264 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_265 = insertelement <2 x i8> undef, i8 %_264, i64 0
  %_266 = shufflevector <2 x i8> %_265, <2 x i8> poison, <2 x i32> zeroinitializer
  %_267 = tail call <2 x i8> @air.abs.v2i8(<2 x i8> %_266)
  %_268 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_269 = insertelement <3 x i8> undef, i8 %_268, i64 0
  %_271 = shufflevector <3 x i8> %_269, <3 x i8> poison, <3 x i32> zeroinitializer
  %_272 = tail call <3 x i8> @air.abs.v3i8(<3 x i8> %_271)
  %_273 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_274 = insertelement <4 x i8> undef, i8 %_273, i64 0
  %_277 = shufflevector <4 x i8> %_274, <4 x i8> poison, <4 x i32> zeroinitializer
  %_278 = tail call <4 x i8> @air.abs.v4i8(<4 x i8> %_277)
  %_279 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_280 = tail call i16 @air.abs.i16(i16 %_279)
  %_281 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_282 = insertelement <2 x i16> undef, i16 %_281, i64 0
  %_283 = shufflevector <2 x i16> %_282, <2 x i16> poison, <2 x i32> zeroinitializer
  %_284 = tail call <2 x i16> @air.abs.v2i16(<2 x i16> %_283)
  %_285 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_286 = insertelement <3 x i16> undef, i16 %_285, i64 0
  %_288 = shufflevector <3 x i16> %_286, <3 x i16> poison, <3 x i32> zeroinitializer
  %_289 = tail call <3 x i16> @air.abs.v3i16(<3 x i16> %_288)
  %_290 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_291 = insertelement <4 x i16> undef, i16 %_290, i64 0
  %_294 = shufflevector <4 x i16> %_291, <4 x i16> poison, <4 x i32> zeroinitializer
  %_295 = tail call <4 x i16> @air.abs.v4i16(<4 x i16> %_294)
  %_296 = tail call i32 @air.abs.i32(i32 0)
  %_297 = tail call <2 x i32> @air.abs.v2i32(<2 x i32> zeroinitializer)
  %_298 = tail call <3 x i32> @air.abs.v3i32(<3 x i32> zeroinitializer)
  %_299 = tail call <4 x i32> @air.abs.v4i32(<4 x i32> zeroinitializer)
  %_300 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_301 = tail call half @air.abs.f16(half %_300)
  %_302 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_303 = insertelement <2 x half> undef, half %_302, i64 0
  %_304 = shufflevector <2 x half> %_303, <2 x half> poison, <2 x i32> zeroinitializer
  %_305 = tail call <2 x half> @air.abs.v2f16(<2 x half> %_304)
  %_306 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_307 = insertelement <3 x half> undef, half %_306, i64 0
  %_309 = shufflevector <3 x half> %_307, <3 x half> poison, <3 x i32> zeroinitializer
  %_310 = tail call <3 x half> @air.abs.v3f16(<3 x half> %_309)
  %_311 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_312 = insertelement <4 x half> undef, half %_311, i64 0
  %_315 = shufflevector <4 x half> %_312, <4 x half> poison, <4 x i32> zeroinitializer
  %_316 = tail call <4 x half> @air.abs.v4f16(<4 x half> %_315)
  %_317 = tail call float @air.abs.f32(float 0.000000e+00)
  %_318 = tail call <2 x float> @air.abs.v2f32(<2 x float> zeroinitializer)
  %_319 = tail call <3 x float> @air.abs.v3f32(<3 x float> zeroinitializer)
  %_320 = tail call <4 x float> @air.abs.v4f32(<4 x float> zeroinitializer)
  %_321 = tail call float @air.acos.f32(float 0.000000e+00)
  %_322 = tail call float @air.acosh.f32(float 0.000000e+00)
  %_323 = tail call float @air.asin.f32(float 0.000000e+00)
  %_324 = tail call float @air.asinh.f32(float 0.000000e+00)
  %_325 = tail call float @air.atan.f32(float 0.000000e+00)
  %_326 = tail call float @air.atanh.f32(float 0.000000e+00)
  %_327 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_328 = tail call half @air.ceil.f16(half %_327)
  %_329 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_330 = insertelement <2 x half> undef, half %_329, i64 0
  %_331 = shufflevector <2 x half> %_330, <2 x half> poison, <2 x i32> zeroinitializer
  %_332 = tail call <2 x half> @air.ceil.v2f16(<2 x half> %_331)
  %_333 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_334 = insertelement <3 x half> undef, half %_333, i64 0
  %_336 = shufflevector <3 x half> %_334, <3 x half> poison, <3 x i32> zeroinitializer
  %_337 = tail call <3 x half> @air.ceil.v3f16(<3 x half> %_336)
  %_338 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_339 = insertelement <4 x half> undef, half %_338, i64 0
  %_342 = shufflevector <4 x half> %_339, <4 x half> poison, <4 x i32> zeroinitializer
  %_343 = tail call <4 x half> @air.ceil.v4f16(<4 x half> %_342)
  %_344 = tail call float @air.ceil.f32(float 0.000000e+00)
  %_345 = tail call <2 x float> @air.ceil.v2f32(<2 x float> zeroinitializer)
  %_346 = tail call <3 x float> @air.ceil.v3f32(<3 x float> zeroinitializer)
  %_347 = tail call <4 x float> @air.ceil.v4f32(<4 x float> zeroinitializer)
  %_348 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_349 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_350 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_351 = tail call i8 @air.clamp.i8(i8 %_348, i8 %_349, i8 %_350)
  %_352 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_353 = insertelement <2 x i8> undef, i8 %_352, i64 0
  %_354 = shufflevector <2 x i8> %_353, <2 x i8> poison, <2 x i32> zeroinitializer
  %_355 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_356 = insertelement <2 x i8> undef, i8 %_355, i64 0
  %_357 = shufflevector <2 x i8> %_356, <2 x i8> poison, <2 x i32> zeroinitializer
  %_358 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_359 = insertelement <2 x i8> undef, i8 %_358, i64 0
  %_360 = shufflevector <2 x i8> %_359, <2 x i8> poison, <2 x i32> zeroinitializer
  %_361 = tail call <2 x i8> @air.clamp.v2i8(<2 x i8> %_354, <2 x i8> %_357, <2 x i8> %_360)
  %_362 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_363 = insertelement <3 x i8> undef, i8 %_362, i64 0
  %_365 = shufflevector <3 x i8> %_363, <3 x i8> poison, <3 x i32> zeroinitializer
  %_366 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_367 = insertelement <3 x i8> undef, i8 %_366, i64 0
  %_369 = shufflevector <3 x i8> %_367, <3 x i8> poison, <3 x i32> zeroinitializer
  %_370 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_371 = insertelement <3 x i8> undef, i8 %_370, i64 0
  %_373 = shufflevector <3 x i8> %_371, <3 x i8> poison, <3 x i32> zeroinitializer
  %_374 = tail call <3 x i8> @air.clamp.v3i8(<3 x i8> %_365, <3 x i8> %_369, <3 x i8> %_373)
  %_375 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_376 = insertelement <4 x i8> undef, i8 %_375, i64 0
  %_379 = shufflevector <4 x i8> %_376, <4 x i8> poison, <4 x i32> zeroinitializer
  %_380 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_381 = insertelement <4 x i8> undef, i8 %_380, i64 0
  %_384 = shufflevector <4 x i8> %_381, <4 x i8> poison, <4 x i32> zeroinitializer
  %_385 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_386 = insertelement <4 x i8> undef, i8 %_385, i64 0
  %_389 = shufflevector <4 x i8> %_386, <4 x i8> poison, <4 x i32> zeroinitializer
  %_390 = tail call <4 x i8> @air.clamp.v4i8(<4 x i8> %_379, <4 x i8> %_384, <4 x i8> %_389)
  %_391 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_392 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_393 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_394 = tail call i16 @air.clamp.i16(i16 %_391, i16 %_392, i16 %_393)
  %_395 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_396 = insertelement <2 x i16> undef, i16 %_395, i64 0
  %_397 = shufflevector <2 x i16> %_396, <2 x i16> poison, <2 x i32> zeroinitializer
  %_398 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_399 = insertelement <2 x i16> undef, i16 %_398, i64 0
  %_400 = shufflevector <2 x i16> %_399, <2 x i16> poison, <2 x i32> zeroinitializer
  %_401 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_402 = insertelement <2 x i16> undef, i16 %_401, i64 0
  %_403 = shufflevector <2 x i16> %_402, <2 x i16> poison, <2 x i32> zeroinitializer
  %_404 = tail call <2 x i16> @air.clamp.v2i16(<2 x i16> %_397, <2 x i16> %_400, <2 x i16> %_403)
  %_405 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_406 = insertelement <3 x i16> undef, i16 %_405, i64 0
  %_408 = shufflevector <3 x i16> %_406, <3 x i16> poison, <3 x i32> zeroinitializer
  %_409 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_410 = insertelement <3 x i16> undef, i16 %_409, i64 0
  %_412 = shufflevector <3 x i16> %_410, <3 x i16> poison, <3 x i32> zeroinitializer
  %_413 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_414 = insertelement <3 x i16> undef, i16 %_413, i64 0
  %_416 = shufflevector <3 x i16> %_414, <3 x i16> poison, <3 x i32> zeroinitializer
  %_417 = tail call <3 x i16> @air.clamp.v3i16(<3 x i16> %_408, <3 x i16> %_412, <3 x i16> %_416)
  %_418 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_419 = insertelement <4 x i16> undef, i16 %_418, i64 0
  %_422 = shufflevector <4 x i16> %_419, <4 x i16> poison, <4 x i32> zeroinitializer
  %_423 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_424 = insertelement <4 x i16> undef, i16 %_423, i64 0
  %_427 = shufflevector <4 x i16> %_424, <4 x i16> poison, <4 x i32> zeroinitializer
  %_428 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_429 = insertelement <4 x i16> undef, i16 %_428, i64 0
  %_432 = shufflevector <4 x i16> %_429, <4 x i16> poison, <4 x i32> zeroinitializer
  %_433 = tail call <4 x i16> @air.clamp.v4i16(<4 x i16> %_422, <4 x i16> %_427, <4 x i16> %_432)
  %_434 = tail call i32 @air.clamp.i32(i32 0, i32 0, i32 0)
  %_435 = tail call <2 x i32> @air.clamp.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_436 = tail call <3 x i32> @air.clamp.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_437 = tail call <4 x i32> @air.clamp.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_438 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_439 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_440 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_441 = tail call half @air.clamp.f16(half %_438, half %_439, half %_440)
  %_442 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_443 = insertelement <2 x half> undef, half %_442, i64 0
  %_444 = shufflevector <2 x half> %_443, <2 x half> poison, <2 x i32> zeroinitializer
  %_445 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_446 = insertelement <2 x half> undef, half %_445, i64 0
  %_447 = shufflevector <2 x half> %_446, <2 x half> poison, <2 x i32> zeroinitializer
  %_448 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_449 = insertelement <2 x half> undef, half %_448, i64 0
  %_450 = shufflevector <2 x half> %_449, <2 x half> poison, <2 x i32> zeroinitializer
  %_451 = tail call <2 x half> @air.clamp.v2f16(<2 x half> %_444, <2 x half> %_447, <2 x half> %_450)
  %_452 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_453 = insertelement <3 x half> undef, half %_452, i64 0
  %_455 = shufflevector <3 x half> %_453, <3 x half> poison, <3 x i32> zeroinitializer
  %_456 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_457 = insertelement <3 x half> undef, half %_456, i64 0
  %_459 = shufflevector <3 x half> %_457, <3 x half> poison, <3 x i32> zeroinitializer
  %_460 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_461 = insertelement <3 x half> undef, half %_460, i64 0
  %_463 = shufflevector <3 x half> %_461, <3 x half> poison, <3 x i32> zeroinitializer
  %_464 = tail call <3 x half> @air.clamp.v3f16(<3 x half> %_455, <3 x half> %_459, <3 x half> %_463)
  %_465 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_466 = insertelement <4 x half> undef, half %_465, i64 0
  %_469 = shufflevector <4 x half> %_466, <4 x half> poison, <4 x i32> zeroinitializer
  %_470 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_471 = insertelement <4 x half> undef, half %_470, i64 0
  %_474 = shufflevector <4 x half> %_471, <4 x half> poison, <4 x i32> zeroinitializer
  %_475 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_476 = insertelement <4 x half> undef, half %_475, i64 0
  %_479 = shufflevector <4 x half> %_476, <4 x half> poison, <4 x i32> zeroinitializer
  %_480 = tail call <4 x half> @air.clamp.v4f16(<4 x half> %_469, <4 x half> %_474, <4 x half> %_479)
  %_481 = tail call float @air.clamp.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_482 = tail call <2 x float> @air.clamp.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_483 = tail call <3 x float> @air.clamp.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_484 = tail call <4 x float> @air.clamp.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_485 = tail call float @air.cos.f32(float 0.000000e+00)
  %_486 = tail call float @air.cosh.f32(float 0.000000e+00)
  %_487 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_488 = insertelement <3 x half> undef, half %_487, i64 0
  %_490 = shufflevector <3 x half> %_488, <3 x half> poison, <3 x i32> zeroinitializer
  %_491 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_492 = insertelement <3 x half> undef, half %_491, i64 0
  %_494 = shufflevector <3 x half> %_492, <3 x half> poison, <3 x i32> zeroinitializer
  %_495 = tail call <3 x half> @air.cross.v3f16(<3 x half> %_490, <3 x half> %_494)
  %_496 = tail call <3 x float> @air.cross.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_497 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_498 = insertelement <2 x half> undef, half %_497, i64 0
  %_499 = shufflevector <2 x half> %_498, <2 x half> poison, <2 x i32> zeroinitializer
  %_500 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_501 = insertelement <2 x half> undef, half %_500, i64 0
  %_502 = shufflevector <2 x half> %_501, <2 x half> poison, <2 x i32> zeroinitializer
  %_503 = tail call half @air.distance.v2f16(<2 x half> %_499, <2 x half> %_502)
  %_504 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_505 = insertelement <3 x half> undef, half %_504, i64 0
  %_507 = shufflevector <3 x half> %_505, <3 x half> poison, <3 x i32> zeroinitializer
  %_508 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_509 = insertelement <3 x half> undef, half %_508, i64 0
  %_511 = shufflevector <3 x half> %_509, <3 x half> poison, <3 x i32> zeroinitializer
  %_512 = tail call half @air.distance.v3f16(<3 x half> %_507, <3 x half> %_511)
  %_513 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_514 = insertelement <4 x half> undef, half %_513, i64 0
  %_517 = shufflevector <4 x half> %_514, <4 x half> poison, <4 x i32> zeroinitializer
  %_518 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_519 = insertelement <4 x half> undef, half %_518, i64 0
  %_522 = shufflevector <4 x half> %_519, <4 x half> poison, <4 x i32> zeroinitializer
  %_523 = tail call half @air.distance.v4f16(<4 x half> %_517, <4 x half> %_522)
  %_524 = tail call float @air.distance.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_525 = tail call float @air.distance.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_526 = tail call float @air.distance.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_527 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_528 = insertelement <2 x half> undef, half %_527, i64 0
  %_529 = shufflevector <2 x half> %_528, <2 x half> poison, <2 x i32> zeroinitializer
  %_530 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_531 = insertelement <2 x half> undef, half %_530, i64 0
  %_532 = shufflevector <2 x half> %_531, <2 x half> poison, <2 x i32> zeroinitializer
  %_533 = tail call half @air.dot.v2f16(<2 x half> %_529, <2 x half> %_532)
  %_534 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_535 = insertelement <3 x half> undef, half %_534, i64 0
  %_537 = shufflevector <3 x half> %_535, <3 x half> poison, <3 x i32> zeroinitializer
  %_538 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_539 = insertelement <3 x half> undef, half %_538, i64 0
  %_541 = shufflevector <3 x half> %_539, <3 x half> poison, <3 x i32> zeroinitializer
  %_542 = tail call half @air.dot.v3f16(<3 x half> %_537, <3 x half> %_541)
  %_543 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_544 = insertelement <4 x half> undef, half %_543, i64 0
  %_547 = shufflevector <4 x half> %_544, <4 x half> poison, <4 x i32> zeroinitializer
  %_548 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_549 = insertelement <4 x half> undef, half %_548, i64 0
  %_552 = shufflevector <4 x half> %_549, <4 x half> poison, <4 x i32> zeroinitializer
  %_553 = tail call half @air.dot.v4f16(<4 x half> %_547, <4 x half> %_552)
  %_554 = tail call float @air.dot.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_555 = tail call float @air.dot.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_556 = tail call float @air.dot.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_557 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_558 = tail call half @air.exp.f16(half %_557)
  %_559 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_560 = insertelement <2 x half> undef, half %_559, i64 0
  %_561 = shufflevector <2 x half> %_560, <2 x half> poison, <2 x i32> zeroinitializer
  %_562 = tail call <2 x half> @air.exp.v2f16(<2 x half> %_561)
  %_563 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_564 = insertelement <3 x half> undef, half %_563, i64 0
  %_566 = shufflevector <3 x half> %_564, <3 x half> poison, <3 x i32> zeroinitializer
  %_567 = tail call <3 x half> @air.exp.v3f16(<3 x half> %_566)
  %_568 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_569 = insertelement <4 x half> undef, half %_568, i64 0
  %_572 = shufflevector <4 x half> %_569, <4 x half> poison, <4 x i32> zeroinitializer
  %_573 = tail call <4 x half> @air.exp.v4f16(<4 x half> %_572)
  %_574 = tail call float @air.exp.f32(float 0.000000e+00)
  %_575 = tail call <2 x float> @air.exp.v2f32(<2 x float> zeroinitializer)
  %_576 = tail call <3 x float> @air.exp.v3f32(<3 x float> zeroinitializer)
  %_577 = tail call <4 x float> @air.exp.v4f32(<4 x float> zeroinitializer)
  %_578 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_579 = tail call half @air.exp2.f16(half %_578)
  %_580 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_581 = insertelement <2 x half> undef, half %_580, i64 0
  %_582 = shufflevector <2 x half> %_581, <2 x half> poison, <2 x i32> zeroinitializer
  %_583 = tail call <2 x half> @air.exp2.v2f16(<2 x half> %_582)
  %_584 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_585 = insertelement <3 x half> undef, half %_584, i64 0
  %_587 = shufflevector <3 x half> %_585, <3 x half> poison, <3 x i32> zeroinitializer
  %_588 = tail call <3 x half> @air.exp2.v3f16(<3 x half> %_587)
  %_589 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_590 = insertelement <4 x half> undef, half %_589, i64 0
  %_593 = shufflevector <4 x half> %_590, <4 x half> poison, <4 x i32> zeroinitializer
  %_594 = tail call <4 x half> @air.exp2.v4f16(<4 x half> %_593)
  %_595 = tail call float @air.exp2.f32(float 0.000000e+00)
  %_596 = tail call <2 x float> @air.exp2.v2f32(<2 x float> zeroinitializer)
  %_597 = tail call <3 x float> @air.exp2.v3f32(<3 x float> zeroinitializer)
  %_598 = tail call <4 x float> @air.exp2.v4f32(<4 x float> zeroinitializer)
  %_599 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_600 = tail call half @air.floor.f16(half %_599)
  %_601 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_602 = insertelement <2 x half> undef, half %_601, i64 0
  %_603 = shufflevector <2 x half> %_602, <2 x half> poison, <2 x i32> zeroinitializer
  %_604 = tail call <2 x half> @air.floor.v2f16(<2 x half> %_603)
  %_605 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_606 = insertelement <3 x half> undef, half %_605, i64 0
  %_608 = shufflevector <3 x half> %_606, <3 x half> poison, <3 x i32> zeroinitializer
  %_609 = tail call <3 x half> @air.floor.v3f16(<3 x half> %_608)
  %_610 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_611 = insertelement <4 x half> undef, half %_610, i64 0
  %_614 = shufflevector <4 x half> %_611, <4 x half> poison, <4 x i32> zeroinitializer
  %_615 = tail call <4 x half> @air.floor.v4f16(<4 x half> %_614)
  %_616 = tail call float @air.floor.f32(float 0.000000e+00)
  %_617 = tail call <2 x float> @air.floor.v2f32(<2 x float> zeroinitializer)
  %_618 = tail call <3 x float> @air.floor.v3f32(<3 x float> zeroinitializer)
  %_619 = tail call <4 x float> @air.floor.v4f32(<4 x float> zeroinitializer)
  %_620 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_621 = tail call half @air.fract.f16(half %_620)
  %_622 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_623 = insertelement <2 x half> undef, half %_622, i64 0
  %_624 = shufflevector <2 x half> %_623, <2 x half> poison, <2 x i32> zeroinitializer
  %_625 = tail call <2 x half> @air.fract.v2f16(<2 x half> %_624)
  %_626 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_627 = insertelement <3 x half> undef, half %_626, i64 0
  %_629 = shufflevector <3 x half> %_627, <3 x half> poison, <3 x i32> zeroinitializer
  %_630 = tail call <3 x half> @air.fract.v3f16(<3 x half> %_629)
  %_631 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_632 = insertelement <4 x half> undef, half %_631, i64 0
  %_635 = shufflevector <4 x half> %_632, <4 x half> poison, <4 x i32> zeroinitializer
  %_636 = tail call <4 x half> @air.fract.v4f16(<4 x half> %_635)
  %_637 = tail call float @air.fract.f32(float 0.000000e+00)
  %_638 = tail call <2 x float> @air.fract.v2f32(<2 x float> zeroinitializer)
  %_639 = tail call <3 x float> @air.fract.v3f32(<3 x float> zeroinitializer)
  %_640 = tail call <4 x float> @air.fract.v4f32(<4 x float> zeroinitializer)
  %_641 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_642 = tail call i1 @air.isinf.f16(half %_641)
  %_643 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_644 = insertelement <2 x half> undef, half %_643, i64 0
  %_645 = shufflevector <2 x half> %_644, <2 x half> poison, <2 x i32> zeroinitializer
  %_646 = tail call <2 x i1> @air.isinf.v2f16(<2 x half> %_645)
  %_647 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_648 = insertelement <3 x half> undef, half %_647, i64 0
  %_650 = shufflevector <3 x half> %_648, <3 x half> poison, <3 x i32> zeroinitializer
  %_651 = tail call <3 x i1> @air.isinf.v3f16(<3 x half> %_650)
  %_652 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_653 = insertelement <4 x half> undef, half %_652, i64 0
  %_656 = shufflevector <4 x half> %_653, <4 x half> poison, <4 x i32> zeroinitializer
  %_657 = tail call <4 x i1> @air.isinf.v4f16(<4 x half> %_656)
  %_658 = tail call i1 @air.isinf.f32(float 0.000000e+00)
  %_659 = tail call <2 x i1> @air.isinf.v2f32(<2 x float> zeroinitializer)
  %_660 = tail call <3 x i1> @air.isinf.v3f32(<3 x float> zeroinitializer)
  %_661 = tail call <4 x i1> @air.isinf.v4f32(<4 x float> zeroinitializer)
  %_662 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_663 = tail call i1 @air.isnan.f16(half %_662)
  %_664 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_665 = insertelement <2 x half> undef, half %_664, i64 0
  %_666 = shufflevector <2 x half> %_665, <2 x half> poison, <2 x i32> zeroinitializer
  %_667 = tail call <2 x i1> @air.isnan.v2f16(<2 x half> %_666)
  %_668 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_669 = insertelement <3 x half> undef, half %_668, i64 0
  %_671 = shufflevector <3 x half> %_669, <3 x half> poison, <3 x i32> zeroinitializer
  %_672 = tail call <3 x i1> @air.isnan.v3f16(<3 x half> %_671)
  %_673 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_674 = insertelement <4 x half> undef, half %_673, i64 0
  %_677 = shufflevector <4 x half> %_674, <4 x half> poison, <4 x i32> zeroinitializer
  %_678 = tail call <4 x i1> @air.isnan.v4f16(<4 x half> %_677)
  %_679 = tail call i1 @air.isnan.f32(float 0.000000e+00)
  %_680 = tail call <2 x i1> @air.isnan.v2f32(<2 x float> zeroinitializer)
  %_681 = tail call <3 x i1> @air.isnan.v3f32(<3 x float> zeroinitializer)
  %_682 = tail call <4 x i1> @air.isnan.v4f32(<4 x float> zeroinitializer)
  %_683 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_684 = insertelement <2 x half> undef, half %_683, i64 0
  %_685 = shufflevector <2 x half> %_684, <2 x half> poison, <2 x i32> zeroinitializer
  %_686 = tail call half @air.length.v2f16(<2 x half> %_685)
  %_687 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_688 = insertelement <3 x half> undef, half %_687, i64 0
  %_690 = shufflevector <3 x half> %_688, <3 x half> poison, <3 x i32> zeroinitializer
  %_691 = tail call half @air.length.v3f16(<3 x half> %_690)
  %_692 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_693 = insertelement <4 x half> undef, half %_692, i64 0
  %_696 = shufflevector <4 x half> %_693, <4 x half> poison, <4 x i32> zeroinitializer
  %_697 = tail call half @air.length.v4f16(<4 x half> %_696)
  %_698 = tail call float @air.length.v2f32(<2 x float> zeroinitializer)
  %_699 = tail call float @air.length.v3f32(<3 x float> zeroinitializer)
  %_700 = tail call float @air.length.v4f32(<4 x float> zeroinitializer)
  %_701 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_702 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_703 = tail call i8 @air.max.i8(i8 %_701, i8 %_702)
  %_704 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_705 = insertelement <2 x i8> undef, i8 %_704, i64 0
  %_706 = shufflevector <2 x i8> %_705, <2 x i8> poison, <2 x i32> zeroinitializer
  %_707 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_708 = insertelement <2 x i8> undef, i8 %_707, i64 0
  %_709 = shufflevector <2 x i8> %_708, <2 x i8> poison, <2 x i32> zeroinitializer
  %_710 = tail call <2 x i8> @air.max.v2i8(<2 x i8> %_706, <2 x i8> %_709)
  %_711 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_712 = insertelement <3 x i8> undef, i8 %_711, i64 0
  %_714 = shufflevector <3 x i8> %_712, <3 x i8> poison, <3 x i32> zeroinitializer
  %_715 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_716 = insertelement <3 x i8> undef, i8 %_715, i64 0
  %_718 = shufflevector <3 x i8> %_716, <3 x i8> poison, <3 x i32> zeroinitializer
  %_719 = tail call <3 x i8> @air.max.v3i8(<3 x i8> %_714, <3 x i8> %_718)
  %_720 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_721 = insertelement <4 x i8> undef, i8 %_720, i64 0
  %_724 = shufflevector <4 x i8> %_721, <4 x i8> poison, <4 x i32> zeroinitializer
  %_725 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_726 = insertelement <4 x i8> undef, i8 %_725, i64 0
  %_729 = shufflevector <4 x i8> %_726, <4 x i8> poison, <4 x i32> zeroinitializer
  %_730 = tail call <4 x i8> @air.max.v4i8(<4 x i8> %_724, <4 x i8> %_729)
  %_731 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_732 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_733 = tail call i16 @air.max.i16(i16 %_731, i16 %_732)
  %_734 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_735 = insertelement <2 x i16> undef, i16 %_734, i64 0
  %_736 = shufflevector <2 x i16> %_735, <2 x i16> poison, <2 x i32> zeroinitializer
  %_737 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_738 = insertelement <2 x i16> undef, i16 %_737, i64 0
  %_739 = shufflevector <2 x i16> %_738, <2 x i16> poison, <2 x i32> zeroinitializer
  %_740 = tail call <2 x i16> @air.max.v2i16(<2 x i16> %_736, <2 x i16> %_739)
  %_741 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_742 = insertelement <3 x i16> undef, i16 %_741, i64 0
  %_744 = shufflevector <3 x i16> %_742, <3 x i16> poison, <3 x i32> zeroinitializer
  %_745 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_746 = insertelement <3 x i16> undef, i16 %_745, i64 0
  %_748 = shufflevector <3 x i16> %_746, <3 x i16> poison, <3 x i32> zeroinitializer
  %_749 = tail call <3 x i16> @air.max.v3i16(<3 x i16> %_744, <3 x i16> %_748)
  %_750 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_751 = insertelement <4 x i16> undef, i16 %_750, i64 0
  %_754 = shufflevector <4 x i16> %_751, <4 x i16> poison, <4 x i32> zeroinitializer
  %_755 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_756 = insertelement <4 x i16> undef, i16 %_755, i64 0
  %_759 = shufflevector <4 x i16> %_756, <4 x i16> poison, <4 x i32> zeroinitializer
  %_760 = tail call <4 x i16> @air.max.v4i16(<4 x i16> %_754, <4 x i16> %_759)
  %_761 = tail call i32 @air.max.i32(i32 0, i32 0)
  %_762 = tail call <2 x i32> @air.max.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_763 = tail call <3 x i32> @air.max.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_764 = tail call <4 x i32> @air.max.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_765 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_766 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_767 = tail call half @air.max.f16(half %_765, half %_766)
  %_768 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_769 = insertelement <2 x half> undef, half %_768, i64 0
  %_770 = shufflevector <2 x half> %_769, <2 x half> poison, <2 x i32> zeroinitializer
  %_771 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_772 = insertelement <2 x half> undef, half %_771, i64 0
  %_773 = shufflevector <2 x half> %_772, <2 x half> poison, <2 x i32> zeroinitializer
  %_774 = tail call <2 x half> @air.max.v2f16(<2 x half> %_770, <2 x half> %_773)
  %_775 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_776 = insertelement <3 x half> undef, half %_775, i64 0
  %_778 = shufflevector <3 x half> %_776, <3 x half> poison, <3 x i32> zeroinitializer
  %_779 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_780 = insertelement <3 x half> undef, half %_779, i64 0
  %_782 = shufflevector <3 x half> %_780, <3 x half> poison, <3 x i32> zeroinitializer
  %_783 = tail call <3 x half> @air.max.v3f16(<3 x half> %_778, <3 x half> %_782)
  %_784 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_785 = insertelement <4 x half> undef, half %_784, i64 0
  %_788 = shufflevector <4 x half> %_785, <4 x half> poison, <4 x i32> zeroinitializer
  %_789 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_790 = insertelement <4 x half> undef, half %_789, i64 0
  %_793 = shufflevector <4 x half> %_790, <4 x half> poison, <4 x i32> zeroinitializer
  %_794 = tail call <4 x half> @air.max.v4f16(<4 x half> %_788, <4 x half> %_793)
  %_795 = tail call float @air.max.f32(float 0.000000e+00, float 0.000000e+00)
  %_796 = tail call <2 x float> @air.max.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_797 = tail call <3 x float> @air.max.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_798 = tail call <4 x float> @air.max.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_799 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_800 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_801 = tail call i8 @air.min.i8(i8 %_799, i8 %_800)
  %_802 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_803 = insertelement <2 x i8> undef, i8 %_802, i64 0
  %_804 = shufflevector <2 x i8> %_803, <2 x i8> poison, <2 x i32> zeroinitializer
  %_805 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_806 = insertelement <2 x i8> undef, i8 %_805, i64 0
  %_807 = shufflevector <2 x i8> %_806, <2 x i8> poison, <2 x i32> zeroinitializer
  %_808 = tail call <2 x i8> @air.min.v2i8(<2 x i8> %_804, <2 x i8> %_807)
  %_809 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_810 = insertelement <3 x i8> undef, i8 %_809, i64 0
  %_812 = shufflevector <3 x i8> %_810, <3 x i8> poison, <3 x i32> zeroinitializer
  %_813 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_814 = insertelement <3 x i8> undef, i8 %_813, i64 0
  %_816 = shufflevector <3 x i8> %_814, <3 x i8> poison, <3 x i32> zeroinitializer
  %_817 = tail call <3 x i8> @air.min.v3i8(<3 x i8> %_812, <3 x i8> %_816)
  %_818 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_819 = insertelement <4 x i8> undef, i8 %_818, i64 0
  %_822 = shufflevector <4 x i8> %_819, <4 x i8> poison, <4 x i32> zeroinitializer
  %_823 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_824 = insertelement <4 x i8> undef, i8 %_823, i64 0
  %_827 = shufflevector <4 x i8> %_824, <4 x i8> poison, <4 x i32> zeroinitializer
  %_828 = tail call <4 x i8> @air.min.v4i8(<4 x i8> %_822, <4 x i8> %_827)
  %_829 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_830 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_831 = tail call i16 @air.min.i16(i16 %_829, i16 %_830)
  %_832 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_833 = insertelement <2 x i16> undef, i16 %_832, i64 0
  %_834 = shufflevector <2 x i16> %_833, <2 x i16> poison, <2 x i32> zeroinitializer
  %_835 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_836 = insertelement <2 x i16> undef, i16 %_835, i64 0
  %_837 = shufflevector <2 x i16> %_836, <2 x i16> poison, <2 x i32> zeroinitializer
  %_838 = tail call <2 x i16> @air.min.v2i16(<2 x i16> %_834, <2 x i16> %_837)
  %_839 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_840 = insertelement <3 x i16> undef, i16 %_839, i64 0
  %_842 = shufflevector <3 x i16> %_840, <3 x i16> poison, <3 x i32> zeroinitializer
  %_843 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_844 = insertelement <3 x i16> undef, i16 %_843, i64 0
  %_846 = shufflevector <3 x i16> %_844, <3 x i16> poison, <3 x i32> zeroinitializer
  %_847 = tail call <3 x i16> @air.min.v3i16(<3 x i16> %_842, <3 x i16> %_846)
  %_848 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_849 = insertelement <4 x i16> undef, i16 %_848, i64 0
  %_852 = shufflevector <4 x i16> %_849, <4 x i16> poison, <4 x i32> zeroinitializer
  %_853 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_854 = insertelement <4 x i16> undef, i16 %_853, i64 0
  %_857 = shufflevector <4 x i16> %_854, <4 x i16> poison, <4 x i32> zeroinitializer
  %_858 = tail call <4 x i16> @air.min.v4i16(<4 x i16> %_852, <4 x i16> %_857)
  %_859 = tail call i32 @air.min.i32(i32 0, i32 0)
  %_860 = tail call <2 x i32> @air.min.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_861 = tail call <3 x i32> @air.min.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_862 = tail call <4 x i32> @air.min.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_863 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_864 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_865 = tail call half @air.min.f16(half %_863, half %_864)
  %_866 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_867 = insertelement <2 x half> undef, half %_866, i64 0
  %_868 = shufflevector <2 x half> %_867, <2 x half> poison, <2 x i32> zeroinitializer
  %_869 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_870 = insertelement <2 x half> undef, half %_869, i64 0
  %_871 = shufflevector <2 x half> %_870, <2 x half> poison, <2 x i32> zeroinitializer
  %_872 = tail call <2 x half> @air.min.v2f16(<2 x half> %_868, <2 x half> %_871)
  %_873 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_874 = insertelement <3 x half> undef, half %_873, i64 0
  %_876 = shufflevector <3 x half> %_874, <3 x half> poison, <3 x i32> zeroinitializer
  %_877 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_878 = insertelement <3 x half> undef, half %_877, i64 0
  %_880 = shufflevector <3 x half> %_878, <3 x half> poison, <3 x i32> zeroinitializer
  %_881 = tail call <3 x half> @air.min.v3f16(<3 x half> %_876, <3 x half> %_880)
  %_882 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_883 = insertelement <4 x half> undef, half %_882, i64 0
  %_886 = shufflevector <4 x half> %_883, <4 x half> poison, <4 x i32> zeroinitializer
  %_887 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_888 = insertelement <4 x half> undef, half %_887, i64 0
  %_891 = shufflevector <4 x half> %_888, <4 x half> poison, <4 x i32> zeroinitializer
  %_892 = tail call <4 x half> @air.min.v4f16(<4 x half> %_886, <4 x half> %_891)
  %_893 = tail call float @air.min.f32(float 0.000000e+00, float 0.000000e+00)
  %_894 = tail call <2 x float> @air.min.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_895 = tail call <3 x float> @air.min.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_896 = tail call <4 x float> @air.min.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_897 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_898 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_899 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_900 = tail call half @air.mix.f16(half %_897, half %_898, half %_899)
  %_901 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_902 = insertelement <2 x half> undef, half %_901, i64 0
  %_903 = shufflevector <2 x half> %_902, <2 x half> poison, <2 x i32> zeroinitializer
  %_904 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_905 = insertelement <2 x half> undef, half %_904, i64 0
  %_906 = shufflevector <2 x half> %_905, <2 x half> poison, <2 x i32> zeroinitializer
  %_907 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_908 = insertelement <2 x half> undef, half %_907, i64 0
  %_909 = shufflevector <2 x half> %_908, <2 x half> poison, <2 x i32> zeroinitializer
  %_910 = tail call <2 x half> @air.mix.v2f16(<2 x half> %_903, <2 x half> %_906, <2 x half> %_909)
  %_911 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_912 = insertelement <3 x half> undef, half %_911, i64 0
  %_914 = shufflevector <3 x half> %_912, <3 x half> poison, <3 x i32> zeroinitializer
  %_915 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_916 = insertelement <3 x half> undef, half %_915, i64 0
  %_918 = shufflevector <3 x half> %_916, <3 x half> poison, <3 x i32> zeroinitializer
  %_919 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_920 = insertelement <3 x half> undef, half %_919, i64 0
  %_922 = shufflevector <3 x half> %_920, <3 x half> poison, <3 x i32> zeroinitializer
  %_923 = tail call <3 x half> @air.mix.v3f16(<3 x half> %_914, <3 x half> %_918, <3 x half> %_922)
  %_924 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_925 = insertelement <4 x half> undef, half %_924, i64 0
  %_928 = shufflevector <4 x half> %_925, <4 x half> poison, <4 x i32> zeroinitializer
  %_929 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_930 = insertelement <4 x half> undef, half %_929, i64 0
  %_933 = shufflevector <4 x half> %_930, <4 x half> poison, <4 x i32> zeroinitializer
  %_934 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_935 = insertelement <4 x half> undef, half %_934, i64 0
  %_938 = shufflevector <4 x half> %_935, <4 x half> poison, <4 x i32> zeroinitializer
  %_939 = tail call <4 x half> @air.mix.v4f16(<4 x half> %_928, <4 x half> %_933, <4 x half> %_938)
  %_940 = tail call float @air.mix.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_941 = tail call <2 x float> @air.mix.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_942 = tail call <3 x float> @air.mix.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_943 = tail call <4 x float> @air.mix.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_944 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_945 = insertelement <2 x half> undef, half %_944, i64 0
  %_946 = shufflevector <2 x half> %_945, <2 x half> poison, <2 x i32> zeroinitializer
  %_947 = tail call <2 x half> @air.normalize.v2f16(<2 x half> %_946)
  %_948 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_949 = insertelement <3 x half> undef, half %_948, i64 0
  %_951 = shufflevector <3 x half> %_949, <3 x half> poison, <3 x i32> zeroinitializer
  %_952 = tail call <3 x half> @air.normalize.v3f16(<3 x half> %_951)
  %_953 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_954 = insertelement <4 x half> undef, half %_953, i64 0
  %_957 = shufflevector <4 x half> %_954, <4 x half> poison, <4 x i32> zeroinitializer
  %_958 = tail call <4 x half> @air.normalize.v4f16(<4 x half> %_957)
  %_959 = tail call <2 x float> @air.normalize.v2f32(<2 x float> zeroinitializer)
  %_960 = tail call <3 x float> @air.normalize.v3f32(<3 x float> zeroinitializer)
  %_961 = tail call <4 x float> @air.normalize.v4f32(<4 x float> zeroinitializer)
  %_962 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_963 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_964 = tail call half @air.pow.f16(half %_962, half %_963)
  %_965 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_966 = insertelement <2 x half> undef, half %_965, i64 0
  %_967 = shufflevector <2 x half> %_966, <2 x half> poison, <2 x i32> zeroinitializer
  %_968 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_969 = insertelement <2 x half> undef, half %_968, i64 0
  %_970 = shufflevector <2 x half> %_969, <2 x half> poison, <2 x i32> zeroinitializer
  %_971 = tail call <2 x half> @air.pow.v2f16(<2 x half> %_967, <2 x half> %_970)
  %_972 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_973 = insertelement <3 x half> undef, half %_972, i64 0
  %_975 = shufflevector <3 x half> %_973, <3 x half> poison, <3 x i32> zeroinitializer
  %_976 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_977 = insertelement <3 x half> undef, half %_976, i64 0
  %_979 = shufflevector <3 x half> %_977, <3 x half> poison, <3 x i32> zeroinitializer
  %_980 = tail call <3 x half> @air.pow.v3f16(<3 x half> %_975, <3 x half> %_979)
  %_981 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_982 = insertelement <4 x half> undef, half %_981, i64 0
  %_985 = shufflevector <4 x half> %_982, <4 x half> poison, <4 x i32> zeroinitializer
  %_986 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_987 = insertelement <4 x half> undef, half %_986, i64 0
  %_990 = shufflevector <4 x half> %_987, <4 x half> poison, <4 x i32> zeroinitializer
  %_991 = tail call <4 x half> @air.pow.v4f16(<4 x half> %_985, <4 x half> %_990)
  %_992 = tail call float @air.pow.f32(float 0.000000e+00, float 0.000000e+00)
  %_993 = tail call <2 x float> @air.pow.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_994 = tail call <3 x float> @air.pow.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_995 = tail call <4 x float> @air.pow.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_996 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_997 = insertelement <2 x half> undef, half %_996, i64 0
  %_998 = shufflevector <2 x half> %_997, <2 x half> poison, <2 x i32> zeroinitializer
  %_999 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1000 = insertelement <2 x half> undef, half %_999, i64 0
  %_1001 = shufflevector <2 x half> %_1000, <2 x half> poison, <2 x i32> zeroinitializer
  %_1002 = tail call <2 x half> @air.reflect.v2f16(<2 x half> %_998, <2 x half> %_1001)
  %_1003 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1004 = insertelement <3 x half> undef, half %_1003, i64 0
  %_1006 = shufflevector <3 x half> %_1004, <3 x half> poison, <3 x i32> zeroinitializer
  %_1007 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1008 = insertelement <3 x half> undef, half %_1007, i64 0
  %_1010 = shufflevector <3 x half> %_1008, <3 x half> poison, <3 x i32> zeroinitializer
  %_1011 = tail call <3 x half> @air.reflect.v3f16(<3 x half> %_1006, <3 x half> %_1010)
  %_1012 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1013 = insertelement <4 x half> undef, half %_1012, i64 0
  %_1016 = shufflevector <4 x half> %_1013, <4 x half> poison, <4 x i32> zeroinitializer
  %_1017 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1018 = insertelement <4 x half> undef, half %_1017, i64 0
  %_1021 = shufflevector <4 x half> %_1018, <4 x half> poison, <4 x i32> zeroinitializer
  %_1022 = tail call <4 x half> @air.reflect.v4f16(<4 x half> %_1016, <4 x half> %_1021)
  %_1023 = tail call <2 x float> @air.reflect.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1024 = tail call <3 x float> @air.reflect.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1025 = tail call <4 x float> @air.reflect.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1026 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1027 = insertelement <2 x half> undef, half %_1026, i64 0
  %_1028 = shufflevector <2 x half> %_1027, <2 x half> poison, <2 x i32> zeroinitializer
  %_1029 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1030 = insertelement <2 x half> undef, half %_1029, i64 0
  %_1031 = shufflevector <2 x half> %_1030, <2 x half> poison, <2 x i32> zeroinitializer
  %_1032 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1033 = tail call <2 x half> @air.refract.v2f16(<2 x half> %_1028, <2 x half> %_1031, half %_1032)
  %_1034 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1035 = insertelement <3 x half> undef, half %_1034, i64 0
  %_1037 = shufflevector <3 x half> %_1035, <3 x half> poison, <3 x i32> zeroinitializer
  %_1038 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1039 = insertelement <3 x half> undef, half %_1038, i64 0
  %_1041 = shufflevector <3 x half> %_1039, <3 x half> poison, <3 x i32> zeroinitializer
  %_1042 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1043 = tail call <3 x half> @air.refract.v3f16(<3 x half> %_1037, <3 x half> %_1041, half %_1042)
  %_1044 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1045 = insertelement <4 x half> undef, half %_1044, i64 0
  %_1048 = shufflevector <4 x half> %_1045, <4 x half> poison, <4 x i32> zeroinitializer
  %_1049 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1050 = insertelement <4 x half> undef, half %_1049, i64 0
  %_1053 = shufflevector <4 x half> %_1050, <4 x half> poison, <4 x i32> zeroinitializer
  %_1054 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1055 = tail call <4 x half> @air.refract.v4f16(<4 x half> %_1048, <4 x half> %_1053, half %_1054)
  %_1056 = tail call <2 x float> @air.refract.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, float 0.000000e+00)
  %_1057 = tail call <3 x float> @air.refract.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, float 0.000000e+00)
  %_1058 = tail call <4 x float> @air.refract.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, float 0.000000e+00)
  %_1059 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1060 = tail call half @air.round.f16(half %_1059)
  %_1061 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1062 = insertelement <2 x half> undef, half %_1061, i64 0
  %_1063 = shufflevector <2 x half> %_1062, <2 x half> poison, <2 x i32> zeroinitializer
  %_1064 = tail call <2 x half> @air.round.v2f16(<2 x half> %_1063)
  %_1065 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1066 = insertelement <3 x half> undef, half %_1065, i64 0
  %_1068 = shufflevector <3 x half> %_1066, <3 x half> poison, <3 x i32> zeroinitializer
  %_1069 = tail call <3 x half> @air.round.v3f16(<3 x half> %_1068)
  %_1070 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1071 = insertelement <4 x half> undef, half %_1070, i64 0
  %_1074 = shufflevector <4 x half> %_1071, <4 x half> poison, <4 x i32> zeroinitializer
  %_1075 = tail call <4 x half> @air.round.v4f16(<4 x half> %_1074)
  %_1076 = tail call float @air.round.f32(float 0.000000e+00)
  %_1077 = tail call <2 x float> @air.round.v2f32(<2 x float> zeroinitializer)
  %_1078 = tail call <3 x float> @air.round.v3f32(<3 x float> zeroinitializer)
  %_1079 = tail call <4 x float> @air.round.v4f32(<4 x float> zeroinitializer)
  %_1082 = tail call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler, <2 x float> zeroinitializer, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %_1083 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1084 = tail call i8 @air.sign.i8(i8 %_1083)
  %_1085 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1086 = insertelement <2 x i8> undef, i8 %_1085, i64 0
  %_1087 = shufflevector <2 x i8> %_1086, <2 x i8> poison, <2 x i32> zeroinitializer
  %_1088 = tail call <2 x i8> @air.sign.v2i8(<2 x i8> %_1087)
  %_1089 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1090 = insertelement <3 x i8> undef, i8 %_1089, i64 0
  %_1092 = shufflevector <3 x i8> %_1090, <3 x i8> poison, <3 x i32> zeroinitializer
  %_1093 = tail call <3 x i8> @air.sign.v3i8(<3 x i8> %_1092)
  %_1094 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1095 = insertelement <4 x i8> undef, i8 %_1094, i64 0
  %_1098 = shufflevector <4 x i8> %_1095, <4 x i8> poison, <4 x i32> zeroinitializer
  %_1099 = tail call <4 x i8> @air.sign.v4i8(<4 x i8> %_1098)
  %_1100 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1101 = tail call i16 @air.sign.i16(i16 %_1100)
  %_1102 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1103 = insertelement <2 x i16> undef, i16 %_1102, i64 0
  %_1104 = shufflevector <2 x i16> %_1103, <2 x i16> poison, <2 x i32> zeroinitializer
  %_1105 = tail call <2 x i16> @air.sign.v2i16(<2 x i16> %_1104)
  %_1106 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1107 = insertelement <3 x i16> undef, i16 %_1106, i64 0
  %_1109 = shufflevector <3 x i16> %_1107, <3 x i16> poison, <3 x i32> zeroinitializer
  %_1110 = tail call <3 x i16> @air.sign.v3i16(<3 x i16> %_1109)
  %_1111 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1112 = insertelement <4 x i16> undef, i16 %_1111, i64 0
  %_1115 = shufflevector <4 x i16> %_1112, <4 x i16> poison, <4 x i32> zeroinitializer
  %_1116 = tail call <4 x i16> @air.sign.v4i16(<4 x i16> %_1115)
  %_1117 = tail call i32 @air.sign.i32(i32 0)
  %_1118 = tail call <2 x i32> @air.sign.v2i32(<2 x i32> zeroinitializer)
  %_1119 = tail call <3 x i32> @air.sign.v3i32(<3 x i32> zeroinitializer)
  %_1120 = tail call <4 x i32> @air.sign.v4i32(<4 x i32> zeroinitializer)
  %_1121 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1122 = tail call half @air.sign.f16(half %_1121)
  %_1123 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1124 = insertelement <2 x half> undef, half %_1123, i64 0
  %_1125 = shufflevector <2 x half> %_1124, <2 x half> poison, <2 x i32> zeroinitializer
  %_1126 = tail call <2 x half> @air.sign.v2f16(<2 x half> %_1125)
  %_1127 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1128 = insertelement <3 x half> undef, half %_1127, i64 0
  %_1130 = shufflevector <3 x half> %_1128, <3 x half> poison, <3 x i32> zeroinitializer
  %_1131 = tail call <3 x half> @air.sign.v3f16(<3 x half> %_1130)
  %_1132 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1133 = insertelement <4 x half> undef, half %_1132, i64 0
  %_1136 = shufflevector <4 x half> %_1133, <4 x half> poison, <4 x i32> zeroinitializer
  %_1137 = tail call <4 x half> @air.sign.v4f16(<4 x half> %_1136)
  %_1138 = tail call float @air.sign.f32(float 0.000000e+00)
  %_1139 = tail call <2 x float> @air.sign.v2f32(<2 x float> zeroinitializer)
  %_1140 = tail call <3 x float> @air.sign.v3f32(<3 x float> zeroinitializer)
  %_1141 = tail call <4 x float> @air.sign.v4f32(<4 x float> zeroinitializer)
  %_1142 = tail call float @air.sin.f32(float 0.000000e+00)
  %_1143 = tail call float @air.sinh.f32(float 0.000000e+00)
  %_1144 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1145 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1146 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1147 = tail call half @air.smoothstep.f16(half %_1144, half %_1145, half %_1146)
  %_1148 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1149 = insertelement <2 x half> undef, half %_1148, i64 0
  %_1150 = shufflevector <2 x half> %_1149, <2 x half> poison, <2 x i32> zeroinitializer
  %_1151 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1152 = insertelement <2 x half> undef, half %_1151, i64 0
  %_1153 = shufflevector <2 x half> %_1152, <2 x half> poison, <2 x i32> zeroinitializer
  %_1154 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1155 = insertelement <2 x half> undef, half %_1154, i64 0
  %_1156 = shufflevector <2 x half> %_1155, <2 x half> poison, <2 x i32> zeroinitializer
  %_1157 = tail call <2 x half> @air.smoothstep.v2f16(<2 x half> %_1150, <2 x half> %_1153, <2 x half> %_1156)
  %_1158 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1159 = insertelement <3 x half> undef, half %_1158, i64 0
  %_1161 = shufflevector <3 x half> %_1159, <3 x half> poison, <3 x i32> zeroinitializer
  %_1162 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1163 = insertelement <3 x half> undef, half %_1162, i64 0
  %_1165 = shufflevector <3 x half> %_1163, <3 x half> poison, <3 x i32> zeroinitializer
  %_1166 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1167 = insertelement <3 x half> undef, half %_1166, i64 0
  %_1169 = shufflevector <3 x half> %_1167, <3 x half> poison, <3 x i32> zeroinitializer
  %_1170 = tail call <3 x half> @air.smoothstep.v3f16(<3 x half> %_1161, <3 x half> %_1165, <3 x half> %_1169)
  %_1171 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1172 = insertelement <4 x half> undef, half %_1171, i64 0
  %_1175 = shufflevector <4 x half> %_1172, <4 x half> poison, <4 x i32> zeroinitializer
  %_1176 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1177 = insertelement <4 x half> undef, half %_1176, i64 0
  %_1180 = shufflevector <4 x half> %_1177, <4 x half> poison, <4 x i32> zeroinitializer
  %_1181 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1182 = insertelement <4 x half> undef, half %_1181, i64 0
  %_1185 = shufflevector <4 x half> %_1182, <4 x half> poison, <4 x i32> zeroinitializer
  %_1186 = tail call <4 x half> @air.smoothstep.v4f16(<4 x half> %_1175, <4 x half> %_1180, <4 x half> %_1185)
  %_1187 = tail call float @air.smoothstep.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_1188 = tail call <2 x float> @air.smoothstep.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1189 = tail call <3 x float> @air.smoothstep.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1190 = tail call <4 x float> @air.smoothstep.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1191 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1192 = tail call half @air.sqrt.f16(half %_1191)
  %_1193 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1194 = insertelement <2 x half> undef, half %_1193, i64 0
  %_1195 = shufflevector <2 x half> %_1194, <2 x half> poison, <2 x i32> zeroinitializer
  %_1196 = tail call <2 x half> @air.sqrt.v2f16(<2 x half> %_1195)
  %_1197 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1198 = insertelement <3 x half> undef, half %_1197, i64 0
  %_1200 = shufflevector <3 x half> %_1198, <3 x half> poison, <3 x i32> zeroinitializer
  %_1201 = tail call <3 x half> @air.sqrt.v3f16(<3 x half> %_1200)
  %_1202 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1203 = insertelement <4 x half> undef, half %_1202, i64 0
  %_1206 = shufflevector <4 x half> %_1203, <4 x half> poison, <4 x i32> zeroinitializer
  %_1207 = tail call <4 x half> @air.sqrt.v4f16(<4 x half> %_1206)
  %_1208 = tail call float @air.sqrt.f32(float 0.000000e+00)
  %_1209 = tail call <2 x float> @air.sqrt.v2f32(<2 x float> zeroinitializer)
  %_1210 = tail call <3 x float> @air.sqrt.v3f32(<3 x float> zeroinitializer)
  %_1211 = tail call <4 x float> @air.sqrt.v4f32(<4 x float> zeroinitializer)
  %_1212 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1213 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1214 = tail call half @air.step.f16(half %_1212, half %_1213)
  %_1215 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1216 = insertelement <2 x half> undef, half %_1215, i64 0
  %_1217 = shufflevector <2 x half> %_1216, <2 x half> poison, <2 x i32> zeroinitializer
  %_1218 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1219 = insertelement <2 x half> undef, half %_1218, i64 0
  %_1220 = shufflevector <2 x half> %_1219, <2 x half> poison, <2 x i32> zeroinitializer
  %_1221 = tail call <2 x half> @air.step.v2f16(<2 x half> %_1217, <2 x half> %_1220)
  %_1222 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1223 = insertelement <3 x half> undef, half %_1222, i64 0
  %_1225 = shufflevector <3 x half> %_1223, <3 x half> poison, <3 x i32> zeroinitializer
  %_1226 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1227 = insertelement <3 x half> undef, half %_1226, i64 0
  %_1229 = shufflevector <3 x half> %_1227, <3 x half> poison, <3 x i32> zeroinitializer
  %_1230 = tail call <3 x half> @air.step.v3f16(<3 x half> %_1225, <3 x half> %_1229)
  %_1231 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1232 = insertelement <4 x half> undef, half %_1231, i64 0
  %_1235 = shufflevector <4 x half> %_1232, <4 x half> poison, <4 x i32> zeroinitializer
  %_1236 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1237 = insertelement <4 x half> undef, half %_1236, i64 0
  %_1240 = shufflevector <4 x half> %_1237, <4 x half> poison, <4 x i32> zeroinitializer
  %_1241 = tail call <4 x half> @air.step.v4f16(<4 x half> %_1235, <4 x half> %_1240)
  %_1242 = tail call float @air.step.f32(float 0.000000e+00, float 0.000000e+00)
  %_1243 = tail call <2 x float> @air.step.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1244 = tail call <3 x float> @air.step.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1245 = tail call <4 x float> @air.step.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1246 = tail call float @air.tan.f32(float 0.000000e+00)
  %_1247 = tail call float @air.tanh.f32(float 0.000000e+00)
  ret %FragmentOut { <4 x float> <float 0.000000e+00, float 0.000000e+00, float 0.000000e+00, float 1.000000e+00> }
}

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!air.fragment = !{!9}
!air.compile_options = !{!15, !16, !17}
!llvm.ident = !{!18}
!air.version = !{!19}
!air.language_version = !{!20}
!air.source_file_name = !{!21}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{i32 7, !"air.max_device_buffers", i32 31}
!4 = !{i32 7, !"air.max_constant_buffers", i32 31}
!5 = !{i32 7, !"air.max_threadgroup_buffers", i32 31}
!6 = !{i32 7, !"air.max_textures", i32 128}
!7 = !{i32 7, !"air.max_read_write_textures", i32 8}
!8 = !{i32 7, !"air.max_samplers", i32 16}
!9 = !{ptr @testStandardFunctions, !10, !12}
!10 = !{!11}
!11 = !{!"air.render_target", i32 0, i32 0, !"air.arg_type_name", !"<4 x float>", !"air.arg_name", !"outColor"}
!12 = !{!13, !14}
!13 = !{i32 0, !"air.texture", !"air.location_index", i32 0, i32 1, !"air.sample", !"air.arg_type_name", !"ptr addrspace(1)", !"air.arg_name", !"testTexture"}
!14 = !{i32 1, !"air.sampler", !"air.location_index", i32 0, i32 1, !"air.arg_type_name", !"ptr addrspace(2)", !"air.arg_name", !"testSampler"}
!15 = !{!"air.compile.denorms_disable"}
!16 = !{!"air.compile.fast_math_disable"}
!17 = !{!"air.compile.framebuffer_fetch_enable"}
!18 = !{!"Lvslang"}
!19 = !{i32 2, i32 6, i32 0}
!20 = !{!"LVSL", i32 0, i32 7, i32 0}
!21 = !{!"/Users/samuliak/Desktop/lvslang/test.lvsl"}
