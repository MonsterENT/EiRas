#include "MaterialDX12Bridge.h"
#include <Material/Shader.hpp>
#include <PlatformDependency/OnDX/Shader/ShaderDX12Bridge.h>
#include <PlatformDependency/OnDX/Material/MaterialDX12.h>

using MaterialSys::MaterialDX12Bridge;
using MaterialSys::Shader;

MaterialDX12Bridge::MaterialDX12Bridge(std::string name, Shader* shaderObj)
{
    raw_obj = new MaterialDX12(name, shaderObj);
}

void MaterialDX12Bridge::SetProperty(int propertyID, void* res)
{
    ((MaterialDX12*)raw_obj)->SetProperty(propertyID, res);
}

void MaterialDX12Bridge::UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj)
{
    MaterialDX12* obj = (MaterialDX12*)raw_obj;
    //obj->UpdateRenderState(renderState)
}
