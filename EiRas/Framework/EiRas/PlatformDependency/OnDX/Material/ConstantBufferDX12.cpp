#include "ConstantBufferDX12.h"
#include <Material/GraphicsResource.hpp>

using namespace MaterialSys;

ConstantBufferDX12::ConstantBufferDX12(UINT bufferSize, GraphicsResourceBehaviors* behaviors) : GraphicsResourceDX12(bufferSize, behaviors, true)
{
}

ConstantBufferDX12::~ConstantBufferDX12()
{
    //heap->Release();
    //buffer->Release();
}