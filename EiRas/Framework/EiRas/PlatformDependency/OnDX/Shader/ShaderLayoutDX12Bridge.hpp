#ifndef Shader_Layout_DX12_Bridge_Hpp
#define Shader_Layout_DX12_Bridge_Hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys
{
    class ShaderLayout;
    class ShaderLayoutDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        void Build(ShaderLayout* layout);
    };
}

#endif