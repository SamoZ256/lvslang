

bool forwardDeclaredFunction(int a, int3 b);

struct FragmentOut {
	float4 outColor : SV_Target0;
};

FragmentOut testAdvancedFeatures();

struct FragmentOut_Output {
	FragmentOut output : TEXCOORD0;
};

FragmentOut_Output _testAdvancedFeatures() {
	//Entry point call
	FragmentOut _entryPointOutput = testAdvancedFeatures();

	//Output
	FragmentOut_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

FragmentOut testAdvancedFeatures() {
	bool a = forwardDeclaredFunction(1, int3(1, 2, 3));
	FragmentOut fragmentOut;
	return fragmentOut;
}

bool forwardDeclaredFunction(int a, int3 b) {
	return (((a == b.x) || (a == b.y)) || (a == b.z));
}

