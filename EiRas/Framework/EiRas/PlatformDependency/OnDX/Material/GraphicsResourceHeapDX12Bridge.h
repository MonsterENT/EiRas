#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class MaterialTable;
    class MaterialProp;
    class GraphicsResourceHeapDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceHeapDX12Bridge(_uint propCount);
        void FillHeap(_uint tableCount, MaterialTable** tableArray);
        void DynamicFillHeap(MaterialSys::MaterialProp*);
        void DynamicFillHeapWithOuterResource(_uint, void*, void*);
    };
}