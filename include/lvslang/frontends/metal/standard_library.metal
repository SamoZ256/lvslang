STD_FUNCTION char abs(char x);
STD_FUNCTION char2 abs(char2 x);
STD_FUNCTION char3 abs(char3 x);
STD_FUNCTION char4 abs(char4 x);
STD_FUNCTION short abs(short x);
STD_FUNCTION short2 abs(short2 x);
STD_FUNCTION short3 abs(short3 x);
STD_FUNCTION short4 abs(short4 x);
STD_FUNCTION int abs(int x);
STD_FUNCTION int2 abs(int2 x);
STD_FUNCTION int3 abs(int3 x);
STD_FUNCTION int4 abs(int4 x);
STD_FUNCTION half abs(half x);
STD_FUNCTION half2 abs(half2 x);
STD_FUNCTION half3 abs(half3 x);
STD_FUNCTION half4 abs(half4 x);
STD_FUNCTION float abs(float x);
STD_FUNCTION float2 abs(float2 x);
STD_FUNCTION float3 abs(float3 x);
STD_FUNCTION float4 abs(float4 x);

STD_FUNCTION float acos(float x);

STD_FUNCTION float acosh(float x);

STD_FUNCTION float asin(float x);

STD_FUNCTION float asinh(float x);

STD_FUNCTION float atan(float x);

STD_FUNCTION float atanh(float x);

STD_FUNCTION half ceil(half x);
STD_FUNCTION half2 ceil(half2 x);
STD_FUNCTION half3 ceil(half3 x);
STD_FUNCTION half4 ceil(half4 x);
STD_FUNCTION float ceil(float x);
STD_FUNCTION float2 ceil(float2 x);
STD_FUNCTION float3 ceil(float3 x);
STD_FUNCTION float4 ceil(float4 x);

STD_FUNCTION char clamp(char x, char minVal, char maxVal);
STD_FUNCTION char2 clamp(char2 x, char2 minVal, char2 maxVal);
STD_FUNCTION char3 clamp(char3 x, char3 minVal, char3 maxVal);
STD_FUNCTION char4 clamp(char4 x, char4 minVal, char4 maxVal);
STD_FUNCTION short clamp(short x, short minVal, short maxVal);
STD_FUNCTION short2 clamp(short2 x, short2 minVal, short2 maxVal);
STD_FUNCTION short3 clamp(short3 x, short3 minVal, short3 maxVal);
STD_FUNCTION short4 clamp(short4 x, short4 minVal, short4 maxVal);
STD_FUNCTION int clamp(int x, int minVal, int maxVal);
STD_FUNCTION int2 clamp(int2 x, int2 minVal, int2 maxVal);
STD_FUNCTION int3 clamp(int3 x, int3 minVal, int3 maxVal);
STD_FUNCTION int4 clamp(int4 x, int4 minVal, int4 maxVal);
STD_FUNCTION half clamp(half x, half minVal, half maxVal);
STD_FUNCTION half2 clamp(half2 x, half2 minVal, half2 maxVal);
STD_FUNCTION half3 clamp(half3 x, half3 minVal, half3 maxVal);
STD_FUNCTION half4 clamp(half4 x, half4 minVal, half4 maxVal);
STD_FUNCTION float clamp(float x, float minVal, float maxVal);
STD_FUNCTION float2 clamp(float2 x, float2 minVal, float2 maxVal);
STD_FUNCTION float3 clamp(float3 x, float3 minVal, float3 maxVal);
STD_FUNCTION float4 clamp(float4 x, float4 minVal, float4 maxVal);

STD_FUNCTION float cos(float x);

STD_FUNCTION float cosh(float x);

STD_FUNCTION half3 cross(half3 x, half3 y);
STD_FUNCTION float3 cross(float3 x, float3 y);

//TODO: add determinant function

STD_FUNCTION half distance(half2 x, half2 y);
STD_FUNCTION half distance(half3 x, half3 y);
STD_FUNCTION half distance(half4 x, half4 y);
STD_FUNCTION float distance(float2 x, float2 y);
STD_FUNCTION float distance(float3 x, float3 y);
STD_FUNCTION float distance(float4 x, float4 y);

