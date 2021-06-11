#include "GraphicsResourceDX12Bridge.h"

#include <Material/GraphicsResource.hpp>

#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceDX12.h>
#include <PlatformDependency/OnDX/Material/ConstantBufferDX12.h>
#include <PlatformDependency/OnDX/Material/ShaderResourceRTDX12.hpp>

using namespace MaterialSys;

GraphicsResourceDX12Bridge::GraphicsResourceDX12Bridge()
{
    raw_obj = 0;
}

void GraphicsResourceDX12Bridge::SetResource(void* res, bool noMoreUpdate)
{
    ((GraphicsResourceDX12*)raw_obj)->SetResource(res, noMoreUpdate);
}

void GraphicsResourceDX12Bridge::GetResource(void* res)
{
    ((GraphicsResourceDX12*)raw_obj)->GetResource(res);
}

void GraphicsResourceDX12Bridge::InitAsDefault(int bufferSize, GraphicsResourceBehaviors* behaviors, GraphicsResourceDimension dimension)
{
    raw_obj = new GraphicsResourceDX12(bufferSize, behaviors);
    ((GraphicsResourceDX12*)raw_obj)->BuildResource(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ, dimension);
}

void GraphicsResourceDX12Bridge::InitAsUAV(int bufferSize, GraphicsResourceBehaviors* behaviors, GraphicsResourceDimension dimension)
{
    raw_obj = new GraphicsResourceDX12(bufferSize, behaviors);
    ((GraphicsResourceDX12*)raw_obj)->BuildResource(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_UNORDERED_ACCESS, dimension);
}

void GraphicsResourceDX12Bridge::InitAsRT(void* rtRawObj)
{
    raw_obj = new ShaderResourceRTDX12(rtRawObj);
}

void GraphicsResourceDX12Bridge::InitAsConstantBuffer(int bufferSize, GraphicsResourceBehaviors* behaviors)
{
    raw_obj = new ConstantBufferDX12(bufferSize, behaviors);
    ((GraphicsResourceDX12*)raw_obj)->BuildResource(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ, GraphicsResourceDimension::GraphicsResourceDimension_Buffer);
}

void GraphicsResourceDX12Bridge::InitAsShaderResource(int bufferSize, GraphicsResourceBehaviors* behaviors)
{
    raw_obj = new ConstantBufferDX12(bufferSize, behaviors);
    ((GraphicsResourceDX12*)raw_obj)->BuildResource(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ, GraphicsResourceDimension::GraphicsResourceDimension_Buffer);
}

void GraphicsResourceDX12Bridge::InitAsShaderResource(int width, int height, _uint channels, void* texData, GraphicsResourceBehaviors* behaviors, bool* buildStatusFlag, GraphicsResourceDimension dimension)
{
    if (channels == 1)
    {
        raw_obj = new ShaderResourceDX12(behaviors, DXGI_FORMAT_A8_UNORM, width, height, channels, texData, buildStatusFlag);
        ((GraphicsResourceDX12*)raw_obj)->BuildResource(D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_GENERIC_READ, dimension, DXGI_FORMAT_A8_UNORM, width, height, 0);
    }
    else //4
    {
        raw_obj = new ShaderResourceDX12(behaviors, DXGI_FORMAT_R8G8B8A8_UNORM, width, height, channels, texData, buildStatusFlag);
        ((GraphicsResourceDX12*)raw_obj)->BuildResource(D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_GENERIC_READ, dimension, DXGI_FORMAT_R8G8B8A8_UNORM, width, height, 0);
    }

}

void GraphicsResourceDX12Bridge::ShaderResourceBuild(void* cmdList)
{
    ((ShaderResourceDX12*)raw_obj)->BuildTextureResource(cmdList);
}

void GraphicsResourceDX12Bridge::ShaderResourceFinishBuild()
{
    ((ShaderResourceDX12*)raw_obj)->FinishBuild();
}