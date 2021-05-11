#include "GraphicsResourceDescriptorHeap.hpp"

#include <Material/MaterialLayout.hpp>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/GraphicsResourceDescriptorHeapDX12Bridge.h>
#elif GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/GraphicsResourceHeapMetalBridge.hpp>
#endif

using namespace MaterialSys;

GraphicsResourceDescriptorHeap::GraphicsResourceDescriptorHeap(_uint propCount)
{
#if GRAPHICS_DX
    PlatformBridge = new GraphicsResourceDescriptorHeapDX12Bridge(propCount);
#elif GRAPHICS_METAL
    PlatformBridge = new GraphicsResourceHeapMetalBridge(propCount);
#endif
}

void GraphicsResourceDescriptorHeap::FillHeap(_uint tableCount, MaterialTable** tableArray)
{
#if GRAPHICS_DX
    ((GraphicsResourceDescriptorHeapDX12Bridge*)PlatformBridge)->FillHeap(tableCount, tableArray);
#elif GRAPHICS_METAL
#endif
}

void GraphicsResourceDescriptorHeap::DynamicFillHeap(MaterialSys::MaterialProp* prop)
{
#if GRAPHICS_DX
    ((GraphicsResourceDescriptorHeapDX12Bridge*)PlatformBridge)->DynamicFillHeap(prop);
#endif
}

_uint GraphicsResourceDescriptorHeap::DynamicFillHeapWithGlobalResource(void* outerRes, void* format)
{
#if GRAPHICS_DX
    return ((GraphicsResourceDescriptorHeapDX12Bridge*)PlatformBridge)->DynamicFillHeapWithGlobalResource(outerRes, format);
#endif
}
