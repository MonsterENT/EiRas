#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class MaterialTable;
    class MaterialProp;
    class GraphicsResourceDescriptorHeapDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceDescriptorHeapDX12Bridge(_uint propCount);
        void FillHeap(_uint tableCount, MaterialTable** tableArray);
        void DynamicFillHeap(MaterialSys::MaterialProp*);
        _uint DynamicFillHeapWithGlobalResource(void*, void*);
    };
}