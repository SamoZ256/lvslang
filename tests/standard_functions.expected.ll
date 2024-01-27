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

declare i8 @convert.s.i8.s.i32(i32) local_unnamed_addr

declare i16 @convert.s.i16.s.i32(i32) local_unnamed_addr

declare half @convert.f.f16.f.f32(float) local_unnamed_addr

define %FragmentOut @testStandardFunctions.t1f32.sm(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler) local_unnamed_addr {
  %_280 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_281 = tail call i8 @air.abs.i8(i8 %_280)
  %_282 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_283 = insertelement <2 x i8> undef, i8 %_282, i64 0
  %_284 = shufflevector <2 x i8> %_283, <2 x i8> poison, <2 x i32> zeroinitializer
  %_285 = tail call <2 x i8> @air.abs.v2i8(<2 x i8> %_284)
  %_286 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_287 = insertelement <3 x i8> undef, i8 %_286, i64 0
  %_289 = shufflevector <3 x i8> %_287, <3 x i8> poison, <3 x i32> zeroinitializer
  %_290 = tail call <3 x i8> @air.abs.v3i8(<3 x i8> %_289)
  %_291 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_292 = insertelement <4 x i8> undef, i8 %_291, i64 0
  %_295 = shufflevector <4 x i8> %_292, <4 x i8> poison, <4 x i32> zeroinitializer
  %_296 = tail call <4 x i8> @air.abs.v4i8(<4 x i8> %_295)
  %_297 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_298 = tail call i16 @air.abs.i16(i16 %_297)
  %_299 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_300 = insertelement <2 x i16> undef, i16 %_299, i64 0
  %_301 = shufflevector <2 x i16> %_300, <2 x i16> poison, <2 x i32> zeroinitializer
  %_302 = tail call <2 x i16> @air.abs.v2i16(<2 x i16> %_301)
  %_303 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_304 = insertelement <3 x i16> undef, i16 %_303, i64 0
  %_306 = shufflevector <3 x i16> %_304, <3 x i16> poison, <3 x i32> zeroinitializer
  %_307 = tail call <3 x i16> @air.abs.v3i16(<3 x i16> %_306)
  %_308 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_309 = insertelement <4 x i16> undef, i16 %_308, i64 0
  %_312 = shufflevector <4 x i16> %_309, <4 x i16> poison, <4 x i32> zeroinitializer
  %_313 = tail call <4 x i16> @air.abs.v4i16(<4 x i16> %_312)
  %_314 = tail call i32 @air.abs.i32(i32 0)
  %_315 = tail call <2 x i32> @air.abs.v2i32(<2 x i32> zeroinitializer)
  %_316 = tail call <3 x i32> @air.abs.v3i32(<3 x i32> zeroinitializer)
  %_317 = tail call <4 x i32> @air.abs.v4i32(<4 x i32> zeroinitializer)
  %_318 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_319 = tail call half @air.abs.f16(half %_318)
  %_320 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_321 = insertelement <2 x half> undef, half %_320, i64 0
  %_322 = shufflevector <2 x half> %_321, <2 x half> poison, <2 x i32> zeroinitializer
  %_323 = tail call <2 x half> @air.abs.v2f16(<2 x half> %_322)
  %_324 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_325 = insertelement <3 x half> undef, half %_324, i64 0
  %_327 = shufflevector <3 x half> %_325, <3 x half> poison, <3 x i32> zeroinitializer
  %_328 = tail call <3 x half> @air.abs.v3f16(<3 x half> %_327)
  %_329 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_330 = insertelement <4 x half> undef, half %_329, i64 0
  %_333 = shufflevector <4 x half> %_330, <4 x half> poison, <4 x i32> zeroinitializer
  %_334 = tail call <4 x half> @air.abs.v4f16(<4 x half> %_333)
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
  %_345 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_346 = tail call half @air.ceil.f16(half %_345)
  %_347 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_348 = insertelement <2 x half> undef, half %_347, i64 0
  %_349 = shufflevector <2 x half> %_348, <2 x half> poison, <2 x i32> zeroinitializer
  %_350 = tail call <2 x half> @air.ceil.v2f16(<2 x half> %_349)
  %_351 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_352 = insertelement <3 x half> undef, half %_351, i64 0
  %_354 = shufflevector <3 x half> %_352, <3 x half> poison, <3 x i32> zeroinitializer
  %_355 = tail call <3 x half> @air.ceil.v3f16(<3 x half> %_354)
  %_356 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_357 = insertelement <4 x half> undef, half %_356, i64 0
  %_360 = shufflevector <4 x half> %_357, <4 x half> poison, <4 x i32> zeroinitializer
  %_361 = tail call <4 x half> @air.ceil.v4f16(<4 x half> %_360)
  %_362 = tail call float @air.ceil.f32(float 0.000000e+00)
  %_363 = tail call <2 x float> @air.ceil.v2f32(<2 x float> zeroinitializer)
  %_364 = tail call <3 x float> @air.ceil.v3f32(<3 x float> zeroinitializer)
  %_365 = tail call <4 x float> @air.ceil.v4f32(<4 x float> zeroinitializer)
  %_366 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_367 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_368 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_369 = tail call i8 @air.clamp.i8(i8 %_366, i8 %_367, i8 %_368)
  %_370 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_371 = insertelement <2 x i8> undef, i8 %_370, i64 0
  %_372 = shufflevector <2 x i8> %_371, <2 x i8> poison, <2 x i32> zeroinitializer
  %_373 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_374 = insertelement <2 x i8> undef, i8 %_373, i64 0
  %_375 = shufflevector <2 x i8> %_374, <2 x i8> poison, <2 x i32> zeroinitializer
  %_376 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_377 = insertelement <2 x i8> undef, i8 %_376, i64 0
  %_378 = shufflevector <2 x i8> %_377, <2 x i8> poison, <2 x i32> zeroinitializer
  %_379 = tail call <2 x i8> @air.clamp.v2i8(<2 x i8> %_372, <2 x i8> %_375, <2 x i8> %_378)
  %_380 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_381 = insertelement <3 x i8> undef, i8 %_380, i64 0
  %_383 = shufflevector <3 x i8> %_381, <3 x i8> poison, <3 x i32> zeroinitializer
  %_384 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_385 = insertelement <3 x i8> undef, i8 %_384, i64 0
  %_387 = shufflevector <3 x i8> %_385, <3 x i8> poison, <3 x i32> zeroinitializer
  %_388 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_389 = insertelement <3 x i8> undef, i8 %_388, i64 0
  %_391 = shufflevector <3 x i8> %_389, <3 x i8> poison, <3 x i32> zeroinitializer
  %_392 = tail call <3 x i8> @air.clamp.v3i8(<3 x i8> %_383, <3 x i8> %_387, <3 x i8> %_391)
  %_393 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_394 = insertelement <4 x i8> undef, i8 %_393, i64 0
  %_397 = shufflevector <4 x i8> %_394, <4 x i8> poison, <4 x i32> zeroinitializer
  %_398 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_399 = insertelement <4 x i8> undef, i8 %_398, i64 0
  %_402 = shufflevector <4 x i8> %_399, <4 x i8> poison, <4 x i32> zeroinitializer
  %_403 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_404 = insertelement <4 x i8> undef, i8 %_403, i64 0
  %_407 = shufflevector <4 x i8> %_404, <4 x i8> poison, <4 x i32> zeroinitializer
  %_408 = tail call <4 x i8> @air.clamp.v4i8(<4 x i8> %_397, <4 x i8> %_402, <4 x i8> %_407)
  %_409 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_410 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_411 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_412 = tail call i16 @air.clamp.i16(i16 %_409, i16 %_410, i16 %_411)
  %_413 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_414 = insertelement <2 x i16> undef, i16 %_413, i64 0
  %_415 = shufflevector <2 x i16> %_414, <2 x i16> poison, <2 x i32> zeroinitializer
  %_416 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_417 = insertelement <2 x i16> undef, i16 %_416, i64 0
  %_418 = shufflevector <2 x i16> %_417, <2 x i16> poison, <2 x i32> zeroinitializer
  %_419 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_420 = insertelement <2 x i16> undef, i16 %_419, i64 0
  %_421 = shufflevector <2 x i16> %_420, <2 x i16> poison, <2 x i32> zeroinitializer
  %_422 = tail call <2 x i16> @air.clamp.v2i16(<2 x i16> %_415, <2 x i16> %_418, <2 x i16> %_421)
  %_423 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_424 = insertelement <3 x i16> undef, i16 %_423, i64 0
  %_426 = shufflevector <3 x i16> %_424, <3 x i16> poison, <3 x i32> zeroinitializer
  %_427 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_428 = insertelement <3 x i16> undef, i16 %_427, i64 0
  %_430 = shufflevector <3 x i16> %_428, <3 x i16> poison, <3 x i32> zeroinitializer
  %_431 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_432 = insertelement <3 x i16> undef, i16 %_431, i64 0
  %_434 = shufflevector <3 x i16> %_432, <3 x i16> poison, <3 x i32> zeroinitializer
  %_435 = tail call <3 x i16> @air.clamp.v3i16(<3 x i16> %_426, <3 x i16> %_430, <3 x i16> %_434)
  %_436 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_437 = insertelement <4 x i16> undef, i16 %_436, i64 0
  %_440 = shufflevector <4 x i16> %_437, <4 x i16> poison, <4 x i32> zeroinitializer
  %_441 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_442 = insertelement <4 x i16> undef, i16 %_441, i64 0
  %_445 = shufflevector <4 x i16> %_442, <4 x i16> poison, <4 x i32> zeroinitializer
  %_446 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_447 = insertelement <4 x i16> undef, i16 %_446, i64 0
  %_450 = shufflevector <4 x i16> %_447, <4 x i16> poison, <4 x i32> zeroinitializer
  %_451 = tail call <4 x i16> @air.clamp.v4i16(<4 x i16> %_440, <4 x i16> %_445, <4 x i16> %_450)
  %_452 = tail call i32 @air.clamp.i32(i32 0, i32 0, i32 0)
  %_453 = tail call <2 x i32> @air.clamp.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_454 = tail call <3 x i32> @air.clamp.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_455 = tail call <4 x i32> @air.clamp.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_456 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_457 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_458 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_459 = tail call half @air.clamp.f16(half %_456, half %_457, half %_458)
  %_460 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_461 = insertelement <2 x half> undef, half %_460, i64 0
  %_462 = shufflevector <2 x half> %_461, <2 x half> poison, <2 x i32> zeroinitializer
  %_463 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_464 = insertelement <2 x half> undef, half %_463, i64 0
  %_465 = shufflevector <2 x half> %_464, <2 x half> poison, <2 x i32> zeroinitializer
  %_466 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_467 = insertelement <2 x half> undef, half %_466, i64 0
  %_468 = shufflevector <2 x half> %_467, <2 x half> poison, <2 x i32> zeroinitializer
  %_469 = tail call <2 x half> @air.clamp.v2f16(<2 x half> %_462, <2 x half> %_465, <2 x half> %_468)
  %_470 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_471 = insertelement <3 x half> undef, half %_470, i64 0
  %_473 = shufflevector <3 x half> %_471, <3 x half> poison, <3 x i32> zeroinitializer
  %_474 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_475 = insertelement <3 x half> undef, half %_474, i64 0
  %_477 = shufflevector <3 x half> %_475, <3 x half> poison, <3 x i32> zeroinitializer
  %_478 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_479 = insertelement <3 x half> undef, half %_478, i64 0
  %_481 = shufflevector <3 x half> %_479, <3 x half> poison, <3 x i32> zeroinitializer
  %_482 = tail call <3 x half> @air.clamp.v3f16(<3 x half> %_473, <3 x half> %_477, <3 x half> %_481)
  %_483 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_484 = insertelement <4 x half> undef, half %_483, i64 0
  %_487 = shufflevector <4 x half> %_484, <4 x half> poison, <4 x i32> zeroinitializer
  %_488 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_489 = insertelement <4 x half> undef, half %_488, i64 0
  %_492 = shufflevector <4 x half> %_489, <4 x half> poison, <4 x i32> zeroinitializer
  %_493 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_494 = insertelement <4 x half> undef, half %_493, i64 0
  %_497 = shufflevector <4 x half> %_494, <4 x half> poison, <4 x i32> zeroinitializer
  %_498 = tail call <4 x half> @air.clamp.v4f16(<4 x half> %_487, <4 x half> %_492, <4 x half> %_497)
  %_499 = tail call float @air.clamp.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_500 = tail call <2 x float> @air.clamp.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_501 = tail call <3 x float> @air.clamp.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_502 = tail call <4 x float> @air.clamp.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_503 = tail call float @air.cos.f32(float 0.000000e+00)
  %_504 = tail call float @air.cosh.f32(float 0.000000e+00)
  %_505 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_506 = insertelement <3 x half> undef, half %_505, i64 0
  %_508 = shufflevector <3 x half> %_506, <3 x half> poison, <3 x i32> zeroinitializer
  %_509 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_510 = insertelement <3 x half> undef, half %_509, i64 0
  %_512 = shufflevector <3 x half> %_510, <3 x half> poison, <3 x i32> zeroinitializer
  %_513 = tail call <3 x half> @air.cross.v3f16(<3 x half> %_508, <3 x half> %_512)
  %_514 = tail call <3 x float> @air.cross.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_515 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_516 = insertelement <2 x half> undef, half %_515, i64 0
  %_517 = shufflevector <2 x half> %_516, <2 x half> poison, <2 x i32> zeroinitializer
  %_518 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_519 = insertelement <2 x half> undef, half %_518, i64 0
  %_520 = shufflevector <2 x half> %_519, <2 x half> poison, <2 x i32> zeroinitializer
  %_521 = tail call half @air.distance.v2f16(<2 x half> %_517, <2 x half> %_520)
  %_522 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_523 = insertelement <3 x half> undef, half %_522, i64 0
  %_525 = shufflevector <3 x half> %_523, <3 x half> poison, <3 x i32> zeroinitializer
  %_526 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_527 = insertelement <3 x half> undef, half %_526, i64 0
  %_529 = shufflevector <3 x half> %_527, <3 x half> poison, <3 x i32> zeroinitializer
  %_530 = tail call half @air.distance.v3f16(<3 x half> %_525, <3 x half> %_529)
  %_531 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_532 = insertelement <4 x half> undef, half %_531, i64 0
  %_535 = shufflevector <4 x half> %_532, <4 x half> poison, <4 x i32> zeroinitializer
  %_536 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_537 = insertelement <4 x half> undef, half %_536, i64 0
  %_540 = shufflevector <4 x half> %_537, <4 x half> poison, <4 x i32> zeroinitializer
  %_541 = tail call half @air.distance.v4f16(<4 x half> %_535, <4 x half> %_540)
  %_542 = tail call float @air.distance.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_543 = tail call float @air.distance.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_544 = tail call float @air.distance.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_545 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_546 = insertelement <2 x half> undef, half %_545, i64 0
  %_547 = shufflevector <2 x half> %_546, <2 x half> poison, <2 x i32> zeroinitializer
  %_548 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_549 = insertelement <2 x half> undef, half %_548, i64 0
  %_550 = shufflevector <2 x half> %_549, <2 x half> poison, <2 x i32> zeroinitializer
  %_551 = tail call half @air.dot.v2f16(<2 x half> %_547, <2 x half> %_550)
  %_552 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_553 = insertelement <3 x half> undef, half %_552, i64 0
  %_555 = shufflevector <3 x half> %_553, <3 x half> poison, <3 x i32> zeroinitializer
  %_556 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_557 = insertelement <3 x half> undef, half %_556, i64 0
  %_559 = shufflevector <3 x half> %_557, <3 x half> poison, <3 x i32> zeroinitializer
  %_560 = tail call half @air.dot.v3f16(<3 x half> %_555, <3 x half> %_559)
  %_561 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_562 = insertelement <4 x half> undef, half %_561, i64 0
  %_565 = shufflevector <4 x half> %_562, <4 x half> poison, <4 x i32> zeroinitializer
  %_566 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_567 = insertelement <4 x half> undef, half %_566, i64 0
  %_570 = shufflevector <4 x half> %_567, <4 x half> poison, <4 x i32> zeroinitializer
  %_571 = tail call half @air.dot.v4f16(<4 x half> %_565, <4 x half> %_570)
  %_572 = tail call float @air.dot.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_573 = tail call float @air.dot.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_574 = tail call float @air.dot.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_575 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_576 = tail call half @air.exp.f16(half %_575)
  %_577 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_578 = insertelement <2 x half> undef, half %_577, i64 0
  %_579 = shufflevector <2 x half> %_578, <2 x half> poison, <2 x i32> zeroinitializer
  %_580 = tail call <2 x half> @air.exp.v2f16(<2 x half> %_579)
  %_581 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_582 = insertelement <3 x half> undef, half %_581, i64 0
  %_584 = shufflevector <3 x half> %_582, <3 x half> poison, <3 x i32> zeroinitializer
  %_585 = tail call <3 x half> @air.exp.v3f16(<3 x half> %_584)
  %_586 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_587 = insertelement <4 x half> undef, half %_586, i64 0
  %_590 = shufflevector <4 x half> %_587, <4 x half> poison, <4 x i32> zeroinitializer
  %_591 = tail call <4 x half> @air.exp.v4f16(<4 x half> %_590)
  %_592 = tail call float @air.exp.f32(float 0.000000e+00)
  %_593 = tail call <2 x float> @air.exp.v2f32(<2 x float> zeroinitializer)
  %_594 = tail call <3 x float> @air.exp.v3f32(<3 x float> zeroinitializer)
  %_595 = tail call <4 x float> @air.exp.v4f32(<4 x float> zeroinitializer)
  %_596 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_597 = tail call half @air.exp2.f16(half %_596)
  %_598 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_599 = insertelement <2 x half> undef, half %_598, i64 0
  %_600 = shufflevector <2 x half> %_599, <2 x half> poison, <2 x i32> zeroinitializer
  %_601 = tail call <2 x half> @air.exp2.v2f16(<2 x half> %_600)
  %_602 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_603 = insertelement <3 x half> undef, half %_602, i64 0
  %_605 = shufflevector <3 x half> %_603, <3 x half> poison, <3 x i32> zeroinitializer
  %_606 = tail call <3 x half> @air.exp2.v3f16(<3 x half> %_605)
  %_607 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_608 = insertelement <4 x half> undef, half %_607, i64 0
  %_611 = shufflevector <4 x half> %_608, <4 x half> poison, <4 x i32> zeroinitializer
  %_612 = tail call <4 x half> @air.exp2.v4f16(<4 x half> %_611)
  %_613 = tail call float @air.exp2.f32(float 0.000000e+00)
  %_614 = tail call <2 x float> @air.exp2.v2f32(<2 x float> zeroinitializer)
  %_615 = tail call <3 x float> @air.exp2.v3f32(<3 x float> zeroinitializer)
  %_616 = tail call <4 x float> @air.exp2.v4f32(<4 x float> zeroinitializer)
  %_617 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_618 = tail call half @air.floor.f16(half %_617)
  %_619 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_620 = insertelement <2 x half> undef, half %_619, i64 0
  %_621 = shufflevector <2 x half> %_620, <2 x half> poison, <2 x i32> zeroinitializer
  %_622 = tail call <2 x half> @air.floor.v2f16(<2 x half> %_621)
  %_623 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_624 = insertelement <3 x half> undef, half %_623, i64 0
  %_626 = shufflevector <3 x half> %_624, <3 x half> poison, <3 x i32> zeroinitializer
  %_627 = tail call <3 x half> @air.floor.v3f16(<3 x half> %_626)
  %_628 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_629 = insertelement <4 x half> undef, half %_628, i64 0
  %_632 = shufflevector <4 x half> %_629, <4 x half> poison, <4 x i32> zeroinitializer
  %_633 = tail call <4 x half> @air.floor.v4f16(<4 x half> %_632)
  %_634 = tail call float @air.floor.f32(float 0.000000e+00)
  %_635 = tail call <2 x float> @air.floor.v2f32(<2 x float> zeroinitializer)
  %_636 = tail call <3 x float> @air.floor.v3f32(<3 x float> zeroinitializer)
  %_637 = tail call <4 x float> @air.floor.v4f32(<4 x float> zeroinitializer)
  %_638 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_639 = tail call half @air.fract.f16(half %_638)
  %_640 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_641 = insertelement <2 x half> undef, half %_640, i64 0
  %_642 = shufflevector <2 x half> %_641, <2 x half> poison, <2 x i32> zeroinitializer
  %_643 = tail call <2 x half> @air.fract.v2f16(<2 x half> %_642)
  %_644 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_645 = insertelement <3 x half> undef, half %_644, i64 0
  %_647 = shufflevector <3 x half> %_645, <3 x half> poison, <3 x i32> zeroinitializer
  %_648 = tail call <3 x half> @air.fract.v3f16(<3 x half> %_647)
  %_649 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_650 = insertelement <4 x half> undef, half %_649, i64 0
  %_653 = shufflevector <4 x half> %_650, <4 x half> poison, <4 x i32> zeroinitializer
  %_654 = tail call <4 x half> @air.fract.v4f16(<4 x half> %_653)
  %_655 = tail call float @air.fract.f32(float 0.000000e+00)
  %_656 = tail call <2 x float> @air.fract.v2f32(<2 x float> zeroinitializer)
  %_657 = tail call <3 x float> @air.fract.v3f32(<3 x float> zeroinitializer)
  %_658 = tail call <4 x float> @air.fract.v4f32(<4 x float> zeroinitializer)
  %_659 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_660 = tail call i1 @air.isinf.f16(half %_659)
  %_661 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_662 = insertelement <2 x half> undef, half %_661, i64 0
  %_663 = shufflevector <2 x half> %_662, <2 x half> poison, <2 x i32> zeroinitializer
  %_664 = tail call <2 x i1> @air.isinf.v2f16(<2 x half> %_663)
  %_665 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_666 = insertelement <3 x half> undef, half %_665, i64 0
  %_668 = shufflevector <3 x half> %_666, <3 x half> poison, <3 x i32> zeroinitializer
  %_669 = tail call <3 x i1> @air.isinf.v3f16(<3 x half> %_668)
  %_670 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_671 = insertelement <4 x half> undef, half %_670, i64 0
  %_674 = shufflevector <4 x half> %_671, <4 x half> poison, <4 x i32> zeroinitializer
  %_675 = tail call <4 x i1> @air.isinf.v4f16(<4 x half> %_674)
  %_676 = tail call i1 @air.isinf.f32(float 0.000000e+00)
  %_677 = tail call <2 x i1> @air.isinf.v2f32(<2 x float> zeroinitializer)
  %_678 = tail call <3 x i1> @air.isinf.v3f32(<3 x float> zeroinitializer)
  %_679 = tail call <4 x i1> @air.isinf.v4f32(<4 x float> zeroinitializer)
  %_680 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_681 = tail call i1 @air.isnan.f16(half %_680)
  %_682 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_683 = insertelement <2 x half> undef, half %_682, i64 0
  %_684 = shufflevector <2 x half> %_683, <2 x half> poison, <2 x i32> zeroinitializer
  %_685 = tail call <2 x i1> @air.isnan.v2f16(<2 x half> %_684)
  %_686 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_687 = insertelement <3 x half> undef, half %_686, i64 0
  %_689 = shufflevector <3 x half> %_687, <3 x half> poison, <3 x i32> zeroinitializer
  %_690 = tail call <3 x i1> @air.isnan.v3f16(<3 x half> %_689)
  %_691 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_692 = insertelement <4 x half> undef, half %_691, i64 0
  %_695 = shufflevector <4 x half> %_692, <4 x half> poison, <4 x i32> zeroinitializer
  %_696 = tail call <4 x i1> @air.isnan.v4f16(<4 x half> %_695)
  %_697 = tail call i1 @air.isnan.f32(float 0.000000e+00)
  %_698 = tail call <2 x i1> @air.isnan.v2f32(<2 x float> zeroinitializer)
  %_699 = tail call <3 x i1> @air.isnan.v3f32(<3 x float> zeroinitializer)
  %_700 = tail call <4 x i1> @air.isnan.v4f32(<4 x float> zeroinitializer)
  %_701 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_702 = insertelement <2 x half> undef, half %_701, i64 0
  %_703 = shufflevector <2 x half> %_702, <2 x half> poison, <2 x i32> zeroinitializer
  %_704 = tail call half @air.length.v2f16(<2 x half> %_703)
  %_705 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_706 = insertelement <3 x half> undef, half %_705, i64 0
  %_708 = shufflevector <3 x half> %_706, <3 x half> poison, <3 x i32> zeroinitializer
  %_709 = tail call half @air.length.v3f16(<3 x half> %_708)
  %_710 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_711 = insertelement <4 x half> undef, half %_710, i64 0
  %_714 = shufflevector <4 x half> %_711, <4 x half> poison, <4 x i32> zeroinitializer
  %_715 = tail call half @air.length.v4f16(<4 x half> %_714)
  %_716 = tail call float @air.length.v2f32(<2 x float> zeroinitializer)
  %_717 = tail call float @air.length.v3f32(<3 x float> zeroinitializer)
  %_718 = tail call float @air.length.v4f32(<4 x float> zeroinitializer)
  %_719 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_720 = tail call half @air.log.f16(half %_719)
  %_721 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_722 = insertelement <2 x half> undef, half %_721, i64 0
  %_723 = shufflevector <2 x half> %_722, <2 x half> poison, <2 x i32> zeroinitializer
  %_724 = tail call <2 x half> @air.log.v2f16(<2 x half> %_723)
  %_725 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_726 = insertelement <3 x half> undef, half %_725, i64 0
  %_728 = shufflevector <3 x half> %_726, <3 x half> poison, <3 x i32> zeroinitializer
  %_729 = tail call <3 x half> @air.log.v3f16(<3 x half> %_728)
  %_730 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_731 = insertelement <4 x half> undef, half %_730, i64 0
  %_734 = shufflevector <4 x half> %_731, <4 x half> poison, <4 x i32> zeroinitializer
  %_735 = tail call <4 x half> @air.log.v4f16(<4 x half> %_734)
  %_736 = tail call float @air.log.f32(float 0.000000e+00)
  %_737 = tail call <2 x float> @air.log.v2f32(<2 x float> zeroinitializer)
  %_738 = tail call <3 x float> @air.log.v3f32(<3 x float> zeroinitializer)
  %_739 = tail call <4 x float> @air.log.v4f32(<4 x float> zeroinitializer)
  %_740 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_741 = tail call half @air.log2.f16(half %_740)
  %_742 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_743 = insertelement <2 x half> undef, half %_742, i64 0
  %_744 = shufflevector <2 x half> %_743, <2 x half> poison, <2 x i32> zeroinitializer
  %_745 = tail call <2 x half> @air.log2.v2f16(<2 x half> %_744)
  %_746 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_747 = insertelement <3 x half> undef, half %_746, i64 0
  %_749 = shufflevector <3 x half> %_747, <3 x half> poison, <3 x i32> zeroinitializer
  %_750 = tail call <3 x half> @air.log2.v3f16(<3 x half> %_749)
  %_751 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_752 = insertelement <4 x half> undef, half %_751, i64 0
  %_755 = shufflevector <4 x half> %_752, <4 x half> poison, <4 x i32> zeroinitializer
  %_756 = tail call <4 x half> @air.log2.v4f16(<4 x half> %_755)
  %_757 = tail call float @air.log2.f32(float 0.000000e+00)
  %_758 = tail call <2 x float> @air.log2.v2f32(<2 x float> zeroinitializer)
  %_759 = tail call <3 x float> @air.log2.v3f32(<3 x float> zeroinitializer)
  %_760 = tail call <4 x float> @air.log2.v4f32(<4 x float> zeroinitializer)
  %_761 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_762 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_763 = tail call i8 @air.max.i8(i8 %_761, i8 %_762)
  %_764 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_765 = insertelement <2 x i8> undef, i8 %_764, i64 0
  %_766 = shufflevector <2 x i8> %_765, <2 x i8> poison, <2 x i32> zeroinitializer
  %_767 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_768 = insertelement <2 x i8> undef, i8 %_767, i64 0
  %_769 = shufflevector <2 x i8> %_768, <2 x i8> poison, <2 x i32> zeroinitializer
  %_770 = tail call <2 x i8> @air.max.v2i8(<2 x i8> %_766, <2 x i8> %_769)
  %_771 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_772 = insertelement <3 x i8> undef, i8 %_771, i64 0
  %_774 = shufflevector <3 x i8> %_772, <3 x i8> poison, <3 x i32> zeroinitializer
  %_775 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_776 = insertelement <3 x i8> undef, i8 %_775, i64 0
  %_778 = shufflevector <3 x i8> %_776, <3 x i8> poison, <3 x i32> zeroinitializer
  %_779 = tail call <3 x i8> @air.max.v3i8(<3 x i8> %_774, <3 x i8> %_778)
  %_780 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_781 = insertelement <4 x i8> undef, i8 %_780, i64 0
  %_784 = shufflevector <4 x i8> %_781, <4 x i8> poison, <4 x i32> zeroinitializer
  %_785 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_786 = insertelement <4 x i8> undef, i8 %_785, i64 0
  %_789 = shufflevector <4 x i8> %_786, <4 x i8> poison, <4 x i32> zeroinitializer
  %_790 = tail call <4 x i8> @air.max.v4i8(<4 x i8> %_784, <4 x i8> %_789)
  %_791 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_792 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_793 = tail call i16 @air.max.i16(i16 %_791, i16 %_792)
  %_794 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_795 = insertelement <2 x i16> undef, i16 %_794, i64 0
  %_796 = shufflevector <2 x i16> %_795, <2 x i16> poison, <2 x i32> zeroinitializer
  %_797 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_798 = insertelement <2 x i16> undef, i16 %_797, i64 0
  %_799 = shufflevector <2 x i16> %_798, <2 x i16> poison, <2 x i32> zeroinitializer
  %_800 = tail call <2 x i16> @air.max.v2i16(<2 x i16> %_796, <2 x i16> %_799)
  %_801 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_802 = insertelement <3 x i16> undef, i16 %_801, i64 0
  %_804 = shufflevector <3 x i16> %_802, <3 x i16> poison, <3 x i32> zeroinitializer
  %_805 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_806 = insertelement <3 x i16> undef, i16 %_805, i64 0
  %_808 = shufflevector <3 x i16> %_806, <3 x i16> poison, <3 x i32> zeroinitializer
  %_809 = tail call <3 x i16> @air.max.v3i16(<3 x i16> %_804, <3 x i16> %_808)
  %_810 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_811 = insertelement <4 x i16> undef, i16 %_810, i64 0
  %_814 = shufflevector <4 x i16> %_811, <4 x i16> poison, <4 x i32> zeroinitializer
  %_815 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_816 = insertelement <4 x i16> undef, i16 %_815, i64 0
  %_819 = shufflevector <4 x i16> %_816, <4 x i16> poison, <4 x i32> zeroinitializer
  %_820 = tail call <4 x i16> @air.max.v4i16(<4 x i16> %_814, <4 x i16> %_819)
  %_821 = tail call i32 @air.max.i32(i32 0, i32 0)
  %_822 = tail call <2 x i32> @air.max.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_823 = tail call <3 x i32> @air.max.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_824 = tail call <4 x i32> @air.max.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_825 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_826 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_827 = tail call half @air.max.f16(half %_825, half %_826)
  %_828 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_829 = insertelement <2 x half> undef, half %_828, i64 0
  %_830 = shufflevector <2 x half> %_829, <2 x half> poison, <2 x i32> zeroinitializer
  %_831 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_832 = insertelement <2 x half> undef, half %_831, i64 0
  %_833 = shufflevector <2 x half> %_832, <2 x half> poison, <2 x i32> zeroinitializer
  %_834 = tail call <2 x half> @air.max.v2f16(<2 x half> %_830, <2 x half> %_833)
  %_835 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_836 = insertelement <3 x half> undef, half %_835, i64 0
  %_838 = shufflevector <3 x half> %_836, <3 x half> poison, <3 x i32> zeroinitializer
  %_839 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_840 = insertelement <3 x half> undef, half %_839, i64 0
  %_842 = shufflevector <3 x half> %_840, <3 x half> poison, <3 x i32> zeroinitializer
  %_843 = tail call <3 x half> @air.max.v3f16(<3 x half> %_838, <3 x half> %_842)
  %_844 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_845 = insertelement <4 x half> undef, half %_844, i64 0
  %_848 = shufflevector <4 x half> %_845, <4 x half> poison, <4 x i32> zeroinitializer
  %_849 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_850 = insertelement <4 x half> undef, half %_849, i64 0
  %_853 = shufflevector <4 x half> %_850, <4 x half> poison, <4 x i32> zeroinitializer
  %_854 = tail call <4 x half> @air.max.v4f16(<4 x half> %_848, <4 x half> %_853)
  %_855 = tail call float @air.max.f32(float 0.000000e+00, float 0.000000e+00)
  %_856 = tail call <2 x float> @air.max.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_857 = tail call <3 x float> @air.max.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_858 = tail call <4 x float> @air.max.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_859 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_860 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_861 = tail call i8 @air.min.i8(i8 %_859, i8 %_860)
  %_862 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_863 = insertelement <2 x i8> undef, i8 %_862, i64 0
  %_864 = shufflevector <2 x i8> %_863, <2 x i8> poison, <2 x i32> zeroinitializer
  %_865 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_866 = insertelement <2 x i8> undef, i8 %_865, i64 0
  %_867 = shufflevector <2 x i8> %_866, <2 x i8> poison, <2 x i32> zeroinitializer
  %_868 = tail call <2 x i8> @air.min.v2i8(<2 x i8> %_864, <2 x i8> %_867)
  %_869 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_870 = insertelement <3 x i8> undef, i8 %_869, i64 0
  %_872 = shufflevector <3 x i8> %_870, <3 x i8> poison, <3 x i32> zeroinitializer
  %_873 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_874 = insertelement <3 x i8> undef, i8 %_873, i64 0
  %_876 = shufflevector <3 x i8> %_874, <3 x i8> poison, <3 x i32> zeroinitializer
  %_877 = tail call <3 x i8> @air.min.v3i8(<3 x i8> %_872, <3 x i8> %_876)
  %_878 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_879 = insertelement <4 x i8> undef, i8 %_878, i64 0
  %_882 = shufflevector <4 x i8> %_879, <4 x i8> poison, <4 x i32> zeroinitializer
  %_883 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_884 = insertelement <4 x i8> undef, i8 %_883, i64 0
  %_887 = shufflevector <4 x i8> %_884, <4 x i8> poison, <4 x i32> zeroinitializer
  %_888 = tail call <4 x i8> @air.min.v4i8(<4 x i8> %_882, <4 x i8> %_887)
  %_889 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_890 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_891 = tail call i16 @air.min.i16(i16 %_889, i16 %_890)
  %_892 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_893 = insertelement <2 x i16> undef, i16 %_892, i64 0
  %_894 = shufflevector <2 x i16> %_893, <2 x i16> poison, <2 x i32> zeroinitializer
  %_895 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_896 = insertelement <2 x i16> undef, i16 %_895, i64 0
  %_897 = shufflevector <2 x i16> %_896, <2 x i16> poison, <2 x i32> zeroinitializer
  %_898 = tail call <2 x i16> @air.min.v2i16(<2 x i16> %_894, <2 x i16> %_897)
  %_899 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_900 = insertelement <3 x i16> undef, i16 %_899, i64 0
  %_902 = shufflevector <3 x i16> %_900, <3 x i16> poison, <3 x i32> zeroinitializer
  %_903 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_904 = insertelement <3 x i16> undef, i16 %_903, i64 0
  %_906 = shufflevector <3 x i16> %_904, <3 x i16> poison, <3 x i32> zeroinitializer
  %_907 = tail call <3 x i16> @air.min.v3i16(<3 x i16> %_902, <3 x i16> %_906)
  %_908 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_909 = insertelement <4 x i16> undef, i16 %_908, i64 0
  %_912 = shufflevector <4 x i16> %_909, <4 x i16> poison, <4 x i32> zeroinitializer
  %_913 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_914 = insertelement <4 x i16> undef, i16 %_913, i64 0
  %_917 = shufflevector <4 x i16> %_914, <4 x i16> poison, <4 x i32> zeroinitializer
  %_918 = tail call <4 x i16> @air.min.v4i16(<4 x i16> %_912, <4 x i16> %_917)
  %_919 = tail call i32 @air.min.i32(i32 0, i32 0)
  %_920 = tail call <2 x i32> @air.min.v2i32(<2 x i32> zeroinitializer, <2 x i32> zeroinitializer)
  %_921 = tail call <3 x i32> @air.min.v3i32(<3 x i32> zeroinitializer, <3 x i32> zeroinitializer)
  %_922 = tail call <4 x i32> @air.min.v4i32(<4 x i32> zeroinitializer, <4 x i32> zeroinitializer)
  %_923 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_924 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_925 = tail call half @air.min.f16(half %_923, half %_924)
  %_926 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_927 = insertelement <2 x half> undef, half %_926, i64 0
  %_928 = shufflevector <2 x half> %_927, <2 x half> poison, <2 x i32> zeroinitializer
  %_929 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_930 = insertelement <2 x half> undef, half %_929, i64 0
  %_931 = shufflevector <2 x half> %_930, <2 x half> poison, <2 x i32> zeroinitializer
  %_932 = tail call <2 x half> @air.min.v2f16(<2 x half> %_928, <2 x half> %_931)
  %_933 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_934 = insertelement <3 x half> undef, half %_933, i64 0
  %_936 = shufflevector <3 x half> %_934, <3 x half> poison, <3 x i32> zeroinitializer
  %_937 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_938 = insertelement <3 x half> undef, half %_937, i64 0
  %_940 = shufflevector <3 x half> %_938, <3 x half> poison, <3 x i32> zeroinitializer
  %_941 = tail call <3 x half> @air.min.v3f16(<3 x half> %_936, <3 x half> %_940)
  %_942 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_943 = insertelement <4 x half> undef, half %_942, i64 0
  %_946 = shufflevector <4 x half> %_943, <4 x half> poison, <4 x i32> zeroinitializer
  %_947 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_948 = insertelement <4 x half> undef, half %_947, i64 0
  %_951 = shufflevector <4 x half> %_948, <4 x half> poison, <4 x i32> zeroinitializer
  %_952 = tail call <4 x half> @air.min.v4f16(<4 x half> %_946, <4 x half> %_951)
  %_953 = tail call float @air.min.f32(float 0.000000e+00, float 0.000000e+00)
  %_954 = tail call <2 x float> @air.min.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_955 = tail call <3 x float> @air.min.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_956 = tail call <4 x float> @air.min.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_957 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_958 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_959 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_960 = tail call half @air.mix.f16(half %_957, half %_958, half %_959)
  %_961 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_962 = insertelement <2 x half> undef, half %_961, i64 0
  %_963 = shufflevector <2 x half> %_962, <2 x half> poison, <2 x i32> zeroinitializer
  %_964 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_965 = insertelement <2 x half> undef, half %_964, i64 0
  %_966 = shufflevector <2 x half> %_965, <2 x half> poison, <2 x i32> zeroinitializer
  %_967 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_968 = insertelement <2 x half> undef, half %_967, i64 0
  %_969 = shufflevector <2 x half> %_968, <2 x half> poison, <2 x i32> zeroinitializer
  %_970 = tail call <2 x half> @air.mix.v2f16(<2 x half> %_963, <2 x half> %_966, <2 x half> %_969)
  %_971 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_972 = insertelement <3 x half> undef, half %_971, i64 0
  %_974 = shufflevector <3 x half> %_972, <3 x half> poison, <3 x i32> zeroinitializer
  %_975 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_976 = insertelement <3 x half> undef, half %_975, i64 0
  %_978 = shufflevector <3 x half> %_976, <3 x half> poison, <3 x i32> zeroinitializer
  %_979 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_980 = insertelement <3 x half> undef, half %_979, i64 0
  %_982 = shufflevector <3 x half> %_980, <3 x half> poison, <3 x i32> zeroinitializer
  %_983 = tail call <3 x half> @air.mix.v3f16(<3 x half> %_974, <3 x half> %_978, <3 x half> %_982)
  %_984 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_985 = insertelement <4 x half> undef, half %_984, i64 0
  %_988 = shufflevector <4 x half> %_985, <4 x half> poison, <4 x i32> zeroinitializer
  %_989 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_990 = insertelement <4 x half> undef, half %_989, i64 0
  %_993 = shufflevector <4 x half> %_990, <4 x half> poison, <4 x i32> zeroinitializer
  %_994 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_995 = insertelement <4 x half> undef, half %_994, i64 0
  %_998 = shufflevector <4 x half> %_995, <4 x half> poison, <4 x i32> zeroinitializer
  %_999 = tail call <4 x half> @air.mix.v4f16(<4 x half> %_988, <4 x half> %_993, <4 x half> %_998)
  %_1000 = tail call float @air.mix.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_1001 = tail call <2 x float> @air.mix.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1002 = tail call <3 x float> @air.mix.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1003 = tail call <4 x float> @air.mix.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1004 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1005 = insertelement <2 x half> undef, half %_1004, i64 0
  %_1006 = shufflevector <2 x half> %_1005, <2 x half> poison, <2 x i32> zeroinitializer
  %_1007 = tail call <2 x half> @air.normalize.v2f16(<2 x half> %_1006)
  %_1008 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1009 = insertelement <3 x half> undef, half %_1008, i64 0
  %_1011 = shufflevector <3 x half> %_1009, <3 x half> poison, <3 x i32> zeroinitializer
  %_1012 = tail call <3 x half> @air.normalize.v3f16(<3 x half> %_1011)
  %_1013 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1014 = insertelement <4 x half> undef, half %_1013, i64 0
  %_1017 = shufflevector <4 x half> %_1014, <4 x half> poison, <4 x i32> zeroinitializer
  %_1018 = tail call <4 x half> @air.normalize.v4f16(<4 x half> %_1017)
  %_1019 = tail call <2 x float> @air.normalize.v2f32(<2 x float> zeroinitializer)
  %_1020 = tail call <3 x float> @air.normalize.v3f32(<3 x float> zeroinitializer)
  %_1021 = tail call <4 x float> @air.normalize.v4f32(<4 x float> zeroinitializer)
  %_1022 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1023 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1024 = tail call half @air.pow.f16(half %_1022, half %_1023)
  %_1025 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1026 = insertelement <2 x half> undef, half %_1025, i64 0
  %_1027 = shufflevector <2 x half> %_1026, <2 x half> poison, <2 x i32> zeroinitializer
  %_1028 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1029 = insertelement <2 x half> undef, half %_1028, i64 0
  %_1030 = shufflevector <2 x half> %_1029, <2 x half> poison, <2 x i32> zeroinitializer
  %_1031 = tail call <2 x half> @air.pow.v2f16(<2 x half> %_1027, <2 x half> %_1030)
  %_1032 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1033 = insertelement <3 x half> undef, half %_1032, i64 0
  %_1035 = shufflevector <3 x half> %_1033, <3 x half> poison, <3 x i32> zeroinitializer
  %_1036 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1037 = insertelement <3 x half> undef, half %_1036, i64 0
  %_1039 = shufflevector <3 x half> %_1037, <3 x half> poison, <3 x i32> zeroinitializer
  %_1040 = tail call <3 x half> @air.pow.v3f16(<3 x half> %_1035, <3 x half> %_1039)
  %_1041 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1042 = insertelement <4 x half> undef, half %_1041, i64 0
  %_1045 = shufflevector <4 x half> %_1042, <4 x half> poison, <4 x i32> zeroinitializer
  %_1046 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1047 = insertelement <4 x half> undef, half %_1046, i64 0
  %_1050 = shufflevector <4 x half> %_1047, <4 x half> poison, <4 x i32> zeroinitializer
  %_1051 = tail call <4 x half> @air.pow.v4f16(<4 x half> %_1045, <4 x half> %_1050)
  %_1052 = tail call float @air.pow.f32(float 0.000000e+00, float 0.000000e+00)
  %_1053 = tail call <2 x float> @air.pow.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1054 = tail call <3 x float> @air.pow.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1055 = tail call <4 x float> @air.pow.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1056 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1057 = insertelement <2 x half> undef, half %_1056, i64 0
  %_1058 = shufflevector <2 x half> %_1057, <2 x half> poison, <2 x i32> zeroinitializer
  %_1059 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1060 = insertelement <2 x half> undef, half %_1059, i64 0
  %_1061 = shufflevector <2 x half> %_1060, <2 x half> poison, <2 x i32> zeroinitializer
  %_1062 = tail call <2 x half> @air.reflect.v2f16(<2 x half> %_1058, <2 x half> %_1061)
  %_1063 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1064 = insertelement <3 x half> undef, half %_1063, i64 0
  %_1066 = shufflevector <3 x half> %_1064, <3 x half> poison, <3 x i32> zeroinitializer
  %_1067 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1068 = insertelement <3 x half> undef, half %_1067, i64 0
  %_1070 = shufflevector <3 x half> %_1068, <3 x half> poison, <3 x i32> zeroinitializer
  %_1071 = tail call <3 x half> @air.reflect.v3f16(<3 x half> %_1066, <3 x half> %_1070)
  %_1072 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1073 = insertelement <4 x half> undef, half %_1072, i64 0
  %_1076 = shufflevector <4 x half> %_1073, <4 x half> poison, <4 x i32> zeroinitializer
  %_1077 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1078 = insertelement <4 x half> undef, half %_1077, i64 0
  %_1081 = shufflevector <4 x half> %_1078, <4 x half> poison, <4 x i32> zeroinitializer
  %_1082 = tail call <4 x half> @air.reflect.v4f16(<4 x half> %_1076, <4 x half> %_1081)
  %_1083 = tail call <2 x float> @air.reflect.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1084 = tail call <3 x float> @air.reflect.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1085 = tail call <4 x float> @air.reflect.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1086 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1087 = insertelement <2 x half> undef, half %_1086, i64 0
  %_1088 = shufflevector <2 x half> %_1087, <2 x half> poison, <2 x i32> zeroinitializer
  %_1089 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1090 = insertelement <2 x half> undef, half %_1089, i64 0
  %_1091 = shufflevector <2 x half> %_1090, <2 x half> poison, <2 x i32> zeroinitializer
  %_1092 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1093 = tail call <2 x half> @air.refract.v2f16(<2 x half> %_1088, <2 x half> %_1091, half %_1092)
  %_1094 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1095 = insertelement <3 x half> undef, half %_1094, i64 0
  %_1097 = shufflevector <3 x half> %_1095, <3 x half> poison, <3 x i32> zeroinitializer
  %_1098 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1099 = insertelement <3 x half> undef, half %_1098, i64 0
  %_1101 = shufflevector <3 x half> %_1099, <3 x half> poison, <3 x i32> zeroinitializer
  %_1102 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1103 = tail call <3 x half> @air.refract.v3f16(<3 x half> %_1097, <3 x half> %_1101, half %_1102)
  %_1104 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1105 = insertelement <4 x half> undef, half %_1104, i64 0
  %_1108 = shufflevector <4 x half> %_1105, <4 x half> poison, <4 x i32> zeroinitializer
  %_1109 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1110 = insertelement <4 x half> undef, half %_1109, i64 0
  %_1113 = shufflevector <4 x half> %_1110, <4 x half> poison, <4 x i32> zeroinitializer
  %_1114 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1115 = tail call <4 x half> @air.refract.v4f16(<4 x half> %_1108, <4 x half> %_1113, half %_1114)
  %_1116 = tail call <2 x float> @air.refract.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, float 0.000000e+00)
  %_1117 = tail call <3 x float> @air.refract.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, float 0.000000e+00)
  %_1118 = tail call <4 x float> @air.refract.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, float 0.000000e+00)
  %_1119 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1120 = tail call half @air.round.f16(half %_1119)
  %_1121 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1122 = insertelement <2 x half> undef, half %_1121, i64 0
  %_1123 = shufflevector <2 x half> %_1122, <2 x half> poison, <2 x i32> zeroinitializer
  %_1124 = tail call <2 x half> @air.round.v2f16(<2 x half> %_1123)
  %_1125 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1126 = insertelement <3 x half> undef, half %_1125, i64 0
  %_1128 = shufflevector <3 x half> %_1126, <3 x half> poison, <3 x i32> zeroinitializer
  %_1129 = tail call <3 x half> @air.round.v3f16(<3 x half> %_1128)
  %_1130 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1131 = insertelement <4 x half> undef, half %_1130, i64 0
  %_1134 = shufflevector <4 x half> %_1131, <4 x half> poison, <4 x i32> zeroinitializer
  %_1135 = tail call <4 x half> @air.round.v4f16(<4 x half> %_1134)
  %_1136 = tail call float @air.round.f32(float 0.000000e+00)
  %_1137 = tail call <2 x float> @air.round.v2f32(<2 x float> zeroinitializer)
  %_1138 = tail call <3 x float> @air.round.v3f32(<3 x float> zeroinitializer)
  %_1139 = tail call <4 x float> @air.round.v4f32(<4 x float> zeroinitializer)
  %_1142 = tail call <4 x float> @air.sample_texture_2d.v4f32(ptr addrspace(1) nocapture readonly %testTexture, ptr addrspace(2) nocapture readonly %testSampler, <2 x float> zeroinitializer, i1 true, <2 x i32> zeroinitializer, i1 false, float 0.000000e+00, float 0.000000e+00, i32 0)
  %_1143 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1144 = tail call i8 @air.sign.i8(i8 %_1143)
  %_1145 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1146 = insertelement <2 x i8> undef, i8 %_1145, i64 0
  %_1147 = shufflevector <2 x i8> %_1146, <2 x i8> poison, <2 x i32> zeroinitializer
  %_1148 = tail call <2 x i8> @air.sign.v2i8(<2 x i8> %_1147)
  %_1149 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1150 = insertelement <3 x i8> undef, i8 %_1149, i64 0
  %_1152 = shufflevector <3 x i8> %_1150, <3 x i8> poison, <3 x i32> zeroinitializer
  %_1153 = tail call <3 x i8> @air.sign.v3i8(<3 x i8> %_1152)
  %_1154 = tail call i8 @convert.s.i8.s.i32(i32 0)
  %_1155 = insertelement <4 x i8> undef, i8 %_1154, i64 0
  %_1158 = shufflevector <4 x i8> %_1155, <4 x i8> poison, <4 x i32> zeroinitializer
  %_1159 = tail call <4 x i8> @air.sign.v4i8(<4 x i8> %_1158)
  %_1160 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1161 = tail call i16 @air.sign.i16(i16 %_1160)
  %_1162 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1163 = insertelement <2 x i16> undef, i16 %_1162, i64 0
  %_1164 = shufflevector <2 x i16> %_1163, <2 x i16> poison, <2 x i32> zeroinitializer
  %_1165 = tail call <2 x i16> @air.sign.v2i16(<2 x i16> %_1164)
  %_1166 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1167 = insertelement <3 x i16> undef, i16 %_1166, i64 0
  %_1169 = shufflevector <3 x i16> %_1167, <3 x i16> poison, <3 x i32> zeroinitializer
  %_1170 = tail call <3 x i16> @air.sign.v3i16(<3 x i16> %_1169)
  %_1171 = tail call i16 @convert.s.i16.s.i32(i32 0)
  %_1172 = insertelement <4 x i16> undef, i16 %_1171, i64 0
  %_1175 = shufflevector <4 x i16> %_1172, <4 x i16> poison, <4 x i32> zeroinitializer
  %_1176 = tail call <4 x i16> @air.sign.v4i16(<4 x i16> %_1175)
  %_1177 = tail call i32 @air.sign.i32(i32 0)
  %_1178 = tail call <2 x i32> @air.sign.v2i32(<2 x i32> zeroinitializer)
  %_1179 = tail call <3 x i32> @air.sign.v3i32(<3 x i32> zeroinitializer)
  %_1180 = tail call <4 x i32> @air.sign.v4i32(<4 x i32> zeroinitializer)
  %_1181 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1182 = tail call half @air.sign.f16(half %_1181)
  %_1183 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1184 = insertelement <2 x half> undef, half %_1183, i64 0
  %_1185 = shufflevector <2 x half> %_1184, <2 x half> poison, <2 x i32> zeroinitializer
  %_1186 = tail call <2 x half> @air.sign.v2f16(<2 x half> %_1185)
  %_1187 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1188 = insertelement <3 x half> undef, half %_1187, i64 0
  %_1190 = shufflevector <3 x half> %_1188, <3 x half> poison, <3 x i32> zeroinitializer
  %_1191 = tail call <3 x half> @air.sign.v3f16(<3 x half> %_1190)
  %_1192 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1193 = insertelement <4 x half> undef, half %_1192, i64 0
  %_1196 = shufflevector <4 x half> %_1193, <4 x half> poison, <4 x i32> zeroinitializer
  %_1197 = tail call <4 x half> @air.sign.v4f16(<4 x half> %_1196)
  %_1198 = tail call float @air.sign.f32(float 0.000000e+00)
  %_1199 = tail call <2 x float> @air.sign.v2f32(<2 x float> zeroinitializer)
  %_1200 = tail call <3 x float> @air.sign.v3f32(<3 x float> zeroinitializer)
  %_1201 = tail call <4 x float> @air.sign.v4f32(<4 x float> zeroinitializer)
  %_1202 = tail call float @air.sin.f32(float 0.000000e+00)
  %_1203 = tail call float @air.sinh.f32(float 0.000000e+00)
  %_1204 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1205 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1206 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1207 = tail call half @air.smoothstep.f16(half %_1204, half %_1205, half %_1206)
  %_1208 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1209 = insertelement <2 x half> undef, half %_1208, i64 0
  %_1210 = shufflevector <2 x half> %_1209, <2 x half> poison, <2 x i32> zeroinitializer
  %_1211 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1212 = insertelement <2 x half> undef, half %_1211, i64 0
  %_1213 = shufflevector <2 x half> %_1212, <2 x half> poison, <2 x i32> zeroinitializer
  %_1214 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1215 = insertelement <2 x half> undef, half %_1214, i64 0
  %_1216 = shufflevector <2 x half> %_1215, <2 x half> poison, <2 x i32> zeroinitializer
  %_1217 = tail call <2 x half> @air.smoothstep.v2f16(<2 x half> %_1210, <2 x half> %_1213, <2 x half> %_1216)
  %_1218 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1219 = insertelement <3 x half> undef, half %_1218, i64 0
  %_1221 = shufflevector <3 x half> %_1219, <3 x half> poison, <3 x i32> zeroinitializer
  %_1222 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1223 = insertelement <3 x half> undef, half %_1222, i64 0
  %_1225 = shufflevector <3 x half> %_1223, <3 x half> poison, <3 x i32> zeroinitializer
  %_1226 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1227 = insertelement <3 x half> undef, half %_1226, i64 0
  %_1229 = shufflevector <3 x half> %_1227, <3 x half> poison, <3 x i32> zeroinitializer
  %_1230 = tail call <3 x half> @air.smoothstep.v3f16(<3 x half> %_1221, <3 x half> %_1225, <3 x half> %_1229)
  %_1231 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1232 = insertelement <4 x half> undef, half %_1231, i64 0
  %_1235 = shufflevector <4 x half> %_1232, <4 x half> poison, <4 x i32> zeroinitializer
  %_1236 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1237 = insertelement <4 x half> undef, half %_1236, i64 0
  %_1240 = shufflevector <4 x half> %_1237, <4 x half> poison, <4 x i32> zeroinitializer
  %_1241 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1242 = insertelement <4 x half> undef, half %_1241, i64 0
  %_1245 = shufflevector <4 x half> %_1242, <4 x half> poison, <4 x i32> zeroinitializer
  %_1246 = tail call <4 x half> @air.smoothstep.v4f16(<4 x half> %_1235, <4 x half> %_1240, <4 x half> %_1245)
  %_1247 = tail call float @air.smoothstep.f32(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00)
  %_1248 = tail call <2 x float> @air.smoothstep.v2f32(<2 x float> zeroinitializer, <2 x float> zeroinitializer, <2 x float> zeroinitializer)
  %_1249 = tail call <3 x float> @air.smoothstep.v3f32(<3 x float> zeroinitializer, <3 x float> zeroinitializer, <3 x float> zeroinitializer)
  %_1250 = tail call <4 x float> @air.smoothstep.v4f32(<4 x float> zeroinitializer, <4 x float> zeroinitializer, <4 x float> zeroinitializer)
  %_1251 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1252 = tail call half @air.sqrt.f16(half %_1251)
  %_1253 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1254 = insertelement <2 x half> undef, half %_1253, i64 0
  %_1255 = shufflevector <2 x half> %_1254, <2 x half> poison, <2 x i32> zeroinitializer
  %_1256 = tail call <2 x half> @air.sqrt.v2f16(<2 x half> %_1255)
  %_1257 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1258 = insertelement <3 x half> undef, half %_1257, i64 0
  %_1260 = shufflevector <3 x half> %_1258, <3 x half> poison, <3 x i32> zeroinitializer
  %_1261 = tail call <3 x half> @air.sqrt.v3f16(<3 x half> %_1260)
  %_1262 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1263 = insertelement <4 x half> undef, half %_1262, i64 0
  %_1266 = shufflevector <4 x half> %_1263, <4 x half> poison, <4 x i32> zeroinitializer
  %_1267 = tail call <4 x half> @air.sqrt.v4f16(<4 x half> %_1266)
  %_1268 = tail call float @air.sqrt.f32(float 0.000000e+00)
  %_1269 = tail call <2 x float> @air.sqrt.v2f32(<2 x float> zeroinitializer)
  %_1270 = tail call <3 x float> @air.sqrt.v3f32(<3 x float> zeroinitializer)
  %_1271 = tail call <4 x float> @air.sqrt.v4f32(<4 x float> zeroinitializer)
  %_1272 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1273 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1274 = tail call half @air.step.f16(half %_1272, half %_1273)
  %_1275 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1276 = insertelement <2 x half> undef, half %_1275, i64 0
  %_1277 = shufflevector <2 x half> %_1276, <2 x half> poison, <2 x i32> zeroinitializer
  %_1278 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1279 = insertelement <2 x half> undef, half %_1278, i64 0
  %_1280 = shufflevector <2 x half> %_1279, <2 x half> poison, <2 x i32> zeroinitializer
  %_1281 = tail call <2 x half> @air.step.v2f16(<2 x half> %_1277, <2 x half> %_1280)
  %_1282 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1283 = insertelement <3 x half> undef, half %_1282, i64 0
  %_1285 = shufflevector <3 x half> %_1283, <3 x half> poison, <3 x i32> zeroinitializer
  %_1286 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1287 = insertelement <3 x half> undef, half %_1286, i64 0
  %_1289 = shufflevector <3 x half> %_1287, <3 x half> poison, <3 x i32> zeroinitializer
  %_1290 = tail call <3 x half> @air.step.v3f16(<3 x half> %_1285, <3 x half> %_1289)
  %_1291 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1292 = insertelement <4 x half> undef, half %_1291, i64 0
  %_1295 = shufflevector <4 x half> %_1292, <4 x half> poison, <4 x i32> zeroinitializer
  %_1296 = tail call half @convert.f.f16.f.f32(float 0.000000e+00)
  %_1297 = insertelement <4 x half> undef, half %_1296, i64 0
  %_1300 = shufflevector <4 x half> %_1297, <4 x half> poison, <4 x i32> zeroinitializer
  %_1301 = tail call <4 x half> @air.step.v4f16(<4 x half> %_1295, <4 x half> %_1300)
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
