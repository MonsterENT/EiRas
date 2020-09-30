#ifndef Comput_Kernel_DX12_Hpp
#define Comput_Kernel_DX12_Hpp

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>

namespace MaterialSys
{
    class ShaderLayout;
    class MaterialLayout;
}

namespace GPCompute
{
    class ComputeKernelDX12
    {
    public:
        ComputeKernelDX12();
        ~ComputeKernelDX12();
        void SetLayout(MaterialSys::ShaderLayout* layout, MaterialSys::MaterialLayout* resLayout);
        void AddKernel(LPCSTR fileName, LPCSTR kernelName);
        void Build();
        ID3D12PipelineState* _ComputePipelineStateObject;
        ID3DBlob* kernelFuncBlob;

        MaterialSys::MaterialLayout* ResLayout;
        ID3D12RootSignature* GetRootSignature();

    private:
        MaterialSys::ShaderLayout* Layout;
    };
}

#endif
