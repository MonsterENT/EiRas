#ifndef Graphics_Resource_Heap_hpp
#define Graphics_Resource_Heap_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys
{
    class GraphicsResource;
    class GraphicsResourceHeap
    {
    public:
        GraphicsResourceHeap(int resCount, GraphicsResource** resArray);
        EiRasPlatformBridgeProtocol* PlatformBridge;
    };
}
#endif // !Graphics_Resource_Heap_hpp
