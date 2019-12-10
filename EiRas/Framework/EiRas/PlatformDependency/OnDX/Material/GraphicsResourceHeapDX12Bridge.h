#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>

namespace MaterialSys
{
    class MaterialTable;
    class GraphicsResourceHeapDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceHeapDX12Bridge(int propCount, int tableCount, MaterialTable** tableArray);
    };
}