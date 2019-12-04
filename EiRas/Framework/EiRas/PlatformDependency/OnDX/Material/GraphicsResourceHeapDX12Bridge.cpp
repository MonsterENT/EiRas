#include "GraphicsResourceHeapDX12Bridge.h"
#include "GraphicsResourceHeapDX12.h"
#include <Material/GraphicsResource.hpp>
#include "GraphicsResourceDX12.h"
using namespace MaterialSys;

GraphicsResourceHeapDX12Bridge::GraphicsResourceHeapDX12Bridge(UINT resCount, GraphicsResource** resArray)
{
    GraphicsResourceDX12** tmpResArray = new GraphicsResourceDX12 * [resCount];

    for (int i = 0; i < resCount; i++)
    {
        tmpResArray[i] = (GraphicsResourceDX12*)resArray[i]->PlatformBridge->raw_obj;
    }

    raw_obj = new GraphicsResourceHeapDX12(resCount, tmpResArray);
}