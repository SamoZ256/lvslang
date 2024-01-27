//TODO: add overloads

STD_FUNCTION int abs(int x);

STD_FUNCTION float acos(float x);

STD_FUNCTION float acosh(float x);

STD_FUNCTION float asin(float x);

STD_FUNCTION float asinh(float x);

STD_FUNCTION float atan(float x);

STD_FUNCTION float atanh(float x);

STD_FUNCTION float ceil(float x);

STD_FUNCTION float clamp(float x, float minVal, float maxVal);

STD_FUNCTION float cos(float x);

STD_FUNCTION float cosh(float x);

STD_FUNCTION float3 cross(float3 x, float3 y);

STD_FUNCTION float distance(float3 x, float3 y);

STD_FUNCTION float dot(float3 x, float3 y);

STD_FUNCTION float exp(float x);

STD_FUNCTION float exp2(float x);

STD_FUNCTION float floor(float x);

STD_FUNCTION float fract(float x);

STD_FUNCTION bool isinf(float x);

STD_FUNCTION bool isnan(float x);

STD_FUNCTION float length(float3 x);

STD_FUNCTION float log(float x);

STD_FUNCTION float log2(float x);

STD_FUNCTION float max(float x, float y);

STD_FUNCTION float min(float x, float y);

STD_FUNCTION float mix(float x, float y, float a);

STD_FUNCTION float3 normalize(float3 x);

STD_FUNCTION float pow(float x, float y);

STD_FUNCTION float3 reflect(float3 I, float3 N);

STD_FUNCTION float3 refract(float3 I, float3 N, float eta);

STD_FUNCTION float round(float x);

STD_FUNCTION float4 sample(texture2d<float> texture, sampler samplr, float2 coord);

STD_FUNCTION float sign(float x);

STD_FUNCTION float sin(float x);

STD_FUNCTION float sinh(float x);

STD_FUNCTION float smoothstep(float edge0, float edge1, float x);

STD_FUNCTION float sqrt(float x);

STD_FUNCTION float step(float edge, float x);

STD_FUNCTION float tan(float x);

STD_FUNCTION float tanh(float x);
