#ifndef Render_Texture_DX12_Hpp
#define Render_Texture_DX12_Hpp

#include <string>
#include <Global/GlobalDefine.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>

namespace MaterialSys
{
    enum class GraphicsResourceFormat;
}

namespace Graphics
{
    class RenderTextureDX12
    {
    public:
        std::string Name;
        RenderTextureDX12(std::string name, MaterialSys::GraphicsResourceFormat colorFormat, bool useStencil, _uint width, _uint height);
        
        ID3D12Resource* ColorBuffer;
        ID3D12Resource* DepthStencilBuffer;

        ID3D12DescriptorHeap* RtvHeap;
        ID3D12DescriptorHeap* DsvHeap;

        _uint Width;
        _uint Height;

        MaterialSys::GraphicsResourceFormat ColorFormat;
        MaterialSys::GraphicsResourceFormat DepthStencilFormat;

        void* GetGraphicsResource();
        _uint SrvHeapOffset;

    private:
        void* _GraphicsResourceInstance;
    };
}

#endif