struct ViewProj {
    float4x4 projection;
    float4x4 view;
};

struct VertexIn {
    float2 pos [[attribute(0)]];
    float2 texCoord [[attribute(1)]];
};

struct VertexOut {
    float4 pos [[position]];
    float2 texCoord;
};

vertex struct VertexOut vertexMain(struct VertexIn vertexIn [[stage_in]],
                                   constant struct ViewProj* viewProj [[descriptor_set(0, 0)]],
                                   constant float4x4* model [[descriptor_set(1, 0)]]) {
    struct VertexOut vertexOut;
    vertexOut.pos = viewProj->projection * viewProj->view * *model * float4(vertexIn.pos, 0.0, 1.0);
    vertexOut.texCoord = vertexIn.texCoord;

    return vertexOut;
};

fragment float4 fragmentMain(struct VertexOut fragmentIn [[stage_in]],
                                         texture2d<half> colorTexture [[descriptor_set(0, 1)]],
                                         sampler colorSampler [[descriptor_set(1, 0)]]) {
    return float4(sample(colorTexture, colorSampler, fragmentIn.texCoord));
}
