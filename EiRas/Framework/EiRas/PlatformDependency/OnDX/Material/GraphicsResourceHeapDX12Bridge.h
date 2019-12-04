#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>

namespace MaterialSys
{
    class GraphicsResource;
    class GraphicsResourceHeapDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceHeapDX12Bridge(UINT resCount, GraphicsResource** resArray);
    };
}