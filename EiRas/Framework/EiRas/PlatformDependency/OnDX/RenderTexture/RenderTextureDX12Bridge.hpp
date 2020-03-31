#ifndef Render_Texture_DX12_Bridge
#define Render_Texture_DX12_Bridge

#include <string>
#include <Global/GlobalDefine.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace Graphics
{
    enum class RenderBufferFormat;

    class RenderTextureDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        RenderTextureDX12Bridge(std::string name, RenderBufferFormat colorFormat, bool useStencil, _uint width, _uint height);
    };
}

#endif