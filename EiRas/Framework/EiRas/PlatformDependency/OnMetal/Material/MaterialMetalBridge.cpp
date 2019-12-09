//
//  MaterialMetalBridge.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/13/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "MaterialMetalBridge.hpp"
#include <Graphics/GraphicsRenderState.hpp>
#include "MaterialMetalAdapter.hpp"

using Graphics::GraphicsRenderState;
using MaterialSys::MaterialMetalBridge;

MaterialMetalBridge::MaterialMetalBridge(std::string name)
{
    raw_obj = createMaterialMetal(name);
}

void MaterialMetalBridge::SetProperty(MaterialProp* prop, void* res)
{
    
}

void MaterialMetalBridge::UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj)
{
    UpdateRenderStateMetal(raw_obj, renderState, shaderObj);
}
