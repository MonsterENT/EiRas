//
//  CommandBuffer.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "CommandBuffer.hpp"

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

using MeshSys::Mesh;
using Graphics::CommandBuffer;

CommandBuffer::CommandBuffer(std::string name)
{
    this->name = name;
#if GRAPHICS_METAL
    PlatformBridge = new CommandBufferMetalBridge(name);
#endif

#if GRAPHICS_DX
    PlatformBridge = new CommandBufferDX12Bridge(name);
#endif
}

void CommandBuffer::SetMaterial(MaterialSys::Material* material)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->SetMaterial(material);
#endif
}

void CommandBuffer::DrawMesh(Mesh* mesh)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->DrawMesh(mesh->GetVertices(), mesh->GetMeshDataSize(), 0);
#endif
}

void CommandBuffer::BeginFrame()
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->BeginFrame();
#endif
}

void CommandBuffer::Commit()
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->Commit();
#endif
}

void CommandBuffer::Present()
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->Present();
#endif
}
