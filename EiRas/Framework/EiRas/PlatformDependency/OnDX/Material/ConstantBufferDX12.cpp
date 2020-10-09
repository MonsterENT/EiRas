#include "ConstantBufferDX12.h"
#include <Material/GraphicsResource.hpp>

using namespace MaterialSys;

ConstantBufferDX12::ConstantBufferDX12(UINT bufferSize, GraphicsResourceBehaviors* behaviors) : GraphicsResourceDX12(bufferSize, behaviors)
{
    BuildResource(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ, GraphicsResourceDimension::GraphicsResourceDimension_Buffer);
}

ConstantBufferDX12::~ConstantBufferDX12()
{
    //heap->Release();
    //buffer->Release();
}