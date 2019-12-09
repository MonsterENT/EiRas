#include "MaterialDX12.h"
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <Material/Shader.hpp>
#include <Material/ShaderLayout.h>
#include <Material/MaterialLayout.hpp>
#include <PlatformDependency/OnDX/DX12Utils.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ConstantBufferDX12.h>

using namespace MaterialSys;
using GraphicsAPI::EiRasDX12;

MaterialDX12::MaterialDX12(std::string name, ShaderDX12* shaderObj)
{
    Name = name;
    RawShaderObj = shaderObj;
    PipelineState = 0;
}

void MaterialDX12::SetProperty(MaterialProp* prop, void* res)
{
    GraphicsResourceDX12* obj = (GraphicsResourceDX12*)prop->Resource->PlatformBridge->raw_obj;
    if (obj->ResType == GraphicsResourceType::CBV)
    {
        ConstantBufferDX12* cbObj = (ConstantBufferDX12*)obj;
        memcpy(cbObj->ResMappingDestPtr, res, cbObj->GetBufferSize());
    }
}

void MaterialDX12::UpdateRenderState(Graphics::GraphicsRenderState* renderState, ShaderDX12* shaderObj)
{
    GET_EIRAS_DX12(deviceObj)
    DX12Utils::g_createPSO(deviceObj->device, shaderObj->VertexFunc, shaderObj->PixelFunc, PipelineState, shaderObj->RootSignature);
}
