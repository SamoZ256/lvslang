struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut testStandardFunctions(texture2d<float> testTexture, sampler testSampler) {
    int absTest = abs(0);
    float acosTest = acos(0.0);
    float acoshTest = acosh(0.0);
    float asinTest = asin(0.0);
    float asinhTest = asinh(0.0);
    float atanTest = atan(0.0);
    float atanhTest = atanh(0.0);
    float ceilTest = ceil(0.0);
    float clampTest = clamp(0.0, 0.0, 0.0);
    float cosTest = cos(0.0);
    float coshTest = cosh(0.0);
    float3 crossTest = cross(float3(0.0), float3(0.0));
    float degreesTest = degrees(0.0);
    float distanceTest = distance(float3(0.0), float3(0.0));
    float dotTest = dot(float3(0.0), float3(0.0));
    float expTest = exp(0.0);
    float exp2Test = exp2(0.0);
    float floorTest = floor(0.0);
    float fractTest = fract(0.0);
    float sinTest = sin(0.0);
    float4 sampleTest = sample(testTexture, testSampler, float2(0.0));

    struct FragmentOut fragmentOut;
    fragmentOut.outColor = float4(0.0, 0.0, 0.0, 1.0);

    return fragmentOut;
}
