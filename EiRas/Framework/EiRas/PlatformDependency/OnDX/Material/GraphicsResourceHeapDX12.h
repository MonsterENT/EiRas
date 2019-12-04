#pragma once

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>

namespace MaterialSys
{
    class GraphicsResourceDX12;

    class GraphicsResourceHeapDX12
    {
    public:
        ID3D12DescriptorHeap* heap = 0;
        GraphicsResourceHeapDX12(UINT resCount, MaterialSys::GraphicsResourceDX12** resArray, UINT initCount = -1);
        ~GraphicsResourceHeapDX12();
    };

}