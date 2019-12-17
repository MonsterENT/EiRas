//
//  Mesh.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/18/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <Global/PlatformDefine.h>
#include <string>
#include <Material/GraphicsResource.hpp>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

#if GRAPHICS_METAL
#include <ShaderFile/Metal/MetalGraphicsPipelineInput.h>
#endif

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/GraphicsPipelineInput.h>
#endif

#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class GraphicsResource;
}

namespace MeshSys {

class Mesh
{
public:
    Mesh(std::string Name);

    std::string Name;

    void* GetVertices();
    _uint GetMeshDataSize();

    void BuildBuffer();

    EiRasPlatformBridgeProtocol* PlatformBridge;

private:
    MaterialSys::GraphicsResource* VertexBuffer;
    MaterialSys::GraphicsResource* IndexBuffer;
};

}

#endif /* Mesh_hpp */
