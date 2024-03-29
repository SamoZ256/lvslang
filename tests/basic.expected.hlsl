struct Model {
	float2 pos;
	float2 scale;
};

struct VertexIn {
	float2 pos : TEXCOORD0;
	float2 texCoord : TEXCOORD1;
};

struct VertexOut {
	float4 pos;
	float2 texCoord;
};

VertexOut vertexMain(VertexIn vertexIn, Model model);

cbuffer model_Uniform : register(b0) {
	Model model;
};

struct VertexOut_Output {
	VertexOut output : TEXCOORD0;
	float4 position : SV_Position;
};

VertexOut_Output _vertexMain(VertexIn vertexIn) {
	// Entry point call
	VertexOut _entryPointOutput = vertexMain(vertexIn, model);

	// Output
	VertexOut_Output __output;
	__output.output = _entryPointOutput;
	__output.position = _entryPointOutput.pos;

	return __output;
}

VertexOut vertexMain(VertexIn vertexIn, Model model) {
	VertexOut vertexOut;
	vertexOut.pos = float4(((model.pos + (vertexIn.pos * model.scale)))[0], ((model.pos + (vertexIn.pos * model.scale)))[1], 0.000000, 1.000000);
	vertexOut.texCoord = vertexIn.texCoord;
	return vertexOut;
}

float4 fragmentMain(VertexOut fragmentIn, Texture2D colorTexture, SamplerState colorSampler);

Texture2D colorTexture : register(t0);

SamplerState colorSampler : register(s0);

struct float4_Output {
	float4 output : TEXCOORD0;
};

float4_Output _fragmentMain(VertexOut fragmentIn) {
	// Entry point call
	float4 _entryPointOutput = fragmentMain(fragmentIn, colorTexture, colorSampler);

	// Output
	float4_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

float4 fragmentMain(VertexOut fragmentIn, Texture2D colorTexture, SamplerState colorSampler) {
	return colorTexture.SampleLevel(colorSampler, fragmentIn.texCoord, 0.0f);
}

