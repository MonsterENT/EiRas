#ifndef Graphics_Resource_hpp
#define Graphics_Resource_hpp

#include <string>
#include <Global/GlobalDefine.h>
#include "GraphicsResourceConfig.hpp"

class EiRasPlatformBridgeProtocol;

namespace MaterialSys
{
    class GraphicsResource
    {
    public:
        GraphicsResource(std::string Name, GraphicsResourceType type, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq, bool shouldInitResource);

        virtual ~GraphicsResource();

        void InitAsCustom(int width, int height, GraphicsResourceFormat format, GraphicsResourceDimension dimension = GraphicsResourceDimension::GraphicsResourceDimension_Buffer);

        void InitAsConstantBuffer(_uint bufferSize);

        void InitAsDefault(_uint bufferSize, GraphicsResourceDimension dimension = GraphicsResourceDimension::GraphicsResourceDimension_Buffer);

        void InitAsUAV(_uint bufferSize, GraphicsResourceDimension dimension = GraphicsResourceDimension::GraphicsResourceDimension_Buffer);

        void InitAsRT(void* rtRawObj);

        void InitAsShaderResource(_uint bufferSize);
        void InitAsShaderResource(_uint width, _uint height, _uint channels, void* texData, bool* buildStatusFlag, GraphicsResourceDimension dimension = GraphicsResourceDimension::GraphicsResourceDimension_Tex2D);
        void ShaderResourceBuild(void* cmdList);
        void ShaderResourceFinishBuild();


        GraphicsResourceBehaviors Behaviors;
        EiRasPlatformBridgeProtocol* PlatformBridge;

        void SetResource(void* res, bool noMoreUpdate);
        void GetResource(void* res);

    private:
        _uint bufferSize;
    };
}

#endif
