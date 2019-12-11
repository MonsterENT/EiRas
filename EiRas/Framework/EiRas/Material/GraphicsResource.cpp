#include <Material/GraphicsResource.hpp>
#include <Global/PlatformDefine.h>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12Bridge.h>
#endif

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/GraphicsResourceMetalBridge.hpp>
#endif

using namespace MaterialSys;

GraphicsResource::GraphicsResource(std::string Name, GraphicsResourceType type, bool shouldInitResource, int bufferSize)
{
    ResourceType = type;
    
#if GRAPHICS_DX
    PlatformBridge = new GraphicsResourceDX12Bridge();
#elif GRAPHICS_METAL
    PlatformBridge = new GraphicsResourceMetalBridge(shouldInitResource);
#endif
    
    this->bufferSize = bufferSize;
    if (type == GraphicsResourceType::CBV)
    {
#if GRAPHICS_DX
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize);
#elif GRAPHICS_METAL
        ((GraphicsResourceMetalBridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize);
#endif
    }
    else if (type == GraphicsResourceType::Default)
    {
#if GRAPHICS_DX
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsDefault(bufferSize);
#elif GRAPHICS_METAL
        ((GraphicsResourceMetalBridge*)PlatformBridge)->InitAsDefault(bufferSize);
#endif
    }
}

void GraphicsResource::SetResource(void* res, bool shouldUnmap)
{
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->SetResource(res, shouldUnmap);
#elif GRAPHICS_METAL
    ((GraphicsResourceMetalBridge*)PlatformBridge)->SetResource(res, shouldUnmap);
#endif
}
