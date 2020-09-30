#include "ComputeKernelDX12Bridge.hpp"
#include "ComputeKernelDX12.hpp"
#include <Material/ShaderLayout.h>
#include <Material/MaterialLayout.hpp>

using namespace GPCompute;
using namespace MaterialSys;

ComputeKernelDX12Bridge::ComputeKernelDX12Bridge()
{
    raw_obj = new ComputeKernelDX12();
}

void ComputeKernelDX12Bridge::SetLayout(MaterialSys::ShaderLayout* layout, MaterialSys::MaterialLayout* resLayout)
{
    ((ComputeKernelDX12*)raw_obj)->SetLayout(layout, resLayout);
}

void ComputeKernelDX12Bridge::AddKernel(std::string fileName, std::string kernelName)
{
    ((ComputeKernelDX12*)raw_obj)->AddKernel(fileName.c_str(), kernelName.c_str());
}

void ComputeKernelDX12Bridge::Build()
{
    ((ComputeKernelDX12*)raw_obj)->Build();
}