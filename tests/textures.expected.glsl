#version 450

#extension GL_EXT_shader_8bit_storage : enable

#extension GL_EXT_shader_16bit_storage : enable

#extension GL_EXT_shader_explicit_arithmetic_types : enable

struct VertexOut {
	vec4 pos;
	vec2 texCoord;
};

vec4 fragmentMain(VertexOut fragmentIn, texture2D tex1, sampler smp);

layout (location = 0) in VertexOut_Input {
	VertexOut fragmentIn;
};

layout (set = 1, binding = 0) uniform texture2D tex1;

layout (set = 1, binding = 1, rgba8) uniform image2D tex2;

layout (set = 0, binding = 0) uniform sampler smp;

layout (location = 0) out vec4 _outputColor;

void main() {
	// Input

	// Entry point call
	vec4 _entryPointOutput = fragmentMain(fragmentIn, tex1, smp);

	// Output
	_outputColor = _entryPointOutput;
}

vec4 fragmentMain(VertexOut fragmentIn, texture2D tex1, sampler smp) {
	vec4 sampled1 = texture(sampler2D(tex1, smp), fragmentIn.texCoord);
	vec4 sampled2 = imageLoad(tex2, u16vec2(0));
	return (sampled1 * sampled2);
}

