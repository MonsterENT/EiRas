//
//  Mesh.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/18/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Mesh.hpp"

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Mesh/MeshDX12Bridge.h>
#endif

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Mesh/MeshMetalBridge.hpp>
#endif

#include <Graphics/GraphicsPipelineInput.h>
#include <Math/Math.hpp>

using namespace MeshSys;
using namespace MaterialSys;
using namespace Graphics;

//#if GRAPHICS_METAL
//static AAPLVertex triangleVertices[] =
//{
//    // 2D positions,    RGBA colors
//    { {  250,  -250 }, { 1, 0, 0, 1 } },
//    { { -250,  -250 }, { 0, 1, 0, 1 } },
//    { {    0,   250 }, { 0, 0, 1, 1 } },
//};
//#endif
//
//#if GRAPHICS_DX
//static VertexDefault triangleVertices[] =
//{
//    { { 0.5, -0.5, 0.5 }, { 0, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0 } },
//    { { -0.5, -0.5, 0.5 }, { 0, 0 }, { 0, 1, 0, 1 }, { 1, 0, 0 } },
//    { { 0, 0.5, 0.5 }, { 0, 0 }, { 0, 0, 1, 1 }, { 1, 0, 0 } }
//};
//#endif

Mesh::Mesh(std::string Name)
{
    this->Name = Name;
#if GRAPHICS_DX
    PlatformBridge = new MeshDX12Bridge();
#endif
    
#if GRAPHICS_METAL
    PlatformBridge = new MeshMetalBridge();
#endif
    
    VerticesCount = 0;
    IndicesCount = 0;
    //Load MeshData
}

void Mesh::BuildBuffer()
{
    MeshData = new VertexData3D[VerticesCount];
    for(_uint i = 0; i < VerticesCount; i++)
    {
        VertexData3D* tmpData = (VertexData3D*)MeshData + i;
        tmpData->Position = PositionData[i];
        tmpData->UV = UVData[i];
        tmpData->Normal = NormalData[i];
    }
    VertexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, true, GetMeshDataSize());
    VertexBuffer->SetResource(GetMeshData(), true);

#if GRAPHICS_DX
    ((MeshDX12Bridge*)PlatformBridge)->BuildBuffer(VertexBuffer->PlatformBridge, NULL, 3, -1);
#endif

#if GRAPHICS_METAL
    ((MeshMetalBridge*)PlatformBridge)->BuildBuffer(VertexBuffer->PlatformBridge, nullptr, 3, 0, 0, 0);
#endif
}

void* Mesh::GetMeshData()
{
    return MeshData;
}

_uint Mesh::GetMeshDataSize()
{
    return MeshDataSize;
}
