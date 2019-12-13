#include "GraphicsResourceDX12.h"
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>

using MaterialSys::GraphicsResourceType;
using MaterialSys::GraphicsResourceDX12;
using GraphicsAPI::EiRasDX12;

GraphicsResourceDX12::GraphicsResourceDX12(int bufferSize, bool initResource)
{
    this->bufferSize = bufferSize;
    ResType = GraphicsResourceType::Default;

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
}

void GraphicsResourceDX12::SetResource(void* res, bool shouldUnmap)
{
    CD3DX12_RANGE range(0, 0);
    Resource->Map(0, &range, (void**)(&ResMappingDestPtr));
    memcpy(ResMappingDestPtr, res, bufferSize);
    if (shouldUnmap)
    {
        Resource->Unmap(0, NULL);
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