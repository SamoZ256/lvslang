struct VertexOut {
    float4 pos [[position]];
    float2 texCoord;
};

fragment float4 fragmentMain(struct VertexOut fragmentIn [[stage_in]],
                              texture2d<float> tex [[descriptor_set(0, 0)]],
                              sampler smp [[descriptor_set(0, 1)]]) {
    return sample(tex, smp, fragmentIn.texCoord);
}
