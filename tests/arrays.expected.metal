#include <metal_stdlib>
using namespace metal;

struct MyBuffer {
	float a[32];
	int i;
};

fragment float4 testArrays(constant MyBuffer* myBuffer [[buffer(0)]]) {
	float4 outColor;
	int multiArray[32][32];
	multiArray[10][myBuffer->i] = 1;
	return float4(myBuffer->a[0], 0.000000, 0.000000, 1.000000);
}

