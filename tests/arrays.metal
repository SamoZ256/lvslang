struct MyBuffer {
    float a[32];
    int i;
};

struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut testArrays(constant struct MyBuffer* myBuffer [[descriptor_set(0, 0)]]) {
    float4 outColor;

    int multiArray[32][32];
    multiArray[10][myBuffer->i] = 1;

    struct FragmentOut fragmentOut;
    fragmentOut.outColor = float4(myBuffer->a[0], 0.0, 0.0, 1.0);

    return fragmentOut;
}
