//
//  CommandBufferMetalBridge.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "CommandBufferMetalBridge.hpp"
#include <Material/Material.hpp>
#include "CommandBufferMetalAdapter.hpp"

using Graphics::CommandBufferMetalBridge;

CommandBufferMetalBridge::CommandBufferMetalBridge(std::string name)
{
    raw_obj = createCommandBufferMetal(name);
}

void CommandBufferMetalBridge::SetMaterial(MaterialSys::Material* material)
{
    setMaterialMetal(raw_obj, material->PlatformBridge->raw_obj, &material->Props, &material->LayoutTables);
}

void CommandBufferMetalBridge::DrawMesh(void* meshData, int dataSize, int index)
{
    drawMeshMetal(raw_obj, meshData, dataSize, index);
}
void CommandBufferMetalBridge::BeginFrame()
{
    beginFrameMetal(raw_obj);
}

void CommandBufferMetalBridge::Present()
{
    presentMetal(raw_obj);
}

void CommandBufferMetalBridge::Commit()
{
    commitMetal(raw_obj);
}
