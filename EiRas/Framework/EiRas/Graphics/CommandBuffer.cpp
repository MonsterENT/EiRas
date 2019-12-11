//
//  CommandBuffer.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "CommandBuffer.hpp"
#include <Material/MaterialLayout.hpp>
#include <Material/GraphicsResource.hpp>
#include <Material/Material.hpp>
#include <Graphics/GraphicsRenderState.hpp>
#include <Global/PlatformDefine.h>

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/CommandBuffer/CommandBufferMetalBridge.hpp>
#endif

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/CommandBuffer/CommandBufferDX12Bridge.h>
#endif

#include <Mesh/Mesh.hpp>

using namespace MaterialSys;
using Graphics::CommandBuffer;

CommandBuffer::CommandBuffer(std::string Name)
{
    this->Name = Name;

#if GRAPHICS_METAL
    PlatformBridge = new CommandBufferMetalBridge(Name);
#endif

#if GRAPHICS_DX
    PlatformBridge = new CommandBufferDX12Bridge(Name);
#endif
}

void CommandBuffer::SetMaterial(MaterialSys::Material* material)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->SetMaterial(material);
#endif

#if GRAPHICS_DX
    ((CommandBufferDX12Bridge*)PlatformBridge)->SetMaterial(material);
#endif
}

void CommandBuffer::DrawMesh(Mesh* mesh)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->DrawMesh(mesh->GetVertices(), mesh->GetMeshDataSize(), 0);
#endif

#if GRAPHICS_DX
    ((CommandBufferDX12Bridge*)PlatformBridge)->DrawMesh(mesh);
#endif
}

void CommandBuffer::BeginFrame()
{
#if GRAPHICS_DX
    ((CommandBufferDX12Bridge*)PlatformBridge)->BeginFrame();
#endif

#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->BeginFrame();
#endif
}

void CommandBuffer::Reset()
{
    if (!resourceHeap)
    {
        UINT materialPropCount = 0;
        tmpMaterialTableArray.clear();
        MaterialCache_MAP::iterator it = MaterialMap.begin();
        while (it != MaterialMap.end())
        {
            Material* mat = it->second;
            for (UINT matTableIndex = 0; matTableIndex < mat->LayoutTables.size(); matTableIndex++)
            {
                MaterialTable* table = mat->LayoutTables[matTableIndex];
                tmpMaterialTableArray.push_back(table);
                materialPropCount += table->PropNum;
            }
            it++;
        }
        resourceHeap = new GraphicsResourceHeap(materialPropCount, tmpMaterialTableArray.size(), &tmpMaterialTableArray[0]);
    }

#if GRAPHICS_DX
    ((CommandBufferDX12Bridge*)PlatformBridge)->Reset(resourceHeap->PlatformBridge);
#endif
    
#if GRAPHICE_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->Reset();
#endif
}

void CommandBuffer::Commit(bool present)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->Commit(present);
#endif

#if GRAPHICS_DX
    ((CommandBufferDX12Bridge*)PlatformBridge)->Commit(present);
#endif
}

void CommandBuffer::RegMaterial(MaterialSys::Material* material)
{
    MaterialMap.insert(MaterialCache_PAIR(material->Name, material));

    if (resourceHeap)
    {
        resourceHeap = NULL;
        delete resourceHeap;
    }
}

void CommandBuffer::RemoveMaterial(MaterialSys::Material* material)
{
    MaterialMap.erase(material->Name);
    if (resourceHeap)
    {
        resourceHeap = NULL;
        delete resourceHeap;
    }
}
