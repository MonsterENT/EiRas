#ifndef Comput_Kernel_Hpp
#define  Comput_Kernel_Hpp

#include <Global/GlobalDefine.h>
#include <string>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys
{
    class ShaderLayout;
    class MaterialLayout;
}

namespace GPCompute
{
    class ComputeKernel
    {

    public:
        ComputeKernel();
        void SetLayout(MaterialSys::ShaderLayout* layout);
        void AddKernel(std::string fileName, std::string kernelName);
        void Build();

        void SetProperty(void* res, _uint slotIndex);
        void GetPropertyData(void* res, _uint slotIndex);

        EiRasPlatformBridgeProtocol* PlatformBridge;
        MaterialSys::MaterialLayout* ResLayout;
    };
}

#endif
