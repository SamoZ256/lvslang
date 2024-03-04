#include <metal_stdlib>
using namespace metal;

struct VertexOut {
	float4 pos [[position]];
	float2 texCoord;
};

fragment float4 fragmentMain(VertexOut fragmentIn [[stage_in]], texture2d<float> tex [[texture(0)]], sampler smp [[sampler(0)]]) {
	return tex.sample(smp, fragmentIn.texCoord);
}

