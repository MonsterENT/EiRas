Texture2D _MainTex : register(t0);
SamplerState _DefaultSampler : register(s0);

struct appdata0
{
    float2 pos : POSITION;
};

struct v2f
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

v2f vs_main_0(appdata0 v)
{
    v2f o = (v2f)0;
    o.pos = float4(v.pos, 0, 1);
    o.uv = o.pos.xy * 0.5 + 0.5;
    o.uv.y = 1 - o.uv.y;
    return o;
};

float4 ps_main(v2f i) : SV_TARGET
{
    return _MainTex.Sample(_DefaultSampler, i.uv);
}