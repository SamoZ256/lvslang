struct Model {
    float2 pos
    float2 scale
}

struct VertexIn {
    float2 [[location(0)]] pos
    float2 [[location(1)]] texCoord
}

struct VertexOut {
    float4 [[position]] pos
    float2 texCoord
}

vertex struct VertexOut vertexMain(struct VertexIn [[input]] vertexIn,
                  constant buffer struct Model* [[descriptor_set(0, 0)]] model) {
    struct VertexOut vertexOut
    vertexOut.pos = float4(model->pos.x + vertexIn.pos.x * model->scale.x, model->pos.y + vertexIn.pos.y * model->scale.y, 0.0, 1.0)
    vertexOut.texCoord = vertexIn.texCoord

    return vertexOut
}

struct FragmentOut {
    float4 color
}

fragment struct FragmentOut fragmentMain(struct VertexOut [[input]] fragmentIn,
                      texture2D<float> [[descriptor_set(0, 1)]]colorTexture,
                      sampler [[descriptor_set(1, 0)]] colorSampler) {
    struct FragmentOut fragmentOut
    fragmentOut.color = sample(colorTexture, colorSampler, fragmentIn.texCoord)

    return fragmentOut
}
