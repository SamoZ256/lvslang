#include <metal_stdlib>
using namespace metal;

bool forwardDeclaredFunction(int a, int3 b);

int2 functionWithDefaultArguments(int2 a, int2 b) {
	return (a + b);
}

fragment void testAdvancedFeatures() {
	bool a = forwardDeclaredFunction(1, int3(1, 2, 3));
	int2 b = functionWithDefaultArguments(int2(1, 2), int2(0));
	int2 c = functionWithDefaultArguments(int2(1, 2), int2(3, 4));
}

bool forwardDeclaredFunction(int a, int3 b) {
	return (((a == b.x) || (a == b.y)) || (a == b.z));
}

