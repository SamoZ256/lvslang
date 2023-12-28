struct Model {
    float2 pos;
    float2 scale;
};

struct VertexIn {
    float2 pos [[location(0)]];
    float2 texCoord [[location(1)]];
};

struct VertexOut {
    float4 pos [[position]];
    float2 texCoord;
};

vertex struct VertexOut vertexMain(struct VertexIn vertexIn [[input]],
                                   constant struct Model* model [[descriptor_set(0, 0)]]) {
    struct VertexOut vertexOut;
    vertexOut.pos = float4(model->pos.x + vertexIn.pos.x * model->scale.x, model->pos.y + vertexIn.pos.y * model->scale.y, 0.0, 1.0);
    vertexOut.texCoord = vertexIn.texCoord;

    return vertexOut;
};

struct FragmentOut {
    float4 color;
};

fragment struct FragmentOut fragmentMain(struct VertexOut fragmentIn [[input]],
                                         texture2d<float> colorTexture [[descriptor_set(0, 1)]],
                                         sampler colorSampler [[descriptor_set(1, 0)]]) {
    struct FragmentOut fragmentOut;
    fragmentOut.color = sample(colorTexture, colorSampler, fragmentIn.texCoord);

    return fragmentOut;
}
