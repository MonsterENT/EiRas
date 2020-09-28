#ifndef Comput_Kernel_DX12_Hpp
#define Comput_Kernel_DX12_Hpp

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>

namespace GPCompute
{
    class ComputeKernelDX12
    {
    public:
        ComputeKernelDX12();
        void SetRootLayout();
        void AddKernel(LPCSTR fileName, LPCSTR kernelName);
        void Build();
        ID3D12PipelineState* _ComputePipelineStateObject;
    };
}

#endif
