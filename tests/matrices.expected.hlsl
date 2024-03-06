float4 testMatrices();

struct float4_Output {
	float4 output : TEXCOORD0;
};

float4_Output _testMatrices() {
	// Entry point call
	float4 _entryPointOutput = testMatrices();

	// Output
	float4_Output __output;
	__output.output = _entryPointOutput;

	return __output;
}

float4 testMatrices() {
	float4x4 matrix1 = float4x4(float4(1.000000, 2.000000, 3.000000, 4.000000), float4(5.000000, 6.000000, 7.000000, 8.000000), float4(9.000000, 10.000000, 11.000000, 12.000000), float4(13.000000, 14.000000, 15.000000, 16.000000));
	float4x4 matrix2 = float4x4(1.000000);
	float4x4 result1 = mul(matrix1, 2.000000);
	float4 result2 = mul(matrix1, float4(1.000000, 2.000000, 3.000000, 4.000000));
	float4x4 result3 = mul(matrix1, matrix2);
	return result3[2];
}

