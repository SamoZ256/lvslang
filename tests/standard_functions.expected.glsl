#version 450

struct FragmentOut {
	vec4 outColor;
};

FragmentOut testStandardFunctions(texture2D testTexture, sampler testSampler);

layout (set = 0, binding = 0) uniform texture2D testTexture;

layout (set = 0, binding = 0) uniform sampler testSampler;

layout (location = 0) out vec4 outColor;

void main() {
	//Input

	//Entry point call
	FragmentOut _entryPointOutput = testStandardFunctions(testTexture, testSampler);

	//Output
	outColor = _entryPointOutput.outColor;
}

FragmentOut testStandardFunctions(texture2D testTexture, sampler testSampler) {
	int absTest = abs(0);
	float16_t absTestHalf = abs(float16_t(0.000000));
	float acosTest = acos(0.000000);
	float acoshTest = acosh(0.000000);
	float asinTest = asin(0.000000);
	float asinhTest = asinh(0.000000);
	float atanTest = atan(0.000000);
	float atanhTest = atanh(0.000000);
	float ceilTest = ceil(0.000000);
	float clampTest = clamp(0.000000, 0.000000, 0.000000);
	float cosTest = cos(0.000000);
	float coshTest = cosh(0.000000);
	vec3 crossTest = cross(vec3(0.000000), vec3(0.000000));
	float distanceTest = distance(vec3(0.000000), vec3(0.000000));
	float dotTest = dot(vec3(0.000000), vec3(0.000000));
	float expTest = exp(0.000000);
	float exp2Test = exp2(0.000000);
	float floorTest = floor(0.000000);
	float fractTest = fract(0.000000);
	bool isinfTest = isinf(0.000000);
	bool isnanTest = isnan(0.000000);
	float lengthTest = length(vec3(0.000000));
	float logTest = log(0.000000);
	float log2Test = log2(0.000000);
	float maxTest = max(0.000000, 0.000000);
	float minTest = min(0.000000, 0.000000);
	float mixTest = mix(0.000000, 0.000000, 0.000000);
	vec3 normalizeTest = normalize(vec3(0.000000));
	float powTest = pow(0.000000, 0.000000);
	vec3 reflectTest = reflect(vec3(0.000000), vec3(0.000000));
	vec3 refractTest = refract(vec3(0.000000), vec3(0.000000), 0.000000);
	float roundTest = round(0.000000);
	vec4 sampleTest = texture(sampler2D(testTexture, testSampler), vec2(0.000000));
	float signTest = sign(0.000000);
	float sinTest = sin(0.000000);
	float sinhTest = sinh(0.000000);
	float smoothstepTest = smoothstep(0.000000, 0.000000, 0.000000);
	float sqrtTest = sqrt(0.000000);
	float stepTest = step(0.000000, 0.000000);
	float tanTest = tan(0.000000);
	float tanhTest = tanh(0.000000);
	FragmentOut fragmentOut;
	fragmentOut.outColor = vec4(0.000000, 0.000000, 0.000000, 1.000000);
	return fragmentOut;
}

