#pragma once

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class MaterialTable;
    class GraphicsResourceHeapDX12
    {
    public:
        int Offset;
        ID3D12DescriptorHeap* heap = 0;
        GraphicsResourceHeapDX12(_uint propCount, _uint tableCount, MaterialTable** tableArray);
        ~GraphicsResourceHeapDX12();
    };

}