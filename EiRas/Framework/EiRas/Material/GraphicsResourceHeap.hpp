#ifndef Graphics_Resource_Heap_hpp
#define Graphics_Resource_Heap_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class MaterialTable;
    class GraphicsResourceHeap
    {
    public:
        GraphicsResourceHeap(_uint propCount, _uint tableCount, MaterialTable** tableArray);
        EiRasPlatformBridgeProtocol* PlatformBridge;
    };
}
#endif // !Graphics_Resource_Heap_hpp
