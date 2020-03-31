#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>

#include <PlatformDependency/OnDX/d3dx12.h>

namespace Graphics
{
    class CommandBufferDX12;
}

namespace GraphicsAPI
{
    class EiRasDX12
    {
        friend Graphics::CommandBufferDX12;
    public:
        EiRasDX12(HWND hwnd, int screenWidth, int screenHeight);
        void InitDevice();

        ID3D12Device* device;

    protected:
        void _BeginFrame(ID3D12GraphicsCommandList* cmdList);
        void _Present(bool swapChainFlip, ID3D12GraphicsCommandList* cmdList);
        void _SetBackBufferState(bool toRenderTarget, ID3D12GraphicsCommandList* cmdList);

    private:
        void WaitForPreviousFrame();

        HWND hwnd;
        int screenWidth, screenHeight;
        UINT curFrameIndex;

        IDXGISwapChain3* swapChain3;
        ID3D12CommandQueue* cmdQueue;

        UINT rtvDescriptorSize;
        ID3D12Resource* renderTargets[2];

        ID3D12DescriptorHeap* rtvHeap;
        ID3D12DescriptorHeap* dsvHeap;
        ID3D12Resource* depthStencil;
    };
}

