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


static MeshBufferManager* g_MeshBfferManager = 0;
MeshBufferManager* MeshBufferManager::GetManager()
{
    if (g_MeshBfferManager == 0)
    {
        g_MeshBfferManager = new MeshBufferManager();
    }
    return g_MeshBfferManager;
}

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

void Mesh::BuildBuffer(MeshType inputType, bool noMoreUpdate)
{
    PackData(inputType);
    _VertexBuffer = MeshBufferManager::GetManager()->GetValideVertexBufferWithSize(_PackedData->VertexDataSize, _PackedData->VertexDataStride);
    _IndexBuffer = MeshBufferManager::GetManager()->GetValideIndexBufferWithSize(_PackedData->IndexDataSize, _PackedData->IndexDataStride);

    _VertexBuffer->Buffer = new GraphicsResource(Name, GraphicsResourceType::Default, GraphicsResourceVisibility::VISIBILITY_VERTEX, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, true);
    _VertexBuffer->Buffer->InitAsDefault(_VertexBuffer->BufferSize);
    _VertexBuffer->Buffer->SetResource(_PackedData->VertexData, noMoreUpdate);

    _IndexBuffer->Buffer = new GraphicsResource(Name, GraphicsResourceType::Default, GraphicsResourceVisibility::VISIBILITY_VERTEX, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, true);
    _IndexBuffer->Buffer->InitAsDefault(_PackedData->IndexDataSize);
    _IndexBuffer->Buffer->SetResource(_PackedData->IndexData, noMoreUpdate);

#ifdef GRAPHICS_DX
    ((MeshDX12Bridge*)PlatformBridge)->BuildBufferView(_VertexBuffer->Buffer->PlatformBridge, _PackedData->VertexDataSize, VertexCount,
        _IndexBuffer->Buffer->PlatformBridge, _PackedData->IndexDataSize);
#endif

    if (noMoreUpdate)
    {
        delete _PackedData;
        _PackedData = 0;
    }

#ifdef GRAPHICS_METAL
    ((MeshMetalBridge*)PlatformBridge)->BuildBuffer(VertexBuffer->PlatformBridge, IndexBuffer->PlatformBridge, VerticesCount, IndicesCount, 0, 0);
#endif
}

void Mesh::PackData(MeshType inputType)
{
    if (_PackedData == 0)
    {
        _PackedData = new MeshPackedData();
        if (inputType == MeshType::VertexInput3D)
        {
            _PackedData->VertexData = new VertexData3D[VertexCount];
            _PackedData->VertexDataStride = sizeof(VertexData3D);
        }
        else
        {
            _PackedData->VertexData = new VertexData2D[VertexCount];
            _PackedData->VertexDataStride = sizeof(VertexData2D);
        }
    }

    _PackedData->VertexDataSize = _PackedData->VertexDataStride * VertexCount;
    _PackedData->IndexDataStride = sizeof(_uint);
    _PackedData->IndexDataSize = sizeof(_uint) * IndexCount;
    _PackedData->IndexData = IndexData;

    for (_uint i = 0; i < VertexCount; i++)
    {
        if (inputType == MeshType::VertexInput3D)
        {
            VertexData3D* tmpData = (VertexData3D*)_PackedData->VertexData + i;
            if (PositionData)
                tmpData->Position = float3(PositionData[i].x, PositionData[i].y, PositionData[i].z);
            if (UVData)
                tmpData->UV = float2(UVData[i].x, UVData[i].y);
            if (NormalData)
                tmpData->Normal = float3(NormalData[i].x, NormalData[i].y, NormalData[i].z);
        }
        else
        {
            VertexData2D* tmpData = (VertexData2D*)_PackedData->VertexData + i;
            if (PositionData)
                tmpData->Position = float2(PositionData[i].x, PositionData[i].y);
            if (UVData)
                tmpData->UV = float2(UVData[i].x, UVData[i].y);
        }
    }
}