#ifndef Graphics_Data_Hpp
#define Graphics_Data_Hpp

#include <vector>
#include <Math/Math.hpp>
using namespace std;
using namespace Math;

struct SceneSearchInfo
{
    float size_x, size_y, size_z;
    float pos_x, pos_y, pos_z;

    int parent;
    int children[8];
    int dataPackage;
};

#endif // !Graphics_Data_Hpp
