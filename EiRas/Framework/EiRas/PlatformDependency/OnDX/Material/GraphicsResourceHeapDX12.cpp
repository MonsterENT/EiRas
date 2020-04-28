#include "GraphicsResourceHeapDX12.h"
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnDX/Material/ConstantBufferDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceRTDX12.hpp>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <Material/MaterialLayout.hpp>
#include <vector>

using std::vector;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;

#define HEAP_HEADER_OFFSET 30

GraphicsResourceHeapDX12::GraphicsResourceHeapDX12(_uint propCount)
{
    g_HeapOffset = 0;
    this->propCount = propCount;
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heapDesc.NumDescriptors = propCount;

    GET_EIRAS_DX12(deviceObj);

        deviceObj->device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));

    Offset = deviceObj->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

GraphicsResourceHeapDX12::~GraphicsResourceHeapDX12()
{
    heap->Release();
    heap = NULL;
}

inline void _FillHeapWithProp(CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle, CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle, MaterialProp* prop)
{
    GET_EIRAS_DX12(deviceObj);
    GraphicsResourceDX12* resObj = (GraphicsResourceDX12*)prop->Resource->PlatformBridge->raw_obj;

    if (prop->Resource->Behaviors.ResourceType == GraphicsResourceType::SRV)
    {
        ShaderResourceDX12* resSrv = (ShaderResourceDX12*)(resObj);
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Format = resSrv->TexFormat;
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;
        deviceObj->device->CreateShaderResourceView(resSrv->Resource, &srvDesc, cpuHandle);
    }
    else if (prop->Resource->Behaviors.ResourceType == GraphicsResourceType::CBV)
    {
        ConstantBufferDX12* resCb = (ConstantBufferDX12*)resObj;
        D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc = {};
        viewDesc.BufferLocation = resCb->Resource->GetGPUVirtualAddress();
        viewDesc.SizeInBytes = (resCb->GetBufferSize() + 255) & ~255;
        deviceObj->device->CreateConstantBufferView(&viewDesc, cpuHandle);
    }
    else if (prop->Resource->Behaviors.ResourceType == GraphicsResourceType::SRV_RT)
    {
        ShaderResourceRTDX12* resRT = (ShaderResourceRTDX12*)(resObj);
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Format = (DXGI_FORMAT)resRT->Format;
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;
        deviceObj->device->CreateShaderResourceView(resRT->Resource, &srvDesc, cpuHandle);
    }
}

void GraphicsResourceHeapDX12::DynamicFillHeap(MaterialSys::MaterialProp* prop)
{
    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle(heap->GetCPUDescriptorHandleForHeapStart());
    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(heap->GetGPUDescriptorHandleForHeapStart());

    cpuHandle.Offset(prop->_heapOffset, Offset);
    gpuHandle.Offset(prop->_heapOffset, Offset);

    _FillHeapWithProp(cpuHandle, gpuHandle, prop);
}

_uint GraphicsResourceHeapDX12::DynamicFillHeapWithGlobalResource(void* outerRes, void* format)
{
    GET_EIRAS_DX12(deviceObj);
    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle(heap->GetCPUDescriptorHandleForHeapStart());
    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(heap->GetGPUDescriptorHandleForHeapStart());

    cpuHandle.Offset(g_HeapOffset, Offset);
    gpuHandle.Offset(g_HeapOffset, Offset);

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = *((DXGI_FORMAT*)format);
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    deviceObj->device->CreateShaderResourceView((ID3D12Resource*)outerRes, &srvDesc, cpuHandle);

    return g_HeapOffset++;
}

void GraphicsResourceHeapDX12::FillHeap(_uint tableCount, MaterialTable** tableArray)
{
    GET_EIRAS_DX12(deviceObj);
    
    _uint heapOffset = HEAP_HEADER_OFFSET;

    for (_uint tableIndex = 0; tableIndex < tableCount; tableIndex++)
    {
        MaterialTable* table = tableArray[tableIndex];

        for (_uint propIndex = 0; propIndex < table->PropNum; propIndex++)
        {
            MaterialProp* prop = table->Props[propIndex];
            prop->InitHeapOffset(heapOffset);

            CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle(heap->GetCPUDescriptorHandleForHeapStart());
            CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(heap->GetGPUDescriptorHandleForHeapStart());
            cpuHandle.Offset(heapOffset, Offset);
            gpuHandle.Offset(heapOffset, Offset);

            if (prop->Resource == 0)
            {
                //unbound SRV slot will be dynamic filled to heap
            }
            else
            {
                _FillHeapWithProp(cpuHandle, gpuHandle, prop);
            }
            heapOffset++;

        }
    }
}
