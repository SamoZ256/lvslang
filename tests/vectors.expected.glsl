#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct FragmentOut {
	vec4 outColor;
};

FragmentOut testVectors();

layout (location = 0) out vec4 outColor;

void main() {
	// Input

	// Entry point call
	FragmentOut _entryPointOutput = testVectors();

	// Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut testVectors() {
	FragmentOut fragmentOut;
	fragmentOut.outColor = vec4(0.000000, 0.000000, 0.000000, 1.000000);
	vec4 vec1 = vec4(1.000000, 2.000000, 3.000000, 4.000000);
	vec4 vec2 = vec4(5.000000, 6.000000, 7.000000, 8.000000);
	vec4 sum = (vec1 + vec2);
	if ((sum == vec4(6.000000, 8.000000, 10.000000, 12.000000))) fragmentOut.outColor.r = 1.000000;
	vec4 diff = (vec2 - vec1);
	if ((diff == vec4(4.000000, 4.000000, 4.000000, 4.000000))) fragmentOut.outColor.g = 1.000000;
	vec4 scaled = (vec1 * vec4(2.000000));
	if ((scaled == vec4(2.000000, 4.000000, 6.000000, 8.000000))) fragmentOut.outColor.b = 1.000000;
	vec4 swizzled = vec1.yxwz;
	vec1.xz = vec2.yw;
	return fragmentOut;
}

