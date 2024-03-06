struct MyBuffer {
    float a[32];
    int i;
};

fragment float4 testArrays(constant struct MyBuffer* myBuffer [[descriptor_set(0, 0)]]) {
    float4 outColor;

    int multiArray[32][32];
    multiArray[10][myBuffer->i] = 1;

    return float4(myBuffer->a[0], 0.0, 0.0, 1.0);
}
