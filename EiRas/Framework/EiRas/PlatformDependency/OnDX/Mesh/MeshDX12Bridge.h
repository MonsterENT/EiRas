#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys
{
    class GraphiceResourceDX12Bridge;
    class MeshDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        MeshDX12Bridge(EiRasPlatformBridgeProtocol* vertexResBridge, EiRasPlatformBridgeProtocol* indexResBridge);
    };
}