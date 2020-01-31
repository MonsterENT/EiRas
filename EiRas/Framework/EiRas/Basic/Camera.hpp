//
//  Camera.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 2/1/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <TransformSys.hpp>

namespace BasicComponent {

class Camera
{
public:
    
    Camera()
    {
        _finishBuildMat = false;
    }
    
    TransformSys Transform;
    
    Math::Matrix4X4* GetViewMatrix();
    
private:
    Math::Matrix4X4 _viewMat;
    
    bool _finishBuildMat;
};

}

#endif /* Camera_hpp */
