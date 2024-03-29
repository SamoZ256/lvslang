#include <metal_stdlib>
using namespace metal;

struct MyBuffer {
	float a;
};

fragment float4 testControlFlow(constant MyBuffer* myBuffer [[buffer(0)]]) {
	float4 outColor;
	if ((myBuffer->a > 0.000000)) outColor = float4(1.000000, 0.000000, 0.000000, 1.000000) else if ((myBuffer->a < 0.000000)) outColor = float4(0.000000, 1.000000, 0.000000, 1.000000) else outColor = float4(0.000000, 0.000000, 1.000000, 1.000000);
	int i = 0;
	while ((i < 10)) i = (i + 1);
	if ((myBuffer->a > 0.000000)) {
		outColor = float4(1.000000, 0.000000, 0.000000, 1.000000);
	} else if ((myBuffer->a < 0.000000)) {
		outColor = float4(0.000000, 1.000000, 0.000000, 1.000000);
	} else {
		outColor = float4(0.000000, 0.000000, 1.000000, 1.000000);
	};
	while ((i < 10)) {
		i = (i + 1);
	};
	return outColor;
}

