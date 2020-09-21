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

namespace MaterialSys
{
    class GraphicsResource;
}

namespace Graphics
{
    class CommandBuffer;
}

namespace BasicComponent {

class Camera;

struct TransformRawData
{
    Math::Matrix4X4 _localToWorldMat;
    Math::Matrix4X4 _worldToLocalMat;
};

class TransformSys
{
    friend Camera;
    friend Graphics::CommandBuffer;
public:
    TransformSys();

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
    Math::Matrix4X4* GetWorldToLocalMatrix();

    void UpdateToGraphics();

protected:
    MaterialSys::GraphicsResource* _WorldMatCB;
private:
    TransformRawData _RawData;
};

}

#endif /* Transform_hpp */
