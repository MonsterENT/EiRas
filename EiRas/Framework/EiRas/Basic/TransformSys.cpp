//
//  Transform.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 2/1/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "TransformSys.hpp"
#include <Material/GraphicsResource.hpp>

using namespace MaterialSys;
using namespace Math;
using BasicComponent::TransformSys;

TransformSys::TransformSys()
{
    LocalScale = Math::float3(1, 1, 1);
    _WorldMatCB = 0;
}

void TransformSys::Init(Math::float3 _forward, Math::float3 _right, Math::float3 _up, Math::float3 _position)
{
    Forward = _forward;
    Right = _right;
    Up = _up;
    Position = _position;
}

Matrix4X4* TransformSys::GetLocalToWorldMatrix()
{
    _RawData._localToWorldMat.m14 = Position.x;
    _RawData._localToWorldMat.m24 = Position.y;
    _RawData._localToWorldMat.m34 = Position.z;
    _RawData._localToWorldMat.m44 = 1;
    //
    _RawData._localToWorldMat.m11 = Right.x;
    _RawData._localToWorldMat.m21 = Right.y;
    _RawData._localToWorldMat.m31 = Right.z;

    _RawData._localToWorldMat.m12 = Up.x;
    _RawData._localToWorldMat.m22 = Up.y;
    _RawData._localToWorldMat.m32 = Up.z;

    _RawData._localToWorldMat.m13 = Forward.x;
    _RawData._localToWorldMat.m23 = Forward.y;
    _RawData._localToWorldMat.m33 = Forward.z;

    //
    _RawData._localToWorldMat.m11 *= LocalScale.x;
    _RawData._localToWorldMat.m22 *= LocalScale.y;
    _RawData._localToWorldMat.m33 *= LocalScale.z;

    _RawData._worldToLocalMat = _RawData._localToWorldMat;
    _RawData._worldToLocalMat.transpose();
    return &_RawData._localToWorldMat;
}

Math::Matrix4X4* TransformSys::GetWorldToLocalMatrix()
{
    return &_RawData._worldToLocalMat;
}

void TransformSys::UpdateToGraphics()
{
    GetLocalToWorldMatrix();
    GetCBRawRes()->SetResource(&_RawData, false);
}

MaterialSys::GraphicsResource* TransformSys::GetCBRawRes()
{
    if (_WorldMatCB == 0)
    {
        _WorldMatCB = new GraphicsResource("TransformSysCB", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, true);
        _WorldMatCB->InitAsConstantBuffer(sizeof(TransformRawData));
    }
    return _WorldMatCB;
}