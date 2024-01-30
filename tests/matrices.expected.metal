#include <metal_stdlib>
using namespace metal;

struct FragmentOut {
	float4 outColor [[color(0)]];
};

fragment FragmentOut testMatrices() {
	float4x4 matrix1;
	float4x4 matrix2;
	FragmentOut fragmentOut;
	fragmentOut.outColor = float4(0.000000, 0.000000, 0.000000, 1.000000);
	return fragmentOut;
}

