#pragma once

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class MaterialTable;
    class MaterialProp;
    class GraphicsResourceDescriptorHeapDX12
    {
    public:
        ID3D12DescriptorHeap* heap = 0;
        GraphicsResourceDescriptorHeapDX12(_uint propCount);
        ~GraphicsResourceDescriptorHeapDX12();

        void FillHeap(_uint tableCount, MaterialTable** tableArray);
        void DynamicFillHeap(MaterialSys::MaterialProp*);
        _uint DynamicFillHeapWithGlobalResource(void*, void*);

    private:
        _uint Offset;
        _uint propCount;
        _uint g_HeapOffset;
    };

}