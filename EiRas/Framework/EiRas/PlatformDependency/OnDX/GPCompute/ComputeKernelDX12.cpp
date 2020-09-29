#include "ComputeKernelDX12.hpp"
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/DX12Utils.h>
#include <Material/ShaderLayout.h>

using namespace GPCompute;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;

ComputeKernelDX12::ComputeKernelDX12()
{
}

void ComputeKernelDX12::SetRootLayout(ShaderLayout* layout)
{
}

void ComputeKernelDX12::AddKernel(LPCSTR fileName, LPCSTR kernelName)
{
    if (!DX12Utils::g_compileShader(fileName, kernelName, "vs_5_1", kernelFuncBlob))
    {

    }
}

void ComputeKernelDX12::Build()
{
    GET_EIRAS_DX12(deviceObj);;

    D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {};
    desc.CS = CD3DX12_SHADER_BYTECODE(kernelFuncBlob);
    desc.NodeMask = 0;
    desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
    //desc.pRootSignature
    HRESULT hr = deviceObj->device->CreateComputePipelineState(&desc, IID_PPV_ARGS(&_ComputePipelineStateObject));
}