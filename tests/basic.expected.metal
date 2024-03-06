#include <metal_stdlib>
using namespace metal;

struct Model {
	float2 pos;
	float2 scale;
};

struct VertexIn {
	float2 pos [[attribute(0)]];
	float2 texCoord [[attribute(1)]];
};

struct VertexOut {
	float4 pos [[position]];
	float2 texCoord;
};

vertex VertexOut vertexMain(VertexIn vertexIn [[stage_in]], constant Model* model [[buffer(0)]]) {
	VertexOut vertexOut;
	vertexOut.pos = float4((model->pos + (vertexIn.pos * model->scale)), 0.000000, 1.000000);
	vertexOut.texCoord = vertexIn.texCoord;
	return vertexOut;
}

fragment float4 fragmentMain(VertexOut fragmentIn [[stage_in]], texture2d<float> colorTexture [[texture(0)]], sampler colorSampler [[sampler(0)]]) {
	return colorTexture.sample(colorSampler, fragmentIn.texCoord);
}

