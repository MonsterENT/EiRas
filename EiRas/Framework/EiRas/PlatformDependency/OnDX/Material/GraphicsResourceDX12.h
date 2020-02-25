#pragma once
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Material/MaterialLayout.hpp>

namespace MaterialSys
{
    enum class GraphicsResourceType;
    enum class GraphicsResourceVisibility;
    enum class GraphicsResourceUpdateFreq;

    class GraphicsResourceDX12
    {
    public:
        GraphicsResourceDX12(int bufferSize, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq, bool initResource);
        virtual ~GraphicsResourceDX12();

        ID3D12Resource* Resource;
        
        GraphicsResourceType ResType;
        CD3DX12_CPU_DESCRIPTOR_HANDLE CpuHandle;
        CD3DX12_GPU_DESCRIPTOR_HANDLE GpuHandle;

        void SetResource(void* res, bool shouldUnmap);

        int GetBufferSize();

    protected:
        UINT8* ResMappingDestPtr;

    private:
        int bufferSize;
    };
}

