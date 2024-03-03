#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct FragmentOut {
	vec4 outColor;
};

FragmentOut testMatrices();

layout (location = 0) out vec4 outColor;

void main() {
	// Input

	// Entry point call
	FragmentOut _entryPointOutput = testMatrices();

	// Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut testMatrices() {
	mat4 matrix1 = mat4(vec4(1.000000, 2.000000, 3.000000, 4.000000), vec4(5.000000, 6.000000, 7.000000, 8.000000), vec4(9.000000, 10.000000, 11.000000, 12.000000), vec4(13.000000, 14.000000, 15.000000, 16.000000));
	mat4 matrix2 = mat4(1.000000);
	mat4 result1 = (matrix1 * 2.000000);
	vec4 result2 = (matrix1 * vec4(1.000000, 2.000000, 3.000000, 4.000000));
	mat4 result3 = (matrix1 * matrix2);
	FragmentOut fragmentOut;
	fragmentOut.outColor = vec4(0.000000, 0.000000, 0.000000, 1.000000);
	return fragmentOut;
}

