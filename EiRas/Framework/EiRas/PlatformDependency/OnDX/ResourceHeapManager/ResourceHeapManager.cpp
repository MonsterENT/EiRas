#include "ResourceHeapManager.hpp"
using namespace MaterialSys;

#define HEAP_SIZE 256

static ResourceHeapManager* g_resourceHeapManager = 0;

ResourceHeapManager* ResourceHeapManager::ShareInstance()
{
    if (g_resourceHeapManager == 0)
    {
        g_resourceHeapManager = new ResourceHeapManager();
        g_resourceHeapManager->AddHeap(HEAP_SIZE);
    }
    return g_resourceHeapManager;
}

MaterialSys::GraphicsResourceHeap* ResourceHeapManager::AddHeap(_uint size)
{
    GraphicsResourceHeap* heap = new GraphicsResourceHeap(size);
    if (heap)
    {
        HeapPool.push_back(heap);
    }
    return heap;
}