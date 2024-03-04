struct VertexOut {
	float4 pos;
	float2 texCoord;
};

float4 fragmentMain(VertexOut fragmentIn, Texture2D tex1, Texture2D tex2, SamplerState smp);

Texture2D tex1 : register(t0);

Texture2D tex2 : register(t0);

SamplerState smp : register(s0);

struct float4_Output {
	float4 output : TEXCOORD0;
};

float4_Output _fragmentMain(VertexOut fragmentIn) {
	// Entry point call
	float4 _entryPointOutput = fragmentMain(fragmentIn, tex1, tex2, smp);

	// Output
	float4_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

float4 fragmentMain(VertexOut fragmentIn, Texture2D tex1, Texture2D tex2, SamplerState smp) {
	float4 sampled1 = tex1.SampleLevel(smp, fragmentIn.texCoord, 0.0f);
	float4 sampled2 = tex2.Read(uint16_t2(0), 0);
	return (sampled1 * sampled2);
}

