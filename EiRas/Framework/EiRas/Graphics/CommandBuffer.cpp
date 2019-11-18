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
#include "CommandBufferMetalBridge.hpp"
#include <Mesh/Mesh.hpp>

using MeshSys::Mesh;
using Graphics::CommandBuffer;

CommandBuffer::CommandBuffer(std::string name)
{
    PlatformBridge = new CommandBufferMetalBridge(name);
}

void CommandBuffer::SetMaterial(MaterialSys::Material* material)
{
    ((CommandBufferMetalBridge*)PlatformBridge)->SetMaterial(material->PlatformBridge);
}

void CommandBuffer::DrawMesh(Mesh* mesh)
{
    ((CommandBufferMetalBridge*)PlatformBridge)->DrawMesh(mesh->GetVertices(), mesh->GetMeshDataSize(), 0);
}

void CommandBuffer::BeginFrame()
{
    ((CommandBufferMetalBridge*)PlatformBridge)->BeginFrame();
}

void CommandBuffer::Commit()
{
    ((CommandBufferMetalBridge*)PlatformBridge)->Commit();
}

void CommandBuffer::Present()
{
    ((CommandBufferMetalBridge*)PlatformBridge)->Present();
}
