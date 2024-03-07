STD char abs(char x);
STD char2 abs(char2 x);
STD char3 abs(char3 x);
STD char4 abs(char4 x);
STD short abs(short x);
STD short2 abs(short2 x);
STD short3 abs(short3 x);
STD short4 abs(short4 x);
STD int abs(int x);
STD int2 abs(int2 x);
STD int3 abs(int3 x);
STD int4 abs(int4 x);
STD half abs(half x);
STD half2 abs(half2 x);
STD half3 abs(half3 x);
STD half4 abs(half4 x);
STD float abs(float x);
STD float2 abs(float2 x);
STD float3 abs(float3 x);
STD float4 abs(float4 x);

STD float acos(float x);

STD float acosh(float x);

STD float asin(float x);

STD float asinh(float x);

STD float atan(float x);

STD float atanh(float x);

// TODO: add atomic functions

STD half ceil(half x);
STD half2 ceil(half2 x);
STD half3 ceil(half3 x);
STD half4 ceil(half4 x);
STD float ceil(float x);
STD float2 ceil(float2 x);
STD float3 ceil(float3 x);
STD float4 ceil(float4 x);

STD char clamp(char x, char minVal, char maxVal);
STD char2 clamp(char2 x, char2 minVal, char2 maxVal);
STD char3 clamp(char3 x, char3 minVal, char3 maxVal);
STD char4 clamp(char4 x, char4 minVal, char4 maxVal);
STD short clamp(short x, short minVal, short maxVal);
STD short2 clamp(short2 x, short2 minVal, short2 maxVal);
STD short3 clamp(short3 x, short3 minVal, short3 maxVal);
STD short4 clamp(short4 x, short4 minVal, short4 maxVal);
STD int clamp(int x, int minVal, int maxVal);
STD int2 clamp(int2 x, int2 minVal, int2 maxVal);
STD int3 clamp(int3 x, int3 minVal, int3 maxVal);
STD int4 clamp(int4 x, int4 minVal, int4 maxVal);
STD half clamp(half x, half minVal, half maxVal);
STD half2 clamp(half2 x, half2 minVal, half2 maxVal);
STD half3 clamp(half3 x, half3 minVal, half3 maxVal);
STD half4 clamp(half4 x, half4 minVal, half4 maxVal);
STD float clamp(float x, float minVal, float maxVal);
STD float2 clamp(float2 x, float2 minVal, float2 maxVal);
STD float3 clamp(float3 x, float3 minVal, float3 maxVal);
STD float4 clamp(float4 x, float4 minVal, float4 maxVal);

STD float cos(float x);

STD float cosh(float x);

STD half3 cross(half3 x, half3 y);
STD float3 cross(float3 x, float3 y);

// TODO: add determinant function

STD half distance(half2 x, half2 y);
STD half distance(half3 x, half3 y);
STD half distance(half4 x, half4 y);
STD float distance(float2 x, float2 y);
STD float distance(float3 x, float3 y);
STD float distance(float4 x, float4 y);

STD half dot(half2 x, half2 y);
STD half dot(half3 x, half3 y);
STD half dot(half4 x, half4 y);
STD float dot(float2 x, float2 y);
STD float dot(float3 x, float3 y);
STD float dot(float4 x, float4 y);

STD half exp(half x);
STD half2 exp(half2 x);
STD half3 exp(half3 x);
STD half4 exp(half4 x);
STD float exp(float x);
STD float2 exp(float2 x);
STD float3 exp(float3 x);
STD float4 exp(float4 x);

STD half exp2(half x);
STD half2 exp2(half2 x);
STD half3 exp2(half3 x);
STD half4 exp2(half4 x);
STD float exp2(float x);
STD float2 exp2(float2 x);
STD float3 exp2(float3 x);
STD float4 exp2(float4 x);

STD half floor(half x);
STD half2 floor(half2 x);
STD half3 floor(half3 x);
STD half4 floor(half4 x);
STD float floor(float x);
STD float2 floor(float2 x);
STD float3 floor(float3 x);
STD float4 floor(float4 x);

STD half fract(half x);
STD half2 fract(half2 x);
STD half3 fract(half3 x);
STD half4 fract(half4 x);
STD float fract(float x);
STD float2 fract(float2 x);
STD float3 fract(float3 x);
STD float4 fract(float4 x);

STD bool isinf(half x);
STD bool2 isinf(half2 x);
STD bool3 isinf(half3 x);
STD bool4 isinf(half4 x);
STD bool isinf(float x);
STD bool2 isinf(float2 x);
STD bool3 isinf(float3 x);
STD bool4 isinf(float4 x);

STD bool isnan(half x);
STD bool2 isnan(half2 x);
STD bool3 isnan(half3 x);
STD bool4 isnan(half4 x);
STD bool isnan(float x);
STD bool2 isnan(float2 x);
STD bool3 isnan(float3 x);
STD bool4 isnan(float4 x);

STD half length(half2 x);
STD half length(half3 x);
STD half length(half4 x);
STD float length(float2 x);
STD float length(float3 x);
STD float length(float4 x);

STD half log(half x);
STD half2 log(half2 x);
STD half3 log(half3 x);
STD half4 log(half4 x);
STD float log(float x);
STD float2 log(float2 x);
STD float3 log(float3 x);
STD float4 log(float4 x);

STD half log2(half x);
STD half2 log2(half2 x);
STD half3 log2(half3 x);
STD half4 log2(half4 x);
STD float log2(float x);
STD float2 log2(float2 x);
STD float3 log2(float3 x);
STD float4 log2(float4 x);

