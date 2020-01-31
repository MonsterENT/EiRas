//
//  Transform.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 2/1/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <Math/Math.hpp>

namespace BasicComponent {

class Camera;

class TransformSys
{
    friend Camera;
public:
    TransformSys()
    {
        _finishBuildMat = false;
    }
    
    Math::float3 Forward;
    Math::float3 Right;
    Math::float3 Up;
    
    Math::float3 Position;
    Math::float3 LocalScale;
    
    void Init(Math::float3 Forward,
    Math::float3 Right,
    Math::float3 Up,
    Math::float3 Position);
    Math::Matrix4X4* GetLocalToWorldMatrix();
    
protected:
    bool _finishBuildMat;
    
private:
    Math::Matrix4X4 _rotateMat;
    Math::Matrix4X4 _scaleMat;
    Math::Matrix4X4 _localToWorldMat;
};

}

#endif /* Transform_hpp */
