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

    typedef enum class GraphicsResourceVisibility
    {
        VISIBILITY_ALL = 0,
        VISIBILITY_VERTEX = (VISIBILITY_ALL + 1),
        VISIBILITY_PIXEL = (VISIBILITY_VERTEX + 1),
    } GraphicsResourceVisibility;

    class GraphicsResource
    {
    public:
        GraphicsResource(std::string Name, GraphicsResourceType type, GraphicsResourceVisibility visibile, bool shouldInitResource, int bufferSize);

        GraphicsResourceType ResourceType;
        GraphicsResourceVisibility Visibility;
        EiRasPlatformBridgeProtocol* PlatformBridge;

        void SetResource(void* res, bool shouldUnmap);

    private:
        int bufferSize;
    };
}

#endif
