#include "GraphicsResourceDX12Bridge.h"
#include <Global/PlatformDefine.h>
#include <Material/GraphicsResource.hpp>

#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ConstantBufferDX12.h>

using namespace MaterialSys;

GraphicsResourceDX12Bridge::GraphicsResourceDX12Bridge()
{
    raw_obj = 0;
}

void GraphicsResourceDX12Bridge::SetResource(void* res, bool noMoreUpdate)
{
    ((GraphicsResourceDX12*)raw_obj)->SetResource(res, noMoreUpdate);
}

void GraphicsResourceDX12Bridge::InitAsDefault(int bufferSize, GraphicsResourceBehaviors* behaviors)
{
    raw_obj = new GraphicsResourceDX12(bufferSize, behaviors, true);
}

void GraphicsResourceDX12Bridge::InitAsConstantBuffer(int bufferSize, GraphicsResourceBehaviors* behaviors)
{
    raw_obj = new ConstantBufferDX12(bufferSize, behaviors);
}

void GraphicsResourceDX12Bridge::InitAsShaderResource(int width, int height, void* texData, GraphicsResourceBehaviors* behaviors, bool* buildStatusFlag)
{
    raw_obj = new ShaderResourceDX12(behaviors, DXGI_FORMAT_R8G8B8A8_UNORM, width, height, texData, buildStatusFlag);
}

void GraphicsResourceDX12Bridge::ShaderResourceBuild(void* cmdList)
{
    ((ShaderResourceDX12*)raw_obj)->BuildTextureResource(cmdList);
}

void GraphicsResourceDX12Bridge::ShaderResourceFinishBuild()
{
    ((ShaderResourceDX12*)raw_obj)->FinishBuild();
}