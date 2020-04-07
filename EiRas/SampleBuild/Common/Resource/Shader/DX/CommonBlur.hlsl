
cbuffer CommonCB0 : register(b0)
{
    float4 _BlurSettings;//x BlurCoef
};

Texture2D _MainTex : register(t0);

SamplerState _DefaultSampler : register(s0);


struct VSInput
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 ss_uv : TEXCOORD;
};


PSInput VSMain(VSInput v)
{
    PSInput o = (PSInput)0;
    o.pos = float4(v.pos, 1);
    o.ss_uv = v.uv;
    //o.ss_uv.y = 1 - o.ss_uv.y;
    return o;
};

float4 PSMain(PSInput i) : SV_TARGET
{
    return float4(_MainTex.Sample(_DefaultSampler, i.ss_uv).rgb, 1) * _BlurSettings.x;
}
//CommonBlur