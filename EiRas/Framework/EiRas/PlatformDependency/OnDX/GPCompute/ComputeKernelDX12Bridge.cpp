#include "ComputeKernelDX12Bridge.hpp"
#include "ComputeKernelDX12.hpp"
using namespace GPCompute;

ComputeKernelDX12Bridge::ComputeKernelDX12Bridge()
{
    raw_obj = new ComputeKernelDX12();
}