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

declare i8 @air.convert.s.i8.s.i32(i32) local_unnamed_addr

declare i16 @air.convert.s.i16.s.i32(i32) local_unnamed_addr

define %FragmentOut @testStandardFunctions.t1f32.sm(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler) local_unnamed_addr {
  %_280 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_281 = tail call i8 @air.abs.i8(i8 %_280)
  %_282 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_283 = insertelement <2 x i8> undef, i8 %_282, i64 0
  %_284 = shufflevector <2 x i8> %_283, <2 x i8> poison, <2 x i32> zeroinitializer
  %_285 = tail call <2 x i8> @air.abs.v2i8(<2 x i8> %_284)
  %_286 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_287 = insertelement <3 x i8> undef, i8 %_286, i64 0
  %_289 = shufflevector <3 x i8> %_287, <3 x i8> poison, <3 x i32> zeroinitializer
  %_290 = tail call <3 x i8> @air.abs.v3i8(<3 x i8> %_289)
  %_291 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_292 = insertelement <4 x i8> undef, i8 %_291, i64 0
  %_295 = shufflevector <4 x i8> %_292, <4 x i8> poison, <4 x i32> zeroinitializer
  %_296 = tail call <4 x i8> @air.abs.v4i8(<4 x i8> %_295)
  %_297 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_298 = tail call i16 @air.abs.i16(i16 %_297)
  %_299 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_300 = insertelement <2 x i16> undef, i16 %_299, i64 0
  %_301 = shufflevector <2 x i16> %_300, <2 x i16> poison, <2 x i32> zeroinitializer
  %_302 = tail call <2 x i16> @air.abs.v2i16(<2 x i16> %_301)
  %_303 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_304 = insertelement <3 x i16> undef, i16 %_303, i64 0
  %_306 = shufflevector <3 x i16> %_304, <3 x i16> poison, <3 x i32> zeroinitializer
  %_307 = tail call <3 x i16> @air.abs.v3i16(<3 x i16> %_306)
  %_308 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_309 = insertelement <4 x i16> undef, i16 %_308, i64 0
  %_312 = shufflevector <4 x i16> %_309, <4 x i16> poison, <4 x i32> zeroinitializer
  %_313 = tail call <4 x i16> @air.abs.v4i16(<4 x i16> %_312)
  %_314 = tail call i32 @air.abs.i32(i32 0)
  %_315 = tail call <2 x i32> @air.abs.v2i32(<2 x i32> zeroinitializer)
  %_316 = tail call <3 x i32> @air.abs.v3i32(<3 x i32> zeroinitializer)
  %_317 = tail call <4 x i32> @air.abs.v4i32(<4 x i32> zeroinitializer)
  %_319 = tail call half @air.abs.f16(half 0xH0000)
  %_323 = tail call <2 x half> @air.abs.v2f16(<2 x half> zeroinitializer)
  %_328 = tail call <3 x half> @air.abs.v3f16(<3 x half> zeroinitializer)
  %_334 = tail call <4 x half> @air.abs.v4f16(<4 x half> zeroinitializer)
  %_335 = tail call float @air.abs.f32(float 0.000000e+00)
  %_336 = tail call <2 x float> @air.abs.v2f32(<2 x float> zeroinitializer)
  %_337 = tail call <3 x float> @air.abs.v3f32(<3 x float> zeroinitializer)
  %_338 = tail call <4 x float> @air.abs.v4f32(<4 x float> zeroinitializer)
  %_339 = tail call float @air.acos.f32(float 0.000000e+00)
  %_340 = tail call float @air.acosh.f32(float 0.000000e+00)
  %_341 = tail call float @air.asin.f32(float 0.000000e+00)
  %_342 = tail call float @air.asinh.f32(float 0.000000e+00)
  %_343 = tail call float @air.atan.f32(float 0.000000e+00)
  %_344 = tail call float @air.atanh.f32(float 0.000000e+00)
  %_346 = tail call half @air.ceil.f16(half 0xH0000)
  %_350 = tail call <2 x half> @air.ceil.v2f16(<2 x half> zeroinitializer)
  %_355 = tail call <3 x half> @air.ceil.v3f16(<3 x half> zeroinitializer)
  %_361 = tail call <4 x half> @air.ceil.v4f16(<4 x half> zeroinitializer)
  %_362 = tail call float @air.ceil.f32(float 0.000000e+00)
  %_363 = tail call <2 x float> @air.ceil.v2f32(<2 x float> zeroinitializer)
  %_364 = tail call <3 x float> @air.ceil.v3f32(<3 x float> zeroinitializer)
  %_365 = tail call <4 x float> @air.ceil.v4f32(<4 x float> zeroinitializer)
  %_366 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_367 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_368 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_369 = tail call i8 @air.clamp.i8(i8 %_366, i8 %_367, i8 %_368)
  %_370 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_371 = insertelement <2 x i8> undef, i8 %_370, i64 0
  %_372 = shufflevector <2 x i8> %_371, <2 x i8> poison, <2 x i32> zeroinitializer
  %_373 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_374 = insertelement <2 x i8> undef, i8 %_373, i64 0
  %_375 = shufflevector <2 x i8> %_374, <2 x i8> poison, <2 x i32> zeroinitializer
  %_376 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_377 = insertelement <2 x i8> undef, i8 %_376, i64 0
  %_378 = shufflevector <2 x i8> %_377, <2 x i8> poison, <2 x i32> zeroinitializer
  %_379 = tail call <2 x i8> @air.clamp.v2i8(<2 x i8> %_372, <2 x i8> %_375, <2 x i8> %_378)
  %_380 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_381 = insertelement <3 x i8> undef, i8 %_380, i64 0
  %_383 = shufflevector <3 x i8> %_381, <3 x i8> poison, <3 x i32> zeroinitializer
  %_384 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_385 = insertelement <3 x i8> undef, i8 %_384, i64 0
  %_387 = shufflevector <3 x i8> %_385, <3 x i8> poison, <3 x i32> zeroinitializer
  %_388 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_389 = insertelement <3 x i8> undef, i8 %_388, i64 0
  %_391 = shufflevector <3 x i8> %_389, <3 x i8> poison, <3 x i32> zeroinitializer
  %_392 = tail call <3 x i8> @air.clamp.v3i8(<3 x i8> %_383, <3 x i8> %_387, <3 x i8> %_391)
  %_393 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_394 = insertelement <4 x i8> undef, i8 %_393, i64 0
  %_397 = shufflevector <4 x i8> %_394, <4 x i8> poison, <4 x i32> zeroinitializer
  %_398 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_399 = insertelement <4 x i8> undef, i8 %_398, i64 0
  %_402 = shufflevector <4 x i8> %_399, <4 x i8> poison, <4 x i32> zeroinitializer
  %_403 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_404 = insertelement <4 x i8> undef, i8 %_403, i64 0
  %_407 = shufflevector <4 x i8> %_404, <4 x i8> poison, <4 x i32> zeroinitializer
  %_408 = tail call <4 x i8> @air.clamp.v4i8(<4 x i8> %_397, <4 x i8> %_402, <4 x i8> %_407)
  %_409 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_410 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_411 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_412 = tail call i16 @air.clamp.i16(i16 %_409, i16 %_410, i16 %_411)
  %_413 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_414 = insertelement <2 x i16> undef, i16 %_413, i64 0
  %_415 = shufflevector <2 x i16> %_414, <2 x i16> poison, <2 x i32> zeroinitializer
  %_416 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_417 = insertelement <2 x i16> undef, i16 %_416, i64 0
  %_418 = shufflevector <2 x i16> %_417, <2 x i16> poison, <2 x i32> zeroinitializer
  %_419 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_420 = insertelement <2 x i16> undef, i16 %_419, i64 0
  %_421 = shufflevector <2 x i16> %_420, <2 x i16> poison, <2 x i32> zeroinitializer
  %_422 = tail call <2 x i16> @air.clamp.v2i16(<2 x i16> %_415, <2 x i16> %_418, <2 x i16> %_421)
  %_423 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_424 = insertelement <3 x i16> undef, i16 %_423, i64 0
  %_426 = shufflevector <3 x i16> %_424, <3 x i16> poison, <3 x i32> zeroinitializer
  %_427 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_428 = insertelement <3 x i16> undef, i16 %_427, i64 0
  %_430 = shufflevector <3 x i16> %_428, <3 x i16> poison, <3 x i32> zeroinitializer
  %_431 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_432 = insertelement <3 x i16> undef, i16 %_431, i64 0
  %_434 = shufflevector <3 x i16> %_432, <3 x i16> poison, <3 x i32> zeroinitializer
  %_435 = tail call <3 x i16> @air.clamp.v3i16(<3 x i16> %_426, <3 x i16> %_430, <3 x i16> %_434)
  %_436 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_437 = insertelement <4 x i16> undef, i16 %_436, i64 0
  %_440 = shufflevector <4 x i16> %_437, <4 x i16> poison, <4 x i32> zeroinitializer
  %_441 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_442 = insertelement <4 x i16> undef, i16 %_441, i64 0
  %_445 = shufflevector <4 x i16> %_442, <4 x i16> poison, <4 x i32> zeroinitializer
  %_446 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_447 = insertelement <4 x i16> undef, i16 %_446, i64 0
  %_450 = shufflevector <4 x i16> %_447, <4 x i16> poison, <4 x i32> zeroinitializer
  %_451 = tail call <4 x i16> @air.clamp.v4i16(<4 x i16> %_440, <4 x i16> %_445, <4 x i16> %_450)
  %_452 = tail call i32 @air.clamp.i32(i32 0, i32 0, i32 0)
  %_453 = tail call <2 x i32> @air.clamp.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_454 = tail call <3 x i32> @air.clamp.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_455 = tail call <4 x i32> @air.clamp.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_459 = tail call half @air.clamp.f16(half 0xH0000, half 0xH0000, half 0xH0000)
  %_469 = tail call <2 x half> @air.clamp.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_482 = tail call <3 x half> @air.clamp.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_498 = tail call <4 x half> @air.clamp.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_499 = tail call float @air.clamp.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_500 = tail call <2 x float> @air.clamp.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_501 = tail call <3 x float> @air.clamp.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_502 = tail call <4 x float> @air.clamp.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_503 = tail call float @air.cos.f32(float 0.000000e+00)
  %_504 = tail call float @air.cosh.f32(float 0.000000e+00)
  %_513 = tail call <3 x half> @air.cross.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_514 = tail call <3 x float> @air.cross.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_521 = tail call half @air.distance.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_530 = tail call half @air.distance.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_541 = tail call half @air.distance.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_542 = tail call float @air.distance.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_543 = tail call float @air.distance.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_544 = tail call float @air.distance.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_551 = tail call half @air.dot.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_560 = tail call half @air.dot.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_571 = tail call half @air.dot.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_572 = tail call float @air.dot.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_573 = tail call float @air.dot.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_574 = tail call float @air.dot.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_576 = tail call half @air.exp.f16(half 0xH0000)
  %_580 = tail call <2 x half> @air.exp.v2f16(<2 x half> zeroinitializer)
  %_585 = tail call <3 x half> @air.exp.v3f16(<3 x half> zeroinitializer)
  %_591 = tail call <4 x half> @air.exp.v4f16(<4 x half> zeroinitializer)
  %_592 = tail call float @air.exp.f32(float 0.000000e+00)
  %_593 = tail call <2 x float> @air.exp.v2f32(<2 x float> zeroinitializer)
  %_594 = tail call <3 x float> @air.exp.v3f32(<3 x float> zeroinitializer)
  %_595 = tail call <4 x float> @air.exp.v4f32(<4 x float> zeroinitializer)
  %_597 = tail call half @air.exp2.f16(half 0xH0000)
  %_601 = tail call <2 x half> @air.exp2.v2f16(<2 x half> zeroinitializer)
  %_606 = tail call <3 x half> @air.exp2.v3f16(<3 x half> zeroinitializer)
  %_612 = tail call <4 x half> @air.exp2.v4f16(<4 x half> zeroinitializer)
  %_613 = tail call float @air.exp2.f32(float 0.000000e+00)
  %_614 = tail call <2 x float> @air.exp2.v2f32(<2 x float> zeroinitializer)
  %_615 = tail call <3 x float> @air.exp2.v3f32(<3 x float> zeroinitializer)
  %_616 = tail call <4 x float> @air.exp2.v4f32(<4 x float> zeroinitializer)
  %_618 = tail call half @air.floor.f16(half 0xH0000)
  %_622 = tail call <2 x half> @air.floor.v2f16(<2 x half> zeroinitializer)
  %_627 = tail call <3 x half> @air.floor.v3f16(<3 x half> zeroinitializer)
  %_633 = tail call <4 x half> @air.floor.v4f16(<4 x half> zeroinitializer)
  %_634 = tail call float @air.floor.f32(float 0.000000e+00)
  %_635 = tail call <2 x float> @air.floor.v2f32(<2 x float> zeroinitializer)
  %_636 = tail call <3 x float> @air.floor.v3f32(<3 x float> zeroinitializer)
  %_637 = tail call <4 x float> @air.floor.v4f32(<4 x float> zeroinitializer)
  %_639 = tail call half @air.fract.f16(half 0xH0000)
  %_643 = tail call <2 x half> @air.fract.v2f16(<2 x half> zeroinitializer)
  %_648 = tail call <3 x half> @air.fract.v3f16(<3 x half> zeroinitializer)
  %_654 = tail call <4 x half> @air.fract.v4f16(<4 x half> zeroinitializer)
  %_655 = tail call float @air.fract.f32(float 0.000000e+00)
  %_656 = tail call <2 x float> @air.fract.v2f32(<2 x float> zeroinitializer)
  %_657 = tail call <3 x float> @air.fract.v3f32(<3 x float> zeroinitializer)
  %_658 = tail call <4 x float> @air.fract.v4f32(<4 x float> zeroinitializer)
  %_660 = tail call i1 @air.isinf.f16(half 0xH0000)
  %_664 = tail call <2 x i1> @air.isinf.v2f16(<2 x half> zeroinitializer)
  %_669 = tail call <3 x i1> @air.isinf.v3f16(<3 x half> zeroinitializer)
  %_675 = tail call <4 x i1> @air.isinf.v4f16(<4 x half> zeroinitializer)
  %_676 = tail call i1 @air.isinf.f32(float 0.000000e+00)
  %_677 = tail call <2 x i1> @air.isinf.v2f32(<2 x float> zeroinitializer)
  %_678 = tail call <3 x i1> @air.isinf.v3f32(<3 x float> zeroinitializer)
  %_679 = tail call <4 x i1> @air.isinf.v4f32(<4 x float> zeroinitializer)
  %_681 = tail call i1 @air.isnan.f16(half 0xH0000)
  %_685 = tail call <2 x i1> @air.isnan.v2f16(<2 x half> zeroinitializer)
  %_690 = tail call <3 x i1> @air.isnan.v3f16(<3 x half> zeroinitializer)
  %_696 = tail call <4 x i1> @air.isnan.v4f16(<4 x half> zeroinitializer)
  %_697 = tail call i1 @air.isnan.f32(float 0.000000e+00)
  %_698 = tail call <2 x i1> @air.isnan.v2f32(<2 x float> zeroinitializer)
  %_699 = tail call <3 x i1> @air.isnan.v3f32(<3 x float> zeroinitializer)
  %_700 = tail call <4 x i1> @air.isnan.v4f32(<4 x float> zeroinitializer)
  %_704 = tail call half @air.length.v2f16(<2 x half> zeroinitializer)
  %_709 = tail call half @air.length.v3f16(<3 x half> zeroinitializer)
  %_715 = tail call half @air.length.v4f16(<4 x half> zeroinitializer)
  %_716 = tail call float @air.length.v2f32(<2 x float> zeroinitializer)
  %_717 = tail call float @air.length.v3f32(<3 x float> zeroinitializer)
  %_718 = tail call float @air.length.v4f32(<4 x float> zeroinitializer)
  %_720 = tail call half @air.log.f16(half 0xH0000)
  %_724 = tail call <2 x half> @air.log.v2f16(<2 x half> zeroinitializer)
  %_729 = tail call <3 x half> @air.log.v3f16(<3 x half> zeroinitializer)
  %_735 = tail call <4 x half> @air.log.v4f16(<4 x half> zeroinitializer)
  %_736 = tail call float @air.log.f32(float 0.000000e+00)
  %_737 = tail call <2 x float> @air.log.v2f32(<2 x float> zeroinitializer)
  %_738 = tail call <3 x float> @air.log.v3f32(<3 x float> zeroinitializer)
  %_739 = tail call <4 x float> @air.log.v4f32(<4 x float> zeroinitializer)
  %_741 = tail call half @air.log2.f16(half 0xH0000)
  %_745 = tail call <2 x half> @air.log2.v2f16(<2 x half> zeroinitializer)
  %_750 = tail call <3 x half> @air.log2.v3f16(<3 x half> zeroinitializer)
  %_756 = tail call <4 x half> @air.log2.v4f16(<4 x half> zeroinitializer)
  %_757 = tail call float @air.log2.f32(float 0.000000e+00)
  %_758 = tail call <2 x float> @air.log2.v2f32(<2 x float> zeroinitializer)
  %_759 = tail call <3 x float> @air.log2.v3f32(<3 x float> zeroinitializer)
  %_760 = tail call <4 x float> @air.log2.v4f32(<4 x float> zeroinitializer)
  %_761 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_762 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_763 = tail call i8 @air.max.i8(i8 %_761, i8 %_762)
  %_764 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_765 = insertelement <2 x i8> undef, i8 %_764, i64 0
  %_766 = shufflevector <2 x i8> %_765, <2 x i8> poison, <2 x i32> zeroinitializer
  %_767 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_768 = insertelement <2 x i8> undef, i8 %_767, i64 0
  %_769 = shufflevector <2 x i8> %_768, <2 x i8> poison, <2 x i32> zeroinitializer
  %_770 = tail call <2 x i8> @air.max.v2i8(<2 x i8> %_766, <2 x i8> %_769)
  %_771 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_772 = insertelement <3 x i8> undef, i8 %_771, i64 0
  %_774 = shufflevector <3 x i8> %_772, <3 x i8> poison, <3 x i32> zeroinitializer
  %_775 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_776 = insertelement <3 x i8> undef, i8 %_775, i64 0
  %_778 = shufflevector <3 x i8> %_776, <3 x i8> poison, <3 x i32> zeroinitializer
  %_779 = tail call <3 x i8> @air.max.v3i8(<3 x i8> %_774, <3 x i8> %_778)
  %_780 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_781 = insertelement <4 x i8> undef, i8 %_780, i64 0
  %_784 = shufflevector <4 x i8> %_781, <4 x i8> poison, <4 x i32> zeroinitializer
  %_785 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_786 = insertelement <4 x i8> undef, i8 %_785, i64 0
  %_789 = shufflevector <4 x i8> %_786, <4 x i8> poison, <4 x i32> zeroinitializer
  %_790 = tail call <4 x i8> @air.max.v4i8(<4 x i8> %_784, <4 x i8> %_789)
  %_791 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_792 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_793 = tail call i16 @air.max.i16(i16 %_791, i16 %_792)
  %_794 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_795 = insertelement <2 x i16> undef, i16 %_794, i64 0
  %_796 = shufflevector <2 x i16> %_795, <2 x i16> poison, <2 x i32> zeroinitializer
  %_797 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_798 = insertelement <2 x i16> undef, i16 %_797, i64 0
  %_799 = shufflevector <2 x i16> %_798, <2 x i16> poison, <2 x i32> zeroinitializer
  %_800 = tail call <2 x i16> @air.max.v2i16(<2 x i16> %_796, <2 x i16> %_799)
  %_801 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_802 = insertelement <3 x i16> undef, i16 %_801, i64 0
  %_804 = shufflevector <3 x i16> %_802, <3 x i16> poison, <3 x i32> zeroinitializer
  %_805 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_806 = insertelement <3 x i16> undef, i16 %_805, i64 0
  %_808 = shufflevector <3 x i16> %_806, <3 x i16> poison, <3 x i32> zeroinitializer
  %_809 = tail call <3 x i16> @air.max.v3i16(<3 x i16> %_804, <3 x i16> %_808)
  %_810 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_811 = insertelement <4 x i16> undef, i16 %_810, i64 0
  %_814 = shufflevector <4 x i16> %_811, <4 x i16> poison, <4 x i32> zeroinitializer
  %_815 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_816 = insertelement <4 x i16> undef, i16 %_815, i64 0
  %_819 = shufflevector <4 x i16> %_816, <4 x i16> poison, <4 x i32> zeroinitializer
  %_820 = tail call <4 x i16> @air.max.v4i16(<4 x i16> %_814, <4 x i16> %_819)
  %_821 = tail call i32 @air.max.i32(i32 0, i32 0)
  %_822 = tail call <2 x i32> @air.max.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_823 = tail call <3 x i32> @air.max.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_824 = tail call <4 x i32> @air.max.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_827 = tail call half @air.max.f16(half 0xH0000, half 0xH0000)
  %_834 = tail call <2 x half> @air.max.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_843 = tail call <3 x half> @air.max.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_854 = tail call <4 x half> @air.max.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_855 = tail call float @air.max.f32(float 0.000000e+00, float 0.000000e+00)
  %_856 = tail call <2 x float> @air.max.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_857 = tail call <3 x float> @air.max.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_858 = tail call <4 x float> @air.max.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_859 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_860 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_861 = tail call i8 @air.min.i8(i8 %_859, i8 %_860)
  %_862 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_863 = insertelement <2 x i8> undef, i8 %_862, i64 0
  %_864 = shufflevector <2 x i8> %_863, <2 x i8> poison, <2 x i32> zeroinitializer
  %_865 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_866 = insertelement <2 x i8> undef, i8 %_865, i64 0
  %_867 = shufflevector <2 x i8> %_866, <2 x i8> poison, <2 x i32> zeroinitializer
  %_868 = tail call <2 x i8> @air.min.v2i8(<2 x i8> %_864, <2 x i8> %_867)
  %_869 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_870 = insertelement <3 x i8> undef, i8 %_869, i64 0
  %_872 = shufflevector <3 x i8> %_870, <3 x i8> poison, <3 x i32> zeroinitializer
  %_873 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_874 = insertelement <3 x i8> undef, i8 %_873, i64 0
  %_876 = shufflevector <3 x i8> %_874, <3 x i8> poison, <3 x i32> zeroinitializer
  %_877 = tail call <3 x i8> @air.min.v3i8(<3 x i8> %_872, <3 x i8> %_876)
  %_878 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_879 = insertelement <4 x i8> undef, i8 %_878, i64 0
  %_882 = shufflevector <4 x i8> %_879, <4 x i8> poison, <4 x i32> zeroinitializer
  %_883 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_884 = insertelement <4 x i8> undef, i8 %_883, i64 0
  %_887 = shufflevector <4 x i8> %_884, <4 x i8> poison, <4 x i32> zeroinitializer
  %_888 = tail call <4 x i8> @air.min.v4i8(<4 x i8> %_882, <4 x i8> %_887)
  %_889 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_890 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_891 = tail call i16 @air.min.i16(i16 %_889, i16 %_890)
  %_892 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_893 = insertelement <2 x i16> undef, i16 %_892, i64 0
  %_894 = shufflevector <2 x i16> %_893, <2 x i16> poison, <2 x i32> zeroinitializer
  %_895 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_896 = insertelement <2 x i16> undef, i16 %_895, i64 0
  %_897 = shufflevector <2 x i16> %_896, <2 x i16> poison, <2 x i32> zeroinitializer
  %_898 = tail call <2 x i16> @air.min.v2i16(<2 x i16> %_894, <2 x i16> %_897)
  %_899 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_900 = insertelement <3 x i16> undef, i16 %_899, i64 0
  %_902 = shufflevector <3 x i16> %_900, <3 x i16> poison, <3 x i32> zeroinitializer
  %_903 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_904 = insertelement <3 x i16> undef, i16 %_903, i64 0
  %_906 = shufflevector <3 x i16> %_904, <3 x i16> poison, <3 x i32> zeroinitializer
  %_907 = tail call <3 x i16> @air.min.v3i16(<3 x i16> %_902, <3 x i16> %_906)
  %_908 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_909 = insertelement <4 x i16> undef, i16 %_908, i64 0
  %_912 = shufflevector <4 x i16> %_909, <4 x i16> poison, <4 x i32> zeroinitializer
  %_913 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_914 = insertelement <4 x i16> undef, i16 %_913, i64 0
  %_917 = shufflevector <4 x i16> %_914, <4 x i16> poison, <4 x i32> zeroinitializer
  %_918 = tail call <4 x i16> @air.min.v4i16(<4 x i16> %_912, <4 x i16> %_917)
  %_919 = tail call i32 @air.min.i32(i32 0, i32 0)
  %_920 = tail call <2 x i32> @air.min.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_921 = tail call <3 x i32> @air.min.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_922 = tail call <4 x i32> @air.min.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_925 = tail call half @air.min.f16(half 0xH0000, half 0xH0000)
  %_932 = tail call <2 x half> @air.min.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_941 = tail call <3 x half> @air.min.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_952 = tail call <4 x half> @air.min.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_953 = tail call float @air.min.f32(float 0.000000e+00, float 0.000000e+00)
  %_954 = tail call <2 x float> @air.min.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_955 = tail call <3 x float> @air.min.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_956 = tail call <4 x float> @air.min.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_960 = tail call half @air.mix.f16(half 0xH0000, half 0xH0000, half 0xH0000)
  %_970 = tail call <2 x half> @air.mix.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_983 = tail call <3 x half> @air.mix.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_999 = tail call <4 x half> @air.mix.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_1000 = tail call float @air.mix.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_1001 = tail call <2 x float> @air.mix.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1002 = tail call <3 x float> @air.mix.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1003 = tail call <4 x float> @air.mix.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1007 = tail call <2 x half> @air.normalize.v2f16(<2 x half> zeroinitializer)
  %_1012 = tail call <3 x half> @air.normalize.v3f16(<3 x half> zeroinitializer)
  %_1018 = tail call <4 x half> @air.normalize.v4f16(<4 x half> zeroinitializer)
  %_1019 = tail call <2 x float> @air.normalize.v2f32(<2 x float> zeroinitializer)
  %_1020 = tail call <3 x float> @air.normalize.v3f32(<3 x float> zeroinitializer)
  %_1021 = tail call <4 x float> @air.normalize.v4f32(<4 x float> zeroinitializer)
  %_1024 = tail call half @air.pow.f16(half 0xH0000, half 0xH0000)
  %_1031 = tail call <2 x half> @air.pow.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_1040 = tail call <3 x half> @air.pow.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_1051 = tail call <4 x half> @air.pow.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_1052 = tail call float @air.pow.f32(float 0.000000e+00, float 0.000000e+00)
  %_1053 = tail call <2 x float> @air.pow.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1054 = tail call <3 x float> @air.pow.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1055 = tail call <4 x float> @air.pow.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1062 = tail call <2 x half> @air.reflect.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_1071 = tail call <3 x half> @air.reflect.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_1082 = tail call <4 x half> @air.reflect.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_1083 = tail call <2 x float> @air.reflect.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1084 = tail call <3 x float> @air.reflect.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1085 = tail call <4 x float> @air.reflect.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1093 = tail call <2 x half> @air.refract.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer, half 0xH0000)
  %_1103 = tail call <3 x half> @air.refract.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer, half 0xH0000)
  %_1115 = tail call <4 x half> @air.refract.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer, half 0xH0000)
  %_1116 = tail call <2 x float> @air.refract.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, float 0.000000e+00)
  %_1117 = tail call <3 x float> @air.refract.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, float 0.000000e+00)
  %_1118 = tail call <4 x float> @air.refract.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, float 0.000000e+00)
  %_1120 = tail call half @air.round.f16(half 0xH0000)
  %_1124 = tail call <2 x half> @air.round.v2f16(<2 x half> zeroinitializer)
  %_1129 = tail call <3 x half> @air.round.v3f16(<3 x half> zeroinitializer)
  %_1135 = tail call <4 x half> @air.round.v4f16(<4 x half> zeroinitializer)
  %_1136 = tail call float @air.round.f32(float 0.000000e+00)
  %_1137 = tail call <2 x float> @air.round.v2f32(<2 x float> zeroinitializer)
  %_1138 = tail call <3 x float> @air.round.v3f32(<3 x float> zeroinitializer)
  %_1139 = tail call <4 x float> @air.round.v4f32(<4 x float> zeroinitializer)
  %_1142 = tail call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler, <2 x float> zeroinitializer, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %_1143 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_1144 = tail call i8 @air.sign.i8(i8 %_1143)
  %_1145 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_1146 = insertelement <2 x i8> undef, i8 %_1145, i64 0
  %_1147 = shufflevector <2 x i8> %_1146, <2 x i8> poison, <2 x i32> zeroinitializer
  %_1148 = tail call <2 x i8> @air.sign.v2i8(<2 x i8> %_1147)
  %_1149 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_1150 = insertelement <3 x i8> undef, i8 %_1149, i64 0
  %_1152 = shufflevector <3 x i8> %_1150, <3 x i8> poison, <3 x i32> zeroinitializer
  %_1153 = tail call <3 x i8> @air.sign.v3i8(<3 x i8> %_1152)
  %_1154 = tail call i8 @air.convert.s.i8.s.i32(i32 0)
  %_1155 = insertelement <4 x i8> undef, i8 %_1154, i64 0
  %_1158 = shufflevector <4 x i8> %_1155, <4 x i8> poison, <4 x i32> zeroinitializer
  %_1159 = tail call <4 x i8> @air.sign.v4i8(<4 x i8> %_1158)
  %_1160 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_1161 = tail call i16 @air.sign.i16(i16 %_1160)
  %_1162 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_1163 = insertelement <2 x i16> undef, i16 %_1162, i64 0
  %_1164 = shufflevector <2 x i16> %_1163, <2 x i16> poison, <2 x i32> zeroinitializer
  %_1165 = tail call <2 x i16> @air.sign.v2i16(<2 x i16> %_1164)
  %_1166 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_1167 = insertelement <3 x i16> undef, i16 %_1166, i64 0
  %_1169 = shufflevector <3 x i16> %_1167, <3 x i16> poison, <3 x i32> zeroinitializer
  %_1170 = tail call <3 x i16> @air.sign.v3i16(<3 x i16> %_1169)
  %_1171 = tail call i16 @air.convert.s.i16.s.i32(i32 0)
  %_1172 = insertelement <4 x i16> undef, i16 %_1171, i64 0
  %_1175 = shufflevector <4 x i16> %_1172, <4 x i16> poison, <4 x i32> zeroinitializer
  %_1176 = tail call <4 x i16> @air.sign.v4i16(<4 x i16> %_1175)
  %_1177 = tail call i32 @air.sign.i32(i32 0)
  %_1178 = tail call <2 x i32> @air.sign.v2i32(<2 x i32> zeroinitializer)
  %_1179 = tail call <3 x i32> @air.sign.v3i32(<3 x i32> zeroinitializer)
  %_1180 = tail call <4 x i32> @air.sign.v4i32(<4 x i32> zeroinitializer)
  %_1182 = tail call half @air.sign.f16(half 0xH0000)
  %_1186 = tail call <2 x half> @air.sign.v2f16(<2 x half> zeroinitializer)
  %_1191 = tail call <3 x half> @air.sign.v3f16(<3 x half> zeroinitializer)
  %_1197 = tail call <4 x half> @air.sign.v4f16(<4 x half> zeroinitializer)
  %_1198 = tail call float @air.sign.f32(float 0.000000e+00)
  %_1199 = tail call <2 x float> @air.sign.v2f32(<2 x float> zeroinitializer)
  %_1200 = tail call <3 x float> @air.sign.v3f32(<3 x float> zeroinitializer)
  %_1201 = tail call <4 x float> @air.sign.v4f32(<4 x float> zeroinitializer)
  %_1202 = tail call float @air.sin.f32(float 0.000000e+00)
  %_1203 = tail call float @air.sinh.f32(float 0.000000e+00)
  %_1207 = tail call half @air.smoothstep.f16(half 0xH0000, half 0xH0000, half 0xH0000)
  %_1217 = tail call <2 x half> @air.smoothstep.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_1230 = tail call <3 x half> @air.smoothstep.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_1246 = tail call <4 x half> @air.smoothstep.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_1247 = tail call float @air.smoothstep.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_1248 = tail call <2 x float> @air.smoothstep.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1249 = tail call <3 x float> @air.smoothstep.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1250 = tail call <4 x float> @air.smoothstep.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1252 = tail call half @air.sqrt.f16(half 0xH0000)
  %_1256 = tail call <2 x half> @air.sqrt.v2f16(<2 x half> zeroinitializer)
  %_1261 = tail call <3 x half> @air.sqrt.v3f16(<3 x half> zeroinitializer)
  %_1267 = tail call <4 x half> @air.sqrt.v4f16(<4 x half> zeroinitializer)
  %_1268 = tail call float @air.sqrt.f32(float 0.000000e+00)
  %_1269 = tail call <2 x float> @air.sqrt.v2f32(<2 x float> zeroinitializer)
  %_1270 = tail call <3 x float> @air.sqrt.v3f32(<3 x float> zeroinitializer)
  %_1271 = tail call <4 x float> @air.sqrt.v4f32(<4 x float> zeroinitializer)
  %_1274 = tail call half @air.step.f16(half 0xH0000, half 0xH0000)
  %_1281 = tail call <2 x half> @air.step.v2f16(<2 x half> zeroinitializer, <2 x half> zeroinitializer)
  %_1290 = tail call <3 x half> @air.step.v3f16(<3 x half> zeroinitializer, <3 x half> zeroinitializer)
  %_1301 = tail call <4 x half> @air.step.v4f16(<4 x half> zeroinitializer, <4 x half> zeroinitializer)
  %_1302 = tail call float @air.step.f32(float 0.000000e+00, float 0.000000e+00)
  %_1303 = tail call <2 x float> @air.step.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1304 = tail call <3 x float> @air.step.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1305 = tail call <4 x float> @air.step.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1306 = tail call float @air.tan.f32(float 0.000000e+00)
  %_1307 = tail call float @air.tanh.f32(float 0.000000e+00)
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
