#include "GraphicsResourceDX12Bridge.h"
#include <Global/PlatformDefine.h>
#include <Material/GraphicsResource.hpp>

#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ConstantBufferDX12.h>

using namespace MaterialSys;

GraphicsResourceDX12Bridge::GraphicsResourceDX12Bridge()
{
    this->type = GraphicsResourceType::CBV;
    raw_obj = 0;
}

void GraphicsResourceDX12Bridge::SetResource(void* res, bool shouldUnmap)
{
    ((GraphicsResourceDX12*)raw_obj)->SetResource(res, shouldUnmap);
}

void GraphicsResourceDX12Bridge::InitAsDefault(int bufferSize, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq)
{
    this->type = GraphicsResourceType::Default;
    raw_obj = new GraphicsResourceDX12(bufferSize, visible, updateFreq, true);
}

void GraphicsResourceDX12Bridge::InitAsConstantBuffer(int bufferSize, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq)
{
    this->type = GraphicsResourceType::CBV;
    raw_obj = new ConstantBufferDX12(bufferSize, visible, updateFreq);
}

void GraphicsResourceDX12Bridge::InitAsShaderResource(int bufferSize, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq)
{
    this->type = GraphicsResourceType::SRV;
    //raw_obj = new ShaderResourceDX12();
}