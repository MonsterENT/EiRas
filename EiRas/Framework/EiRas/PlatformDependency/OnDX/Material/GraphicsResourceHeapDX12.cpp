#include "GraphicsResourceHeapDX12.h"
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnDX/Material/ConstantBufferDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceDX12.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <Material/MaterialLayout.hpp>
#include <vector>

using std::vector;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;

GraphicsResourceHeapDX12::GraphicsResourceHeapDX12(_uint propCount)
{
    this->propCount = propCount;
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heapDesc.NumDescriptors = propCount;

    GET_EIRAS_DX12(deviceObj)

    deviceObj->device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));

    Offset = deviceObj->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

GraphicsResourceHeapDX12::~GraphicsResourceHeapDX12()
{
    heap->Release();
    heap = NULL;
}

void GraphicsResourceHeapDX12::FillHeap(_uint tableCount, MaterialTable** tableArray)
{
    GET_EIRAS_DX12(deviceObj)
    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(heap->GetCPUDescriptorHandleForHeapStart());
    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(heap->GetGPUDescriptorHandleForHeapStart());

    for (_uint tableIndex = 0; tableIndex < tableCount; tableIndex++)
    {
        MaterialTable* table = tableArray[tableIndex];
    
        for (_uint propIndex = 0; propIndex < table->PropNum; propIndex++)
        {
            MaterialProp* prop = table->Props[propIndex];
    
            GraphicsResourceDX12* resObj = (GraphicsResourceDX12*)prop->Resource->PlatformBridge->raw_obj;
    
            if (resObj->Behaviors->ResourceType == GraphicsResourceType::CBV)
            {
                ConstantBufferDX12* resCb = (ConstantBufferDX12*)resObj;
                D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc = {};
                viewDesc.BufferLocation = resCb->Resource->GetGPUVirtualAddress();
                viewDesc.SizeInBytes = (resCb->GetBufferSize() + 255) & ~255;
                deviceObj->device->CreateConstantBufferView(&viewDesc, cpuHandle);
            }
            else if (resObj->Behaviors->ResourceType == GraphicsResourceType::CBV)
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
    
            cpuHandle.Offset(1, Offset);
            gpuHandle.Offset(1, Offset);
        }
    }
}
