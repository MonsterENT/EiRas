#ifndef Graphics_Resource_hpp
#define Graphics_Resource_hpp

#include <string>
#include <Global/GlobalDefine.h>

class EiRasPlatformBridgeProtocol;

namespace MaterialSys
{
    typedef enum class GraphicsResourceType
    {
        SRV = 0,
        UAV = (SRV + 1),
        CBV = (UAV + 1),
        SAMPLER = (CBV + 1),
        Default = (SAMPLER + 1)
    } GraphicsResourceType;

    typedef enum class GraphicsResourceVisibility
    {
        VISIBILITY_ALL = 0,
        VISIBILITY_VERTEX = (VISIBILITY_ALL + 1),
        VISIBILITY_PIXEL = (VISIBILITY_VERTEX + 1),
    } GraphicsResourceVisibility;

    //D3D12_SHADER_VISIBILITY_ALL = 0,
    //    D3D12_SHADER_VISIBILITY_VERTEX = 1,
    //    D3D12_SHADER_VISIBILITY_HULL = 2,
    //    D3D12_SHADER_VISIBILITY_DOMAIN = 3,
    //    D3D12_SHADER_VISIBILITY_GEOMETRY = 4,
    //    D3D12_SHADER_VISIBILITY_PIXEL = 5

    inline int GraphicsResourceVisibilityToDX12(GraphicsResourceVisibility visibility)
    {
        switch (visibility)
        {
        case GraphicsResourceVisibility::VISIBILITY_ALL:
            return 0;
            break;
        case GraphicsResourceVisibility::VISIBILITY_VERTEX:
            return 1;
            break;
        case GraphicsResourceVisibility::VISIBILITY_PIXEL:
            return 5;
            break;
        default:
            return 0;
            break;
        }
    }

    typedef enum class GraphicsResourceUpdateFreq
    {
        UPDATE_FREQ_ONINIT = 0,
        UPDATE_FREQ_LOW = (UPDATE_FREQ_ONINIT + 1),
        UPDATE_FREQ_HIGH = (UPDATE_FREQ_LOW + 1),
    } GraphicsResourceUpdateFreq;

    typedef struct GraphicsResourceBehaviors
    {
        GraphicsResourceType ResourceType;
        GraphicsResourceVisibility Visibility;
        GraphicsResourceUpdateFreq UpdateFreq;
    } GraphicsResourceBehaviors;

    class GraphicsResource
    {
    public:
        GraphicsResource(std::string Name, GraphicsResourceType type, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq, bool shouldInitResource);

        void InitAsConstantBuffer(_uint bufferSize);

        void InitAsDefault(_uint bufferSize);

        void InitAsShaderResource(_uint width, _uint height, _uint channels, void* texData, bool* buildStatusFlag);
        void ShaderResourceBuild(void* cmdList);
        void ShaderResourceFinishBuild();


        GraphicsResourceBehaviors Behaviors;
        EiRasPlatformBridgeProtocol* PlatformBridge;

        void SetResource(void* res, bool noMoreUpdate);

    private:
        _uint bufferSize;
    };
}

#endif
