#include "ConstantBufferDX12.h"
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>

using MaterialSys::ConstantBufferDX12;
using GraphicsAPI::EiRasDX12;

ConstantBufferDX12::ConstantBufferDX12(UINT bufferSize)
{
    ResType = ResourceTypeDX12::TypeCB;
    this->bufferSize = bufferSize;
    GET_EIRAS_DX12(deviceObj)
    deviceObj->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&Resource));
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
