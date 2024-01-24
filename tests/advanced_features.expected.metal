#include <metal_stdlib>
using namespace metal;

bool forwardDeclaredFunction(int a, int3 b);

struct FragmentOut {
	float4 outColor [[color(0)]];
};

fragment FragmentOut testAdvancedFeatures() {
	bool a = forwardDeclaredFunction(1, int3(1, 2, 3));
	FragmentOut fragmentOut;
	return fragmentOut;
}

bool forwardDeclaredFunction(int a, int3 b) {
	return (((a == b.x) || (a == b.y)) || (a == b.z));
}

