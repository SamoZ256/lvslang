source_filename = "/Users/samuliak/Desktop/lvslang/build/../tests/standard_functions.lvsl"
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

declare half @air.log.f16(half) local_unnamed_addr

declare <2 x half> @air.log.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.log.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.log.v4f16(<4 x half>) local_unnamed_addr

declare float @air.log.f32(float) local_unnamed_addr

declare <2 x float> @air.log.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.log.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.log.v4f32(<4 x float>) local_unnamed_addr

declare half @air.log2.f16(half) local_unnamed_addr

declare <2 x half> @air.log2.v2f16(<2 x half>) local_unnamed_addr

declare <3 x half> @air.log2.v3f16(<3 x half>) local_unnamed_addr

declare <4 x half> @air.log2.v4f16(<4 x half>) local_unnamed_addr

declare float @air.log2.f32(float) local_unnamed_addr

declare <2 x float> @air.log2.v2f32(<2 x float>) local_unnamed_addr

declare <3 x float> @air.log2.v3f32(<3 x float>) local_unnamed_addr

declare <4 x float> @air.log2.v4f32(<4 x float>) local_unnamed_addr

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

define %FragmentOut @testStandardFunctions.t1f32.sm(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler) local_unnamed_addr {
  %_276 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_277 = tail call i8 @air.abs.i8(i8 %_276)
  %_278 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_279 = insertelement <2 x i8> undef, i8 %_278, i64 0
  %_280 = shufflevector <2 x i8> %_279, <2 x i8> poison, <2 x i32> zeroinitializer
  %_281 = tail call <2 x i8> @air.abs.v2i8(<2 x i8> %_280)
  %_282 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_283 = insertelement <3 x i8> undef, i8 %_282, i64 0
  %_285 = shufflevector <3 x i8> %_283, <3 x i8> poison, <3 x i32> zeroinitializer
  %_286 = tail call <3 x i8> @air.abs.v3i8(<3 x i8> %_285)
  %_287 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_288 = insertelement <4 x i8> undef, i8 %_287, i64 0
  %_291 = shufflevector <4 x i8> %_288, <4 x i8> poison, <4 x i32> zeroinitializer
  %_292 = tail call <4 x i8> @air.abs.v4i8(<4 x i8> %_291)
  %_293 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_294 = tail call i16 @air.abs.i16(i16 %_293)
  %_295 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_296 = insertelement <2 x i16> undef, i16 %_295, i64 0
  %_297 = shufflevector <2 x i16> %_296, <2 x i16> poison, <2 x i32> zeroinitializer
  %_298 = tail call <2 x i16> @air.abs.v2i16(<2 x i16> %_297)
  %_299 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_300 = insertelement <3 x i16> undef, i16 %_299, i64 0
  %_302 = shufflevector <3 x i16> %_300, <3 x i16> poison, <3 x i32> zeroinitializer
  %_303 = tail call <3 x i16> @air.abs.v3i16(<3 x i16> %_302)
  %_304 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_305 = insertelement <4 x i16> undef, i16 %_304, i64 0
  %_308 = shufflevector <4 x i16> %_305, <4 x i16> poison, <4 x i32> zeroinitializer
  %_309 = tail call <4 x i16> @air.abs.v4i16(<4 x i16> %_308)
  %_310 = tail call i32 @air.abs.i32(i32 0)
  %_311 = tail call <2 x i32> @air.abs.v2i32(<2 x i32> zeroinitializer)
  %_312 = tail call <3 x i32> @air.abs.v3i32(<3 x i32> zeroinitializer)
  %_313 = tail call <4 x i32> @air.abs.v4i32(<4 x i32> zeroinitializer)
  %_314 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_315 = tail call half @air.abs.f16(half %_314)
  %_316 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_317 = insertelement <2 x half> undef, half %_316, i64 0
  %_318 = shufflevector <2 x half> %_317, <2 x half> poison, <2 x i32> zeroinitializer
  %_319 = tail call <2 x half> @air.abs.v2f16(<2 x half> %_318)
  %_320 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_321 = insertelement <3 x half> undef, half %_320, i64 0
  %_323 = shufflevector <3 x half> %_321, <3 x half> poison, <3 x i32> zeroinitializer
  %_324 = tail call <3 x half> @air.abs.v3f16(<3 x half> %_323)
  %_325 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_326 = insertelement <4 x half> undef, half %_325, i64 0
  %_329 = shufflevector <4 x half> %_326, <4 x half> poison, <4 x i32> zeroinitializer
  %_330 = tail call <4 x half> @air.abs.v4f16(<4 x half> %_329)
  %_331 = tail call float @air.abs.f32(float 0.000000e+00)
  %_332 = tail call <2 x float> @air.abs.v2f32(<2 x float> zeroinitializer)
  %_333 = tail call <3 x float> @air.abs.v3f32(<3 x float> zeroinitializer)
  %_334 = tail call <4 x float> @air.abs.v4f32(<4 x float> zeroinitializer)
  %_335 = tail call float @air.acos.f32(float 0.000000e+00)
  %_336 = tail call float @air.acosh.f32(float 0.000000e+00)
  %_337 = tail call float @air.asin.f32(float 0.000000e+00)
  %_338 = tail call float @air.asinh.f32(float 0.000000e+00)
  %_339 = tail call float @air.atan.f32(float 0.000000e+00)
  %_340 = tail call float @air.atanh.f32(float 0.000000e+00)
  %_341 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_342 = tail call half @air.ceil.f16(half %_341)
  %_343 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_344 = insertelement <2 x half> undef, half %_343, i64 0
  %_345 = shufflevector <2 x half> %_344, <2 x half> poison, <2 x i32> zeroinitializer
  %_346 = tail call <2 x half> @air.ceil.v2f16(<2 x half> %_345)
  %_347 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_348 = insertelement <3 x half> undef, half %_347, i64 0
  %_350 = shufflevector <3 x half> %_348, <3 x half> poison, <3 x i32> zeroinitializer
  %_351 = tail call <3 x half> @air.ceil.v3f16(<3 x half> %_350)
  %_352 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_353 = insertelement <4 x half> undef, half %_352, i64 0
  %_356 = shufflevector <4 x half> %_353, <4 x half> poison, <4 x i32> zeroinitializer
  %_357 = tail call <4 x half> @air.ceil.v4f16(<4 x half> %_356)
  %_358 = tail call float @air.ceil.f32(float 0.000000e+00)
  %_359 = tail call <2 x float> @air.ceil.v2f32(<2 x float> zeroinitializer)
  %_360 = tail call <3 x float> @air.ceil.v3f32(<3 x float> zeroinitializer)
  %_361 = tail call <4 x float> @air.ceil.v4f32(<4 x float> zeroinitializer)
  %_362 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_363 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_364 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_365 = tail call i8 @air.clamp.i8(i8 %_362, i8 %_363, i8 %_364)
  %_366 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_367 = insertelement <2 x i8> undef, i8 %_366, i64 0
  %_368 = shufflevector <2 x i8> %_367, <2 x i8> poison, <2 x i32> zeroinitializer
  %_369 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_370 = insertelement <2 x i8> undef, i8 %_369, i64 0
  %_371 = shufflevector <2 x i8> %_370, <2 x i8> poison, <2 x i32> zeroinitializer
  %_372 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_373 = insertelement <2 x i8> undef, i8 %_372, i64 0
  %_374 = shufflevector <2 x i8> %_373, <2 x i8> poison, <2 x i32> zeroinitializer
  %_375 = tail call <2 x i8> @air.clamp.v2i8(<2 x i8> %_368, <2 x i8> %_371, <2 x i8> %_374)
  %_376 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_377 = insertelement <3 x i8> undef, i8 %_376, i64 0
  %_379 = shufflevector <3 x i8> %_377, <3 x i8> poison, <3 x i32> zeroinitializer
  %_380 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_381 = insertelement <3 x i8> undef, i8 %_380, i64 0
  %_383 = shufflevector <3 x i8> %_381, <3 x i8> poison, <3 x i32> zeroinitializer
  %_384 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_385 = insertelement <3 x i8> undef, i8 %_384, i64 0
  %_387 = shufflevector <3 x i8> %_385, <3 x i8> poison, <3 x i32> zeroinitializer
  %_388 = tail call <3 x i8> @air.clamp.v3i8(<3 x i8> %_379, <3 x i8> %_383, <3 x i8> %_387)
  %_389 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_390 = insertelement <4 x i8> undef, i8 %_389, i64 0
  %_393 = shufflevector <4 x i8> %_390, <4 x i8> poison, <4 x i32> zeroinitializer
  %_394 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_395 = insertelement <4 x i8> undef, i8 %_394, i64 0
  %_398 = shufflevector <4 x i8> %_395, <4 x i8> poison, <4 x i32> zeroinitializer
  %_399 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_400 = insertelement <4 x i8> undef, i8 %_399, i64 0
  %_403 = shufflevector <4 x i8> %_400, <4 x i8> poison, <4 x i32> zeroinitializer
  %_404 = tail call <4 x i8> @air.clamp.v4i8(<4 x i8> %_393, <4 x i8> %_398, <4 x i8> %_403)
  %_405 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_406 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_407 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_408 = tail call i16 @air.clamp.i16(i16 %_405, i16 %_406, i16 %_407)
  %_409 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_410 = insertelement <2 x i16> undef, i16 %_409, i64 0
  %_411 = shufflevector <2 x i16> %_410, <2 x i16> poison, <2 x i32> zeroinitializer
  %_412 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_413 = insertelement <2 x i16> undef, i16 %_412, i64 0
  %_414 = shufflevector <2 x i16> %_413, <2 x i16> poison, <2 x i32> zeroinitializer
  %_415 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_416 = insertelement <2 x i16> undef, i16 %_415, i64 0
  %_417 = shufflevector <2 x i16> %_416, <2 x i16> poison, <2 x i32> zeroinitializer
  %_418 = tail call <2 x i16> @air.clamp.v2i16(<2 x i16> %_411, <2 x i16> %_414, <2 x i16> %_417)
  %_419 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_420 = insertelement <3 x i16> undef, i16 %_419, i64 0
  %_422 = shufflevector <3 x i16> %_420, <3 x i16> poison, <3 x i32> zeroinitializer
  %_423 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_424 = insertelement <3 x i16> undef, i16 %_423, i64 0
  %_426 = shufflevector <3 x i16> %_424, <3 x i16> poison, <3 x i32> zeroinitializer
  %_427 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_428 = insertelement <3 x i16> undef, i16 %_427, i64 0
  %_430 = shufflevector <3 x i16> %_428, <3 x i16> poison, <3 x i32> zeroinitializer
  %_431 = tail call <3 x i16> @air.clamp.v3i16(<3 x i16> %_422, <3 x i16> %_426, <3 x i16> %_430)
  %_432 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_433 = insertelement <4 x i16> undef, i16 %_432, i64 0
  %_436 = shufflevector <4 x i16> %_433, <4 x i16> poison, <4 x i32> zeroinitializer
  %_437 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_438 = insertelement <4 x i16> undef, i16 %_437, i64 0
  %_441 = shufflevector <4 x i16> %_438, <4 x i16> poison, <4 x i32> zeroinitializer
  %_442 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_443 = insertelement <4 x i16> undef, i16 %_442, i64 0
  %_446 = shufflevector <4 x i16> %_443, <4 x i16> poison, <4 x i32> zeroinitializer
  %_447 = tail call <4 x i16> @air.clamp.v4i16(<4 x i16> %_436, <4 x i16> %_441, <4 x i16> %_446)
  %_448 = tail call i32 @air.clamp.i32(i32 0, i32 0, i32 0)
  %_449 = tail call <2 x i32> @air.clamp.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_450 = tail call <3 x i32> @air.clamp.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_451 = tail call <4 x i32> @air.clamp.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_452 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_453 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_454 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_455 = tail call half @air.clamp.f16(half %_452, half %_453, half %_454)
  %_456 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_457 = insertelement <2 x half> undef, half %_456, i64 0
  %_458 = shufflevector <2 x half> %_457, <2 x half> poison, <2 x i32> zeroinitializer
  %_459 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_460 = insertelement <2 x half> undef, half %_459, i64 0
  %_461 = shufflevector <2 x half> %_460, <2 x half> poison, <2 x i32> zeroinitializer
  %_462 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_463 = insertelement <2 x half> undef, half %_462, i64 0
  %_464 = shufflevector <2 x half> %_463, <2 x half> poison, <2 x i32> zeroinitializer
  %_465 = tail call <2 x half> @air.clamp.v2f16(<2 x half> %_458, <2 x half> %_461, <2 x half> %_464)
  %_466 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_467 = insertelement <3 x half> undef, half %_466, i64 0
  %_469 = shufflevector <3 x half> %_467, <3 x half> poison, <3 x i32> zeroinitializer
  %_470 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_471 = insertelement <3 x half> undef, half %_470, i64 0
  %_473 = shufflevector <3 x half> %_471, <3 x half> poison, <3 x i32> zeroinitializer
  %_474 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_475 = insertelement <3 x half> undef, half %_474, i64 0
  %_477 = shufflevector <3 x half> %_475, <3 x half> poison, <3 x i32> zeroinitializer
  %_478 = tail call <3 x half> @air.clamp.v3f16(<3 x half> %_469, <3 x half> %_473, <3 x half> %_477)
  %_479 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_480 = insertelement <4 x half> undef, half %_479, i64 0
  %_483 = shufflevector <4 x half> %_480, <4 x half> poison, <4 x i32> zeroinitializer
  %_484 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_485 = insertelement <4 x half> undef, half %_484, i64 0
  %_488 = shufflevector <4 x half> %_485, <4 x half> poison, <4 x i32> zeroinitializer
  %_489 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_490 = insertelement <4 x half> undef, half %_489, i64 0
  %_493 = shufflevector <4 x half> %_490, <4 x half> poison, <4 x i32> zeroinitializer
  %_494 = tail call <4 x half> @air.clamp.v4f16(<4 x half> %_483, <4 x half> %_488, <4 x half> %_493)
  %_495 = tail call float @air.clamp.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_496 = tail call <2 x float> @air.clamp.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_497 = tail call <3 x float> @air.clamp.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_498 = tail call <4 x float> @air.clamp.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_499 = tail call float @air.cos.f32(float 0.000000e+00)
  %_500 = tail call float @air.cosh.f32(float 0.000000e+00)
  %_501 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_502 = insertelement <3 x half> undef, half %_501, i64 0
  %_504 = shufflevector <3 x half> %_502, <3 x half> poison, <3 x i32> zeroinitializer
  %_505 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_506 = insertelement <3 x half> undef, half %_505, i64 0
  %_508 = shufflevector <3 x half> %_506, <3 x half> poison, <3 x i32> zeroinitializer
  %_509 = tail call <3 x half> @air.cross.v3f16(<3 x half> %_504, <3 x half> %_508)
  %_510 = tail call <3 x float> @air.cross.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_511 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_512 = insertelement <2 x half> undef, half %_511, i64 0
  %_513 = shufflevector <2 x half> %_512, <2 x half> poison, <2 x i32> zeroinitializer
  %_514 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_515 = insertelement <2 x half> undef, half %_514, i64 0
  %_516 = shufflevector <2 x half> %_515, <2 x half> poison, <2 x i32> zeroinitializer
  %_517 = tail call half @air.distance.v2f16(<2 x half> %_513, <2 x half> %_516)
  %_518 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_519 = insertelement <3 x half> undef, half %_518, i64 0
  %_521 = shufflevector <3 x half> %_519, <3 x half> poison, <3 x i32> zeroinitializer
  %_522 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_523 = insertelement <3 x half> undef, half %_522, i64 0
  %_525 = shufflevector <3 x half> %_523, <3 x half> poison, <3 x i32> zeroinitializer
  %_526 = tail call half @air.distance.v3f16(<3 x half> %_521, <3 x half> %_525)
  %_527 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_528 = insertelement <4 x half> undef, half %_527, i64 0
  %_531 = shufflevector <4 x half> %_528, <4 x half> poison, <4 x i32> zeroinitializer
  %_532 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_533 = insertelement <4 x half> undef, half %_532, i64 0
  %_536 = shufflevector <4 x half> %_533, <4 x half> poison, <4 x i32> zeroinitializer
  %_537 = tail call half @air.distance.v4f16(<4 x half> %_531, <4 x half> %_536)
  %_538 = tail call float @air.distance.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_539 = tail call float @air.distance.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_540 = tail call float @air.distance.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_541 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_542 = insertelement <2 x half> undef, half %_541, i64 0
  %_543 = shufflevector <2 x half> %_542, <2 x half> poison, <2 x i32> zeroinitializer
  %_544 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_545 = insertelement <2 x half> undef, half %_544, i64 0
  %_546 = shufflevector <2 x half> %_545, <2 x half> poison, <2 x i32> zeroinitializer
  %_547 = tail call half @air.dot.v2f16(<2 x half> %_543, <2 x half> %_546)
  %_548 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_549 = insertelement <3 x half> undef, half %_548, i64 0
  %_551 = shufflevector <3 x half> %_549, <3 x half> poison, <3 x i32> zeroinitializer
  %_552 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_553 = insertelement <3 x half> undef, half %_552, i64 0
  %_555 = shufflevector <3 x half> %_553, <3 x half> poison, <3 x i32> zeroinitializer
  %_556 = tail call half @air.dot.v3f16(<3 x half> %_551, <3 x half> %_555)
  %_557 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_558 = insertelement <4 x half> undef, half %_557, i64 0
  %_561 = shufflevector <4 x half> %_558, <4 x half> poison, <4 x i32> zeroinitializer
  %_562 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_563 = insertelement <4 x half> undef, half %_562, i64 0
  %_566 = shufflevector <4 x half> %_563, <4 x half> poison, <4 x i32> zeroinitializer
  %_567 = tail call half @air.dot.v4f16(<4 x half> %_561, <4 x half> %_566)
  %_568 = tail call float @air.dot.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_569 = tail call float @air.dot.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_570 = tail call float @air.dot.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_571 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_572 = tail call half @air.exp.f16(half %_571)
  %_573 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_574 = insertelement <2 x half> undef, half %_573, i64 0
  %_575 = shufflevector <2 x half> %_574, <2 x half> poison, <2 x i32> zeroinitializer
  %_576 = tail call <2 x half> @air.exp.v2f16(<2 x half> %_575)
  %_577 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_578 = insertelement <3 x half> undef, half %_577, i64 0
  %_580 = shufflevector <3 x half> %_578, <3 x half> poison, <3 x i32> zeroinitializer
  %_581 = tail call <3 x half> @air.exp.v3f16(<3 x half> %_580)
  %_582 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_583 = insertelement <4 x half> undef, half %_582, i64 0
  %_586 = shufflevector <4 x half> %_583, <4 x half> poison, <4 x i32> zeroinitializer
  %_587 = tail call <4 x half> @air.exp.v4f16(<4 x half> %_586)
  %_588 = tail call float @air.exp.f32(float 0.000000e+00)
  %_589 = tail call <2 x float> @air.exp.v2f32(<2 x float> zeroinitializer)
  %_590 = tail call <3 x float> @air.exp.v3f32(<3 x float> zeroinitializer)
  %_591 = tail call <4 x float> @air.exp.v4f32(<4 x float> zeroinitializer)
  %_592 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_593 = tail call half @air.exp2.f16(half %_592)
  %_594 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_595 = insertelement <2 x half> undef, half %_594, i64 0
  %_596 = shufflevector <2 x half> %_595, <2 x half> poison, <2 x i32> zeroinitializer
  %_597 = tail call <2 x half> @air.exp2.v2f16(<2 x half> %_596)
  %_598 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_599 = insertelement <3 x half> undef, half %_598, i64 0
  %_601 = shufflevector <3 x half> %_599, <3 x half> poison, <3 x i32> zeroinitializer
  %_602 = tail call <3 x half> @air.exp2.v3f16(<3 x half> %_601)
  %_603 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_604 = insertelement <4 x half> undef, half %_603, i64 0
  %_607 = shufflevector <4 x half> %_604, <4 x half> poison, <4 x i32> zeroinitializer
  %_608 = tail call <4 x half> @air.exp2.v4f16(<4 x half> %_607)
  %_609 = tail call float @air.exp2.f32(float 0.000000e+00)
  %_610 = tail call <2 x float> @air.exp2.v2f32(<2 x float> zeroinitializer)
  %_611 = tail call <3 x float> @air.exp2.v3f32(<3 x float> zeroinitializer)
  %_612 = tail call <4 x float> @air.exp2.v4f32(<4 x float> zeroinitializer)
  %_613 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_614 = tail call half @air.floor.f16(half %_613)
  %_615 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_616 = insertelement <2 x half> undef, half %_615, i64 0
  %_617 = shufflevector <2 x half> %_616, <2 x half> poison, <2 x i32> zeroinitializer
  %_618 = tail call <2 x half> @air.floor.v2f16(<2 x half> %_617)
  %_619 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_620 = insertelement <3 x half> undef, half %_619, i64 0
  %_622 = shufflevector <3 x half> %_620, <3 x half> poison, <3 x i32> zeroinitializer
  %_623 = tail call <3 x half> @air.floor.v3f16(<3 x half> %_622)
  %_624 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_625 = insertelement <4 x half> undef, half %_624, i64 0
  %_628 = shufflevector <4 x half> %_625, <4 x half> poison, <4 x i32> zeroinitializer
  %_629 = tail call <4 x half> @air.floor.v4f16(<4 x half> %_628)
  %_630 = tail call float @air.floor.f32(float 0.000000e+00)
  %_631 = tail call <2 x float> @air.floor.v2f32(<2 x float> zeroinitializer)
  %_632 = tail call <3 x float> @air.floor.v3f32(<3 x float> zeroinitializer)
  %_633 = tail call <4 x float> @air.floor.v4f32(<4 x float> zeroinitializer)
  %_634 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_635 = tail call half @air.fract.f16(half %_634)
  %_636 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_637 = insertelement <2 x half> undef, half %_636, i64 0
  %_638 = shufflevector <2 x half> %_637, <2 x half> poison, <2 x i32> zeroinitializer
  %_639 = tail call <2 x half> @air.fract.v2f16(<2 x half> %_638)
  %_640 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_641 = insertelement <3 x half> undef, half %_640, i64 0
  %_643 = shufflevector <3 x half> %_641, <3 x half> poison, <3 x i32> zeroinitializer
  %_644 = tail call <3 x half> @air.fract.v3f16(<3 x half> %_643)
  %_645 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_646 = insertelement <4 x half> undef, half %_645, i64 0
  %_649 = shufflevector <4 x half> %_646, <4 x half> poison, <4 x i32> zeroinitializer
  %_650 = tail call <4 x half> @air.fract.v4f16(<4 x half> %_649)
  %_651 = tail call float @air.fract.f32(float 0.000000e+00)
  %_652 = tail call <2 x float> @air.fract.v2f32(<2 x float> zeroinitializer)
  %_653 = tail call <3 x float> @air.fract.v3f32(<3 x float> zeroinitializer)
  %_654 = tail call <4 x float> @air.fract.v4f32(<4 x float> zeroinitializer)
  %_655 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_656 = tail call i1 @air.isinf.f16(half %_655)
  %_657 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_658 = insertelement <2 x half> undef, half %_657, i64 0
  %_659 = shufflevector <2 x half> %_658, <2 x half> poison, <2 x i32> zeroinitializer
  %_660 = tail call <2 x i1> @air.isinf.v2f16(<2 x half> %_659)
  %_661 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_662 = insertelement <3 x half> undef, half %_661, i64 0
  %_664 = shufflevector <3 x half> %_662, <3 x half> poison, <3 x i32> zeroinitializer
  %_665 = tail call <3 x i1> @air.isinf.v3f16(<3 x half> %_664)
  %_666 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_667 = insertelement <4 x half> undef, half %_666, i64 0
  %_670 = shufflevector <4 x half> %_667, <4 x half> poison, <4 x i32> zeroinitializer
  %_671 = tail call <4 x i1> @air.isinf.v4f16(<4 x half> %_670)
  %_672 = tail call i1 @air.isinf.f32(float 0.000000e+00)
  %_673 = tail call <2 x i1> @air.isinf.v2f32(<2 x float> zeroinitializer)
  %_674 = tail call <3 x i1> @air.isinf.v3f32(<3 x float> zeroinitializer)
  %_675 = tail call <4 x i1> @air.isinf.v4f32(<4 x float> zeroinitializer)
  %_676 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_677 = tail call i1 @air.isnan.f16(half %_676)
  %_678 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_679 = insertelement <2 x half> undef, half %_678, i64 0
  %_680 = shufflevector <2 x half> %_679, <2 x half> poison, <2 x i32> zeroinitializer
  %_681 = tail call <2 x i1> @air.isnan.v2f16(<2 x half> %_680)
  %_682 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_683 = insertelement <3 x half> undef, half %_682, i64 0
  %_685 = shufflevector <3 x half> %_683, <3 x half> poison, <3 x i32> zeroinitializer
  %_686 = tail call <3 x i1> @air.isnan.v3f16(<3 x half> %_685)
  %_687 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_688 = insertelement <4 x half> undef, half %_687, i64 0
  %_691 = shufflevector <4 x half> %_688, <4 x half> poison, <4 x i32> zeroinitializer
  %_692 = tail call <4 x i1> @air.isnan.v4f16(<4 x half> %_691)
  %_693 = tail call i1 @air.isnan.f32(float 0.000000e+00)
  %_694 = tail call <2 x i1> @air.isnan.v2f32(<2 x float> zeroinitializer)
  %_695 = tail call <3 x i1> @air.isnan.v3f32(<3 x float> zeroinitializer)
  %_696 = tail call <4 x i1> @air.isnan.v4f32(<4 x float> zeroinitializer)
  %_697 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_698 = insertelement <2 x half> undef, half %_697, i64 0
  %_699 = shufflevector <2 x half> %_698, <2 x half> poison, <2 x i32> zeroinitializer
  %_700 = tail call half @air.length.v2f16(<2 x half> %_699)
  %_701 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_702 = insertelement <3 x half> undef, half %_701, i64 0
  %_704 = shufflevector <3 x half> %_702, <3 x half> poison, <3 x i32> zeroinitializer
  %_705 = tail call half @air.length.v3f16(<3 x half> %_704)
  %_706 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_707 = insertelement <4 x half> undef, half %_706, i64 0
  %_710 = shufflevector <4 x half> %_707, <4 x half> poison, <4 x i32> zeroinitializer
  %_711 = tail call half @air.length.v4f16(<4 x half> %_710)
  %_712 = tail call float @air.length.v2f32(<2 x float> zeroinitializer)
  %_713 = tail call float @air.length.v3f32(<3 x float> zeroinitializer)
  %_714 = tail call float @air.length.v4f32(<4 x float> zeroinitializer)
  %_715 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_716 = tail call half @air.log.f16(half %_715)
  %_717 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_718 = insertelement <2 x half> undef, half %_717, i64 0
  %_719 = shufflevector <2 x half> %_718, <2 x half> poison, <2 x i32> zeroinitializer
  %_720 = tail call <2 x half> @air.log.v2f16(<2 x half> %_719)
  %_721 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_722 = insertelement <3 x half> undef, half %_721, i64 0
  %_724 = shufflevector <3 x half> %_722, <3 x half> poison, <3 x i32> zeroinitializer
  %_725 = tail call <3 x half> @air.log.v3f16(<3 x half> %_724)
  %_726 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_727 = insertelement <4 x half> undef, half %_726, i64 0
  %_730 = shufflevector <4 x half> %_727, <4 x half> poison, <4 x i32> zeroinitializer
  %_731 = tail call <4 x half> @air.log.v4f16(<4 x half> %_730)
  %_732 = tail call float @air.log.f32(float 0.000000e+00)
  %_733 = tail call <2 x float> @air.log.v2f32(<2 x float> zeroinitializer)
  %_734 = tail call <3 x float> @air.log.v3f32(<3 x float> zeroinitializer)
  %_735 = tail call <4 x float> @air.log.v4f32(<4 x float> zeroinitializer)
  %_736 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_737 = tail call half @air.log2.f16(half %_736)
  %_738 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_739 = insertelement <2 x half> undef, half %_738, i64 0
  %_740 = shufflevector <2 x half> %_739, <2 x half> poison, <2 x i32> zeroinitializer
  %_741 = tail call <2 x half> @air.log2.v2f16(<2 x half> %_740)
  %_742 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_743 = insertelement <3 x half> undef, half %_742, i64 0
  %_745 = shufflevector <3 x half> %_743, <3 x half> poison, <3 x i32> zeroinitializer
  %_746 = tail call <3 x half> @air.log2.v3f16(<3 x half> %_745)
  %_747 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_748 = insertelement <4 x half> undef, half %_747, i64 0
  %_751 = shufflevector <4 x half> %_748, <4 x half> poison, <4 x i32> zeroinitializer
  %_752 = tail call <4 x half> @air.log2.v4f16(<4 x half> %_751)
  %_753 = tail call float @air.log2.f32(float 0.000000e+00)
  %_754 = tail call <2 x float> @air.log2.v2f32(<2 x float> zeroinitializer)
  %_755 = tail call <3 x float> @air.log2.v3f32(<3 x float> zeroinitializer)
  %_756 = tail call <4 x float> @air.log2.v4f32(<4 x float> zeroinitializer)
  %_757 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_758 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_759 = tail call i8 @air.max.i8(i8 %_757, i8 %_758)
  %_760 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_761 = insertelement <2 x i8> undef, i8 %_760, i64 0
  %_762 = shufflevector <2 x i8> %_761, <2 x i8> poison, <2 x i32> zeroinitializer
  %_763 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_764 = insertelement <2 x i8> undef, i8 %_763, i64 0
  %_765 = shufflevector <2 x i8> %_764, <2 x i8> poison, <2 x i32> zeroinitializer
  %_766 = tail call <2 x i8> @air.max.v2i8(<2 x i8> %_762, <2 x i8> %_765)
  %_767 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_768 = insertelement <3 x i8> undef, i8 %_767, i64 0
  %_770 = shufflevector <3 x i8> %_768, <3 x i8> poison, <3 x i32> zeroinitializer
  %_771 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_772 = insertelement <3 x i8> undef, i8 %_771, i64 0
  %_774 = shufflevector <3 x i8> %_772, <3 x i8> poison, <3 x i32> zeroinitializer
  %_775 = tail call <3 x i8> @air.max.v3i8(<3 x i8> %_770, <3 x i8> %_774)
  %_776 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_777 = insertelement <4 x i8> undef, i8 %_776, i64 0
  %_780 = shufflevector <4 x i8> %_777, <4 x i8> poison, <4 x i32> zeroinitializer
  %_781 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_782 = insertelement <4 x i8> undef, i8 %_781, i64 0
  %_785 = shufflevector <4 x i8> %_782, <4 x i8> poison, <4 x i32> zeroinitializer
  %_786 = tail call <4 x i8> @air.max.v4i8(<4 x i8> %_780, <4 x i8> %_785)
  %_787 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_788 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_789 = tail call i16 @air.max.i16(i16 %_787, i16 %_788)
  %_790 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_791 = insertelement <2 x i16> undef, i16 %_790, i64 0
  %_792 = shufflevector <2 x i16> %_791, <2 x i16> poison, <2 x i32> zeroinitializer
  %_793 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_794 = insertelement <2 x i16> undef, i16 %_793, i64 0
  %_795 = shufflevector <2 x i16> %_794, <2 x i16> poison, <2 x i32> zeroinitializer
  %_796 = tail call <2 x i16> @air.max.v2i16(<2 x i16> %_792, <2 x i16> %_795)
  %_797 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_798 = insertelement <3 x i16> undef, i16 %_797, i64 0
  %_800 = shufflevector <3 x i16> %_798, <3 x i16> poison, <3 x i32> zeroinitializer
  %_801 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_802 = insertelement <3 x i16> undef, i16 %_801, i64 0
  %_804 = shufflevector <3 x i16> %_802, <3 x i16> poison, <3 x i32> zeroinitializer
  %_805 = tail call <3 x i16> @air.max.v3i16(<3 x i16> %_800, <3 x i16> %_804)
  %_806 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_807 = insertelement <4 x i16> undef, i16 %_806, i64 0
  %_810 = shufflevector <4 x i16> %_807, <4 x i16> poison, <4 x i32> zeroinitializer
  %_811 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_812 = insertelement <4 x i16> undef, i16 %_811, i64 0
  %_815 = shufflevector <4 x i16> %_812, <4 x i16> poison, <4 x i32> zeroinitializer
  %_816 = tail call <4 x i16> @air.max.v4i16(<4 x i16> %_810, <4 x i16> %_815)
  %_817 = tail call i32 @air.max.i32(i32 0, i32 0)
  %_818 = tail call <2 x i32> @air.max.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_819 = tail call <3 x i32> @air.max.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_820 = tail call <4 x i32> @air.max.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_821 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_822 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_823 = tail call half @air.max.f16(half %_821, half %_822)
  %_824 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_825 = insertelement <2 x half> undef, half %_824, i64 0
  %_826 = shufflevector <2 x half> %_825, <2 x half> poison, <2 x i32> zeroinitializer
  %_827 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_828 = insertelement <2 x half> undef, half %_827, i64 0
  %_829 = shufflevector <2 x half> %_828, <2 x half> poison, <2 x i32> zeroinitializer
  %_830 = tail call <2 x half> @air.max.v2f16(<2 x half> %_826, <2 x half> %_829)
  %_831 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_832 = insertelement <3 x half> undef, half %_831, i64 0
  %_834 = shufflevector <3 x half> %_832, <3 x half> poison, <3 x i32> zeroinitializer
  %_835 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_836 = insertelement <3 x half> undef, half %_835, i64 0
  %_838 = shufflevector <3 x half> %_836, <3 x half> poison, <3 x i32> zeroinitializer
  %_839 = tail call <3 x half> @air.max.v3f16(<3 x half> %_834, <3 x half> %_838)
  %_840 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_841 = insertelement <4 x half> undef, half %_840, i64 0
  %_844 = shufflevector <4 x half> %_841, <4 x half> poison, <4 x i32> zeroinitializer
  %_845 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_846 = insertelement <4 x half> undef, half %_845, i64 0
  %_849 = shufflevector <4 x half> %_846, <4 x half> poison, <4 x i32> zeroinitializer
  %_850 = tail call <4 x half> @air.max.v4f16(<4 x half> %_844, <4 x half> %_849)
  %_851 = tail call float @air.max.f32(float 0.000000e+00, float 0.000000e+00)
  %_852 = tail call <2 x float> @air.max.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_853 = tail call <3 x float> @air.max.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_854 = tail call <4 x float> @air.max.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_855 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_856 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_857 = tail call i8 @air.min.i8(i8 %_855, i8 %_856)
  %_858 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_859 = insertelement <2 x i8> undef, i8 %_858, i64 0
  %_860 = shufflevector <2 x i8> %_859, <2 x i8> poison, <2 x i32> zeroinitializer
  %_861 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_862 = insertelement <2 x i8> undef, i8 %_861, i64 0
  %_863 = shufflevector <2 x i8> %_862, <2 x i8> poison, <2 x i32> zeroinitializer
  %_864 = tail call <2 x i8> @air.min.v2i8(<2 x i8> %_860, <2 x i8> %_863)
  %_865 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_866 = insertelement <3 x i8> undef, i8 %_865, i64 0
  %_868 = shufflevector <3 x i8> %_866, <3 x i8> poison, <3 x i32> zeroinitializer
  %_869 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_870 = insertelement <3 x i8> undef, i8 %_869, i64 0
  %_872 = shufflevector <3 x i8> %_870, <3 x i8> poison, <3 x i32> zeroinitializer
  %_873 = tail call <3 x i8> @air.min.v3i8(<3 x i8> %_868, <3 x i8> %_872)
  %_874 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_875 = insertelement <4 x i8> undef, i8 %_874, i64 0
  %_878 = shufflevector <4 x i8> %_875, <4 x i8> poison, <4 x i32> zeroinitializer
  %_879 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_880 = insertelement <4 x i8> undef, i8 %_879, i64 0
  %_883 = shufflevector <4 x i8> %_880, <4 x i8> poison, <4 x i32> zeroinitializer
  %_884 = tail call <4 x i8> @air.min.v4i8(<4 x i8> %_878, <4 x i8> %_883)
  %_885 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_886 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_887 = tail call i16 @air.min.i16(i16 %_885, i16 %_886)
  %_888 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_889 = insertelement <2 x i16> undef, i16 %_888, i64 0
  %_890 = shufflevector <2 x i16> %_889, <2 x i16> poison, <2 x i32> zeroinitializer
  %_891 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_892 = insertelement <2 x i16> undef, i16 %_891, i64 0
  %_893 = shufflevector <2 x i16> %_892, <2 x i16> poison, <2 x i32> zeroinitializer
  %_894 = tail call <2 x i16> @air.min.v2i16(<2 x i16> %_890, <2 x i16> %_893)
  %_895 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_896 = insertelement <3 x i16> undef, i16 %_895, i64 0
  %_898 = shufflevector <3 x i16> %_896, <3 x i16> poison, <3 x i32> zeroinitializer
  %_899 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_900 = insertelement <3 x i16> undef, i16 %_899, i64 0
  %_902 = shufflevector <3 x i16> %_900, <3 x i16> poison, <3 x i32> zeroinitializer
  %_903 = tail call <3 x i16> @air.min.v3i16(<3 x i16> %_898, <3 x i16> %_902)
  %_904 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_905 = insertelement <4 x i16> undef, i16 %_904, i64 0
  %_908 = shufflevector <4 x i16> %_905, <4 x i16> poison, <4 x i32> zeroinitializer
  %_909 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_910 = insertelement <4 x i16> undef, i16 %_909, i64 0
  %_913 = shufflevector <4 x i16> %_910, <4 x i16> poison, <4 x i32> zeroinitializer
  %_914 = tail call <4 x i16> @air.min.v4i16(<4 x i16> %_908, <4 x i16> %_913)
  %_915 = tail call i32 @air.min.i32(i32 0, i32 0)
  %_916 = tail call <2 x i32> @air.min.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_917 = tail call <3 x i32> @air.min.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_918 = tail call <4 x i32> @air.min.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_919 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_920 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_921 = tail call half @air.min.f16(half %_919, half %_920)
  %_922 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_923 = insertelement <2 x half> undef, half %_922, i64 0
  %_924 = shufflevector <2 x half> %_923, <2 x half> poison, <2 x i32> zeroinitializer
  %_925 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_926 = insertelement <2 x half> undef, half %_925, i64 0
  %_927 = shufflevector <2 x half> %_926, <2 x half> poison, <2 x i32> zeroinitializer
  %_928 = tail call <2 x half> @air.min.v2f16(<2 x half> %_924, <2 x half> %_927)
  %_929 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_930 = insertelement <3 x half> undef, half %_929, i64 0
  %_932 = shufflevector <3 x half> %_930, <3 x half> poison, <3 x i32> zeroinitializer
  %_933 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_934 = insertelement <3 x half> undef, half %_933, i64 0
  %_936 = shufflevector <3 x half> %_934, <3 x half> poison, <3 x i32> zeroinitializer
  %_937 = tail call <3 x half> @air.min.v3f16(<3 x half> %_932, <3 x half> %_936)
  %_938 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_939 = insertelement <4 x half> undef, half %_938, i64 0
  %_942 = shufflevector <4 x half> %_939, <4 x half> poison, <4 x i32> zeroinitializer
  %_943 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_944 = insertelement <4 x half> undef, half %_943, i64 0
  %_947 = shufflevector <4 x half> %_944, <4 x half> poison, <4 x i32> zeroinitializer
  %_948 = tail call <4 x half> @air.min.v4f16(<4 x half> %_942, <4 x half> %_947)
  %_949 = tail call float @air.min.f32(float 0.000000e+00, float 0.000000e+00)
  %_950 = tail call <2 x float> @air.min.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_951 = tail call <3 x float> @air.min.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_952 = tail call <4 x float> @air.min.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_953 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_954 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_955 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_956 = tail call half @air.mix.f16(half %_953, half %_954, half %_955)
  %_957 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_958 = insertelement <2 x half> undef, half %_957, i64 0
  %_959 = shufflevector <2 x half> %_958, <2 x half> poison, <2 x i32> zeroinitializer
  %_960 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_961 = insertelement <2 x half> undef, half %_960, i64 0
  %_962 = shufflevector <2 x half> %_961, <2 x half> poison, <2 x i32> zeroinitializer
  %_963 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_964 = insertelement <2 x half> undef, half %_963, i64 0
  %_965 = shufflevector <2 x half> %_964, <2 x half> poison, <2 x i32> zeroinitializer
  %_966 = tail call <2 x half> @air.mix.v2f16(<2 x half> %_959, <2 x half> %_962, <2 x half> %_965)
  %_967 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_968 = insertelement <3 x half> undef, half %_967, i64 0
  %_970 = shufflevector <3 x half> %_968, <3 x half> poison, <3 x i32> zeroinitializer
  %_971 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_972 = insertelement <3 x half> undef, half %_971, i64 0
  %_974 = shufflevector <3 x half> %_972, <3 x half> poison, <3 x i32> zeroinitializer
  %_975 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_976 = insertelement <3 x half> undef, half %_975, i64 0
  %_978 = shufflevector <3 x half> %_976, <3 x half> poison, <3 x i32> zeroinitializer
  %_979 = tail call <3 x half> @air.mix.v3f16(<3 x half> %_970, <3 x half> %_974, <3 x half> %_978)
  %_980 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_981 = insertelement <4 x half> undef, half %_980, i64 0
  %_984 = shufflevector <4 x half> %_981, <4 x half> poison, <4 x i32> zeroinitializer
  %_985 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_986 = insertelement <4 x half> undef, half %_985, i64 0
  %_989 = shufflevector <4 x half> %_986, <4 x half> poison, <4 x i32> zeroinitializer
  %_990 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_991 = insertelement <4 x half> undef, half %_990, i64 0
  %_994 = shufflevector <4 x half> %_991, <4 x half> poison, <4 x i32> zeroinitializer
  %_995 = tail call <4 x half> @air.mix.v4f16(<4 x half> %_984, <4 x half> %_989, <4 x half> %_994)
  %_996 = tail call float @air.mix.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_997 = tail call <2 x float> @air.mix.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_998 = tail call <3 x float> @air.mix.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_999 = tail call <4 x float> @air.mix.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1000 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1001 = insertelement <2 x half> undef, half %_1000, i64 0
  %_1002 = shufflevector <2 x half> %_1001, <2 x half> poison, <2 x i32> zeroinitializer
  %_1003 = tail call <2 x half> @air.normalize.v2f16(<2 x half> %_1002)
  %_1004 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1005 = insertelement <3 x half> undef, half %_1004, i64 0
  %_1007 = shufflevector <3 x half> %_1005, <3 x half> poison, <3 x i32> zeroinitializer
  %_1008 = tail call <3 x half> @air.normalize.v3f16(<3 x half> %_1007)
  %_1009 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1010 = insertelement <4 x half> undef, half %_1009, i64 0
  %_1013 = shufflevector <4 x half> %_1010, <4 x half> poison, <4 x i32> zeroinitializer
  %_1014 = tail call <4 x half> @air.normalize.v4f16(<4 x half> %_1013)
  %_1015 = tail call <2 x float> @air.normalize.v2f32(<2 x float> zeroinitializer)
  %_1016 = tail call <3 x float> @air.normalize.v3f32(<3 x float> zeroinitializer)
  %_1017 = tail call <4 x float> @air.normalize.v4f32(<4 x float> zeroinitializer)
  %_1018 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1019 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1020 = tail call half @air.pow.f16(half %_1018, half %_1019)
  %_1021 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1022 = insertelement <2 x half> undef, half %_1021, i64 0
  %_1023 = shufflevector <2 x half> %_1022, <2 x half> poison, <2 x i32> zeroinitializer
  %_1024 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1025 = insertelement <2 x half> undef, half %_1024, i64 0
  %_1026 = shufflevector <2 x half> %_1025, <2 x half> poison, <2 x i32> zeroinitializer
  %_1027 = tail call <2 x half> @air.pow.v2f16(<2 x half> %_1023, <2 x half> %_1026)
  %_1028 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1029 = insertelement <3 x half> undef, half %_1028, i64 0
  %_1031 = shufflevector <3 x half> %_1029, <3 x half> poison, <3 x i32> zeroinitializer
  %_1032 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1033 = insertelement <3 x half> undef, half %_1032, i64 0
  %_1035 = shufflevector <3 x half> %_1033, <3 x half> poison, <3 x i32> zeroinitializer
  %_1036 = tail call <3 x half> @air.pow.v3f16(<3 x half> %_1031, <3 x half> %_1035)
  %_1037 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1038 = insertelement <4 x half> undef, half %_1037, i64 0
  %_1041 = shufflevector <4 x half> %_1038, <4 x half> poison, <4 x i32> zeroinitializer
  %_1042 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1043 = insertelement <4 x half> undef, half %_1042, i64 0
  %_1046 = shufflevector <4 x half> %_1043, <4 x half> poison, <4 x i32> zeroinitializer
  %_1047 = tail call <4 x half> @air.pow.v4f16(<4 x half> %_1041, <4 x half> %_1046)
  %_1048 = tail call float @air.pow.f32(float 0.000000e+00, float 0.000000e+00)
  %_1049 = tail call <2 x float> @air.pow.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1050 = tail call <3 x float> @air.pow.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1051 = tail call <4 x float> @air.pow.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1052 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1053 = insertelement <2 x half> undef, half %_1052, i64 0
  %_1054 = shufflevector <2 x half> %_1053, <2 x half> poison, <2 x i32> zeroinitializer
  %_1055 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1056 = insertelement <2 x half> undef, half %_1055, i64 0
  %_1057 = shufflevector <2 x half> %_1056, <2 x half> poison, <2 x i32> zeroinitializer
  %_1058 = tail call <2 x half> @air.reflect.v2f16(<2 x half> %_1054, <2 x half> %_1057)
  %_1059 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1060 = insertelement <3 x half> undef, half %_1059, i64 0
  %_1062 = shufflevector <3 x half> %_1060, <3 x half> poison, <3 x i32> zeroinitializer
  %_1063 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1064 = insertelement <3 x half> undef, half %_1063, i64 0
  %_1066 = shufflevector <3 x half> %_1064, <3 x half> poison, <3 x i32> zeroinitializer
  %_1067 = tail call <3 x half> @air.reflect.v3f16(<3 x half> %_1062, <3 x half> %_1066)
  %_1068 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1069 = insertelement <4 x half> undef, half %_1068, i64 0
  %_1072 = shufflevector <4 x half> %_1069, <4 x half> poison, <4 x i32> zeroinitializer
  %_1073 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1074 = insertelement <4 x half> undef, half %_1073, i64 0
  %_1077 = shufflevector <4 x half> %_1074, <4 x half> poison, <4 x i32> zeroinitializer
  %_1078 = tail call <4 x half> @air.reflect.v4f16(<4 x half> %_1072, <4 x half> %_1077)
  %_1079 = tail call <2 x float> @air.reflect.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1080 = tail call <3 x float> @air.reflect.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1081 = tail call <4 x float> @air.reflect.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1082 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1083 = insertelement <2 x half> undef, half %_1082, i64 0
  %_1084 = shufflevector <2 x half> %_1083, <2 x half> poison, <2 x i32> zeroinitializer
  %_1085 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1086 = insertelement <2 x half> undef, half %_1085, i64 0
  %_1087 = shufflevector <2 x half> %_1086, <2 x half> poison, <2 x i32> zeroinitializer
  %_1088 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1089 = tail call <2 x half> @air.refract.v2f16(<2 x half> %_1084, <2 x half> %_1087, half %_1088)
  %_1090 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1091 = insertelement <3 x half> undef, half %_1090, i64 0
  %_1093 = shufflevector <3 x half> %_1091, <3 x half> poison, <3 x i32> zeroinitializer
  %_1094 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1095 = insertelement <3 x half> undef, half %_1094, i64 0
  %_1097 = shufflevector <3 x half> %_1095, <3 x half> poison, <3 x i32> zeroinitializer
  %_1098 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1099 = tail call <3 x half> @air.refract.v3f16(<3 x half> %_1093, <3 x half> %_1097, half %_1098)
  %_1100 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1101 = insertelement <4 x half> undef, half %_1100, i64 0
  %_1104 = shufflevector <4 x half> %_1101, <4 x half> poison, <4 x i32> zeroinitializer
  %_1105 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1106 = insertelement <4 x half> undef, half %_1105, i64 0
  %_1109 = shufflevector <4 x half> %_1106, <4 x half> poison, <4 x i32> zeroinitializer
  %_1110 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1111 = tail call <4 x half> @air.refract.v4f16(<4 x half> %_1104, <4 x half> %_1109, half %_1110)
  %_1112 = tail call <2 x float> @air.refract.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, float 0.000000e+00)
  %_1113 = tail call <3 x float> @air.refract.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, float 0.000000e+00)
  %_1114 = tail call <4 x float> @air.refract.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, float 0.000000e+00)
  %_1115 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1116 = tail call half @air.round.f16(half %_1115)
  %_1117 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1118 = insertelement <2 x half> undef, half %_1117, i64 0
  %_1119 = shufflevector <2 x half> %_1118, <2 x half> poison, <2 x i32> zeroinitializer
  %_1120 = tail call <2 x half> @air.round.v2f16(<2 x half> %_1119)
  %_1121 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1122 = insertelement <3 x half> undef, half %_1121, i64 0
  %_1124 = shufflevector <3 x half> %_1122, <3 x half> poison, <3 x i32> zeroinitializer
  %_1125 = tail call <3 x half> @air.round.v3f16(<3 x half> %_1124)
  %_1126 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1127 = insertelement <4 x half> undef, half %_1126, i64 0
  %_1130 = shufflevector <4 x half> %_1127, <4 x half> poison, <4 x i32> zeroinitializer
  %_1131 = tail call <4 x half> @air.round.v4f16(<4 x half> %_1130)
  %_1132 = tail call float @air.round.f32(float 0.000000e+00)
  %_1133 = tail call <2 x float> @air.round.v2f32(<2 x float> zeroinitializer)
  %_1134 = tail call <3 x float> @air.round.v3f32(<3 x float> zeroinitializer)
  %_1135 = tail call <4 x float> @air.round.v4f32(<4 x float> zeroinitializer)
  %_1138 = tail call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler, <2 x float> zeroinitializer, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %_1139 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1140 = tail call i8 @air.sign.i8(i8 %_1139)
  %_1141 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1142 = insertelement <2 x i8> undef, i8 %_1141, i64 0
  %_1143 = shufflevector <2 x i8> %_1142, <2 x i8> poison, <2 x i32> zeroinitializer
  %_1144 = tail call <2 x i8> @air.sign.v2i8(<2 x i8> %_1143)
  %_1145 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1146 = insertelement <3 x i8> undef, i8 %_1145, i64 0
  %_1148 = shufflevector <3 x i8> %_1146, <3 x i8> poison, <3 x i32> zeroinitializer
  %_1149 = tail call <3 x i8> @air.sign.v3i8(<3 x i8> %_1148)
  %_1150 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1151 = insertelement <4 x i8> undef, i8 %_1150, i64 0
  %_1154 = shufflevector <4 x i8> %_1151, <4 x i8> poison, <4 x i32> zeroinitializer
  %_1155 = tail call <4 x i8> @air.sign.v4i8(<4 x i8> %_1154)
  %_1156 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1157 = tail call i16 @air.sign.i16(i16 %_1156)
  %_1158 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1159 = insertelement <2 x i16> undef, i16 %_1158, i64 0
  %_1160 = shufflevector <2 x i16> %_1159, <2 x i16> poison, <2 x i32> zeroinitializer
  %_1161 = tail call <2 x i16> @air.sign.v2i16(<2 x i16> %_1160)
  %_1162 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1163 = insertelement <3 x i16> undef, i16 %_1162, i64 0
  %_1165 = shufflevector <3 x i16> %_1163, <3 x i16> poison, <3 x i32> zeroinitializer
  %_1166 = tail call <3 x i16> @air.sign.v3i16(<3 x i16> %_1165)
  %_1167 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1168 = insertelement <4 x i16> undef, i16 %_1167, i64 0
  %_1171 = shufflevector <4 x i16> %_1168, <4 x i16> poison, <4 x i32> zeroinitializer
  %_1172 = tail call <4 x i16> @air.sign.v4i16(<4 x i16> %_1171)
  %_1173 = tail call i32 @air.sign.i32(i32 0)
  %_1174 = tail call <2 x i32> @air.sign.v2i32(<2 x i32> zeroinitializer)
  %_1175 = tail call <3 x i32> @air.sign.v3i32(<3 x i32> zeroinitializer)
  %_1176 = tail call <4 x i32> @air.sign.v4i32(<4 x i32> zeroinitializer)
  %_1177 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1178 = tail call half @air.sign.f16(half %_1177)
  %_1179 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1180 = insertelement <2 x half> undef, half %_1179, i64 0
  %_1181 = shufflevector <2 x half> %_1180, <2 x half> poison, <2 x i32> zeroinitializer
  %_1182 = tail call <2 x half> @air.sign.v2f16(<2 x half> %_1181)
  %_1183 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1184 = insertelement <3 x half> undef, half %_1183, i64 0
  %_1186 = shufflevector <3 x half> %_1184, <3 x half> poison, <3 x i32> zeroinitializer
  %_1187 = tail call <3 x half> @air.sign.v3f16(<3 x half> %_1186)
  %_1188 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1189 = insertelement <4 x half> undef, half %_1188, i64 0
  %_1192 = shufflevector <4 x half> %_1189, <4 x half> poison, <4 x i32> zeroinitializer
  %_1193 = tail call <4 x half> @air.sign.v4f16(<4 x half> %_1192)
  %_1194 = tail call float @air.sign.f32(float 0.000000e+00)
  %_1195 = tail call <2 x float> @air.sign.v2f32(<2 x float> zeroinitializer)
  %_1196 = tail call <3 x float> @air.sign.v3f32(<3 x float> zeroinitializer)
  %_1197 = tail call <4 x float> @air.sign.v4f32(<4 x float> zeroinitializer)
  %_1198 = tail call float @air.sin.f32(float 0.000000e+00)
  %_1199 = tail call float @air.sinh.f32(float 0.000000e+00)
  %_1200 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1201 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1202 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1203 = tail call half @air.smoothstep.f16(half %_1200, half %_1201, half %_1202)
  %_1204 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1205 = insertelement <2 x half> undef, half %_1204, i64 0
  %_1206 = shufflevector <2 x half> %_1205, <2 x half> poison, <2 x i32> zeroinitializer
  %_1207 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1208 = insertelement <2 x half> undef, half %_1207, i64 0
  %_1209 = shufflevector <2 x half> %_1208, <2 x half> poison, <2 x i32> zeroinitializer
  %_1210 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1211 = insertelement <2 x half> undef, half %_1210, i64 0
  %_1212 = shufflevector <2 x half> %_1211, <2 x half> poison, <2 x i32> zeroinitializer
  %_1213 = tail call <2 x half> @air.smoothstep.v2f16(<2 x half> %_1206, <2 x half> %_1209, <2 x half> %_1212)
  %_1214 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1215 = insertelement <3 x half> undef, half %_1214, i64 0
  %_1217 = shufflevector <3 x half> %_1215, <3 x half> poison, <3 x i32> zeroinitializer
  %_1218 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1219 = insertelement <3 x half> undef, half %_1218, i64 0
  %_1221 = shufflevector <3 x half> %_1219, <3 x half> poison, <3 x i32> zeroinitializer
  %_1222 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1223 = insertelement <3 x half> undef, half %_1222, i64 0
  %_1225 = shufflevector <3 x half> %_1223, <3 x half> poison, <3 x i32> zeroinitializer
  %_1226 = tail call <3 x half> @air.smoothstep.v3f16(<3 x half> %_1217, <3 x half> %_1221, <3 x half> %_1225)
  %_1227 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1228 = insertelement <4 x half> undef, half %_1227, i64 0
  %_1231 = shufflevector <4 x half> %_1228, <4 x half> poison, <4 x i32> zeroinitializer
  %_1232 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1233 = insertelement <4 x half> undef, half %_1232, i64 0
  %_1236 = shufflevector <4 x half> %_1233, <4 x half> poison, <4 x i32> zeroinitializer
  %_1237 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1238 = insertelement <4 x half> undef, half %_1237, i64 0
  %_1241 = shufflevector <4 x half> %_1238, <4 x half> poison, <4 x i32> zeroinitializer
  %_1242 = tail call <4 x half> @air.smoothstep.v4f16(<4 x half> %_1231, <4 x half> %_1236, <4 x half> %_1241)
  %_1243 = tail call float @air.smoothstep.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_1244 = tail call <2 x float> @air.smoothstep.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1245 = tail call <3 x float> @air.smoothstep.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1246 = tail call <4 x float> @air.smoothstep.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1247 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1248 = tail call half @air.sqrt.f16(half %_1247)
  %_1249 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1250 = insertelement <2 x half> undef, half %_1249, i64 0
  %_1251 = shufflevector <2 x half> %_1250, <2 x half> poison, <2 x i32> zeroinitializer
  %_1252 = tail call <2 x half> @air.sqrt.v2f16(<2 x half> %_1251)
  %_1253 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1254 = insertelement <3 x half> undef, half %_1253, i64 0
  %_1256 = shufflevector <3 x half> %_1254, <3 x half> poison, <3 x i32> zeroinitializer
  %_1257 = tail call <3 x half> @air.sqrt.v3f16(<3 x half> %_1256)
  %_1258 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1259 = insertelement <4 x half> undef, half %_1258, i64 0
  %_1262 = shufflevector <4 x half> %_1259, <4 x half> poison, <4 x i32> zeroinitializer
  %_1263 = tail call <4 x half> @air.sqrt.v4f16(<4 x half> %_1262)
  %_1264 = tail call float @air.sqrt.f32(float 0.000000e+00)
  %_1265 = tail call <2 x float> @air.sqrt.v2f32(<2 x float> zeroinitializer)
  %_1266 = tail call <3 x float> @air.sqrt.v3f32(<3 x float> zeroinitializer)
  %_1267 = tail call <4 x float> @air.sqrt.v4f32(<4 x float> zeroinitializer)
  %_1268 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1269 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1270 = tail call half @air.step.f16(half %_1268, half %_1269)
  %_1271 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1272 = insertelement <2 x half> undef, half %_1271, i64 0
  %_1273 = shufflevector <2 x half> %_1272, <2 x half> poison, <2 x i32> zeroinitializer
  %_1274 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1275 = insertelement <2 x half> undef, half %_1274, i64 0
  %_1276 = shufflevector <2 x half> %_1275, <2 x half> poison, <2 x i32> zeroinitializer
  %_1277 = tail call <2 x half> @air.step.v2f16(<2 x half> %_1273, <2 x half> %_1276)
  %_1278 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1279 = insertelement <3 x half> undef, half %_1278, i64 0
  %_1281 = shufflevector <3 x half> %_1279, <3 x half> poison, <3 x i32> zeroinitializer
  %_1282 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1283 = insertelement <3 x half> undef, half %_1282, i64 0
  %_1285 = shufflevector <3 x half> %_1283, <3 x half> poison, <3 x i32> zeroinitializer
  %_1286 = tail call <3 x half> @air.step.v3f16(<3 x half> %_1281, <3 x half> %_1285)
  %_1287 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1288 = insertelement <4 x half> undef, half %_1287, i64 0
  %_1291 = shufflevector <4 x half> %_1288, <4 x half> poison, <4 x i32> zeroinitializer
  %_1292 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1293 = insertelement <4 x half> undef, half %_1292, i64 0
  %_1296 = shufflevector <4 x half> %_1293, <4 x half> poison, <4 x i32> zeroinitializer
  %_1297 = tail call <4 x half> @air.step.v4f16(<4 x half> %_1291, <4 x half> %_1296)
  %_1298 = tail call float @air.step.f32(float 0.000000e+00, float 0.000000e+00)
  %_1299 = tail call <2 x float> @air.step.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1300 = tail call <3 x float> @air.step.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1301 = tail call <4 x float> @air.step.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1302 = tail call float @air.tan.f32(float 0.000000e+00)
  %_1303 = tail call float @air.tanh.f32(float 0.000000e+00)
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
!9 = !{ptr @testStandardFunctions.t1f32.sm, !10, !12}
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
