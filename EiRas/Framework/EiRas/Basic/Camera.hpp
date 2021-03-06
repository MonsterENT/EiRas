//
//  Camera.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 2/1/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <Basic/TransformSys.hpp>

namespace BasicComponent {

class Camera
{
public:
    
    Camera()
    {
    }
    
    TransformSys Transform;
    
    void SetProjection(float fov, float aspect, float ZNear, float ZFar);
    
    const Math::Matrix4X4* GetViewMatrix();
    
    const Math::Matrix4X4* GetProjectionMatrix();
    
private:
    Math::Matrix4X4 _viewMat;
    Math::Matrix4X4 _projectionMat;
    
    float _fov, _aspect, _ZNear, _ZFar;
};

}

#endif /* Camera_hpp */
