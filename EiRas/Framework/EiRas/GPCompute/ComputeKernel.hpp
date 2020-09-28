#ifndef Comput_Kernel_Hpp
#define  Comput_Kernel_Hpp

#include <Global/GlobalDefine.h>
#include <string>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace GPCompute
{
    class ComputeKernel
    {

    public:
        ComputeKernel();

        EiRasPlatformBridgeProtocol* PlatformBridge;
    };
}

#endif