STD char max(char x, char y);
STD char2 max(char2 x, char2 y);
STD char3 max(char3 x, char3 y);
STD char4 max(char4 x, char4 y);
STD short max(short x, short y);
STD short2 max(short2 x, short2 y);
STD short3 max(short3 x, short3 y);
STD short4 max(short4 x, short4 y);
STD int max(int x, int y);
STD int2 max(int2 x, int2 y);
STD int3 max(int3 x, int3 y);
STD int4 max(int4 x, int4 y);
STD half max(half x, half y);
STD half2 max(half2 x, half2 y);
STD half3 max(half3 x, half3 y);
STD half4 max(half4 x, half4 y);
STD float max(float x, float y);
STD float2 max(float2 x, float2 y);
STD float3 max(float3 x, float3 y);
STD float4 max(float4 x, float4 y);

STD char min(char x, char y);
STD char2 min(char2 x, char2 y);
STD char3 min(char3 x, char3 y);
STD char4 min(char4 x, char4 y);
STD short min(short x, short y);
STD short2 min(short2 x, short2 y);
STD short3 min(short3 x, short3 y);
STD short4 min(short4 x, short4 y);
STD int min(int x, int y);
STD int2 min(int2 x, int2 y);
STD int3 min(int3 x, int3 y);
STD int4 min(int4 x, int4 y);
STD half min(half x, half y);
STD half2 min(half2 x, half2 y);
STD half3 min(half3 x, half3 y);
STD half4 min(half4 x, half4 y);
STD float min(float x, float y);
STD float2 min(float2 x, float2 y);
STD float3 min(float3 x, float3 y);
STD float4 min(float4 x, float4 y);

STD half mix(half x, half y, half a);
STD half2 mix(half2 x, half2 y, half2 a);
STD half3 mix(half3 x, half3 y, half3 a);
STD half4 mix(half4 x, half4 y, half4 a);
STD float mix(float x, float y, float a);
STD float2 mix(float2 x, float2 y, float2 a);
STD float3 mix(float3 x, float3 y, float3 a);
STD float4 mix(float4 x, float4 y, float4 a);

STD half2 normalize(half2 x);
STD half3 normalize(half3 x);
STD half4 normalize(half4 x);
STD float2 normalize(float2 x);
STD float3 normalize(float3 x);
STD float4 normalize(float4 x);

STD half pow(half x, half y);
STD half2 pow(half2 x, half2 y);
STD half3 pow(half3 x, half3 y);
STD half4 pow(half4 x, half4 y);
STD float pow(float x, float y);
STD float2 pow(float2 x, float2 y);
STD float3 pow(float3 x, float3 y);
STD float4 pow(float4 x, float4 y);

STD half2 reflect(half2 I, half2 N);
STD half3 reflect(half3 I, half3 N);
STD half4 reflect(half4 I, half4 N);
STD float2 reflect(float2 I, float2 N);
STD float3 reflect(float3 I, float3 N);
STD float4 reflect(float4 I, float4 N);

STD half2 refract(half2 I, half2 N, half eta);
STD half3 refract(half3 I, half3 N, half eta);
STD half4 refract(half4 I, half4 N, half eta);
STD float2 refract(float2 I, float2 N, float eta);
STD float3 refract(float3 I, float3 N, float eta);
STD float4 refract(float4 I, float4 N, float eta);

STD half round(half x);
STD half2 round(half2 x);
STD half3 round(half3 x);
STD half4 round(half4 x);
STD float round(float x);
STD float2 round(float2 x);
STD float3 round(float3 x);
STD float4 round(float4 x);

// TODO: check if integers are supported
STD char sign(char x);
STD char2 sign(char2 x);
STD char3 sign(char3 x);
STD char4 sign(char4 x);
STD short sign(short x);
STD short2 sign(short2 x);
STD short3 sign(short3 x);
STD short4 sign(short4 x);
STD int sign(int x);
STD int2 sign(int2 x);
STD int3 sign(int3 x);
STD int4 sign(int4 x);
STD half sign(half x);
STD half2 sign(half2 x);
STD half3 sign(half3 x);
STD half4 sign(half4 x);
STD float sign(float x);
STD float2 sign(float2 x);
STD float3 sign(float3 x);
STD float4 sign(float4 x);

STD float sin(float x);

STD float sinh(float x);

STD half smoothstep(half edge0, half edge1, half x);
STD half2 smoothstep(half2 edge0, half2 edge1, half2 x);
STD half3 smoothstep(half3 edge0, half3 edge1, half3 x);
STD half4 smoothstep(half4 edge0, half4 edge1, half4 x);
STD float smoothstep(float edge0, float edge1, float x);
STD float2 smoothstep(float2 edge0, float2 edge1, float2 x);
STD float3 smoothstep(float3 edge0, float3 edge1, float3 x);
STD float4 smoothstep(float4 edge0, float4 edge1, float4 x);

STD half sqrt(half x);
STD half2 sqrt(half2 x);
STD half3 sqrt(half3 x);
STD half4 sqrt(half4 x);
STD float sqrt(float x);
STD float2 sqrt(float2 x);
STD float3 sqrt(float3 x);
STD float4 sqrt(float4 x);

STD half step(half edge, half x);
STD half2 step(half2 edge, half2 x);
STD half3 step(half3 edge, half3 x);
STD half4 step(half4 edge, half4 x);
STD float step(float edge, float x);
STD float2 step(float2 edge, float2 x);
STD float3 step(float3 edge, float3 x);
STD float4 step(float4 edge, float4 x);

STD float tan(float x);

STD float tanh(float x);

// TODO: add transpose function
