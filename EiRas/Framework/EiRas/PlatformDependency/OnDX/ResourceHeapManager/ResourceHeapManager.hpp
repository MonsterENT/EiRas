#ifndef Resource_Heap_Manager_Hpp
#define Resource_Heap_Manager_Hpp

#include <Global/GlobalDefine.h>
#include <vector>
#include <Material/GraphicsResourceDescriptorHeap.hpp>

namespace MaterialSys
{
    class ResourceHeapManager
    {
    public:
        static ResourceHeapManager* ShareInstance();
        ResourceHeapManager() {}
        MaterialSys::GraphicsResourceDescriptorHeap* AddHeap(_uint size);
        std::vector<MaterialSys::GraphicsResourceDescriptorHeap*> HeapPool;
    };
}

#endif
