#include "RenderTextureDX12Bridge.hpp"
#include "RenderTextureDX12.hpp"

using namespace Graphics;

RenderTextureDX12Bridge::RenderTextureDX12Bridge(std::string name, MaterialSys::GraphicsResourceFormat colorFormat, bool useStencil, _uint width, _uint height)
{
    raw_obj = new RenderTextureDX12(name, colorFormat, useStencil, width, height);
}
