struct VertexOut {
    float4 pos [[position]];
    float2 texCoord;
};

fragment float4 fragmentMain(struct VertexOut fragmentIn [[stage_in]],
                             texture2d<float              > tex1 [[descriptor_set(1, 0)]],
                             texture2d<float, access::read> tex2 [[descriptor_set(1, 1)]],
                             sampler smp [[descriptor_set(0, 0)]]) {
    float4 sampled1 = sample(tex1, smp, fragmentIn.texCoord, struct bias(0.2), int2(64));
    float4 sampled2 = read(tex2, ushort2(0));
    
    return sampled1 * sampled2;
}
