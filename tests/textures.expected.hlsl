struct VertexOut {
	float4 pos;
	float2 texCoord;
};

float4 fragmentMain(VertexOut fragmentIn, Texture2D tex, SamplerState smp);

Texture2D tex : register(t0);

SamplerState smp : register(s0);

struct float4_Output {
	float4 output : TEXCOORD0;
};

float4_Output _fragmentMain(VertexOut fragmentIn) {
	// Entry point call
	float4 _entryPointOutput = fragmentMain(fragmentIn, tex, smp);

	// Output
	float4_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

float4 fragmentMain(VertexOut fragmentIn, Texture2D tex, SamplerState smp) {
	return tex.SampleLevel(smp, fragmentIn.texCoord, 0.0f);
}

