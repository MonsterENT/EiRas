#include "RenderTexture.hpp"

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/RenderTexture/RenderTextureDX12Bridge.hpp>
#endif

using namespace Graphics;

RenderTexture::RenderTexture(std::string name, RenderBufferFormat colorFormat, bool useStencil, _uint width, _uint height)
{
#ifdef GRAPHICS_DX
    PlatformBridge = new RenderTextureDX12Bridge(name, colorFormat, useStencil, width, height);
#endif
}
