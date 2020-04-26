#ifndef Shader_Resource_RT_Hpp
#define Shader_Resource_RT_Hpp
#include <d3d12.h>

namespace Graphics
{
    enum class RenderBufferFormat;
}

namespace MaterialSys
{
    class ShaderResourceRTDX12
    {
    public:
        ShaderResourceRTDX12(void* format, void* resource)
        {
            Format = *((Graphics::RenderBufferFormat*)format);
            Resource = (ID3D12Resource*)resource;
        }
        Graphics::RenderBufferFormat Format;
        ID3D12Resource* Resource;
    };
}

#endif