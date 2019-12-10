#include "GraphicsResourceHeap.hpp"
#include <Global/PlatformDefine.h>
#include <Material/MaterialLayout.hpp>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/GraphicsResourceHeapDX12Bridge.h>
#endif

using namespace MaterialSys;

GraphicsResourceHeap::GraphicsResourceHeap(int propCount, int tableCount, MaterialTable** tableArray)
{
#if GRAPHICS_DX
    PlatformBridge = new GraphicsResourceHeapDX12Bridge(propCount, tableCount, tableArray);
#endif
}
