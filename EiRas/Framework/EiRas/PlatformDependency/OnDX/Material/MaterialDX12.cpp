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

#include <PlatformDependency/OnDX/Material/GraphicsResourceDescriptorHeapDX12.h>
#include <PlatformDependency/OnDX/ResourceHeapManager/ResourceDescriptorHeapManager.hpp>

using namespace MaterialSys;
using namespace Graphics;
using GraphicsAPI::EiRasDX12;

MaterialDX12::MaterialDX12(std::string Name, ShaderDX12* shaderObj, Material* matObj)
{
    this->Name = Name;
    RawShaderObj = shaderObj;
    RawMatObj = matObj;

#if GRAPHICS_DX
    ResourceDescriptorHeapManager::ShareInstance()->HeapPool[0]->RegMaterial(RawMatObj);
#endif
}

void MaterialDX12::UpdateRenderState(Graphics::GraphicsRenderState* renderState, ShaderDX12* shaderObj, _uint pass)
{
#pragma warning("Remove it")
    GET_ACTIVED_CMD(cmdBuffer);
    
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

void MaterialDX12::Release()
{
    ResourceDescriptorHeapManager::ShareInstance()->HeapPool[0]->RemoveMaterial(RawMatObj);
}