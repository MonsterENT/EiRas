#include "ComputeKernel.hpp"

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/GPCompute/ComputeKernelDX12Bridge.hpp>
#endif

using namespace GPCompute;


ComputeKernel::ComputeKernel()
{
#if GRAPHICS_DX
    PlatformBridge = new ComputeKernelDX12Bridge();
#endif
}