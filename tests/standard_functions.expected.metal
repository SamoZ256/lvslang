#include <metal_stdlib>
using namespace metal;

struct FragmentOut {
	float4 outColor [[color(0)]];
};

fragment FragmentOut testStandardFunctions(texture2d<float> testTexture [[texture(0)]], sampler testSampler [[sampler(0)]]) {
	int absTest = abs(0);
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
	float3 crossTest = cross(float3(0.000000), float3(0.000000));
	float distanceTest = distance(float3(0.000000), float3(0.000000));
	float dotTest = dot(float3(0.000000), float3(0.000000));
	float expTest = exp(0.000000);
	float exp2Test = exp2(0.000000);
	float floorTest = floor(0.000000);
	float fractTest = fract(0.000000);
	bool isinfTest = isinf(0.000000);
	bool isnanTest = isnan(0.000000);
	float lengthTest = length(float3(0.000000));
	float logTest = log(0.000000);
	float log2Test = log2(0.000000);
	float maxTest = max(0.000000, 0.000000);
	float minTest = min(0.000000, 0.000000);
	float mixTest = mix(0.000000, 0.000000, 0.000000);
	float3 normalizeTest = normalize(float3(0.000000));
	float powTest = pow(0.000000, 0.000000);
	float3 reflectTest = reflect(float3(0.000000), float3(0.000000));
	float3 refractTest = refract(float3(0.000000), float3(0.000000), 0.000000);
	float roundTest = round(0.000000);
	float4 sampleTest = testTexture.sample(testSampler, float2(0.000000));
	float signTest = sign(0.000000);
	float sinTest = sin(0.000000);
	float sinhTest = sinh(0.000000);
	float smoothstepTest = smoothstep(0.000000, 0.000000, 0.000000);
	float sqrtTest = sqrt(0.000000);
	float stepTest = step(0.000000, 0.000000);
	float tanTest = tan(0.000000);
	float tanhTest = tanh(0.000000);
	FragmentOut fragmentOut;
	fragmentOut.outColor = float4(0.000000, 0.000000, 0.000000, 1.000000);
	return fragmentOut;
}

