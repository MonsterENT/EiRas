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

#include "MeshLoader.h"
#include <Graphics/GraphicsPipelineInput.h>
#include <Math/Math.hpp>

#include <Component/LogSys/LogManager.hpp>

using namespace MeshSys;
using namespace MaterialSys;
using namespace Graphics;

Mesh::Mesh(std::string Name)
{
    this->Name = Name;
#if GRAPHICS_DX
    PlatformBridge = new MeshDX12Bridge();
#endif
    
#if GRAPHICS_METAL
    PlatformBridge = new MeshMetalBridge();
#endif
    
    SubMeshCount = 0;
    VerticesCount = 0;
    IndicesCount = 0;
    //Load MeshData
    LoadMeshFromFile(Name, this);
}

void Mesh::BuildBuffer()
{
    for(_uint i = 0; i < SubMeshCount; i++)
    {
        SubMesh* subMesh = &SubMeshes[i];
        
        VerticesCount += subMesh->VerticesCount;
        IndicesCount += subMesh->IndicesCount;
    }
    
    TriangleData = new VertexData3D[VerticesCount];
    TriangleDataSize = sizeof(VertexData3D) * VerticesCount;
    
    IndexData = new _uint[IndicesCount];
    IndexDataSize = sizeof(_uint) * IndicesCount;
    
    _uint curMeshDataIndex = 0;
    _uint curIndexDataIndex = 0;
    for(_uint i = 0; i < SubMeshCount; i++)
    {
        SubMesh* subMesh = &SubMeshes[i];
        for(_uint j = 0; j < subMesh->VerticesCount; j++)
        {
            VertexData3D* tmpData = (VertexData3D*)TriangleData + curMeshDataIndex;
            tmpData->Position = subMesh->PositionData[j];
            tmpData->UV = subMesh->UVData[j];
            tmpData->Normal = subMesh->NormalData[j];
            curMeshDataIndex++;
        }
        
        memcpy((_uint*)IndexData + curIndexDataIndex, subMesh->IndicesData, subMesh->IndicesCount * sizeof(_uint));
        curIndexDataIndex += subMesh->IndicesCount;
    }

    
    VertexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, true, GetTriangleDataSize());
    VertexBuffer->SetResource(GetTriangleData(), true);
    
    IndexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, true, GetIndexDataSize());
    IndexBuffer->SetResource(GetIndexData(), true);

#if GRAPHICS_DX
    ((MeshDX12Bridge*)PlatformBridge)->BuildBuffer(VertexBuffer->PlatformBridge, IndexBuffer->PlatformBridge, VerticesCount, IndicesCount);
#endif

#if GRAPHICS_METAL
    ((MeshMetalBridge*)PlatformBridge)->BuildBuffer(VertexBuffer->PlatformBridge, IndexBuffer->PlatformBridge, VerticesCount, IndicesCount, 0, 0);
#endif
}

void* Mesh::GetTriangleData()
{
    return TriangleData;
}

_uint Mesh::GetTriangleDataSize()
{
    return TriangleDataSize;
}

void* Mesh::GetIndexData()
{
    return IndexData;
}

_uint Mesh::GetIndexDataSize()
{
    return IndexDataSize;
}
