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
#include <Graphics/VertexDataType.h>
#include <Math/Math.hpp>

#include <Component/LogSys/LogManager.hpp>

using namespace MeshSys;
using namespace MaterialSys;
using namespace Graphics;

Mesh::Mesh(std::string name)
{
    this->Name = name;
#ifdef GRAPHICS_DX
    PlatformBridge = new MeshDX12Bridge();
#endif

#ifdef GRAPHICS_METAL
    PlatformBridge = new MeshMetalBridge();
#endif

    SubMeshCount = 0;
}

void Mesh::LoadDataFromFile(std::string fileName)
{
    //Load MeshData
    LoadMeshFromFile(fileName, this);
}

void Mesh::BuildBuffer(MeshType inputType)
{
    for (_uint i = 0; i < SubMeshCount; i++)
    {
        SubMesh* subMesh = &SubMeshes[i];

        if (inputType == MeshType::VertexInput3D)
        {
            subMesh->TriangleData = new VertexData3D[subMesh->VerticesCount];
            subMesh->TriangleDataSize = sizeof(VertexData3D) * subMesh->VerticesCount;
        }
        else
        {
            subMesh->TriangleData = new VertexData2D[subMesh->VerticesCount];
            subMesh->TriangleDataSize = sizeof(VertexData2D) * subMesh->VerticesCount;
        }
        subMesh->IndexDataSize = sizeof(_uint) * subMesh->IndicesCount;

        for (_uint j = 0; j < subMesh->VerticesCount; j++)
        {
            if (inputType == MeshType::VertexInput3D)
            {
                VertexData3D* tmpData = (VertexData3D*)subMesh->TriangleData + j;
                if (subMesh->PositionData)
                    tmpData->Position = float3(subMesh->PositionData[j].x, subMesh->PositionData[j].y, subMesh->PositionData[j].z);
                if (subMesh->UVData)
                    tmpData->UV = float2(subMesh->UVData[j].x, subMesh->UVData[j].y);
                if (subMesh->NormalData)
                    tmpData->Normal = float3(subMesh->NormalData[j].x, subMesh->NormalData[j].y, subMesh->NormalData[j].z);
            }
            else
            {
                VertexData2D* tmpData = (VertexData2D*)subMesh->TriangleData + j;
                if (subMesh->PositionData)
                    tmpData->Position = float2(subMesh->PositionData[j].x, subMesh->PositionData[j].y);
                if (subMesh->UVData)
                    tmpData->UV = float2(subMesh->UVData[j].x, subMesh->UVData[j].y);
            }
        }

        subMesh->VertexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, GraphicsResourceVisibility::VISIBILITY_VERTEX, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, true);
        subMesh->VertexBuffer->InitAsDefault(subMesh->TriangleDataSize);
        subMesh->VertexBuffer->SetResource(subMesh->TriangleData, true);

        subMesh->IndexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, GraphicsResourceVisibility::VISIBILITY_VERTEX, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, true);
        subMesh->IndexBuffer->InitAsDefault(subMesh->IndexDataSize);
        subMesh->IndexBuffer->SetResource(subMesh->IndicesData, true);

#ifdef GRAPHICS_DX
        ((MeshDX12Bridge*)PlatformBridge)->BuildBufferView(subMesh->VertexBuffer->PlatformBridge, subMesh->TriangleDataSize, subMesh->VerticesCount,
            subMesh->IndexBuffer->PlatformBridge, subMesh->IndexDataSize);
#endif
    }

#ifdef GRAPHICS_METAL
    ((MeshMetalBridge*)PlatformBridge)->BuildBuffer(VertexBuffer->PlatformBridge, IndexBuffer->PlatformBridge, VerticesCount, IndicesCount, 0, 0);
#endif


}