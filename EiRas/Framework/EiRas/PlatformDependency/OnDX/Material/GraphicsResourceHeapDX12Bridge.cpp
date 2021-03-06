#include "GraphicsResourceHeapDX12Bridge.h"
#include "GraphicsResourceHeapDX12.h"
#include <Material/MaterialLayout.hpp>
using namespace MaterialSys;

GraphicsResourceHeapDX12Bridge::GraphicsResourceHeapDX12Bridge(_uint propCount)
{
    raw_obj = new GraphicsResourceHeapDX12(propCount);
}

void GraphicsResourceHeapDX12Bridge::FillHeap(_uint tableCount, MaterialTable** tableArray)
{
    ((GraphicsResourceHeapDX12*)raw_obj)->FillHeap(tableCount, tableArray);
}

void GraphicsResourceHeapDX12Bridge::DynamicFillHeap(MaterialSys::MaterialProp* prop)
{
    ((GraphicsResourceHeapDX12*)raw_obj)->DynamicFillHeap(prop);
}

_uint GraphicsResourceHeapDX12Bridge::DynamicFillHeapWithGlobalResource(void* outerRes, void* format)
{
    return ((GraphicsResourceHeapDX12*)raw_obj)->DynamicFillHeapWithGlobalResource(outerRes, format);
}