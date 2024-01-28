struct MyBuffer {
    float a;
};

struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut testControlFlow(constant struct MyBuffer* myBuffer [[descriptor_set(0, 0)]]) {
    struct FragmentOut fragmentOut;
    fragmentOut.outColor = float4(0.0, 0.0, 0.0, 1.0);

    //Initialize
    float4 vec1 = float4(1.0, 2.0, 3.0, 4.0);
    float4 vec2 = float4(5.0, 6.0, 7.0, 8.0);

    //Addition
    float4 sum = vec1 + vec2;
    if (sum == float4(6.0, 8.0, 10.0, 12.0))
        fragmentOut.outColor.r = 1.0;

    //Subtraction
    float4 diff = vec2 - vec1;
    if (diff == float4(4.0, 4.0, 4.0, 4.0))
        fragmentOut.outColor.g = 1.0;

    //Scalar multiplication
    float4 scaled = vec1 * 2.0;
    if (scaled == float4(2.0, 4.0, 6.0, 8.0))
        fragmentOut.outColor.b = 1.0;

    //Swizzling
    float4 swizzled = vec1.yxwz;
    vec1.xz = vec2.yw;

    return fragmentOut;
}
