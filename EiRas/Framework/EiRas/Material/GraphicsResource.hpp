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
        SAMPLER = (CBV + 1)
    } GraphicsResourceType;

    class GraphicsResource
    {
    public:
        GraphicsResource(std::string Name, GraphicsResourceType type, int bufferSize = -1);

        GraphicsResourceType ResourceType;
        EiRasPlatformBridgeProtocol* PlatformBridge;

    private:
        int bufferSize;
    };
}

#endif