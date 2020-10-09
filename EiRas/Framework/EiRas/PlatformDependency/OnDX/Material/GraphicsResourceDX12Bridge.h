#ifndef Graphics_ResourceDX12_Bridge_hpp
#define Graphics_ResourceDX12_Bridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    struct GraphicsResourceBehaviors;
    enum class GraphicsResourceDimension;

    class GraphicsResourceDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceDX12Bridge();

        void SetResource(void* res, bool noMoreUpdate);
        void GetResource(void* res);

        void InitAsDefault(int bufferSize, GraphicsResourceBehaviors* behaviors, GraphicsResourceDimension dimension);
        void InitAsUAV(int bufferSize, GraphicsResourceBehaviors* behaviors, GraphicsResourceDimension dimension);

        void InitAsRT(void* renderBufferFormat, void* rawResourceObj);

        void InitAsConstantBuffer(int bufferSize, GraphicsResourceBehaviors* behaviors);

        void InitAsShaderResource(int width, int height, _uint channels, void* texData, GraphicsResourceBehaviors* behaviors, bool* buildStatusFlag, GraphicsResourceDimension dimension);
        void ShaderResourceBuild(void* cmdList);
        void ShaderResourceFinishBuild();
    };
}

#endif // !Graphics_ResourceDX12_Bridge_hpp
