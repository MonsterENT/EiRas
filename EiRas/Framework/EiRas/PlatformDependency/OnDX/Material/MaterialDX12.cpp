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
#include <PlatformDependency/OnDX/CommandBuffer/CommandBufferDX12.h>

using namespace MaterialSys;
using namespace Graphics;
using GraphicsAPI::EiRasDX12;

MaterialDX12::MaterialDX12(std::string Name, ShaderDX12* shaderObj)
{
    this->Name = Name;
    RawShaderObj = shaderObj;
}

void MaterialDX12::SetProperty(MaterialProp* prop, void* res)
{
    if (prop->Resource->Behaviors.ResourceType == GraphicsResourceType::CBV)
    {
        prop->Resource->SetResource(res, false);
    }
}

void MaterialDX12::UpdateRenderState(Graphics::GraphicsRenderState* renderState, ShaderDX12* shaderObj, void* rawCmdBuffer, _uint pass)
{
    CommandBufferDX12* cmdBuffer = (CommandBufferDX12*)rawCmdBuffer;
    
    _uint numRT = 0;
    DXGI_FORMAT rtFormats[8];
    DXGI_FORMAT depthFormat;
    cmdBuffer->GetCurrentRenderTextureInfo(&numRT, rtFormats, &depthFormat);
    if (pass >= PassedPipelineState.size())
    {
        PassedPipelineState.push_back(RawShaderObj->_GetPSO(renderState, numRT, rtFormats, depthFormat, pass));
    }
    else
    {
        PassedPipelineState[pass] = RawShaderObj->_GetPSO(renderState, numRT, rtFormats, depthFormat, pass);
    }
}