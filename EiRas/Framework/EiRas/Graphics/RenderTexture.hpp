#ifndef Render_Texture_Hpp
#define Render_Texture_Hpp

#include <string>
#include <Global/GlobalDefine.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys
{
    class GraphicsResource;
    enum class GraphicsResourceFormat;
}

namespace Graphics
{
    class RenderTexture
    {
    public:
        std::string Name;
        RenderTexture(std::string name, MaterialSys::GraphicsResourceFormat colorFormat, bool useStencil, _uint width, _uint height);
        EiRasPlatformBridgeProtocol* PlatformBridge;
    private:
    };
}

#endif