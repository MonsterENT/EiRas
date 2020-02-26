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

    typedef enum class GraphicsResourceUpdateFreq
    {
        UPDATE_FREQ_ONINIT = 0,
        UPDATE_FREQ_LOW = (UPDATE_FREQ_ONINIT + 1),
        UPDATE_FREQ_HEIGH = (UPDATE_FREQ_LOW + 1),
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

        void InitAsShaderResource(_uint width, _uint height, void* texData, bool* buildStatusFlag);
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
