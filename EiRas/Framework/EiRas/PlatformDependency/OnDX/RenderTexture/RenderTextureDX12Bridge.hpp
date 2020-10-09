#ifndef Render_Texture_DX12_Bridge
#define Render_Texture_DX12_Bridge

#include <string>
#include <Global/GlobalDefine.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys
{
    enum class GraphicsResourceFormat;
}

namespace Graphics
{
    class RenderTextureDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        RenderTextureDX12Bridge(std::string name, MaterialSys::GraphicsResourceFormat colorFormat, bool useStencil, _uint width, _uint height);
    };
}

#endif