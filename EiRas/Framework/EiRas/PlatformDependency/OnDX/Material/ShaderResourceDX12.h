#pragma once
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>

namespace MaterialSys
{
    class ShaderResourceDX12 : public GraphicsResourceDX12
    {
    public:
        ShaderResourceDX12(GraphicsResourceBehaviors* behaviors, DXGI_FORMAT format, UINT width, UINT height, UINT channels, void* texData, bool* buildStatusFlag);
        ~ShaderResourceDX12();

        DXGI_FORMAT TexFormat;
        
        bool isReady()
        {
            return buildStatusFlag;
        }

        void BuildTextureResource(void* cmdList);
        void FinishBuild();

        virtual void SetResource(void* res, bool noMoreUpdate);

    private:
        bool* outBuildStatusFlagPtr;
        bool buildStatusFlag = false;
        void* texData = 0;
        ID3D12Resource* tmpResource = 0;
        UINT width, height, channels;
    };
}