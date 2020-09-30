#ifndef Comput_Kernel_DX12_Bridge_Hpp
#define  Comput_Kernel_DX12_Bridge_Hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>
namespace MaterialSys
{
    class ShaderLayout;
    class MaterialLayout;
}

namespace GPCompute
{
    class ComputeKernelDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        ComputeKernelDX12Bridge();
        void SetLayout(MaterialSys::ShaderLayout* layout, MaterialSys::MaterialLayout* resLayout);
        void AddKernel(std::string fileName, std::string kernelName);
        void Build();
    };
}

#endif
