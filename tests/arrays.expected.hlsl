struct MyBuffer {
	float a[32];
	int i;
};

float4 testArrays(MyBuffer myBuffer);

cbuffer myBuffer_Uniform : register(b0) {
	MyBuffer myBuffer;
};

struct float4_Output {
	float4 output : TEXCOORD0;
};

float4_Output _testArrays() {
	// Entry point call
	float4 _entryPointOutput = testArrays(myBuffer);

	// Output
	float4_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

float4 testArrays(MyBuffer myBuffer) {
	float4 outColor;
	int multiArray[32][32];
	multiArray[10][myBuffer.i] = 1;
	return float4(myBuffer.a[0], 0.000000, 0.000000, 1.000000);
}

