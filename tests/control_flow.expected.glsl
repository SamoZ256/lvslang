#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct MyBuffer {
	float a;
};

vec4 testControlFlow(MyBuffer myBuffer);

layout (set = 0, binding = 0) uniform myBuffer_Uniform {
	MyBuffer myBuffer;
};

layout (location = 0) out vec4 _outputColor;

void main() {
	// Entry point call
	vec4 _entryPointOutput = testControlFlow(myBuffer);

	// Output
	_outputColor = _entryPointOutput;
}

vec4 testControlFlow(MyBuffer myBuffer) {
	vec4 outColor;
	if ((myBuffer.a > 0.000000)) outColor = vec4(1.000000, 0.000000, 0.000000, 1.000000) else if ((myBuffer.a < 0.000000)) outColor = vec4(0.000000, 1.000000, 0.000000, 1.000000) else outColor = vec4(0.000000, 0.000000, 1.000000, 1.000000);
	int i = 0;
	while ((i < 10)) i = (i + 1);
	if ((myBuffer.a > 0.000000)) {
		outColor = vec4(1.000000, 0.000000, 0.000000, 1.000000);
	} else if ((myBuffer.a < 0.000000)) {
		outColor = vec4(0.000000, 1.000000, 0.000000, 1.000000);
	} else {
		outColor = vec4(0.000000, 0.000000, 1.000000, 1.000000);
	};
	while ((i < 10)) {
		i = (i + 1);
	};
	return outColor;
}

