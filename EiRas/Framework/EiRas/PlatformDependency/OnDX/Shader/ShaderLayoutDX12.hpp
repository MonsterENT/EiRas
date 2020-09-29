#ifndef Shader_Layout_DX12_Hpp
#define Shader_Layout_DX12_Hpp

#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>

namespace MaterialSys
{
    class ShaderLayout;
    class ShaderLayoutDX12
    {
    public:
        ShaderLayoutDX12();
        ~ShaderLayoutDX12();
        void Build(ShaderLayout* layout);
        ID3D12RootSignature* m_RootSignature;
    };
}

#endif