STD_FUNCTION half dot(half2 x, half2 y);
STD_FUNCTION half dot(half3 x, half3 y);
STD_FUNCTION half dot(half4 x, half4 y);
STD_FUNCTION float dot(float2 x, float2 y);
STD_FUNCTION float dot(float3 x, float3 y);
STD_FUNCTION float dot(float4 x, float4 y);

STD_FUNCTION half exp(half x);
STD_FUNCTION half2 exp(half2 x);
STD_FUNCTION half3 exp(half3 x);
STD_FUNCTION half4 exp(half4 x);
STD_FUNCTION float exp(float x);
STD_FUNCTION float2 exp(float2 x);
STD_FUNCTION float3 exp(float3 x);
STD_FUNCTION float4 exp(float4 x);

STD_FUNCTION half exp2(half x);
STD_FUNCTION half2 exp2(half2 x);
STD_FUNCTION half3 exp2(half3 x);
STD_FUNCTION half4 exp2(half4 x);
STD_FUNCTION float exp2(float x);
STD_FUNCTION float2 exp2(float2 x);
STD_FUNCTION float3 exp2(float3 x);
STD_FUNCTION float4 exp2(float4 x);

STD_FUNCTION half floor(half x);
STD_FUNCTION half2 floor(half2 x);
STD_FUNCTION half3 floor(half3 x);
STD_FUNCTION half4 floor(half4 x);
STD_FUNCTION float floor(float x);
STD_FUNCTION float2 floor(float2 x);
STD_FUNCTION float3 floor(float3 x);
STD_FUNCTION float4 floor(float4 x);

STD_FUNCTION half fract(half x);
STD_FUNCTION half2 fract(half2 x);
STD_FUNCTION half3 fract(half3 x);
STD_FUNCTION half4 fract(half4 x);
STD_FUNCTION float fract(float x);
STD_FUNCTION float2 fract(float2 x);
STD_FUNCTION float3 fract(float3 x);
STD_FUNCTION float4 fract(float4 x);

//TODO: add image functions

STD_FUNCTION bool isinf(half x);
STD_FUNCTION bool2 isinf(half2 x);
STD_FUNCTION bool3 isinf(half3 x);
STD_FUNCTION bool4 isinf(half4 x);
STD_FUNCTION bool isinf(float x);
STD_FUNCTION bool2 isinf(float2 x);
STD_FUNCTION bool3 isinf(float3 x);
STD_FUNCTION bool4 isinf(float4 x);

STD_FUNCTION bool isnan(half x);
STD_FUNCTION bool2 isnan(half2 x);
STD_FUNCTION bool3 isnan(half3 x);
STD_FUNCTION bool4 isnan(half4 x);
STD_FUNCTION bool isnan(float x);
STD_FUNCTION bool2 isnan(float2 x);
STD_FUNCTION bool3 isnan(float3 x);
STD_FUNCTION bool4 isnan(float4 x);

STD_FUNCTION half length(half2 x);
STD_FUNCTION half length(half3 x);
STD_FUNCTION half length(half4 x);
STD_FUNCTION float length(float2 x);
STD_FUNCTION float length(float3 x);
STD_FUNCTION float length(float4 x);

STD_FUNCTION half log(half x);
STD_FUNCTION half2 log(half2 x);
STD_FUNCTION half3 log(half3 x);
STD_FUNCTION half4 log(half4 x);
STD_FUNCTION float log(float x);
STD_FUNCTION float2 log(float2 x);
STD_FUNCTION float3 log(float3 x);
STD_FUNCTION float4 log(float4 x);

STD_FUNCTION half log2(half x);
STD_FUNCTION half2 log2(half2 x);
STD_FUNCTION half3 log2(half3 x);
STD_FUNCTION half4 log2(half4 x);
STD_FUNCTION float log2(float x);
STD_FUNCTION float2 log2(float2 x);
STD_FUNCTION float3 log2(float3 x);
STD_FUNCTION float4 log2(float4 x);

