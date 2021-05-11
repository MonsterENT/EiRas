#include "GraphicsResourceDescriptorHeapDX12Bridge.h"
#include "GraphicsResourceDescriptorHeapDX12.h"
#include <Material/MaterialLayout.hpp>
using namespace MaterialSys;

GraphicsResourceDescriptorHeapDX12Bridge::GraphicsResourceDescriptorHeapDX12Bridge(_uint propCount)
{
    raw_obj = new GraphicsResourceDescriptorHeapDX12(propCount);
}

void GraphicsResourceDescriptorHeapDX12Bridge::FillHeap(_uint tableCount, MaterialTable** tableArray)
{
    ((GraphicsResourceDescriptorHeapDX12*)raw_obj)->FillHeap(tableCount, tableArray);
}

void GraphicsResourceDescriptorHeapDX12Bridge::DynamicFillHeap(MaterialSys::MaterialProp* prop)
{
    ((GraphicsResourceDescriptorHeapDX12*)raw_obj)->DynamicFillHeap(prop);
}

_uint GraphicsResourceDescriptorHeapDX12Bridge::DynamicFillHeapWithGlobalResource(void* outerRes, void* format)
{
    return ((GraphicsResourceDescriptorHeapDX12*)raw_obj)->DynamicFillHeapWithGlobalResource(outerRes, format);
}