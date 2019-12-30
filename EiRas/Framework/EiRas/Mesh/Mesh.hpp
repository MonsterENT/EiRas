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

namespace Math {
class float2;
class float3;
class float4;
}

namespace MeshSys {

class SubMesh
{
public:
    _uint IndicesCount;
    _uint* IndicesData;
    
    _uint VerticesCount;
    Math::float3* PositionData;
    Math::float3* NormalData;
    Math::float2* UVData;
    Math::float4* ColorData;
};

class Mesh
{
public:
    Mesh(std::string Name);

    std::string Name;
    
    void* GetTriangleData();
    _uint GetTriangleDataSize();
    
    void* GetIndexData();
    _uint GetIndexDataSize();

    void BuildBuffer();

    EiRasPlatformBridgeProtocol* PlatformBridge;

    _uint SubMeshCount;
    SubMesh* SubMeshes;
    
private:
    MaterialSys::GraphicsResource* VertexBuffer;
    MaterialSys::GraphicsResource* IndexBuffer;
    
    void* TriangleData;
    _uint TriangleDataSize;
    
    void* IndexData;
    _uint IndexDataSize;
    
    _uint VerticesCount;
    _uint IndicesCount;
};

}

#endif /* Mesh_hpp */
