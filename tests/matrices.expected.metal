#include <metal_stdlib>
using namespace metal;

fragment float4 testMatrices() {
	float4x4 matrix1 = float4x4(float4(1.000000, 2.000000, 3.000000, 4.000000), float4(5.000000, 6.000000, 7.000000, 8.000000), float4(9.000000, 10.000000, 11.000000, 12.000000), float4(13.000000, 14.000000, 15.000000, 16.000000));
	float4x4 matrix2 = float4x4(1.000000);
	float4x4 result1 = (matrix1 * 2.000000);
	float4 result2 = (matrix1 * float4(1.000000, 2.000000, 3.000000, 4.000000));
	float4x4 result3 = (matrix1 * matrix2);
	return result3[2];
}