STD_FUNCTION char max(char x, char y);
STD_FUNCTION char2 max(char2 x, char2 y);
STD_FUNCTION char3 max(char3 x, char3 y);
STD_FUNCTION char4 max(char4 x, char4 y);
STD_FUNCTION short max(short x, short y);
STD_FUNCTION short2 max(short2 x, short2 y);
STD_FUNCTION short3 max(short3 x, short3 y);
STD_FUNCTION short4 max(short4 x, short4 y);
STD_FUNCTION int max(int x, int y);
STD_FUNCTION int2 max(int2 x, int2 y);
STD_FUNCTION int3 max(int3 x, int3 y);
STD_FUNCTION int4 max(int4 x, int4 y);
STD_FUNCTION half max(half x, half y);
STD_FUNCTION half2 max(half2 x, half2 y);
STD_FUNCTION half3 max(half3 x, half3 y);
STD_FUNCTION half4 max(half4 x, half4 y);
STD_FUNCTION float max(float x, float y);
STD_FUNCTION float2 max(float2 x, float2 y);
STD_FUNCTION float3 max(float3 x, float3 y);
STD_FUNCTION float4 max(float4 x, float4 y);

STD_FUNCTION char min(char x, char y);
STD_FUNCTION char2 min(char2 x, char2 y);
STD_FUNCTION char3 min(char3 x, char3 y);
STD_FUNCTION char4 min(char4 x, char4 y);
STD_FUNCTION short min(short x, short y);
STD_FUNCTION short2 min(short2 x, short2 y);
STD_FUNCTION short3 min(short3 x, short3 y);
STD_FUNCTION short4 min(short4 x, short4 y);
STD_FUNCTION int min(int x, int y);
STD_FUNCTION int2 min(int2 x, int2 y);
STD_FUNCTION int3 min(int3 x, int3 y);
STD_FUNCTION int4 min(int4 x, int4 y);
STD_FUNCTION half min(half x, half y);
STD_FUNCTION half2 min(half2 x, half2 y);
STD_FUNCTION half3 min(half3 x, half3 y);
STD_FUNCTION half4 min(half4 x, half4 y);
STD_FUNCTION float min(float x, float y);
STD_FUNCTION float2 min(float2 x, float2 y);
STD_FUNCTION float3 min(float3 x, float3 y);
STD_FUNCTION float4 min(float4 x, float4 y);

STD_FUNCTION half mix(half x, half y, half a);
STD_FUNCTION half2 mix(half2 x, half2 y, half2 a);
STD_FUNCTION half3 mix(half3 x, half3 y, half3 a);
STD_FUNCTION half4 mix(half4 x, half4 y, half4 a);
STD_FUNCTION float mix(float x, float y, float a);
STD_FUNCTION float2 mix(float2 x, float2 y, float2 a);
STD_FUNCTION float3 mix(float3 x, float3 y, float3 a);
STD_FUNCTION float4 mix(float4 x, float4 y, float4 a);

STD_FUNCTION half2 normalize(half2 x);
STD_FUNCTION half3 normalize(half3 x);
STD_FUNCTION half4 normalize(half4 x);
STD_FUNCTION float2 normalize(float2 x);
STD_FUNCTION float3 normalize(float3 x);
STD_FUNCTION float4 normalize(float4 x);

STD_FUNCTION half pow(half x, half y);
STD_FUNCTION half2 pow(half2 x, half2 y);
STD_FUNCTION half3 pow(half3 x, half3 y);
STD_FUNCTION half4 pow(half4 x, half4 y);
STD_FUNCTION float pow(float x, float y);
STD_FUNCTION float2 pow(float2 x, float2 y);
STD_FUNCTION float3 pow(float3 x, float3 y);
STD_FUNCTION float4 pow(float4 x, float4 y);

STD_FUNCTION half2 reflect(half2 I, half2 N);
STD_FUNCTION half3 reflect(half3 I, half3 N);
STD_FUNCTION half4 reflect(half4 I, half4 N);
STD_FUNCTION float2 reflect(float2 I, float2 N);
STD_FUNCTION float3 reflect(float3 I, float3 N);
STD_FUNCTION float4 reflect(float4 I, float4 N);

