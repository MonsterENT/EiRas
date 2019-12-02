#include "ShaderResourceHeapDX12.h"
#include <PlatformDependency/OnDX/Shader/ShaderResource/ConstantBufferDX12.h>
#include <PlatformDependency/OnDX/Shader/ShaderResource/ShaderResourceDX12.h>
#include <PlatformDependency/OnDX/Resource/ResourceDX12.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>

#include <PlatformDependency/OnDX/DXMacro.h>

using GraphicsAPI::EiRasDX12;
using MaterialSys::ResourceDX12;
using MaterialSys::ConstantBufferDX12;
using MaterialSys::ShaderResourceDX12;

ShaderResourceHeapDX12::ShaderResourceHeapDX12(UINT resCount, ResourceDX12** resArray, UINT initCount)
{
    if (initCount == -1)
    {
        initCount = resCount;
    }
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heapDesc.NumDescriptors = resCount;

    GET_EIRAS_DX12(deviceObj)

    deviceObj->device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));

    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle =  CD3DX12_CPU_DESCRIPTOR_HANDLE(heap->GetCPUDescriptorHandleForHeapStart());
    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(heap->GetGPUDescriptorHandleForHeapStart());

    UINT offset = deviceObj->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    for (UINT i = 0; i < initCount; i++)
    {
        ResourceDX12* resObj = resArray[i];
        
        if (resObj->ResType == ResourceDX12::ResourceTypeDX12::TypeCB)
        {
            ConstantBufferDX12* resCb = (ConstantBufferDX12*)resObj;
            D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc = {};
            viewDesc.BufferLocation = resCb->Resource->GetGPUVirtualAddress();
            viewDesc.SizeInBytes = (resCb->GetBufferSize() + 255) & ~255;
            deviceObj->device->CreateConstantBufferView(&viewDesc, cpuHandle);
        }
        else if (resObj->ResType == ResourceDX12::ResourceTypeDX12::TypeSRV)
        {
            ShaderResourceDX12* resSrv = dynamic_cast<ShaderResourceDX12*>(resObj);
            D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
            srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            srvDesc.Format = resSrv->getTextureFormat();
            srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
            srvDesc.Texture2D.MipLevels = 1;
            deviceObj->device->CreateShaderResourceView(resSrv->Resource, &srvDesc, cpuHandle);
        }

        resObj->CpuHandle = cpuHandle;
        resObj->GpuHandle = gpuHandle;

        cpuHandle.Offset(1, offset);
        gpuHandle.Offset(1, offset);
    }
}


ShaderResourceHeapDX12::~ShaderResourceHeapDX12()
{
}
