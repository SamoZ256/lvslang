fragment float4 testVectors() {
    float4 outColor = float4(0.0, 0.0, 0.0, 1.0);

    // Initialization
    float4 vec1 = float4(1.0, 2.0, 3.0, 4.0);
    float4 vec2 = float4(5.0, 6.0, 7.0, 8.0);

    // Addition
    float4 sum = vec1 + vec2;
    if (sum == float4(6.0, 8.0, 10.0, 12.0))
        outColor.r = 1.0;

    // Subtraction
    float4 diff = vec2 - vec1;
    if (diff == float4(4.0, 4.0, 4.0, 4.0))
        outColor.g = 1.0;

    // Scalar multiplication
    float4 scaled = vec1 * 2.0;
    if (scaled == float4(2.0, 4.0, 6.0, 8.0))
        outColor.b = 1.0;

    // Swizzling
    float4 swizzled = vec1.yxwz;
    vec1.xz = vec2.yw;

    return outColor;
}
