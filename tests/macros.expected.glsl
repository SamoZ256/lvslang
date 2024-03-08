#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

void fragmentMain();

layout (location = 0) out void _outputColor;

void main() {
	// Entry point call
	fragmentMain();
}

void fragmentMain() {
	int a = abs((1 + (0 - 2)));
}

int myAbs(int x) {
	if ((x < 0)) return (0 - x) else return x;
}

