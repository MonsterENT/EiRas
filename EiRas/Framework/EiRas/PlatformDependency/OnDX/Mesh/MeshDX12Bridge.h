#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>

namespace MeshSys
{
    class MeshDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        MeshDX12Bridge();
        void BuildBuffer(EiRasPlatformBridgeProtocol* vertexResBridge, EiRasPlatformBridgeProtocol* indexResBridgem, UINT vertexCount, UINT indexCount);
    };
}