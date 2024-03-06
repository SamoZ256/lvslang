struct Model {
    float2 pos;
    float2 scale;
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
                                   constant struct Model* model [[descriptor_set(0, 0)]]) {
    struct VertexOut vertexOut;
    vertexOut.pos = float4(model->pos + vertexIn.pos * model->scale, 0.0, 1.0);
    vertexOut.texCoord = vertexIn.texCoord;

    return vertexOut;
};

fragment float4 fragmentMain(struct VertexOut fragmentIn [[stage_in]],
                             texture2d<float> colorTexture [[descriptor_set(0, 1)]],
                             sampler colorSampler [[descriptor_set(1, 0)]]) {
    return sample(colorTexture, colorSampler, fragmentIn.texCoord);
}
