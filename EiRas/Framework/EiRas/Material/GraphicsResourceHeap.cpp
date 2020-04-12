#include "GraphicsResourceHeap.hpp"

#include <Material/MaterialLayout.hpp>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/GraphicsResourceHeapDX12Bridge.h>
#elif GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/GraphicsResourceHeapMetalBridge.hpp>
#endif

using namespace MaterialSys;

GraphicsResourceHeap::GraphicsResourceHeap(_uint propCount)
{
#if GRAPHICS_DX
    PlatformBridge = new GraphicsResourceHeapDX12Bridge(propCount);
#elif GRAPHICS_METAL
    PlatformBridge = new GraphicsResourceHeapMetalBridge(propCount);
#endif
}

void GraphicsResourceHeap::FillHeap(_uint tableCount, MaterialTable** tableArray)
{
#if GRAPHICS_DX
    ((GraphicsResourceHeapDX12Bridge*)PlatformBridge)->FillHeap(tableCount, tableArray);
#elif GRAPHICS_METAL
#endif
}

void GraphicsResourceHeap::DynamicFillHeap(MaterialSys::MaterialProp* prop)
{
#if GRAPHICS_DX
    ((GraphicsResourceHeapDX12Bridge*)PlatformBridge)->DynamicFillHeap(prop);
#endif
}

_uint GraphicsResourceHeap::DynamicFillHeapWithGlobalResource(void* outerRes, void* format)
{
#if GRAPHICS_DX
    return ((GraphicsResourceHeapDX12Bridge*)PlatformBridge)->DynamicFillHeapWithGlobalResource(outerRes, format);
#endif
}
