#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

bool forwardDeclaredFunction(int a, ivec3 b);

ivec2 functionWithDefaultArguments(ivec2 a, ivec2 b) {
	return (a + b);
}

void testAdvancedFeatures();

layout (location = 0) out void _outputColor;

void main() {
	// Entry point call
	testAdvancedFeatures();
}

void testAdvancedFeatures() {
	bool a = forwardDeclaredFunction(1, ivec3(1, 2, 3));
	ivec2 b = functionWithDefaultArguments(ivec2(1, 2), ivec2(0));
	ivec2 c = functionWithDefaultArguments(ivec2(1, 2), ivec2(3, 4));
}

bool forwardDeclaredFunction(int a, ivec3 b) {
	return (((a == b.x) || (a == b.y)) || (a == b.z));
}