STD_FUNCTION half2 refract(half2 I, half2 N, half eta);
STD_FUNCTION half3 refract(half3 I, half3 N, half eta);
STD_FUNCTION half4 refract(half4 I, half4 N, half eta);
STD_FUNCTION float2 refract(float2 I, float2 N, float eta);
STD_FUNCTION float3 refract(float3 I, float3 N, float eta);
STD_FUNCTION float4 refract(float4 I, float4 N, float eta);

STD_FUNCTION half round(half x);
STD_FUNCTION half2 round(half2 x);
STD_FUNCTION half3 round(half3 x);
STD_FUNCTION half4 round(half4 x);
STD_FUNCTION float round(float x);
STD_FUNCTION float2 round(float2 x);
STD_FUNCTION float3 round(float3 x);
STD_FUNCTION float4 round(float4 x);

//TODO: add more overloads
STD_FUNCTION char4 sample(texture2d<char> texture, sampler samplr, float2 coord);
STD_FUNCTION short4 sample(texture2d<short> texture, sampler samplr, float2 coord);
STD_FUNCTION int4 sample(texture2d<int> texture, sampler samplr, float2 coord);
STD_FUNCTION half4 sample(texture2d<half> texture, sampler samplr, float2 coord);
STD_FUNCTION float4 sample(texture2d<float> texture, sampler samplr, float2 coord);

//TODO: check if integers are supported
STD_FUNCTION char sign(char x);
STD_FUNCTION char2 sign(char2 x);
STD_FUNCTION char3 sign(char3 x);
STD_FUNCTION char4 sign(char4 x);
STD_FUNCTION short sign(short x);
STD_FUNCTION short2 sign(short2 x);
STD_FUNCTION short3 sign(short3 x);
STD_FUNCTION short4 sign(short4 x);
STD_FUNCTION int sign(int x);
STD_FUNCTION int2 sign(int2 x);
STD_FUNCTION int3 sign(int3 x);
STD_FUNCTION int4 sign(int4 x);
STD_FUNCTION half sign(half x);
STD_FUNCTION half2 sign(half2 x);
STD_FUNCTION half3 sign(half3 x);
STD_FUNCTION half4 sign(half4 x);
STD_FUNCTION float sign(float x);
STD_FUNCTION float2 sign(float2 x);
STD_FUNCTION float3 sign(float3 x);
STD_FUNCTION float4 sign(float4 x);

STD_FUNCTION float sin(float x);

STD_FUNCTION float sinh(float x);

STD_FUNCTION half smoothstep(half edge0, half edge1, half x);
STD_FUNCTION half2 smoothstep(half2 edge0, half2 edge1, half2 x);
STD_FUNCTION half3 smoothstep(half3 edge0, half3 edge1, half3 x);
STD_FUNCTION half4 smoothstep(half4 edge0, half4 edge1, half4 x);
STD_FUNCTION float smoothstep(float edge0, float edge1, float x);
STD_FUNCTION float2 smoothstep(float2 edge0, float2 edge1, float2 x);
STD_FUNCTION float3 smoothstep(float3 edge0, float3 edge1, float3 x);
STD_FUNCTION float4 smoothstep(float4 edge0, float4 edge1, float4 x);

STD_FUNCTION half sqrt(half x);
STD_FUNCTION half2 sqrt(half2 x);
STD_FUNCTION half3 sqrt(half3 x);
STD_FUNCTION half4 sqrt(half4 x);
STD_FUNCTION float sqrt(float x);
STD_FUNCTION float2 sqrt(float2 x);
STD_FUNCTION float3 sqrt(float3 x);
STD_FUNCTION float4 sqrt(float4 x);

STD_FUNCTION half step(half edge, half x);
STD_FUNCTION half2 step(half2 edge, half2 x);
STD_FUNCTION half3 step(half3 edge, half3 x);
STD_FUNCTION half4 step(half4 edge, half4 x);
STD_FUNCTION float step(float edge, float x);
STD_FUNCTION float2 step(float2 edge, float2 x);
STD_FUNCTION float3 step(float3 edge, float3 x);
STD_FUNCTION float4 step(float4 edge, float4 x);

STD_FUNCTION float tan(float x);

STD_FUNCTION float tanh(float x);

//TODO: add transpose function
