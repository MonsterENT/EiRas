#pragma once
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>

namespace MaterialSys
{
    class ResourceDX12
    {
    public:
        enum class ResourceTypeDX12
        {
            TypeCB = 0,
            TypeSRV = 1,
        };
        ResourceDX12();
        virtual ~ResourceDX12();

    public:
        ID3D12Resource* Resource;

        ResourceTypeDX12 ResType;
        CD3DX12_CPU_DESCRIPTOR_HANDLE CpuHandle;
        CD3DX12_GPU_DESCRIPTOR_HANDLE GpuHandle;
    protected:

    };
}

