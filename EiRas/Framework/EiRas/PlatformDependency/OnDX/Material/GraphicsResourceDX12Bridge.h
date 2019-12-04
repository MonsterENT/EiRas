#ifndef Graphics_ResourceDX12_Bridge_hpp
#define Graphics_ResourceDX12_Bridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>

namespace MaterialSys
{
    enum class GraphicsResourceType;

    class GraphicsResourceDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceDX12Bridge();

        void InitAsConstantBuffer(int bufferSize);

        void InitAsShaderResource();

        GraphicsResourceType type;
    };
}

#endif // !Graphics_ResourceDX12_Bridge_hpp
