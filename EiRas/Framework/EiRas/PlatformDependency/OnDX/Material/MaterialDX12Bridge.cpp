#include "MaterialDX12Bridge.h"
#include <Material/Shader.hpp>
#include <PlatformDependency/OnDX/Shader/ShaderDX12Bridge.h>
#include <PlatformDependency/OnDX/Material/MaterialDX12.h>

using namespace MaterialSys;

MaterialDX12Bridge::MaterialDX12Bridge(std::string name, EiRasPlatformBridgeProtocol* shaderObj)
{
    raw_obj = new MaterialDX12(name, (ShaderDX12*)shaderObj->raw_obj);
}

void MaterialDX12Bridge::SetProperty(MaterialProp* prop, void* res)
{
    ((MaterialDX12*)raw_obj)->SetProperty(prop, res);
}

void MaterialDX12Bridge::UpdateRenderState(Graphics::GraphicsRenderState* renderState, EiRasPlatformBridgeProtocol* shaderObj)
{
    MaterialDX12* obj = (MaterialDX12*)raw_obj;
    obj->UpdateRenderState(renderState, (ShaderDX12*)shaderObj->raw_obj);
}
