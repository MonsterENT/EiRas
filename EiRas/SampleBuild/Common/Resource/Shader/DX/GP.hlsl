
RWStructuredBuffer<float> _CommonBuffer : register(u0);
SamplerState _DefaultSampler : register(s0);

[numthreads(1, 1, 1)]
void CSMain(uint3 groupIdx : SV_GroupID)
{
    _CommonBuffer[groupIdx.x] = 10 - groupIdx.x;
}
//GP