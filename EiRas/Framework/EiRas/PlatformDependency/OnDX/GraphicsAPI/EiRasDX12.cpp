#include "EiRasDX12.h"

#pragma comment (lib, "D3D12.lib")
#pragma comment (lib, "DXGI.lib")

using GraphicsAPI::EiRasDX12;

HANDLE fenceEvent;
ID3D12Fence* fence = 0;
UINT64 fenceValue = 0;

IDXGISwapChain3* swapChain3 = 0;
UINT frameCount = 2; 
UINT curFrameIndex = -1;
UINT rtvDescriptorSize;
ID3D12Resource* renderTargets[2];
ID3D12PipelineState* curPipelineState;

ID3D12CommandAllocator* workCmdAllocator = 0;
ID3D12CommandAllocator* cmdAllocator = 0;
ID3D12GraphicsCommandList* cmdList = 0;
ID3D12GraphicsCommandList* workCmdList;
ID3D12CommandQueue* cmdQueue = 0;

ID3D12DescriptorHeap* rtvHeap = 0;
ID3D12DescriptorHeap* dsvHeap = 0;
ID3D12Resource* depthStencil = 0;

EiRasDX12::EiRasDX12(HWND hwnd, int frameWidth, int frameHeight)
{
    this->hwnd = hwnd;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->device = nullptr;
    viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight));
    scissorRect = CD3DX12_RECT(0, 0, static_cast<LONG>(frameWidth), static_cast<LONG>(frameHeight));
}

void EiRasDX12::InitDevice()
{
    IDXGIFactory4* factory = 0;
    CreateDXGIFactory2(0, IID_PPV_ARGS(&factory));

    IDXGIAdapter1* adapter = 0;
    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            // Don't select the Basic Render Driver adapter.
            // If you want a software adapter, pass in "/warp" on the command line.
            continue;
        }

        // Check to see if the adapter supports Direct3D 12, but don't create the
        // actual device yet.
        if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
        {
            break;
        }
    }

    // Create Device.///////////////
    D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));

    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
    cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));
    /////////////////

    // Describe and create the swap chain.///////////////
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = frameCount;
    swapChainDesc.Width = frameWidth;
    swapChainDesc.Height = frameHeight;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    IDXGISwapChain1* swapChain = 0;

    factory->CreateSwapChainForHwnd(cmdQueue, hwnd, &swapChainDesc, 0, 0, &swapChain);
    swapChain3 = (IDXGISwapChain3*)swapChain;
    /////////////////

    //factory->MakeWindowAssociation(windowHwnd, DXGI_MWA_NO_ALT_ENTER);
    curFrameIndex = swapChain3->GetCurrentBackBufferIndex();

    // Create descriptor heaps.///////////////
    {
        // Describe and create a render target view (RTV) descriptor heap.
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = frameCount;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

        device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

        rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    // Create frame resources.
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());

    // Create a RTV for each frame.
    for (UINT n = 0; n < frameCount; n++)
    {
        swapChain3->GetBuffer(n, IID_PPV_ARGS(&renderTargets[n]));
        device->CreateRenderTargetView(renderTargets[n], nullptr, rtvHandle);
        rtvHandle.Offset(1, rtvDescriptorSize);
    }

    // Describe and create a depth stencil view(DSV) descriptor heap.
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

    // Create the depth stencil view.
    {
        D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
        depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
        depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

        D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
        depthOptimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
        depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
        depthOptimizedClearValue.DepthStencil.Stencil = 0;

        device->CreateCommittedResource(
            &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
            D3D12_HEAP_FLAG_NONE,
            &CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, frameWidth, frameHeight, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
            D3D12_RESOURCE_STATE_DEPTH_WRITE,
            &depthOptimizedClearValue,
            IID_PPV_ARGS(&depthStencil));

        device->CreateDepthStencilView(depthStencil, &depthStencilDesc, dsvHeap->GetCPUDescriptorHandleForHeapStart());
    }
    /////////////////

    // Create CommandAllocator///////////////
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));

    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&workCmdAllocator));
    /////////////////

    // Create the command list.
    device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, 0, IID_PPV_ARGS(&cmdList));
    // Create the work command list.
    device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, workCmdAllocator, 0, IID_PPV_ARGS(&workCmdList));

    // Create synchronization objects and wait until assets have been uploaded to the GPU.
    device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    fenceValue = 1;

    // Create an event handle to use for frame synchronization.
    fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    assert(fenceEvent != nullptr);
}