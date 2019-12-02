#pragma once
#include <PlatformDependency/OnDX/Resource/ResourceDX12.h>
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>

namespace MaterialSys
{
    class ShaderResourceDX12 : public virtual ResourceDX12
    {
    public:
        ShaderResourceDX12(DXGI_FORMAT format, UINT width, UINT height, UINT8* texData);
        ~ShaderResourceDX12();

        DXGI_FORMAT getTextureFormat()
        {
            return textureFormat;
        }

        bool isReady()
        {
            return _isReady;
        }

        void invoke(void* data);

        void invokeFinished(void* data)
        {
            _isReady = true;
        }
    private:
        DXGI_FORMAT textureFormat;
        bool _isReady = false;
        UINT8* texData = 0;
        ID3D12Resource* tmpResource = 0;
        UINT width, height;
    };
}