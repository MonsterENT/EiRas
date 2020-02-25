#include "GraphicsResourceHeap.hpp"
#include <Global/PlatformDefine.h>
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
    PlatformBridge = new GraphicsResourceHeapMetalBridge(propCount, tableCount, tableArray);
#endif
}

void GraphicsResourceHeap::FillHeap(_uint tableCount, MaterialTable** tableArray)
{
#if GRAPHICS_DX
    ((GraphicsResourceHeapDX12Bridge*)PlatformBridge)->FillHeap(tableCount, tableArray);
#elif GRAPHICS_METAL
    PlatformBridge = new GraphicsResourceHeapMetalBridge(propCount, tableCount, tableArray);
#endif
}
