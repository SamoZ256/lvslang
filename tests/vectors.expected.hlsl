float4 testVectors();

struct float4_Output {
	float4 output : TEXCOORD0;
};

float4_Output _testVectors() {
	// Entry point call
	float4 _entryPointOutput = testVectors();

	// Output
	float4_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

float4 testVectors() {
	float4 outColor = float4(0.000000, 0.000000, 0.000000, 1.000000);
	float4 vec1 = float4(1.000000, 2.000000, 3.000000, 4.000000);
	float4 vec2 = float4(5.000000, 6.000000, 7.000000, 8.000000);
	float4 sum = (vec1 + vec2);
	if ((sum == float4(6.000000, 8.000000, 10.000000, 12.000000))) outColor.r = 1.000000;
	float4 diff = (vec2 - vec1);
	if ((diff == float4(4.000000, 4.000000, 4.000000, 4.000000))) outColor.g = 1.000000;
	float4 scaled = (vec1 * 2.000000);
	if ((scaled == float4(2.000000, 4.000000, 6.000000, 8.000000))) outColor.b = 1.000000;
	float4 swizzled = vec1.yxwz;
	vec1.xz = vec2.yw;
	return outColor;
}

