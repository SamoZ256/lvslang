#version 450

struct MyBuffer {
	float a;
};

struct FragmentOut {
	vec4 outColor;
};

FragmentOut testControlFlow(MyBuffer myBuffer);

layout (set = 0, binding = 0) uniform myBuffer_Uniform {
	MyBuffer myBuffer;
};

layout (location = 0) out vec4 outColor;

void main() {
	//Input

	//Entry point call
	FragmentOut _entryPointOutput = testControlFlow(myBuffer);

	//Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut testControlFlow(MyBuffer myBuffer) {
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

