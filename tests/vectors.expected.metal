#include <metal_stdlib>
using namespace metal;

struct FragmentOut {
	float4 outColor [[color(0)]];
};

fragment FragmentOut testVectors() {
	FragmentOut fragmentOut;
	fragmentOut.outColor = float4(0.000000, 0.000000, 0.000000, 1.000000);
	float4 vec1 = float4(1.000000, 2.000000, 3.000000, 4.000000);
	float4 vec2 = float4(5.000000, 6.000000, 7.000000, 8.000000);
	float4 sum = (vec1 + vec2);
	if ((sum == float4(6.000000, 8.000000, 10.000000, 12.000000))) fragmentOut.outColor.r = 1.000000;
	float4 diff = (vec2 - vec1);
	if ((diff == float4(4.000000, 4.000000, 4.000000, 4.000000))) fragmentOut.outColor.g = 1.000000;
	float4 scaled = (vec1 * 2.000000);
	if ((scaled == float4(2.000000, 4.000000, 6.000000, 8.000000))) fragmentOut.outColor.b = 1.000000;
	float4 swizzled = vec1.yxwz;
	vec1.xz = vec2.yw;
	return fragmentOut;
}

