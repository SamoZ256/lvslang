#version 450

bool forwardDeclaredFunction(int a, ivec3 b);

struct FragmentOut {
	vec4 outColor;
};

FragmentOut testAdvancedFeatures();

layout (location = 0) out vec4 outColor;

void main() {
	//Input

	//Entry point call
	FragmentOut _entryPointOutput = testAdvancedFeatures();

	//Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut testAdvancedFeatures() {
	bool a = forwardDeclaredFunction(1, ivec3(1, 2, 3));
	FragmentOut fragmentOut;
	return fragmentOut;
}

bool forwardDeclaredFunction(int a, ivec3 b) {
	return (((a == b.x) || (a == b.y)) || (a == b.z));
}

