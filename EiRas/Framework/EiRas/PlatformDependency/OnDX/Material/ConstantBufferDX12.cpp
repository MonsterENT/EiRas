#include "ConstantBufferDX12.h"
#include <Material/GraphicsResource.hpp>

using namespace MaterialSys;

ConstantBufferDX12::ConstantBufferDX12(UINT bufferSize, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq) : GraphicsResourceDX12(bufferSize, visible, updateFreq, true)
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