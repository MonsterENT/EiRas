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
    setMaterialMetal(raw_obj, material);
}

void CommandBufferMetalBridge::DrawMesh(EiRasPlatformBridgeProtocol* meshObjBridge)
{
    drawMeshMetal(raw_obj, meshObjBridge->raw_obj);
}
void CommandBufferMetalBridge::BeginFrame()
{
    beginFrameMetal(raw_obj);
}

void CommandBufferMetalBridge::Reset()
{
    resetCmdBufferMetal(raw_obj);
}

void CommandBufferMetalBridge::Commit(bool present)
{
    commitMetal(raw_obj, present);
}
