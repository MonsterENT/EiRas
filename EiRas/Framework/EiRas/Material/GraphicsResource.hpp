#ifndef Graphics_Resource_hpp
#define Graphics_Resource_hpp

class EiRasPlatformBridgeProtocol;

#include <string>

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

    class GraphicsResource
    {
    public:
        GraphicsResource(std::string Name, GraphicsResourceType type, bool shouldInitResource, int bufferSize);

        GraphicsResourceType ResourceType;
        EiRasPlatformBridgeProtocol* PlatformBridge;

        void SetResource(void* res, bool shouldUnmap);

    private:
        int bufferSize;
    };
}

#endif
