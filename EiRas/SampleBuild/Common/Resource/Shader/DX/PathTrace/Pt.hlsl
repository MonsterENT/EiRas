RWTexture2D<half4> _Target : register(u0);
SamplerState _DefaultSampler : register(s0);

[numthreads(8, 8, 1)]
void pt_kernel(uint3 groupIdx : SV_GroupID, uint3 groupThreadIdx : SV_GroupThreadID)
{
    int2 idx = groupThreadIdx.xy + groupIdx.xy * 8;
    int2 mid = int2(1920, 1080) / 2;
    int2 gap = abs(idx - mid);

    if(gap.x < 100 && gap.y < 100 && (idx - mid).y < 0)
    {
        _Target[idx] = half4(0, 1, 0, 1);
    }
    else
    {
        _Target[idx] = half4(1, 0, 0, 1);
    }
}