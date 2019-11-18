//
//  Material.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Material.hpp"
#include <Graphics/GraphicsRenderState.hpp>
#include "PlatformDependency/Material/Metal/MaterialMetalBridge.hpp"

using Graphics::GraphicsRenderState;

using MaterialSys::Material;

Material::Material(std::string name, Shader* shader)
{
    this->RenderState = new GraphicsRenderState();
    this->PlatformBridge = new MaterialMetalBridge(name);
    this->shader = shader;
    //init platform pso
    FinishStateChange();
}

void Material::FinishStateChange()
{
    ((MaterialMetalBridge*)this->PlatformBridge)->UpdateRenderState(RenderState, shader);
}
