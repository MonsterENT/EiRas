#include "ResourceDescriptorHeapManager.hpp"
#include <PlatformDependency/OnDX/Material/GraphicsResourceDescriptorHeapDX12.h>
using namespace MaterialSys;

#define HEAP_SIZE 256

static ResourceDescriptorHeapManager* g_resourceHeapManager = 0;

ResourceDescriptorHeapManager* ResourceDescriptorHeapManager::ShareInstance()
{
    if (g_resourceHeapManager == 0)
    {
        g_resourceHeapManager = new ResourceDescriptorHeapManager();
        g_resourceHeapManager->AddHeap(HEAP_SIZE);
    }
    return g_resourceHeapManager;
}

MaterialSys::GraphicsResourceDescriptorHeapDX12* ResourceDescriptorHeapManager::AddHeap(_uint size)
{
    GraphicsResourceDescriptorHeapDX12* heap = new GraphicsResourceDescriptorHeapDX12(size);
    if (heap)
    {
        HeapPool.push_back(heap);
    }
    return heap;
}