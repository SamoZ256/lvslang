#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct MyBuffer {
	float a[32];
	int i;
};

vec4 testArrays(MyBuffer myBuffer);

layout (set = 0, binding = 0) uniform myBuffer_Uniform {
	MyBuffer myBuffer;
};

layout (location = 0) out vec4 _outputColor;

void main() {
	// Entry point call
	vec4 _entryPointOutput = testArrays(myBuffer);

	// Output
	_outputColor = _entryPointOutput;
}

vec4 testArrays(MyBuffer myBuffer) {
	vec4 outColor;
	int multiArray[32][32];
	multiArray[10][myBuffer.i] = 1;
	return vec4(myBuffer.a[0], 0.000000, 0.000000, 1.000000);
}

