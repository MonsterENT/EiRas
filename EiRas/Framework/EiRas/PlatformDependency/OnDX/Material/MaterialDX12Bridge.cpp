#include "MaterialDX12Bridge.h"
#include <Material/Shader.hpp>
#include <PlatformDependency/OnDX/Shader/ShaderDX12Bridge.h>
#include <PlatformDependency/OnDX/Material/MaterialDX12.h>

using namespace MaterialSys;

MaterialDX12Bridge::MaterialDX12Bridge(std::string Name, EiRasPlatformBridgeProtocol* shaderObj, Material* matObj)
{
    raw_obj = new MaterialDX12(Name, (ShaderDX12*)shaderObj->raw_obj, matObj);
}

void MaterialDX12Bridge::UpdateRenderState(Graphics::GraphicsRenderState* renderState, EiRasPlatformBridgeProtocol* shaderObj, _uint pass)
{
    MaterialDX12* obj = (MaterialDX12*)raw_obj;
    obj->UpdateRenderState(renderState, (ShaderDX12*)shaderObj->raw_obj, pass);
}

MaterialDX12Bridge::~MaterialDX12Bridge()
{
    MaterialDX12* obj = (MaterialDX12*)raw_obj;
    obj->Release();
    delete raw_obj;
    raw_obj = 0;
}