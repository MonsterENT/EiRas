
cbuffer CommonCB0 : register(b0)
{
    float4 _TmpColor;
};

Texture2D _MainTex : register(t0);

SamplerState _DefaultSampler : register(s0);


struct VSInput
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};


PSInput VSMain(VSInput v)
{
    PSInput o = (PSInput)0;
    
    o.pos = float4(v.pos, 1);
    o.uv = v.uv;
    return o;
};

float4 PSMain(PSInput i) : SV_TARGET
{
    return _MainTex.Sample(_DefaultSampler, i.uv) * _TmpColor;
}