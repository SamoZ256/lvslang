struct MyBuffer {
	float a;
};

float4 testControlFlow(MyBuffer myBuffer);

cbuffer myBuffer_Uniform : register(b0) {
	MyBuffer myBuffer;
};

struct float4_Output {
	float4 output : TEXCOORD0;
};

float4_Output _testControlFlow() {
	// Entry point call
	float4 _entryPointOutput = testControlFlow(myBuffer);

	// Output
	float4_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

float4 testControlFlow(MyBuffer myBuffer) {
	float4 outColor;
	if ((myBuffer.a > 0.000000)) outColor = float4(1.000000, 0.000000, 0.000000, 1.000000) else if ((myBuffer.a < 0.000000)) outColor = float4(0.000000, 1.000000, 0.000000, 1.000000) else outColor = float4(0.000000, 0.000000, 1.000000, 1.000000);
	int i = 0;
	while ((i < 10)) i = (i + 1);
	if ((myBuffer.a > 0.000000)) {
		outColor = float4(1.000000, 0.000000, 0.000000, 1.000000);
	} else if ((myBuffer.a < 0.000000)) {
		outColor = float4(0.000000, 1.000000, 0.000000, 1.000000);
	} else {
		outColor = float4(0.000000, 0.000000, 1.000000, 1.000000);
	};
	while ((i < 10)) {
		i = (i + 1);
	};
	return outColor;
}

