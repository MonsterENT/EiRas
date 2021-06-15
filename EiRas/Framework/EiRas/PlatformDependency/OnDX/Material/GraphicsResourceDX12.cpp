#include "GraphicsResourceDX12.h"
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>

using namespace MaterialSys;
using GraphicsAPI::EiRasDX12;

GraphicsResourceDX12::GraphicsResourceDX12(int bufferSize, GraphicsResourceBehaviors* behaviors)
{
    this->bufferSize = bufferSize;
    Resource = NULL;
    Behaviors = behaviors;
    ResMappingDestPtr = NULL;
}

void GraphicsResourceDX12::BuildResource(D3D12_HEAP_TYPE heapType, D3D12_RESOURCE_STATES resourceState, GraphicsResourceDimension type, int format, int width, int height, int depth)
{
    D3D12_RESOURCE_DESC desc = {};

    switch (type)
    {
    case MaterialSys::GraphicsResourceDimension::GraphicsResourceDimension_Buffer:
        desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
        break;
    case MaterialSys::GraphicsResourceDimension::GraphicsResourceDimension_Tex1D:
        desc = CD3DX12_RESOURCE_DESC::Tex1D((DXGI_FORMAT)format, width, 1, 0, D3D12_RESOURCE_FLAG_NONE, D3D12_TEXTURE_LAYOUT_UNKNOWN, 0);
        break;
    case MaterialSys::GraphicsResourceDimension::GraphicsResourceDimension_Tex2D:
        desc = CD3DX12_RESOURCE_DESC::Tex2D((DXGI_FORMAT)format, width, height, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_NONE, D3D12_TEXTURE_LAYOUT_UNKNOWN, 0);
        break;
    case MaterialSys::GraphicsResourceDimension::GraphicsResourceDimension_Tex3D:
        desc = CD3DX12_RESOURCE_DESC::Tex3D((DXGI_FORMAT)format, width, height, depth, 0, D3D12_RESOURCE_FLAG_NONE, D3D12_TEXTURE_LAYOUT_UNKNOWN, 0);
        break;
    }

    if (resourceState == D3D12_RESOURCE_STATE_UNORDERED_ACCESS)
    {
        desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    }

    GET_EIRAS_DX12(deviceObj);
    HRESULT hr = deviceObj->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(heapType),
        D3D12_HEAP_FLAG_NONE,
        &desc,
        resourceState,
        nullptr,
        IID_PPV_ARGS(&Resource));
    HRESULT hrRemove = deviceObj->device->GetDeviceRemovedReason();
    assert(SUCCEEDED(hr));

    ResADDR = Resource->GetGPUVirtualAddress();

    ResMappingDestPtr = NULL;

    ResourceState = resourceState;

    if (Behaviors->UpdateFreq == GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH)
    {
        CD3DX12_RANGE range(0, 0);
        Resource->Map(0, &range, (void**)(&ResMappingDestPtr));
    }
}

void GraphicsResourceDX12::SetResource(void* res, bool noMoreUpdate)
{
    if (bufferSize <= 0)
    {
        return;
    }
    if (ResMappingDestPtr == NULL)
    {
        CD3DX12_RANGE range(0, 0);
        Resource->Map(0, &range, (void**)(&ResMappingDestPtr));
    }

    memcpy(ResMappingDestPtr, res, bufferSize);

    if (Behaviors->UpdateFreq == GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW || noMoreUpdate)
    {
        Resource->Unmap(0, NULL);
        ResMappingDestPtr = NULL;
    }

    if (noMoreUpdate)
    {
        Behaviors->UpdateFreq = GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT;
    }
}

void GraphicsResourceDX12::GetResource(void* res)
{
    if(bufferSize <= 0)
    {
        return;
    }

    if (ResMappingDestPtr == NULL)
    {
        CD3DX12_RANGE range(0, 0);
        Resource->Map(0, &range, (void**)(&ResMappingDestPtr));
    }

    memcpy(res, ResMappingDestPtr, bufferSize);

    if (Behaviors->UpdateFreq == GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW || Behaviors->UpdateFreq == GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT)
    {
        Resource->Unmap(0, NULL);
        ResMappingDestPtr = NULL;
    }
}

GraphicsResourceDX12::~GraphicsResourceDX12()
{
    if (ResMappingDestPtr != NULL && Resource != NULL)
    {
        Resource->Unmap(0, NULL);
    }
    if (Resource != NULL)
    {
        Resource->Release();
    }
}


int GraphicsResourceDX12::GetBufferSize()
{
    return bufferSize;
}

void GraphicsResourceDX12::ChangeState(bool cbv, bool srv, bool uav, bool target, ID3D12GraphicsCommandList* cmdList)
{
    if (cbv)
    {
        ChangeState(D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, cmdList);
    }
    else if (srv)
    {
        D3D12_RESOURCE_STATES state;
        if (Behaviors->Visibility == GraphicsResourceVisibility::VISIBILITY_ALL)
        {
            state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
        }
        else if (Behaviors->Visibility == GraphicsResourceVisibility::VISIBILITY_VERTEX)
        {
            state = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
        }
        else
        {
            state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
        }
        ChangeState(state, cmdList);
    }
    else if (uav)
    {
        ChangeState(D3D12_RESOURCE_STATE_UNORDERED_ACCESS, cmdList);
    }
    else if (target)
    {
        ChangeState(D3D12_RESOURCE_STATE_RENDER_TARGET, cmdList);
    }
}
void GraphicsResourceDX12::ChangeState(D3D12_RESOURCE_STATES state, ID3D12GraphicsCommandList* cmdList)
{
    if (ResourceState == state || ResourceState & state != 0)
    {
        return;
    }
    
    cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(Resource, ResourceState, state));
    ResourceState = state;
}