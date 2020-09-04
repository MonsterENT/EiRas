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
    if (VertexCount == 0 || IndexCount == 0)
    {
        return;
    }
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

void Mesh::SetVertexData(Math::float3* position, Math::float2* uv, _uint count)
{
    VertexCount = count;
    RELEASE_ARRAY(PositionData);
    PositionData = position;

    RELEASE_ARRAY(UVData);
    UVData = uv;
}

void Mesh::SetIndexData(_uint* index, _uint count)
{
    IndexCount = count;
    RELEASE_ARRAY(IndexData);
    IndexData = index;
}

void Mesh::SetVertexData(std::vector<Math::float3> position, std::vector<Math::float2> uv)
{
    VertexCount = position.size();
    RELEASE_ARRAY(PositionData);
    COPY_VECTOR_DATA(float3, position, PositionData);
    
    RELEASE_ARRAY(UVData);
    COPY_VECTOR_DATA(float2, uv, UVData);
}

void Mesh::SetVertexData(std::vector<float3> position, std::vector<float3> normal, std::vector<float2> uv)
{
    VertexCount = position.size();
    RELEASE_ARRAY(PositionData);
    COPY_VECTOR_DATA(float3, position, PositionData);

    RELEASE_ARRAY(NormalData);
    COPY_VECTOR_DATA(float3, normal, NormalData);

    RELEASE_ARRAY(UVData);
    COPY_VECTOR_DATA(float2, uv, UVData);
}

void Mesh::SetVertexData(std::vector<Math::float3> position, std::vector<Math::float3> normal, std::vector<Math::float2> uv, std::vector<Math::float4> color)
{
    SetVertexData(position, normal, uv);

    RELEASE_ARRAY(ColorData);
    COPY_VECTOR_DATA(float4, color, ColorData);
}


void Mesh::SetIndexData(std::vector<_uint> index)
{
    RELEASE_ARRAY(IndexData);
    IndexCount = index.size();
    COPY_VECTOR_DATA(_uint, index, IndexData);
}