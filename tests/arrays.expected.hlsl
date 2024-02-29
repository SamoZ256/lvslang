struct MyBuffer {
	float a[32];
	int i;
};

struct FragmentOut {
	float4 outColor : SV_Target0;
};

FragmentOut testArrays(MyBuffer myBuffer);

cbuffer myBuffer_Uniform : register(b0) {
	MyBuffer myBuffer;
};

struct FragmentOut_Output {
	FragmentOut output : TEXCOORD0;
};

FragmentOut_Output _testArrays() {
	// Entry point call
	FragmentOut _entryPointOutput = testArrays(myBuffer);

	// Output
	FragmentOut_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

FragmentOut testArrays(MyBuffer myBuffer) {
	float4 outColor;
	int multiArray[32][32];
	multiArray[10][myBuffer.i] = 1;
	FragmentOut fragmentOut;
	fragmentOut.outColor = float4(myBuffer.a[0], 0.000000, 0.000000, 1.000000);
	return fragmentOut;
}

