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


namespace MaterialSys {

class Mesh
{
public:
    Mesh(std::string Name);

    void* GetVertices();
    int GetMeshDataSize();

    EiRasPlatformBridgeProtocol* PlatformBridge;

private:
    GraphicsResource* VertexBuffer;
    GraphicsResource* IndexBuffer;
};

}

#endif /* Mesh_hpp */
