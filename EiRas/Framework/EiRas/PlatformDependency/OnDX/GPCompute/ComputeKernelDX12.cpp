#include "ComputeKernelDX12.hpp"
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>

using namespace GPCompute;
using GraphicsAPI::EiRasDX12;

ComputeKernelDX12::ComputeKernelDX12()
{
}

void ComputeKernelDX12::SetRootLayout()
{
}

void ComputeKernelDX12::AddKernel(LPCSTR fileName, LPCSTR kernelName)
{
}

void ComputeKernelDX12::Build()
{
    GET_EIRAS_DX12(deviceObj);;

    D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {};
    //desc.CS 
    desc.NodeMask = 0;
    desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
    //desc.pRootSignature
    HRESULT hr = deviceObj->device->CreateComputePipelineState(&desc, IID_PPV_ARGS(&_ComputePipelineStateObject));
}