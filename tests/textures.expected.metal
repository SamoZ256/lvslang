#include <metal_stdlib>
using namespace metal;

struct VertexOut {
	float4 pos [[position]];
	float2 texCoord;
};

fragment float4 fragmentMain(VertexOut fragmentIn [[stage_in]], texture2d<float> tex1 [[texture(0)]], texture2d<float, access::read> tex2 [[texture(1)]], sampler smp [[sampler(0)]]) {
	float4 sampled1 = tex1.sample(smp, fragmentIn.texCoord);
	float4 sampled2 = tex2.read(ushort2(0));
	return (sampled1 * sampled2);
}

