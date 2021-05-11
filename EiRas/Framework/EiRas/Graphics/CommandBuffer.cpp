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
#include <Basic/TransformSys.hpp>
#include <GPCompute/ComputeKernel.hpp>

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/CommandBuffer/CommandBufferMetalBridge.hpp>
#endif

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/CommandBuffer/CommandBufferDX12Bridge.h>
#endif

#include <Mesh/Mesh.hpp>

using namespace BasicComponent;
using namespace MaterialSys;
using namespace Graphics;
using namespace GPCompute;

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

void CommandBuffer::SetMaterial(MaterialSys::Material* material, _uint pass)
{
#if GRAPHICS_METAL
    ((CommandBufferMetalBridge*)PlatformBridge)->SetMaterial(material);
#endif

#if GRAPHICS_DX
    ((CommandBufferDX12Bridge*)PlatformBridge)->SetMaterial(material, pass);
#endif
}

void CommandBuffer::SetTransform(BasicComponent::TransformSys* transform)
{
    if (transform != 0 && transform->_WorldMatCB != 0)
    {
        ((CommandBufferDX12Bridge*)PlatformBridge)->SetTransformGraphics(transform->_WorldMatCB);
    }
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

void CommandBuffer::DrawRenderData(RenderData* render)
{
    ((CommandBufferDX12Bridge*)PlatformBridge)->DrawRenderData(render);
}

void CommandBuffer::DispatchComputeKernel(GPCompute::ComputeKernel* kernel, Math::int3 groupCount)
{
    ((CommandBufferDX12Bridge*)PlatformBridge)->DispatchComputeKernel(kernel, groupCount);
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
    ((CommandBufferDX12Bridge*)PlatformBridge)->Reset();
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
