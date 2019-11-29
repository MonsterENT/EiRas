#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>

#include <OnDX/d3dx12.h>

namespace GraphicsAPI
{
    class EiRasDX12
    {
    public:
        EiRasDX12(HWND hwnd, int frameWidth, int frameHeight);
        void InitDevice();

    private:
        ID3D12Device* device;
        HWND hwnd;
        int frameWidth, frameHeight;
        CD3DX12_VIEWPORT viewPort;
        CD3DX12_RECT scissorRect;
    };
}

