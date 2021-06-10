#include "RenderTextureDX12.hpp"
#include <Material/GraphicsResource.hpp>

using namespace Graphics;
using namespace GraphicsAPI;
using namespace MaterialSys;

RenderTextureDX12::RenderTextureDX12(std::string name, MaterialSys::GraphicsResourceFormat colorFormat, bool useStencil, _uint width, _uint height)
{
    Name = name;
    Width = width;
    Height = height;
    ColorFormat = colorFormat;

    DepthStencilFormat = (MaterialSys::GraphicsResourceFormat)(useStencil ? DXGI_FORMAT_D32_FLOAT_S8X24_UINT : DXGI_FORMAT_D32_FLOAT);

#pragma region Init Color Buffer
    GET_EIRAS_DX12(device);
    device->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
            D3D12_HEAP_FLAG_NONE,
            &CD3DX12_RESOURCE_DESC::Tex2D((DXGI_FORMAT)colorFormat, width, height, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET),
            D3D12_RESOURCE_STATE_RENDER_TARGET,
            NULL,
            IID_PPV_ARGS(&ColorBuffer));

    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = 1;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    device->device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&RtvHeap));
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(RtvHeap->GetCPUDescriptorHandleForHeapStart());
    device->device->CreateRenderTargetView(ColorBuffer, nullptr, rtvHandle);
#pragma endregion

#pragma region Init DepthStencil Buffer
    D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
    depthStencilDesc.Format = (DXGI_FORMAT)DepthStencilFormat;
    depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

    D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
    depthOptimizedClearValue.Format = (DXGI_FORMAT)DepthStencilFormat;
    depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
    depthOptimizedClearValue.DepthStencil.Stencil = 0;

    device->device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Tex2D((DXGI_FORMAT)DepthStencilFormat, width, height, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &depthOptimizedClearValue,
        IID_PPV_ARGS(&DepthStencilBuffer));


    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    device->device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&DsvHeap));
    device->device->CreateDepthStencilView(DepthStencilBuffer, &depthStencilDesc, DsvHeap->GetCPUDescriptorHandleForHeapStart());
#pragma endregion

    _GraphicsResourceInstance = NULL;
}
#pragma warning("TOFIX")
void* RenderTextureDX12::GetGraphicsResource()
{
    if (_GraphicsResourceInstance == 0)
    {
        _GraphicsResourceInstance = new GraphicsResource(Name, GraphicsResourceType::SRV_RT, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT, false);
        ((GraphicsResource*)_GraphicsResourceInstance)->InitAsRT(this);
    }
    return _GraphicsResourceInstance;
}

void RenderTextureDX12::ChangeState(bool asSrv, ID3D12GraphicsCommandList* cmdList)
{
    if (asSrv)
    {
        ASSRV = true;
        cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(ColorBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
        cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(DepthStencilBuffer, D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_DEPTH_READ));
    }
    else
    {
        ASSRV = false;
        cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(ColorBuffer, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET));
        cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(DepthStencilBuffer, D3D12_RESOURCE_STATE_DEPTH_READ, D3D12_RESOURCE_STATE_DEPTH_WRITE));
    }
}