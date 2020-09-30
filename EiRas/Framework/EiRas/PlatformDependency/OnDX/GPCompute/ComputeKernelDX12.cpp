#include "ComputeKernelDX12.hpp"
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/DX12Utils.h>
#include <Material/ShaderLayout.h>
#include <PlatformDependency/OnDX/Shader/ShaderLayoutDX12.hpp>

using namespace GPCompute;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;

ComputeKernelDX12::ComputeKernelDX12()
{
    Layout = NULL;
    kernelFuncBlob = NULL;
    _ComputePipelineStateObject = NULL;
}

ComputeKernelDX12::~ComputeKernelDX12()
{
    if (Layout != NULL)
    {
        delete Layout;
    }

    if (_ComputePipelineStateObject != NULL)
    {
        _ComputePipelineStateObject->Release();
    }

    if (kernelFuncBlob != NULL)
    {
        kernelFuncBlob->Release();
    }
}

void ComputeKernelDX12::SetLayout(MaterialSys::ShaderLayout* layout, MaterialSys::MaterialLayout* resLayout)
{
    Layout = layout;
    ResLayout = resLayout;
}

void ComputeKernelDX12::AddKernel(LPCSTR fileName, LPCSTR kernelName)
{
    assert(DX12Utils::g_compileShader(fileName, kernelName, "cs_5_1", kernelFuncBlob));
}

void ComputeKernelDX12::Build()
{
    assert(Layout != NULL);
    assert(kernelFuncBlob != NULL);

    GET_EIRAS_DX12(deviceObj);;

    D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {};
    desc.CS = CD3DX12_SHADER_BYTECODE(kernelFuncBlob);
    desc.NodeMask = 0;
    desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
    desc.pRootSignature = ((ShaderLayoutDX12*)Layout->PlatformBridge->raw_obj)->m_RootSignature;
    HRESULT hr = deviceObj->device->CreateComputePipelineState(&desc, IID_PPV_ARGS(&_ComputePipelineStateObject));
    assert(hr == S_OK);
}

ID3D12RootSignature* ComputeKernelDX12::GetRootSignature()
{
    if (Layout != NULL)
    {
        return ((ShaderLayoutDX12*)Layout->PlatformBridge->raw_obj)->m_RootSignature;
    }

    return NULL;
}