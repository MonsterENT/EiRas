//
//  Material.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Material.hpp"
#include "Shader.hpp"
#include <Graphics/GraphicsRenderState.hpp>

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/MaterialMetalBridge.hpp>
#endif

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/MaterialDX12Bridge.h>
#endif

using Graphics::GraphicsRenderState;

using MaterialSys::Material;
using MaterialSys::Shader;

Material::Material(std::string name, Shader* shader)
{
    this->RenderState = new GraphicsRenderState();

#if GRAPHICS_METAL
    this->PlatformBridge = new MaterialMetalBridge(name);
#endif

#if GRAPHICS_DX
    this->PlatformBridge = new MaterialDX12Bridge(name, shader);
#endif

    this->shader = shader;
    //init platform pso
    FinishStateChange();
}

void Material::SetProperty(int propertyId, void* res)
{
#if GRAPHICS_DX
    ((MaterialDX12Bridge*)PlatformBridge)->SetProperty(propertyId, res);
#endif
}

void Material::FinishStateChange()
{
#if GRAPHICS_METAL
    ((MaterialMetalBridge*)this->PlatformBridge)->UpdateRenderState(RenderState, shader);
#endif

}
