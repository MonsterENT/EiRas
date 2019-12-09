#pragma once
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>

namespace MaterialSys
{
    class Material;
}

namespace Graphics {
    class CommandBufferDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        CommandBufferDX12Bridge(std::string name);

        void SetMaterial(MaterialSys::Material* mat);
    };
}