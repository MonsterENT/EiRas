#ifndef Shader_Resource_RT_Hpp
#define Shader_Resource_RT_Hpp
#include <d3d12.h>

namespace MaterialSys
{
    enum class GraphicsResourceFormat;
}

namespace MaterialSys
{
    class ShaderResourceRTDX12
    {
    public:
        ShaderResourceRTDX12(void* format, void* resource)
        {
            Format = *((MaterialSys::GraphicsResourceFormat*)format);
            Resource = (ID3D12Resource*)resource;
        }
        MaterialSys::GraphicsResourceFormat Format;
        ID3D12Resource* Resource;
    };
}

#endif