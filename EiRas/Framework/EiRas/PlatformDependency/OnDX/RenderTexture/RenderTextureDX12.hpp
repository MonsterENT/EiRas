#ifndef Render_Texture_DX12_Hpp
#define Render_Texture_DX12_Hpp

#include <string>
#include <Global/GlobalDefine.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>

namespace Graphics
{
    enum class RenderBufferFormat;

    class RenderTextureDX12
    {
    public:
        RenderTextureDX12(std::string name, RenderBufferFormat colorFormat, bool useStencil, _uint width, _uint height);
        
        ID3D12Resource* ColorBuffer;
        ID3D12Resource* DepthStencilBuffer;

        ID3D12DescriptorHeap* RtvHeap;
        ID3D12DescriptorHeap* DsvHeap;

        _uint Width;
        _uint Height;

        RenderBufferFormat ColorFormat;
        RenderBufferFormat DepthStencilFormat;
    };
}

#endif