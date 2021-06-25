#ifndef Graphics_Data_Hpp
#define Graphics_Data_Hpp

#include <vector>
#include <Math/Math.hpp>
using namespace std;
using namespace Math;

struct mfloat3
{
    float x, y, z;

    mfloat3(float3& o)
    {
        x = o.x;
        y = o.y;
        z = o.z;
    }

    mfloat3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
    {
    }

    mfloat3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    void operator=(float3 f3)
    {
        x = f3.x;
        y = f3.y;
        z = f3.z;
    }
};

struct mfloat4
{
    float r, g, b, a;

    mfloat4(float4& o)
    {
        r = o.x;
        g = o.y;
        b = o.z;
        a = o.w;
    }

    mfloat4(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a)
    {
    }

    mfloat4()
    {
        r = 0;
        g = 0;
        b = 0;
        a = 0;
    }
};

struct SceneBlock
{
    mfloat3 size;
    mfloat3 pos;

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
    mfloat3 normal;
    mfloat3 pos0, pos1, pos2;
    int materialId;
};

struct MaterialData
{
    mfloat4 color;
    mfloat4 emission;

    MaterialData() : color(mfloat4(0, 0, 0, 0)), emission(mfloat4(0, 0, 0, 0))
    {
    }
};

struct JobInfo
{
    int sampleCount;
    mfloat4 majorPos;
    mfloat4 targetOffset;
};

#endif // !Graphics_Data_Hpp
