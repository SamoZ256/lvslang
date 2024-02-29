struct MyBuffer {
	float a;
};

struct FragmentOut {
	float4 outColor : SV_Target0;
};

FragmentOut testControlFlow(MyBuffer myBuffer);

cbuffer myBuffer_Uniform : register(b0) {
	MyBuffer myBuffer;
};

struct FragmentOut_Output {
	FragmentOut output : TEXCOORD0;
};

FragmentOut_Output _testControlFlow() {
	// Entry point call
	FragmentOut _entryPointOutput = testControlFlow(myBuffer);

	// Output
	FragmentOut_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

FragmentOut testControlFlow(MyBuffer myBuffer) {
	float4 outColor;
	if ((myBuffer.a > 0.000000)) outColor = float4(1.000000, 0.000000, 0.000000, 1.000000) else if ((myBuffer.a < 0.000000)) outColor = float4(0.000000, 1.000000, 0.000000, 1.000000) else outColor = float4(0.000000, 0.000000, 1.000000, 1.000000);
	int i = 0;
	while ((i < 10))i = (i + 1);
	if ((myBuffer.a > 0.000000)) {
		outColor = float4(1.000000, 0.000000, 0.000000, 1.000000);
	} else if ((myBuffer.a < 0.000000)) {
		outColor = float4(0.000000, 1.000000, 0.000000, 1.000000);
	} else {
		outColor = float4(0.000000, 0.000000, 1.000000, 1.000000);
	};
	while ((i < 10)){
		i = (i + 1);
	};
	FragmentOut fragmentOut;
	fragmentOut.outColor = outColor;
	return fragmentOut;
}

