#include "GraphicsResourceHeap.hpp"
#include <Global/PlatformDefine.h>
#include <Material/GraphicsResource.hpp>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/GraphicsResourceHeapDX12Bridge.h>
#endif

using namespace MaterialSys;

GraphicsResourceHeap::GraphicsResourceHeap(int resCount, GraphicsResource** resArray)
{
    PlatformBridge = new GraphicsResourceHeapDX12Bridge(resCount, resArray);
}