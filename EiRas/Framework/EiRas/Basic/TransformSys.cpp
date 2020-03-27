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
    _localToWorldMat.m14 = Position.x;
    _localToWorldMat.m24 = Position.y;
    _localToWorldMat.m34 = Position.z;

    //
    _localToWorldMat.m11 = Right.x;
    _localToWorldMat.m21 = Right.y;
    _localToWorldMat.m31 = Right.z;

    _worldToLocalMat.m11 = Right.x;
    _worldToLocalMat.m21 = Right.y;
    _worldToLocalMat.m31 = Right.z;


    _localToWorldMat.m12 = Up.x;
    _localToWorldMat.m22 = Up.y;
    _localToWorldMat.m32 = Up.z;

    _worldToLocalMat.m12 = Up.x;
    _worldToLocalMat.m22 = Up.y;
    _worldToLocalMat.m32 = Up.z;

    _localToWorldMat.m13 = Forward.x;
    _localToWorldMat.m23 = Forward.y;
    _localToWorldMat.m33 = Forward.z;

    _worldToLocalMat.m13 = Forward.x;
    _worldToLocalMat.m23 = Forward.y;
    _worldToLocalMat.m33 = Forward.z;

    //
    _localToWorldMat.m11 *= LocalScale.x;
    _localToWorldMat.m22 *= LocalScale.y;
    _localToWorldMat.m33 *= LocalScale.z;

#if GRAPHICS_DX
    _localToWorldMat.transpose();
#endif
    return &_localToWorldMat;
}

Math::Matrix4X4* TransformSys::GetWorldToLocalMatrix()
{
    return &_worldToLocalMat;
}