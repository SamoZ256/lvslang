#version 450

struct FragmentOut {
	vec4 outColor;
};

FragmentOut testMatrices();

layout (location = 0) out vec4 outColor;

void main() {
	//Input

	//Entry point call
	FragmentOut _entryPointOutput = testMatrices();

	//Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut testMatrices() {
	mat4 matrix1;
	mat4 matrix2;
	FragmentOut fragmentOut;
	fragmentOut.outColor = vec4(0.000000, 0.000000, 0.000000, 1.000000);
	return fragmentOut;
}

