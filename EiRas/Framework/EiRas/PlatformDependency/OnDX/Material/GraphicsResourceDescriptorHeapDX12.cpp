#include "GraphicsResourceDescriptorHeapDX12.h"
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnDX/Material/ConstantBufferDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceRTDX12.hpp>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <Material/MaterialLayout.hpp>
#include <vector>
#include <math.h>
#include <Material/Material.hpp>

using std::vector;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;

#define HEAP_HEADER_OFFSET 30

int g_CompareFunc(void const* a, void const* b)
{
    return -(int)((HeapTable*)a)->size - ((HeapTable*)b)->size;
}

int g_FindApproximate(void const* a, void const* b)
{
    return std::abs((long)((HeapTable*)a)->size - *(int*)b);
}

GraphicsResourceDescriptorHeapDX12::GraphicsResourceDescriptorHeapDX12(_uint propCount)
{
    HeapOffsetPool.Compare = g_CompareFunc;
    HeapOffsetPool.Insert(HeapTable(HEAP_HEADER_OFFSET, propCount - 1));

    g_HeapOffset = 1;
    isDirty = false;
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heapDesc.NumDescriptors = propCount;

    GET_EIRAS_DX12(deviceObj);

    deviceObj->device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));
    OffsetSize = deviceObj->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

GraphicsResourceDescriptorHeapDX12::~GraphicsResourceDescriptorHeapDX12()
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
        srvDesc.Format = (DXGI_FORMAT)resRT->RTRawObj->ColorFormat;
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;
        deviceObj->device->CreateShaderResourceView(resRT->RTRawObj->ColorBuffer, &srvDesc, cpuHandle);
    }
}

_uint GraphicsResourceDescriptorHeapDX12::DynamicFillHeapGlobal(void* res, void* format, bool DepthStencilRes, bool asUAV)
{
    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle(heap->GetCPUDescriptorHandleForHeapStart());
    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(heap->GetGPUDescriptorHandleForHeapStart());

    cpuHandle.Offset(g_HeapOffset, OffsetSize);
    gpuHandle.Offset(g_HeapOffset, OffsetSize);

    GET_EIRAS_DX12(deviceObj);
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = *((DXGI_FORMAT*)format);
    if (DepthStencilRes)
    {
        //hack
        srvDesc.Format = DXGI_FORMAT((int)(srvDesc.Format) + 1);
    }
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    HRESULT hr = deviceObj->device->GetDeviceRemovedReason();

    if (!asUAV)
    {
        deviceObj->device->CreateShaderResourceView((ID3D12Resource*)res, &srvDesc, cpuHandle);
    }
    else
    {
        D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Format = *((DXGI_FORMAT*)format);
        uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
        deviceObj->device->CreateUnorderedAccessView((ID3D12Resource*)res, 0, &uavDesc, cpuHandle);
    }
    HRESULT hr2 = deviceObj->device->GetDeviceRemovedReason();
    assert(SUCCEEDED(hr2));
    return g_HeapOffset++;
}

void GraphicsResourceDescriptorHeapDX12::DynamicFillHeap(MaterialSys::MaterialProp* prop)
{
    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle(heap->GetCPUDescriptorHandleForHeapStart());
    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(heap->GetGPUDescriptorHandleForHeapStart());

    cpuHandle.Offset(prop->_heapOffset, OffsetSize);
    gpuHandle.Offset(prop->_heapOffset, OffsetSize);

    _FillHeapWithProp(cpuHandle, gpuHandle, prop);
}


void GraphicsResourceDescriptorHeapDX12::FillHeap(_uint tableCount, MaterialTable** tableArray)
{
    GET_EIRAS_DX12(deviceObj);

    for (_uint tableIndex = 0; tableIndex < tableCount; tableIndex++)
    {
        MaterialTable* table = tableArray[tableIndex];

        for (_uint propIndex = 0; propIndex < table->PropNum; propIndex++)
        {
            MaterialProp* prop = table->Props[propIndex];

            CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle(heap->GetCPUDescriptorHandleForHeapStart());
            CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(heap->GetGPUDescriptorHandleForHeapStart());
            cpuHandle.Offset(prop->_heapOffset, OffsetSize);
            gpuHandle.Offset(prop->_heapOffset, OffsetSize);

            if (prop->Resource == 0)
            {
                //unbound SRV slot will be dynamic filled to heap
            }
            else
            {
                _FillHeapWithProp(cpuHandle, gpuHandle, prop);
            }
        }
    }
}

void GraphicsResourceDescriptorHeapDX12::FillHeap()
{
    if (!isDirty)
    {
        return;
    }

    isDirty = false;
    std::vector<MaterialSys::MaterialTable*> tmpMaterialTableArray;
    std::vector<Material*>::iterator it = MaterialArray.begin();
    while (it != MaterialArray.end())
    {
        Material* mat = *it;
        for (_uint slotIndex = 0; slotIndex < mat->materialLayout->SlotNum; slotIndex++)
        {
            MaterialSlot* slot = mat->materialLayout->Slots[slotIndex];
            if (slot->SlotType == MaterialSlotType::MaterialSlotType_Table)
            {
                tmpMaterialTableArray.push_back((MaterialTable*)slot);
            }
        }
        it++;
    }

    if (tmpMaterialTableArray.size() > 0)
    {
        FillHeap((_uint)tmpMaterialTableArray.size(), &tmpMaterialTableArray[0]);
    }
}

void GraphicsResourceDescriptorHeapDX12::RegMaterial(MaterialSys::Material* material)
{
    isDirty = true;
    MaterialArray.push_back(material);

    for (int i = 0; i < material->materialLayout->SlotNum; i++)
    {
        auto slot = material->materialLayout->Slots[i];

        if (slot->SlotType == MaterialSlotType::MaterialSlotType_Table)
        {
            if (((MaterialTable*)slot)->Props[0]->Resource != 0)
            {
                HeapTable ht;
                int htIdx;
                assert(HeapOffsetPool.FindApproximate(ht, htIdx, &((MaterialTable*)slot)->PropNum, g_FindApproximate));

                _uint remainSize = ht.size - ((MaterialTable*)slot)->PropNum;
                assert(remainSize >= 0);
                if (remainSize >= 0)
                {
                    HeapOffsetPool.RemoveAt(htIdx);
                    for (int j = 0; j < ((MaterialTable*)slot)->PropNum; j++)
                    {
                        ((MaterialTable*)slot)->Props[j]->InitHeapOffset(ht.start + j);
                    }

                    if (remainSize > 0)
                    {
                        remainSize--;
                        HeapOffsetPool.Insert(HeapTable(ht.end - remainSize, ht.end));
                    }
                }
            }
        }
    }
}

void GraphicsResourceDescriptorHeapDX12::RemoveMaterial(MaterialSys::Material* material)
{
    isDirty = true;
    auto it = MaterialArray.begin();
    while (it != MaterialArray.end())
    {
        if (material == *it)
        {
            for (int i = 0; i < material->materialLayout->SlotNum; i++)
            {
                auto slot = material->materialLayout->Slots[i];

                if (slot->SlotType == MaterialSlotType::MaterialSlotType_Table)
                {
                    if (((MaterialTable*)slot)->Props[0]->_heapOffset < HEAP_HEADER_OFFSET)
                    {
                        continue;
                    }
                    HeapTable ht(((MaterialTable*)slot)->Props[0]->_heapOffset, ((MaterialTable*)slot)->Props[0]->_heapOffset + ((MaterialTable*)slot)->PropNum - 1);
                    HeapOffsetPool.Insert(ht);
                }
            }
            MaterialArray.erase(it);
            break;
        }
        it++;
    }
}