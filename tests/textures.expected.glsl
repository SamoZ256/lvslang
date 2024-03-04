#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct VertexOut {
	vec4 pos;
	vec2 texCoord;
};

vec4 fragmentMain(VertexOut fragmentIn, texture2D tex, sampler smp);

layout (location = 0) in VertexOut_Input {
	VertexOut fragmentIn;
};

layout (set = 0, binding = 0) uniform texture2D tex;

layout (set = 0, binding = 1) uniform sampler smp;

layout (location = 0) out vec4 _outputColor;

void main() {
	// Input

	// Entry point call
	vec4 _entryPointOutput = fragmentMain(fragmentIn, tex, smp);

	// Output
	_outputColor = _entryPointOutput;
}

vec4 fragmentMain(VertexOut fragmentIn, texture2D tex, sampler smp) {
	return texture(sampler2D(tex, smp), fragmentIn.texCoord);
}

