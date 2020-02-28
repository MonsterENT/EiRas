//
//  Camera.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 2/1/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "Camera.hpp"
#include <Global/PlatformDefine.h>
#include <math.h>

using namespace BasicComponent;

void perspectiveFov(Math::Matrix4X4 &mat, const float fov, const float aspect, const float ZNear, const float ZFar)
{
    const float fViewSpaceHeight = 1.0f / tanf(fov * 0.5f);
    const float fViewSpaceWidth = fViewSpaceHeight / aspect;

    mat.m11 = fViewSpaceWidth;
    mat.m12 = 0;
    mat.m13 = 0;
    mat.m14 = 0;
    
    mat.m21 = 0;
    mat.m22 = fViewSpaceHeight;
    mat.m23 = 0;
    mat.m24 = 0;
    
    mat.m31 = 0;
    mat.m32 = 0;
    mat.m33 = ZFar / (ZFar - ZNear);
    mat.m34 = -ZNear * ZFar / (ZFar - ZNear);
    
    mat.m41 = 0;
    mat.m42 = 0;
    mat.m43 = 1;
    mat.m44 = 0;
    
#if GRAPHICS_DX
    mat.transpose();
#endif
}

void Camera::SetProjection(float fov, float aspect, float ZNear, float ZFar)
{
    _finishBuildProjectionMat = false;
    _fov = fov;
    _aspect = aspect;
    _ZNear = ZNear;
    _ZFar = ZFar;
}

const Math::Matrix4X4* Camera::GetViewMatrix()
{
    if(!Transform._finishBuildMat || !_finishBuildViewMat)
    {
        Transform._finishBuildMat = true;
        _finishBuildViewMat = true;
        
        _viewMat.m11 = Transform.Right.x;
        _viewMat.m12 = Transform.Right.y;
        _viewMat.m13 = Transform.Right.z;
        _viewMat.m14 = -Transform.Position.x;
        
        _viewMat.m21 = Transform.Up.x;
        _viewMat.m22 = Transform.Up.y;
        _viewMat.m23 = Transform.Up.z;
        _viewMat.m24 = -Transform.Position.y;
        
        _viewMat.m31 = Transform.Forward.x;
        _viewMat.m32 = Transform.Forward.y;
        _viewMat.m33 = Transform.Forward.z;
        _viewMat.m34 = -Transform.Position.z;
        
#if GRAPHICS_DX
        _viewMat.transpose();
#endif
    }
    return &_viewMat;
}

const Math::Matrix4X4* Camera::GetProjectionMatrix()
{
    if(!_finishBuildProjectionMat)
    {
        _finishBuildProjectionMat = true;
        perspectiveFov(_projectionMat, _fov, _aspect, _ZNear, _ZFar);
    }
    return &_projectionMat;
}

