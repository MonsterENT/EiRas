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
#include <Graphics/RenderTexture.hpp>

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/CommandBuffer/CommandBufferMetalBridge.hpp>
#endif

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/CommandBuffer/CommandBufferDX12Bridge.h>
#endif

#ifdef GRAPHICS_DX
#include <PlatformDependency/OnDX/ResourceHeapManager/ResourceHeapManager.hpp>
#endif

#include <Mesh/Mesh.hpp>

using namespace MaterialSys;
using namespace Graphics;

CommandBuffer::CommandBuffer(std::string Name)
{
    this->Name = Name;

#if GRAPHICS_METAL
    PlatformBridge = new CommandBufferMetalBridge(Name);
#endif

#if GRAPHICS_DX
    PlatformBridge = new CommandBufferDX12Bridge(Name);
    
    resourceHeap = ResourceHeapManager::ShareInstance()->HeapPool[0];
#endif
}

void CommandBuffer::SetMaterial(MaterialSys::Material* material, _uint pass)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->SetMaterial(material);
#endif

#if GRAPHICS_DX
    ((CommandBufferDX12Bridge*)PlatformBridge)->SetMaterial(material, pass);
#endif
}

void CommandBuffer::DrawMesh(MeshSys::Mesh* mesh)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->DrawMesh(mesh->PlatformBridge);
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
#if GRAPHICS_DX
    EiRasPlatformBridgeProtocol* tmpBridge = NULL;
    if (resourceHeap)
    {
        tmpBridge = resourceHeap->PlatformBridge;
    }
    ((CommandBufferDX12Bridge*)PlatformBridge)->Reset(tmpBridge);
#endif

#if GRAPHICS_METAL
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

void CommandBuffer::SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth, float maxDepth)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->Commit(present);
#endif

#if GRAPHICS_DX
    ((CommandBufferDX12Bridge*)PlatformBridge)->SetViewPort(topLeftX, topLeftY, width, height, minDepth, maxDepth);
#endif
}

void CommandBuffer::SetRenderTexture(Graphics::RenderTexture* renderTexture)
{
#if GRAPHICS_DX
    EiRasPlatformBridgeProtocol* pb = renderTexture == 0 ? 0 : renderTexture->PlatformBridge;
    ((CommandBufferDX12Bridge*)PlatformBridge)->SetRenderTexture(pb);
#endif
}

#if GRAPHICS_DX
void CommandBuffer::_ReFillHeap()
{
    _uint materialPropCount = 0;
    tmpMaterialTableArray.clear();
    MaterialCache_MAP::iterator it = MaterialMap.begin();
    while (it != MaterialMap.end())
    {
        Material* mat = it->second;
        for (_uint slotIndex = 0; slotIndex < mat->materialLayout->SlotNum; slotIndex++)
        {
            MaterialSlot* slot = mat->materialLayout->Slots[slotIndex];
            if (slot->SlotType == MaterialSlotType::MaterialSlotType_Table)
            {
                tmpMaterialTableArray.push_back((MaterialTable*)slot);
                materialPropCount += ((MaterialTable*)slot)->PropNum;
            }
        }
        it++;
    }

#pragma message("TOFIX")
    if (tmpMaterialTableArray.size() > 0)
    {
        resourceHeap->FillHeap((_uint)tmpMaterialTableArray.size(), &tmpMaterialTableArray[0]);
    }
}

void CommandBuffer::RegMaterial(MaterialSys::Material* material)
{
    MaterialMap.insert(MaterialCache_PAIR(material->Name, material));
    _ReFillHeap();
}

void CommandBuffer::RemoveMaterial(MaterialSys::Material* material)
{
    MaterialMap.erase(material->Name);
    _ReFillHeap();
}
#endif
