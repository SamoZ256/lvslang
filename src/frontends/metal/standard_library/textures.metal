STD enum class access {
    sample,
    read,
    write,
    read_write
};

STD struct bias {
    float value;
};

STD struct level {
    float lod;
};

STD struct gradient2d {
    float2 dPdx;
    float2 dPdy;
};

STD struct min_lod_clamp {
    float lod;
};

// -------- 2D --------

// Sample
// TODO: add more overloads
STD char4 sample(texture2d<char> texture, sampler samplr, float2 coord, int2 offset = int2(0));
STD short4 sample(texture2d<short> texture, sampler samplr, float2 coord, int2 offset = int2(0));
STD int4 sample(texture2d<int> texture, sampler samplr, float2 coord, int2 offset = int2(0));
STD half4 sample(texture2d<half> texture, sampler samplr, float2 coord, int2 offset = int2(0));
STD float4 sample(texture2d<float> texture, sampler samplr, float2 coord, int2 offset = int2(0));

// Read
// TODO: add more overloads
STD char4 read(texture2d<char> texture, ushort2 coord);
STD short4 read(texture2d<short> texture, ushort2 coord);
STD int4 read(texture2d<int> texture, ushort2 coord);
STD half4 read(texture2d<half> texture, ushort2 coord);
STD float4 read(texture2d<float> texture, ushort2 coord);
STD char4 read(texture2d<char> texture, uint2 coord);
STD short4 read(texture2d<short> texture, uint2 coord);
STD int4 read(texture2d<int> texture, uint2 coord);
STD half4 read(texture2d<half> texture, uint2 coord);
STD float4 read(texture2d<float> texture, uint2 coord);

// Write
// TODO: add more overloads
STD void write(texture2d<char> texture, char4 data, ushort2 coord);
STD void write(texture2d<short> texture, short4 data, ushort2 coord);
STD void write(texture2d<int> texture, int4 data, ushort2 coord);
STD void write(texture2d<half> texture, half4 data, ushort2 coord);
STD void write(texture2d<float> texture, float4 data, ushort2 coord);
STD void write(texture2d<char> texture, char4 data, uint2 coord);
STD void write(texture2d<short> texture, short4 data, uint2 coord);
STD void write(texture2d<int> texture, int4 data, uint2 coord);
STD void write(texture2d<half> texture, half4 data, uint2 coord);
STD void write(texture2d<float> texture, float4 data, uint2 coord);

