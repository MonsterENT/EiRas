#ifndef Graphics_Resource_Heap_hpp
#define Graphics_Resource_Heap_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class MaterialTable;
    class MaterialProp;
    class GraphicsResourceHeap
    {
    public:
        GraphicsResourceHeap(_uint propCount);

        void FillHeap(_uint tableCount, MaterialTable** tableArray);

        void DynamicFillHeap(MaterialSys::MaterialProp*);
        _uint DynamicFillHeapWithGlobalResource(void* outerRes, void* format);

        EiRasPlatformBridgeProtocol* PlatformBridge;
    };
}
#endif // !Graphics_Resource_Heap_hpp
