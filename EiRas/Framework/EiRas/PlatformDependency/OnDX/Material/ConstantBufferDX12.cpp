#include "ConstantBufferDX12.h"
#include <Material/GraphicsResource.hpp>

using MaterialSys::ConstantBufferDX12;
using MaterialSys::GraphicsResourceType;

ConstantBufferDX12::ConstantBufferDX12(UINT bufferSize) : GraphicsResourceDX12(bufferSize, true)
{
    ResType = GraphicsResourceType::CBV;
    CD3DX12_RANGE range(0, 0);
    Resource->Map(0, &range, (void**)&ResMappingDestPtr);
}

ConstantBufferDX12::~ConstantBufferDX12()
{
    //heap->Release();
    //buffer->Release();
}