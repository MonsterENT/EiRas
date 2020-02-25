//
//  Transform.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 2/1/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "TransformSys.hpp"

using namespace Math;
using BasicComponent::TransformSys;

void TransformSys::Init(Math::float3 _forward, Math::float3 _right, Math::float3 _up, Math::float3 _position)
{
    Forward = _forward;
    Right = _right;
    Up = _up;
    Position = _position;
}

Matrix4X4* TransformSys::GetLocalToWorldMatrix()
{
    if(!_finishBuildMat)
    {
        _finishBuildMat = true;
        
        _rotateMat.m14 = Position.x;
        _rotateMat.m24 = Position.y;
        _rotateMat.m34 = Position.z;
        
        //
        _rotateMat.m11 = Right.x;
        _rotateMat.m21 = Right.y;
        _rotateMat.m31 = Right.z;
        
        _rotateMat.m12 = Up.x;
        _rotateMat.m22 = Up.y;
        _rotateMat.m32 = Up.z;
        
        _rotateMat.m13 = Forward.x;
        _rotateMat.m23 = Forward.y;
        _rotateMat.m33 = Forward.z;
        
        //
        _scaleMat.m11 = LocalScale.x;
        _scaleMat.m22 = LocalScale.y;
        _scaleMat.m33 = LocalScale.z;
        
        _localToWorldMat = Matrix4X4::mul(_scaleMat, _localToWorldMat);
        _localToWorldMat = Matrix4X4::mul(_rotateMat, _localToWorldMat);
#if GRAPHICS_DX
        _viewMat.transpose();
#endif
    }
    return &_localToWorldMat;
}
