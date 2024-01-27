struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut testStandardFunctions(texture2d<float> testTexture, sampler testSampler) {
    char absTestChar = abs(char(0));
    char2 absTestChar2 = abs(char2(0));
    char3 absTestChar3 = abs(char3(0));
    char4 absTestChar4 = abs(char4(0));
    short absTestShort = abs(short(0));
    short2 absTestShort2 = abs(short2(0));
    short3 absTestShort3 = abs(short3(0));
    short4 absTestShort4 = abs(short4(0));
    int absTestInt = abs(int(0));
    int2 absTestInt2 = abs(int2(0));
    int3 absTestInt3 = abs(int3(0));
    int4 absTestInt4 = abs(int4(0));
    half absTestHalf = abs(half(0.0));
    half2 absTestHalf2 = abs(half2(0.0));
    half3 absTestHalf3 = abs(half3(0.0));
    half4 absTestHalf4 = abs(half4(0.0));
    float absTestFloat = abs(float(0.0));
    float2 absTestFloat2 = abs(float2(0.0));
    float3 absTestFloat3 = abs(float3(0.0));
    float4 absTestFloat4 = abs(float4(0.0));

    float acosTest = acos(0.0);

    float acoshTest = acosh(0.0);

    float asinTest = asin(0.0);

    float asinhTest = asinh(0.0);

    float atanTest = atan(0.0);

    float atanhTest = atanh(0.0);
    
    half ceilTestHalf = ceil(half(0.0));
    half2 ceilTestHalf2 = ceil(half2(0.0));
    half3 ceilTestHalf3 = ceil(half3(0.0));
    half4 ceilTestHalf4 = ceil(half4(0.0));
    float ceilTestFloat = ceil(float(0.0));
    float2 ceilTestFloat2 = ceil(float2(0.0));
    float3 ceilTestFloat3 = ceil(float3(0.0));
    float4 ceilTestFloat4 = ceil(float4(0.0));

    char clampTestChar = clamp(char(0), char(0), char(0));
    char2 clampTestChar2 = clamp(char2(0), char2(0), char2(0));
    char3 clampTestChar3 = clamp(char3(0), char3(0), char3(0));
    char4 clampTestChar4 = clamp(char4(0), char4(0), char4(0));
    short clampTestShort = clamp(short(0), short(0), short(0));
    short2 clampTestShort2 = clamp(short2(0), short2(0), short2(0));
    short3 clampTestShort3 = clamp(short3(0), short3(0), short3(0));
    short4 clampTestShort4 = clamp(short4(0), short4(0), short4(0));
    int clampTestInt = clamp(int(0), int(0), int(0));
    int2 clampTestInt2 = clamp(int2(0), int2(0), int2(0));
    int3 clampTestInt3 = clamp(int3(0), int3(0), int3(0));
    int4 clampTestInt4 = clamp(int4(0), int4(0), int4(0));
    half clampTestHalf = clamp(half(0.0), half(0.0), half(0.0));
    half2 clampTestHalf2 = clamp(half2(0.0), half2(0.0), half2(0.0));
    half3 clampTestHalf3 = clamp(half3(0.0), half3(0.0), half3(0.0));
    half4 clampTestHalf4 = clamp(half4(0.0), half4(0.0), half4(0.0));
    float clampTestFloat = clamp(float(0.0), float(0.0), float(0.0));
    float2 clampTestFloat2 = clamp(float2(0.0), float2(0.0), float2(0.0));
    float3 clampTestFloat3 = clamp(float3(0.0), float3(0.0), float3(0.0));
    float4 clampTestFloat4 = clamp(float4(0.0), float4(0.0), float4(0.0));

    float cosTest = cos(0.0);

    float coshTest = cosh(0.0);

    half3 crossTestHalf3 = cross(half3(0.0), half3(0.0));
    float3 crossTestFloat3 = cross(float3(0.0), float3(0.0));

    half distanceTestHalf2 = distance(half2(0.0), half2(0.0));
    half distanceTestHalf3 = distance(half3(0.0), half3(0.0));
    half distanceTestHalf4 = distance(half4(0.0), half4(0.0));
    float distanceTestFloat2 = distance(float2(0.0), float2(0.0));
    float distanceTestFloat3 = distance(float3(0.0), float3(0.0));
    float distanceTestFloat4 = distance(float4(0.0), float4(0.0));

    half dotTestHalf2 = dot(half2(0.0), half2(0.0));
    half dotTestHalf3 = dot(half3(0.0), half3(0.0));
    half dotTestHalf4 = dot(half4(0.0), half4(0.0));
    float dotTestFloat2 = dot(float2(0.0), float2(0.0));
    float dotTestFloat3 = dot(float3(0.0), float3(0.0));
    float dotTestFloat4 = dot(float4(0.0), float4(0.0));

    half expTestHalf = exp(half(0.0));
    half2 expTestHalf2 = exp(half2(0.0));
    half3 expTestHalf3 = exp(half3(0.0));
    half4 expTestHalf4 = exp(half4(0.0));
    float expTestFloat = exp(float(0.0));
    float2 expTestFloat2 = exp(float2(0.0));
    float3 expTestFloat3 = exp(float3(0.0));
    float4 expTestFloat4 = exp(float4(0.0));

    half exp2TestHalf = exp2(half(0.0));
    half2 exp2TestHalf2 = exp2(half2(0.0));
    half3 exp2TestHalf3 = exp2(half3(0.0));
    half4 exp2TestHalf4 = exp2(half4(0.0));
    float exp2TestFloat = exp2(float(0.0));
    float2 exp2TestFloat2 = exp2(float2(0.0));
    float3 exp2TestFloat3 = exp2(float3(0.0));
    float4 exp2TestFloat4 = exp2(float4(0.0));

    half floorTestHalf = floor(half(0.0));
    half2 floorTestHalf2 = floor(half2(0.0));
    half3 floorTestHalf3 = floor(half3(0.0));
    half4 floorTestHalf4 = floor(half4(0.0));
    float floorTestFloat = floor(float(0.0));
    float2 floorTestFloat2 = floor(float2(0.0));
    float3 floorTestFloat3 = floor(float3(0.0));
    float4 floorTestFloat4 = floor(float4(0.0));

    half fractTestHalf = fract(half(0.0));
    half2 fractTestHalf2 = fract(half2(0.0));
    half3 fractTestHalf3 = fract(half3(0.0));
    half4 fractTestHalf4 = fract(half4(0.0));
    float fractTestFloat = fract(float(0.0));
    float2 fractTestFloat2 = fract(float2(0.0));
    float3 fractTestFloat3 = fract(float3(0.0));
    float4 fractTestFloat4 = fract(float4(0.0));

    bool isinfTestHalf = isinf(half(0.0));
    bool2 isinfTestHalf2 = isinf(half2(0.0));
    bool3 isinfTestHalf3 = isinf(half3(0.0));
    bool4 isinfTestHalf4 = isinf(half4(0.0));
    bool isinfTestFloat = isinf(float(0.0));
    bool2 isinfTestFloat2 = isinf(float2(0.0));
    bool3 isinfTestFloat3 = isinf(float3(0.0));
    bool4 isinfTestFloat4 = isinf(float4(0.0));

    bool isnanTestHalf = isnan(half(0.0));
    bool2 isnanTestHalf2 = isnan(half2(0.0));
    bool3 isnanTestHalf3 = isnan(half3(0.0));
    bool4 isnanTestHalf4 = isnan(half4(0.0));
    bool isnanTestFloat = isnan(float(0.0));
    bool2 isnanTestFloat2 = isnan(float2(0.0));
    bool3 isnanTestFloat3 = isnan(float3(0.0));
    bool4 isnanTestFloat4 = isnan(float4(0.0));

    half lengthTestHalf2 = length(half2(0.0));
    half lengthTestHalf3 = length(half3(0.0));
    half lengthTestHalf4 = length(half4(0.0));
    float lengthTestFloat2 = length(float2(0.0));
    float lengthTestFloat3 = length(float3(0.0));
    float lengthTestFloat4 = length(float4(0.0));

    //TODO: test log and log2

    char maxTestChar = max(char(0), char(0));
    char2 maxTestChar2 = max(char2(0), char2(0));
    char3 maxTestChar3 = max(char3(0), char3(0));
    char4 maxTestChar4 = max(char4(0), char4(0));
    short maxTestShort = max(short(0), short(0));
    short2 maxTestShort2 = max(short2(0), short2(0));
    short3 maxTestShort3 = max(short3(0), short3(0));
    short4 maxTestShort4 = max(short4(0), short4(0));
    int maxTestInt = max(int(0), int(0));
    int2 maxTestInt2 = max(int2(0), int2(0));
    int3 maxTestInt3 = max(int3(0), int3(0));
    int4 maxTestInt4 = max(int4(0), int4(0));
    half maxTestHalf = max(half(0.0), half(0.0));
    half2 maxTestHalf2 = max(half2(0.0), half2(0.0));
    half3 maxTestHalf3 = max(half3(0.0), half3(0.0));
    half4 maxTestHalf4 = max(half4(0.0), half4(0.0));
    float maxTestFloat = max(float(0.0), float(0.0));
    float2 maxTestFloat2 = max(float2(0.0), float2(0.0));
    float3 maxTestFloat3 = max(float3(0.0), float3(0.0));
    float4 maxTestFloat4 = max(float4(0.0), float4(0.0));

    char minTestChar = min(char(0), char(0));
    char2 minTestChar2 = min(char2(0), char2(0));
    char3 minTestChar3 = min(char3(0), char3(0));
    char4 minTestChar4 = min(char4(0), char4(0));
    short minTestShort = min(short(0), short(0));
    short2 minTestShort2 = min(short2(0), short2(0));
    short3 minTestShort3 = min(short3(0), short3(0));
    short4 minTestShort4 = min(short4(0), short4(0));
    int minTestInt = min(int(0), int(0));
    int2 minTestInt2 = min(int2(0), int2(0));
    int3 minTestInt3 = min(int3(0), int3(0));
    int4 minTestInt4 = min(int4(0), int4(0));
    half minTestHalf = min(half(0.0), half(0.0));
    half2 minTestHalf2 = min(half2(0.0), half2(0.0));
    half3 minTestHalf3 = min(half3(0.0), half3(0.0));
    half4 minTestHalf4 = min(half4(0.0), half4(0.0));
    float minTestFloat = min(float(0.0), float(0.0));
    float2 minTestFloat2 = min(float2(0.0), float2(0.0));
    float3 minTestFloat3 = min(float3(0.0), float3(0.0));
    float4 minTestFloat4 = min(float4(0.0), float4(0.0));
    
    half mixTestHalf = mix(half(0.0), half(0.0), half(0.0));
    half2 mixTestHalf2 = mix(half2(0.0), half2(0.0), half2(0.0));
    half3 mixTestHalf3 = mix(half3(0.0), half3(0.0), half3(0.0));
    half4 mixTestHalf4 = mix(half4(0.0), half4(0.0), half4(0.0));
    float mixTestFloat = mix(float(0.0), float(0.0), float(0.0));
    float2 mixTestFloat2 = mix(float2(0.0), float2(0.0), float2(0.0));
    float3 mixTestFloat3 = mix(float3(0.0), float3(0.0), float3(0.0));
    float4 mixTestFloat4 = mix(float4(0.0), float4(0.0), float4(0.0));

    half2 normalizeTestHalf2 = normalize(half2(0.0));
    half3 normalizeTestHalf3 = normalize(half3(0.0));
    half4 normalizeTestHalf4 = normalize(half4(0.0));
    float2 normalizeTestFloat2 = normalize(float2(0.0));
    float3 normalizeTestFloat3 = normalize(float3(0.0));
    float4 normalizeTestFloat4 = normalize(float4(0.0));

    half powTestHalf = pow(half(0.0), half(0.0));
    half2 powTestHalf2 = pow(half2(0.0), half2(0.0));
    half3 powTestHalf3 = pow(half3(0.0), half3(0.0));
    half4 powTestHalf4 = pow(half4(0.0), half4(0.0));
    float powTestFloat = pow(float(0.0), float(0.0));
    float2 powTestFloat2 = pow(float2(0.0), float2(0.0));
    float3 powTestFloat3 = pow(float3(0.0), float3(0.0));
    float4 powTestFloat4 = pow(float4(0.0), float4(0.0));

    half2 reflectTestHalf2 = reflect(half2(0.0), half2(0.0));
    half3 reflectTestHalf3 = reflect(half3(0.0), half3(0.0));
    half4 reflectTestHalf4 = reflect(half4(0.0), half4(0.0));
    float2 reflectTestFloat2 = reflect(float2(0.0), float2(0.0));
    float3 reflectTestFloat3 = reflect(float3(0.0), float3(0.0));
    float4 reflectTestFloat4 = reflect(float4(0.0), float4(0.0));

    half2 refractTestHalf2 = refract(half2(0.0), half2(0.0), half(0.0));
    half3 refractTestHalf3 = refract(half3(0.0), half3(0.0), half(0.0));
    half4 refractTestHalf4 = refract(half4(0.0), half4(0.0), half(0.0));
    float2 refractTestFloat2 = refract(float2(0.0), float2(0.0), float(0.0));
    float3 refractTestFloat3 = refract(float3(0.0), float3(0.0), float(0.0));
    float4 refractTestFloat4 = refract(float4(0.0), float4(0.0), float(0.0));

    half roundTestHalf = round(half(0.0));
    half2 roundTestHalf2 = round(half2(0.0));
    half3 roundTestHalf3 = round(half3(0.0));
    half4 roundTestHalf4 = round(half4(0.0));
    float roundTestFloat = round(float(0.0));
    float2 roundTestFloat2 = round(float2(0.0));
    float3 roundTestFloat3 = round(float3(0.0));
    float4 roundTestFloat4 = round(float4(0.0));

    float4 sampleTest = sample(testTexture, testSampler, float2(0.0));

    char signTestChar = sign(char(0));
    char2 signTestChar2 = sign(char2(0));
    char3 signTestChar3 = sign(char3(0));
    char4 signTestChar4 = sign(char4(0));
    short signTestShort = sign(short(0));
    short2 signTestShort2 = sign(short2(0));
    short3 signTestShort3 = sign(short3(0));
    short4 signTestShort4 = sign(short4(0));
    int signTestInt = sign(int(0));
    int2 signTestInt2 = sign(int2(0));
    int3 signTestInt3 = sign(int3(0));
    int4 signTestInt4 = sign(int4(0));
    half signTestHalf = sign(half(0.0));
    half2 signTestHalf2 = sign(half2(0.0));
    half3 signTestHalf3 = sign(half3(0.0));
    half4 signTestHalf4 = sign(half4(0.0));
    float signTestFloat = sign(float(0.0));
    float2 signTestFloat2 = sign(float2(0.0));
    float3 signTestFloat3 = sign(float3(0.0));
    float4 signTestFloat4 = sign(float4(0.0));

    float sinTest = sin(0.0);

    float sinhTest = sinh(0.0);

    half smoothstepTestHalf = smoothstep(half(0.0), half(0.0), half(0.0));
    half2 smoothstepTestHalf2 = smoothstep(half2(0.0), half2(0.0), half2(0.0));
    half3 smoothstepTestHalf3 = smoothstep(half3(0.0), half3(0.0), half3(0.0));
    half4 smoothstepTestHalf4 = smoothstep(half4(0.0), half4(0.0), half4(0.0));
    float smoothstepTestFloat = smoothstep(float(0.0), float(0.0), float(0.0));
    float2 smoothstepTestFloat2 = smoothstep(float2(0.0), float2(0.0), float2(0.0));
    float3 smoothstepTestFloat3 = smoothstep(float3(0.0), float3(0.0), float3(0.0));
    float4 smoothstepTestFloat4 = smoothstep(float4(0.0), float4(0.0), float4(0.0));

    half sqrtTestHalf = sqrt(half(0.0));
    half2 sqrtTestHalf2 = sqrt(half2(0.0));
    half3 sqrtTestHalf3 = sqrt(half3(0.0));
    half4 sqrtTestHalf4 = sqrt(half4(0.0));
    float sqrtTestFloat = sqrt(float(0.0));
    float2 sqrtTestFloat2 = sqrt(float2(0.0));
    float3 sqrtTestFloat3 = sqrt(float3(0.0));
    float4 sqrtTestFloat4 = sqrt(float4(0.0));

    half stepTestHalf = step(half(0.0), half(0.0));
    half2 stepTestHalf2 = step(half2(0.0), half2(0.0));
    half3 stepTestHalf3 = step(half3(0.0), half3(0.0));
    half4 stepTestHalf4 = step(half4(0.0), half4(0.0));
    float stepTestFloat = step(float(0.0), float(0.0));
    float2 stepTestFloat2 = step(float2(0.0), float2(0.0));
    float3 stepTestFloat3 = step(float3(0.0), float3(0.0));
    float4 stepTestFloat4 = step(float4(0.0), float4(0.0));

    float tanTest = tan(0.0);

    float tanhTest = tanh(0.0);

    struct FragmentOut fragmentOut;
    fragmentOut.outColor = float4(0.0, 0.0, 0.0, 1.0);

    return fragmentOut;
}
