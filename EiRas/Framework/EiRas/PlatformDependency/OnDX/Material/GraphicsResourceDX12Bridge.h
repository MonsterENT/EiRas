#ifndef Graphics_ResourceDX12_Bridge_hpp
#define Graphics_ResourceDX12_Bridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>

namespace MaterialSys
{
    enum class GraphicsResourceType;
    enum class GraphicsResourceVisibility;
    enum class GraphicsResourceUpdateFreq;

    class GraphicsResourceDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceDX12Bridge();

        void SetResource(void* res, bool shouldUnmap);

        void InitAsDefault(int bufferSize, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq);

        void InitAsConstantBuffer(int bufferSize, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq);

        void InitAsShaderResource(int bufferSize, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq);

        GraphicsResourceType type;
    };
}

#endif // !Graphics_ResourceDX12_Bridge_hpp
