struct MyBuffer {
    float a;
};

struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut testControlFlow(constant struct MyBuffer* myBuffer [[descriptor_set(0, 0)]]) {
    float4 outColor;

    if (myBuffer->a > 0.0)
        outColor = float4(1.0, 0.0, 0.0, 1.0);
    else if (myBuffer->a < 0.0)
        outColor = float4(0.0, 1.0, 0.0, 1.0);
    else
        outColor = float4(0.0, 0.0, 1.0, 1.0);
    int i = 0;
    while (i < 10)
        i = i + 1;

    if (myBuffer->a > 0.0) {
        outColor = float4(1.0, 0.0, 0.0, 1.0);
    } else if (myBuffer->a < 0.0) {
        outColor = float4(0.0, 1.0, 0.0, 1.0);
    } else {
        outColor = float4(0.0, 0.0, 1.0, 1.0);
    } while (i < 10) {
        i = i + 1;
    }

    struct FragmentOut fragmentOut;
    fragmentOut.outColor = outColor;

    return fragmentOut;
}
