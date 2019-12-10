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
#endif
}
