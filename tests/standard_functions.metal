struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut testStandardFunctions(texture2d<float> testTexture, sampler testSampler) {
    abs(0);
    acos(0.0);
    acosh(0.0);
    asin(0.0);
    asinh(0.0);
    atan(0.0);
    atanh(0.0);
    ceil(0.0);
    clamp(0.0, 0.0, 0.0);
    cos(0.0);
    cosh(0.0);
    cross(float3(0.0), float3(0.0));
    degrees(0.0);
    distance(0.0, 0.0);
    dot(float3(0.0), float3(0.0));
    exp(0.0);
    exp2(0.0);
    floor(0.0);
    fract(0.0);
    sin(0.0);
    sample(testTexture, testSampler, float2(0.0));

    struct FragmentOut fragmentOut;
    fragmentOut.outColor = float4(0.0, 0.0, 0.0, 1.0);

    return fragmentOut;
}