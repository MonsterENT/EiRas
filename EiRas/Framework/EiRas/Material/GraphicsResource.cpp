#include <Material/GraphicsResource.hpp>
#include <Global/PlatformDefine.h>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12Bridge.h>
#endif

using namespace MaterialSys;

GraphicsResource::GraphicsResource(std::string Name, GraphicsResourceType type, int bufferSize)
{
    ResourceType = type;
#if GRAPHICS_DX
    PlatformBridge = new GraphicsResourceDX12Bridge();
    this->bufferSize = bufferSize;
    if (type == GraphicsResourceType::CBV)
    {
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsConstantBuffer(bufferSize);
    }
    else if (type == GraphicsResourceType::Default)
    {
        ((GraphicsResourceDX12Bridge*)PlatformBridge)->InitAsDefault(bufferSize);
    }
#endif
}

void GraphicsResource::SetResource(void* res, bool shouldUnmap)
{
#if GRAPHICS_DX
    ((GraphicsResourceDX12Bridge*)PlatformBridge)->SetResource(res, shouldUnmap);
#endif
}
