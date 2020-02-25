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
    Behaviors.ResourceType = type;
    Behaviors.Visibility = visible;
    Behaviors.UpdateFreq = updateFreq;

#if GRAPHICS_DX
    PlatformBridge = new GraphicsResourceDX12Bridge();
#elif GRAPHICS_METAL
    PlatformBridge = new GraphicsResourceMetalBridge(Name, shouldInitResource);
#endif
    
    this->bufferSize = bufferSize;
    if (type == GraphicsResourceType::CBV)
    {
#if GRAPHICS_DX
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize, &Behaviors);
#elif GRAPHICS_METAL
        ((GraphicsResourceMetalBridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize);
#endif
    }
    else if (type == GraphicsResourceType::SRV)
    {
#if GRAPHICS_DX
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsShaderResource(bufferSize, &Behaviors);
#elif GRAPHICS_METAL
#endif
    }
    else if (type == GraphicsResourceType::Default)
    {
#if GRAPHICS_DX
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsDefault(bufferSize, &Behaviors);
#elif GRAPHICS_METAL
        ((GraphicsResourceMetalBridge*)PlatformBridge)->InitAsDefault(bufferSize);
#endif
    }
}

void GraphicsResource::SetResource(void* res, bool noMoreUpdate)
{
    if (Behaviors.UpdateFreq == GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT)
    {
        return;
    }
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->SetResource(res, noMoreUpdate);
#elif GRAPHICS_METAL
    ((GraphicsResourceMetalBridge*)PlatformBridge)->SetResource(res);
#endif
}
