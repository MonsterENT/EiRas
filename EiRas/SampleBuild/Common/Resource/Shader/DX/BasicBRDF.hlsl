
cbuffer CommonCB0 : register(b0)
{
    float4x4 _WorldToViewMatrix;
    float4x4 _ProjectionMatrix;
};

cbuffer CommonCB1 : register(b1)
{
    float4x4 _LocalToWorldMatrix;
    float4x4 _WorldToLocalMatrix;
};

cbuffer CustomCB : register(b2)
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
    float3 normal : NORMAL;
};


PSInput VSMain(VSInput v)
{
    PSInput o = (PSInput)0;
    
    o.pos = mul(_LocalToWorldMatrix, float4(v.pos, 1));
    o.pos = mul(_WorldToViewMatrix, o.pos);
    o.pos = mul(_ProjectionMatrix, o.pos);
    o.uv = v.uv;
    o.normal = mul(v.normal, (float3x3)_WorldToLocalMatrix);
    return o;
};

float4 PSMain(PSInput i) : SV_TARGET
{
    return dot(i.normal, float3(0, 1, 0));
}