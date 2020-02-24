#include <Material/GraphicsResource.hpp>
#include <Global/PlatformDefine.h>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12Bridge.h>
#endif

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/GraphicsResourceMetalBridge.hpp>
#endif

using namespace MaterialSys;

GraphicsResource::GraphicsResource(std::string Name, GraphicsResourceType type, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq, bool shouldInitResource, int bufferSize)
{
    ResourceType = type;
    
    Visibility = visible;

    UpdateFreq = updateFreq;
    
#if GRAPHICS_DX
    PlatformBridge = new GraphicsResourceDX12Bridge();
#elif GRAPHICS_METAL
    PlatformBridge = new GraphicsResourceMetalBridge(Name, shouldInitResource);
#endif
    
    this->bufferSize = bufferSize;
    if (type == GraphicsResourceType::CBV)
    {
#if GRAPHICS_DX
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize, Visibility, UpdateFreq);
#elif GRAPHICS_METAL
        ((GraphicsResourceMetalBridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize);
#endif
    }
    else if (type == GraphicsResourceType::SRV)
    {
#if GRAPHICS_DX
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsShaderResource(bufferSize, Visibility, UpdateFreq);
#elif GRAPHICS_METAL
#endif
    }
    else if (type == GraphicsResourceType::Default)
    {
#if GRAPHICS_DX
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsDefault(bufferSize, Visibility, UpdateFreq);
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
    ((GraphicsResourceMetalBridge*)PlatformBridge)->SetResource(res);
#endif
}
