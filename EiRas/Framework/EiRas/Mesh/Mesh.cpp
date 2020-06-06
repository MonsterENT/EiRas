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

void Mesh::BuildBuffer(MeshType inputType)
{
    for (_uint i = 0; i < SubMeshCount; i++)
    {
        SubMesh* subMesh = &SubMeshes[i];
        subMesh->PackData(inputType);

        MeshBuffer* vertexBuffer = MeshBufferManager::GetManager()->GetValideVertexBufferWithSize(subMesh->_PackedData->VertexDataSize, subMesh->_PackedData->VertexDataStride);
        MeshBuffer* indexBuffer = MeshBufferManager::GetManager()->GetValideIndexBufferWithSize(subMesh->_PackedData->IndexDataSize, subMesh->_PackedData->IndexDataStride);

//        subMesh->VertexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, GraphicsResourceVisibility::VISIBILITY_VERTEX, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, true);
//        subMesh->VertexBuffer->InitAsDefault(subMesh->TriangleDataSize);
//        subMesh->VertexBuffer->SetResource(subMesh->TriangleData, true);
//
//        subMesh->IndexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, GraphicsResourceVisibility::VISIBILITY_VERTEX, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, true);
//        subMesh->IndexBuffer->InitAsDefault(subMesh->IndexDataSize);
//        subMesh->IndexBuffer->SetResource(subMesh->IndicesData, true);
//
//#ifdef GRAPHICS_DX
//        ((MeshDX12Bridge*)PlatformBridge)->BuildBufferView(subMesh->VertexBuffer->PlatformBridge, subMesh->TriangleDataSize, subMesh->VertexCount,
//            subMesh->IndexBuffer->PlatformBridge, subMesh->IndexDataSize);
//#endif
    }

#ifdef GRAPHICS_METAL
    ((MeshMetalBridge*)PlatformBridge)->BuildBuffer(VertexBuffer->PlatformBridge, IndexBuffer->PlatformBridge, VerticesCount, IndicesCount, 0, 0);
#endif


}