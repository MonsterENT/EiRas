#include "Common.hlsl"

cbuffer CommonCB0 : register(b0)
{
    row_major float4x4 _WorldToViewMatrix;
    row_major float4x4 _ProjectionMatrix;
};

cbuffer CommonCB1 : register(b1)
{
    row_major float4x4 _LocalToWorldMatrix;
    row_major float4x4 _WorldToLocalMatrix;
};

cbuffer CustomCB : register(b2)
{
    float4 _TmpColor;
};

Texture2D _MainTex : register(t0);

SamplerState _DefaultSampler : register(s0);

RWStructuredBuffer<float> _CommonBuffer : register(u0);

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
    o.uv = o.pos.xy / o.pos.w / 2.0f + 0.5f;
    o.normal = mul(v.normal, (float3x3)_WorldToLocalMatrix);
    return o;
};

float4 PSMain(PSInput i) : SV_TARGET
{
    float4 col = 0;
    float roughness = 0.2f;
    float3 viewDir = float3(0, 0, -1);
    float3 lightDir = float3(0, 1, 0);
    float3 H = normalize(viewDir + lightDir);
    float4 albedo = _MainTex.Sample(_DefaultSampler, i.uv);
    float3 specColor = float3(1, 1, 1);
    float NdotL = saturate(dot(i.normal, lightDir));
    float NdotV = abs(dot(i.normal, viewDir));
    float NdotH = saturate(dot(i.normal, H));

    float diffuseTerm = saturate(NdotL);
    float V = SmithJointGGXVisibilityTerm (NdotL, NdotV, roughness);
    float D = GGXTerm (NdotH, roughness);
    float specularTerm = V * D * 3.14159f;
    specularTerm = max(0, specularTerm * NdotL);

    col.a = albedo.a;

    half4 gpCol = 0;
    gpCol.r = _CommonBuffer[0];
    gpCol.g = _CommonBuffer[1];
    gpCol.b = _CommonBuffer[2];
    gpCol.a = _CommonBuffer[3];
    albedo.rgb *= gpCol.rgb;

    col.rgb = diffuseTerm * albedo.rgb * 0.05f;
    specColor *= albedo.rgb;
    col.rgb += specColor.rgb * specularTerm;


    return col;
}
//BasicBRDF