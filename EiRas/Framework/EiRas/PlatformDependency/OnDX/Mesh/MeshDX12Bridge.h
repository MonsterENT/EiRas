#pragma once
#include <Global/PlatformDefine.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>

namespace MaterialSys
{
    class GraphiceResourceDX12Bridge;
    class MeshDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        MeshDX12Bridge(EiRasPlatformBridgeProtocol* vertexResBridge, EiRasPlatformBridgeProtocol* indexResBridgem, UINT vertexCount, UINT indexCount);
    };
}