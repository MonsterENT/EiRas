#include "ConstantBufferDX12.h"
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <Material/GraphicsResource.hpp>

using MaterialSys::ConstantBufferDX12;
using GraphicsAPI::EiRasDX12;
using MaterialSys::GraphicsResourceType;

ConstantBufferDX12::ConstantBufferDX12(UINT bufferSize)
{
    ResType = GraphicsResourceType::CBV;
    this->bufferSize = bufferSize;
    GET_EIRAS_DX12(deviceObj)
    deviceObj->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&Resource));
    CD3DX12_RANGE range(0, 0);
    Resource->Map(0, &range, (void**)&ResMappingDestPtr);
}


ConstantBufferDX12::~ConstantBufferDX12()
{
    //heap->Release();
    //buffer->Release();
}

UINT ConstantBufferDX12::GetBufferSize()
{
    return bufferSize;
}
