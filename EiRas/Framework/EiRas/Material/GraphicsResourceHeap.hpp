#ifndef Graphics_Resource_Heap_hpp
#define Graphics_Resource_Heap_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys
{
    class MaterialTable;
    class GraphicsResourceHeap
    {
    public:
        GraphicsResourceHeap(int propCount, int tableCount, MaterialTable** tableArray);
        EiRasPlatformBridgeProtocol* PlatformBridge;
    };
}
#endif // !Graphics_Resource_Heap_hpp
