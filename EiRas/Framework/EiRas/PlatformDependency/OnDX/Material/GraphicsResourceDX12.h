#pragma once
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Material/MaterialLayout.hpp>

namespace MaterialSys
{
    enum class GraphicsResourceType;

    class GraphicsResourceDX12
    {
    public:
        GraphicsResourceDX12();
        virtual ~GraphicsResourceDX12();

    public:
        ID3D12Resource* Resource;
        UINT8* ResMappingDestPtr;
        GraphicsResourceType ResType;
        CD3DX12_CPU_DESCRIPTOR_HANDLE CpuHandle;
        CD3DX12_GPU_DESCRIPTOR_HANDLE GpuHandle;
    protected:

    };
}

