//
//  Camera.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 2/1/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "Camera.hpp"
#include <Global/PlatformDefine.h>

using namespace BasicComponent;

Math::Matrix4X4* Camera::GetViewMatrix()
{
    if(!Transform._finishBuildMat || !_finishBuildMat)
    {
        Transform._finishBuildMat = true;
        _finishBuildMat = true;
        
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
