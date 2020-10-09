
RWStructuredBuffer<float> _CommonBuffer : register(u0);
SamplerState _DefaultSampler : register(s0);

[numthreads(1, 1, 1)]
void CSMain(uint3 groupIdx : SV_GroupID)
{
    if(groupIdx.x == 2)
    {
        _CommonBuffer[groupIdx.x] = 1;
    }
    else
    {
        _CommonBuffer[groupIdx.x] = groupIdx.x / 10.0f;
    }
}
//GP