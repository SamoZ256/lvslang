

struct FragmentOut {
	float4 outColor : SV_Target0;
};

FragmentOut testMatrices();

struct FragmentOut_Output {
	FragmentOut output : TEXCOORD0;
};

FragmentOut_Output _testMatrices() {
	//Entry point call
	FragmentOut _entryPointOutput = testMatrices();

	//Output
	FragmentOut_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

FragmentOut testMatrices() {
	float4x4 matrix1;
	float4x4 matrix2;
	FragmentOut fragmentOut;
	fragmentOut.outColor = float4(0.000000, 0.000000, 0.000000, 1.000000);
	return fragmentOut;
}

