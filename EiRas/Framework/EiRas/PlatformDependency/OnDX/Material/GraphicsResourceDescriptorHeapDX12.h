#ifndef Graphics_Resource_Descriptor_Heap_DX12
#define Graphics_Resource_Descriptor_Heap_DX12

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Global/GlobalDefine.h>
#include <Common/Heap.hpp>
#include <assert.h>

namespace MaterialSys
{

    struct HeapTable
    {
        _uint start;
        _uint end;

        _uint size;

        HeapTable()
        {
            start = -1;
            end = -1;
            size = 0;
        }
        HeapTable(_uint s, _uint e) : start(s), end(e)
        {
            size = e - s + 1;
            assert(size > 0);
        }
    };

    class Material;
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
#pragma warning("TOFIX")
        _uint DynamicFillHeapGlobal(void* res, void* format, bool DepthStencilRes = false, bool asUAV = false);

        void FillHeap();
        void RegMaterial(MaterialSys::Material* material);
        void RemoveMaterial(MaterialSys::Material* material);


    private:
        bool isDirty;

        std::vector<MaterialSys::Material*> MaterialArray;

        _uint g_HeapOffset;
        _uint OffsetSize;

        Common::Heap<HeapTable> HeapOffsetPool;
    };

}
#endif