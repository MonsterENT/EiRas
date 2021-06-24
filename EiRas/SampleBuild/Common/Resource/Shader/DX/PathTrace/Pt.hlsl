RWTexture2D<half4> _Target : register(u0);
SamplerState _DefaultSampler : register(s0);

struct SceneBlock
{
    float3 size;
    float3 pos;

    int parent;
    int children[8];
    int dataPackage;
};

struct SceneNodeDataPackInfo
{
    int start;
    int end;
};

struct TriangleData
{
    float3 normal;
    float3 pos0;
    float3 pos1;
    float3 pos2;
    int materialId;
};

struct MaterialData
{
    float4 color;
};

StructuredBuffer<MaterialData> _MaterialData : register(t0);
StructuredBuffer<TriangleData> _TriangleData : register(t1);

// Determine whether a ray intersect with a triangle
// Parameters
// orig: origin of the ray
// dir: direction of the ray
// v0, v1, v2: vertices of triangle
// t(out): weight of the intersection for the ray
// u(out), v(out): barycentric coordinate of intersection

bool IntersectTriangle(float3 orig, float3 dir,
    float3 v0, float3 v1, float3 v2, inout float t, inout float u, inout float v)
{
    float3 E1 = v1 - v0;
    float3 E2 = v2 - v0;
    float3 P = cross(dir, E2);
    float det = dot(E1, P);

    float3 T = 0;
    if(det > 0)
    {
        T = orig - v0;
    }
    else
    {
        T = v0 - orig;
        det = -det;
    }

    if(det > 0.0001f)
    {
        u = dot(T, P);
        if( u > 0.0f && u < det )
        {
            float3 Q = cross(T, E1);
            v = dot(dir, Q);
            if( v > 0.0f && u + v < det )
            {
                t = dot(E2, Q);
                float fInvDet = 1.0f / det;
                t *= fInvDet;
                u *= fInvDet;
                v *= fInvDet;
                return true;
            }
        }
    }
    return false;
}

bool isTraceTriangle(float3 o, float3 ray, out int idx)
{
    idx = -1;

    float minDis = 99999;

    for(int i = 0; i < 10; i++)
    {
        TriangleData tri = _TriangleData[i];
        float t = 1, u = 0, v = 0;
        if(IntersectTriangle(o, ray, tri.pos0, tri.pos1, tri.pos2, t, u, v))
        {
            float3 tpos = tri.pos0 * t + tri.pos1 * u + tri.pos2 * v;
            float dis = distance(tpos, o);
            if(minDis > dis)
            {
                minDis = dis;
                idx = i;
            }
        }
    }

    if(idx >= 0)
    {
        return true;
    }
    return false;
}

[numthreads(8, 8, 1)]
void pt_kernel(uint3 groupIdx : SV_GroupID, uint3 groupThreadIdx : SV_GroupThreadID)
{
    float3 majorPos = float3(0, 4, 0);


    float nearPlane = 0.3;
    float3 cameraPos = float3(0, 0, 0) + majorPos;
    float3 targetPos = float3(0, -0.2, nearPlane) + majorPos;

    int2 idx = groupThreadIdx.xy + groupIdx.xy * 8;
    float2 mid = float2(1920, 1080) / 2;
    float2 xy = (idx - mid) / mid;
    xy.y *= -1;

    targetPos.xy += xy;
    float3 ray = normalize(targetPos - cameraPos);

    int triIdx = -1;
    if(isTraceTriangle(cameraPos, ray, triIdx))
    {
        TriangleData t = _TriangleData[triIdx];
        _Target[idx] = _MaterialData[t.materialId].color;
    }
    else
    {
        _Target[idx] = abs(ray.xyzz);
    }

    // _Target[idx] = _MaterialData[1].color;

}