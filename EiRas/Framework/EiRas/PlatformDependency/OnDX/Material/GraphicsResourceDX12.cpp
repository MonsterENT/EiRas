#include "GraphicsResourceDX12.h"
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>

using namespace MaterialSys;
using GraphicsAPI::EiRasDX12;

GraphicsResourceDX12::GraphicsResourceDX12(int bufferSize, GraphicsResourceBehaviors* behaviors, bool initResource)
{
    this->bufferSize = bufferSize;

    Behaviors = behaviors;

    if (initResource)
    {
        GET_EIRAS_DX12(deviceObj)
            deviceObj->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&Resource));
    }
    else
    {
        Resource = NULL;
    }
    ResMappingDestPtr = NULL;

    if (Behaviors->UpdateFreq == GraphicsResourceUpdateFreq::UPDATE_FREQ_HEIGH)
    {
        CD3DX12_RANGE range(0, 0);
        Resource->Map(0, &range, (void**)(&ResMappingDestPtr));
    }
}

void GraphicsResourceDX12::SetResource(void* res, bool noMoreUpdate)
{
    if (Behaviors->UpdateFreq == GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW)
    {
        CD3DX12_RANGE range(0, 0);
        Resource->Map(0, &range, (void**)(&ResMappingDestPtr));
    }

    memcpy(ResMappingDestPtr, res, bufferSize);

    if (Behaviors->UpdateFreq == GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW || noMoreUpdate)
    {
        Resource->Unmap(0, NULL);
    }

    if (noMoreUpdate)
    {
        Behaviors->UpdateFreq = GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT;
    }
}

GraphicsResourceDX12::~GraphicsResourceDX12()
{
    if (Resource != NULL)
    {
        Resource->Release();
    }
}


int GraphicsResourceDX12::GetBufferSize()
{
    return bufferSize;
}