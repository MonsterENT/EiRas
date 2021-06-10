#include <Material/GraphicsResource.hpp>


#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12Bridge.h>
#endif

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/GraphicsResourceMetalBridge.hpp>
#endif

using namespace MaterialSys;

GraphicsResource::GraphicsResource(std::string Name, GraphicsResourceType type, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq, bool shouldInitResource)
{
    Behaviors.ResourceType = type;
    Behaviors.Visibility = visible;
    Behaviors.UpdateFreq = updateFreq;

#if GRAPHICS_DX
    PlatformBridge = new GraphicsResourceDX12Bridge();
#elif GRAPHICS_METAL
    PlatformBridge = new GraphicsResourceMetalBridge(Name, shouldInitResource);
#endif

    this->bufferSize = -1;
}

void GraphicsResource::InitAsConstantBuffer(_uint bufferSize)
{
    this->bufferSize = bufferSize;
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize, &Behaviors);
#elif GRAPHICS_METAL
    ((GraphicsResourceMetalBridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize);
#endif
}

void GraphicsResource::InitAsDefault(_uint bufferSize, GraphicsResourceDimension dimension)
{
    this->bufferSize = bufferSize;
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsDefault(bufferSize, &Behaviors, dimension);
#elif GRAPHICS_METAL
    ((GraphicsResourceMetalBridge*)PlatformBridge)->InitAsDefault(bufferSize);
#endif
}

void GraphicsResource::InitAsUAV(_uint bufferSize, GraphicsResourceDimension dimension)
{
    this->bufferSize = bufferSize;
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsUAV(bufferSize, &Behaviors, dimension);
}

void GraphicsResource::InitAsRT(void* rtRawObj)
{
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsRT(rtRawObj);
#endif
}

void GraphicsResource::InitAsShaderResource(_uint width, _uint height, _uint channels, void* texData, bool* buildStatusFlag, GraphicsResourceDimension dimension)
{
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsShaderResource(width, height, channels, texData, &Behaviors, buildStatusFlag, dimension);
#elif GRAPHICS_METAL
    ((GraphicsResourceMetalBridge*)PlatformBridge)->InitAsShaderResourceTexture(width, height, texData, buildStatusFlag);
#endif
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

void GraphicsResource::GetResource(void* res)
{
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->GetResource(res);
}

void GraphicsResource::ShaderResourceBuild(void* cmdList)
{
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->ShaderResourceBuild(cmdList);
#elif GRAPHICS_METAL
#endif
}

void GraphicsResource::ShaderResourceFinishBuild()
{
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->ShaderResourceFinishBuild();
#elif GRAPHICS_METAL
#endif
}
