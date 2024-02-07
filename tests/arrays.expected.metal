#include <metal_stdlib>
using namespace metal;

struct MyBuffer {
	float a[32];
	int i;
};

struct FragmentOut {
	float4 outColor [[color(0)]];
};

fragment FragmentOut testArrays(constant MyBuffer* myBuffer [[buffer(0)]]) {
	float4 outColor;
	int multiArray[32][32];
	multiArray[10][(*myBuffer).i] = 1;
	FragmentOut fragmentOut;
	fragmentOut.outColor = float4((*myBuffer).a[0], 0.000000, 0.000000, 1.000000);
	return fragmentOut;
}

