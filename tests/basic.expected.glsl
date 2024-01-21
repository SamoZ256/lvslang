#version 450

struct Model {
	vec2 pos;
	vec2 scale;
};

struct VertexIn {
	vec2 pos;
	vec2 texCoord;
};

struct VertexOut {
	vec4 pos;
	vec2 texCoord;
};

VertexOut vertexMain(VertexIn vertexIn, Model model);

layout (location = 0) in vec2 pos;

layout (location = 1) in vec2 texCoord;

layout (set = 0, binding = 0) uniform model_Uniform {
	Model model;
};

layout (location = 0) out VertexOut_Output {
	VertexOut _output;
} _output;

void main() {
	//Input
	VertexIn vertexIn;
	vertexIn.pos = pos;
	vertexIn.texCoord = texCoord;

	//Entry point call
	VertexOut _entryPointOutput = vertexMain(vertexIn, model);

	//Output
	gl_Position = _entryPointOutput.pos;
	_output._output.pos = _entryPointOutput.pos;
	_output._output.texCoord = _entryPointOutput.texCoord;
}

VertexOut vertexMain(VertexIn vertexIn, Model model) {
	VertexOut vertexOut;
	vertexOut.pos = vec4((model.pos + (vertexIn.pos * model.scale)), 0.000000, 1.000000);
	vertexOut.texCoord = vertexIn.texCoord;
	return vertexOut;
}

struct FragmentOut {
	vec4 outColor;
};

FragmentOut fragmentMain(VertexOut fragmentIn, texture2D colorTexture, sampler colorSampler);

layout (location = 0) in VertexOut_Input {
	VertexOut fragmentIn;
};

layout (set = 0, binding = 1) uniform texture2D colorTexture;

layout (set = 1, binding = 0) uniform sampler colorSampler;

layout (location = 0) out vec4 outColor;

void main() {
	//Input

	//Entry point call
	FragmentOut _entryPointOutput = fragmentMain(fragmentIn, colorTexture, colorSampler);

	//Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut fragmentMain(VertexOut fragmentIn, texture2D colorTexture, sampler colorSampler) {
	FragmentOut fragmentOut;
	fragmentOut.outColor = texture(sampler2D(colorTexture, colorSampler), fragmentIn.texCoord);
	return fragmentOut;
}

