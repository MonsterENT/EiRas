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

using Graphics::CommandBuffer;

CommandBuffer::CommandBuffer(std::string name)
{
    PlatformBridge = new CommandBufferMetalBridge(name);
}

void CommandBuffer::SetGraphicsRenderState(GraphicsRenderSate* renderState)
{
    
}

void CommandBuffer::SetMaterial(Material* material)
{
    
}

void CommandBuffer::DrawMesh(Mesh* mesh)
{
    
}
