RWTexture2D<half4> _Target : register(u0);
SamplerState _DefaultSampler : register(s0);

[numthreads(8, 8, 1)]
void pt_kernel(uint3 groupIdx : SV_GroupID, uint3 groupThreadIdx : SV_GroupThreadID)
{
    _Target[groupThreadIdx.xy + groupIdx.xy * 8] = half4(0, 1, 0, 1);
}