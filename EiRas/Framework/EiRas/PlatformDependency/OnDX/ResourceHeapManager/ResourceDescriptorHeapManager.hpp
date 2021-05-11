#ifndef Resource_Descriptor_Heap_Manager_Hpp
#define Resource_Descriptor_Heap_Manager_Hpp

#include <Global/GlobalDefine.h>
#include <vector>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDescriptorHeapDX12.h>

namespace MaterialSys
{
    class ResourceDescriptorHeapManager
    {
    public:
        static ResourceDescriptorHeapManager* ShareInstance();
        ResourceDescriptorHeapManager() {}
        MaterialSys::GraphicsResourceDescriptorHeapDX12* AddHeap(_uint size);
        std::vector<MaterialSys::GraphicsResourceDescriptorHeapDX12*> HeapPool;
    };
}

#endif
