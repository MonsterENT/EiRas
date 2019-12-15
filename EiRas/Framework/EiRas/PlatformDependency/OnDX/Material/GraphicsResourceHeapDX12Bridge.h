#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class MaterialTable;
    class GraphicsResourceHeapDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceHeapDX12Bridge(_uint propCount, _uint tableCount, MaterialTable** tableArray);
    };
}