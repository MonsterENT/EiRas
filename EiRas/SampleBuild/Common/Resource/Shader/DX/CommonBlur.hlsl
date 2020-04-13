
cbuffer CommonCB0 : register(b0)
{
    float4 _BlurSettings;//x width, y height, z BlurCoef
};

Texture2D _MainTex : register(t0);

SamplerState _DefaultSampler : register(s0);


struct VSInput
{
    float3 pos : POSITION;
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
    o.ss_uv = o.pos.xy;
    o.ss_uv.y = 1 - o.ss_uv.y;
    return o;
};

float4 PSMainH(PSInput i) : SV_TARGET
{
    const float BlurCoef[9] = { 0.0947416, 0.0947416, 0.118318, 0.118318, 0.147761, 0.118318, 0.118318, 0.0947416, 0.0947416 };

    float2 uvOffset = 1.0f / _BlurSettings.xy * _BlurSettings.z;
    i.ss_uv.x -= uvOffset * 4;
    float4 col = 0;

    for(int index = 0; index < 9; index++)
    {
        col.rgb += _MainTex.Sample(_DefaultSampler, i.ss_uv).rgb * BlurCoef[index];
        i.ss_uv.x += uvOffset;
    }
    col.a = 1;
    return col;
}

float4 PSMainV(PSInput i) : SV_TARGET
{
    const float BlurCoef[9] = { 0.0947416, 0.0947416, 0.118318, 0.118318, 0.147761, 0.118318, 0.118318, 0.0947416, 0.0947416 };

    float2 uvOffset = 1.0f / _BlurSettings.xy * _BlurSettings.z;
    i.ss_uv.y -= uvOffset * 4;
    float4 col = 0;

    for(int index = 0; index < 9; index++)
    {
        col.rgb += _MainTex.Sample(_DefaultSampler, i.ss_uv).rgb * BlurCoef[index];
        i.ss_uv.y += uvOffset;
    }
    col.a = 1;
    return col;
}
//CommonBlur