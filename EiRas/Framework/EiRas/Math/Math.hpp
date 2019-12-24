//
//  Math.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/22/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Math_hpp
#define Math_hpp

namespace Math {

class float2
{
public:
    float x, y;
    
    float2(){}
    
    float2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};

class float3
{
public:
    float x, y, z;
    
    float3(){}
    
    float3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

class float4
{
public:
    float x, y, z, w;
    
    float4(){}
    
    float4(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
};

}

#endif /* Math_hpp */
