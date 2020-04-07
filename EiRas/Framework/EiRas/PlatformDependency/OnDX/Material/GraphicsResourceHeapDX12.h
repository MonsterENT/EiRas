#pragma once

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class MaterialTable;
    class MaterialProp;
    class GraphicsResourceHeapDX12
    {
    public:
        ID3D12DescriptorHeap* heap = 0;
        GraphicsResourceHeapDX12(_uint propCount);
        ~GraphicsResourceHeapDX12();

        void FillHeap(_uint tableCount, MaterialTable** tableArray);
        void DynamicFillHeap(MaterialSys::MaterialProp*);
        void DynamicFillHeapWithOuterResource(_uint, void*, void*);

    private:
        _uint Offset;
        _uint propCount;
    };

}