#ifndef Graphics_Resource_Descriptor_Heap_DX12
#define Graphics_Resource_Descriptor_Heap_DX12

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
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
        _uint DynamicFillHeapGlobal(void* res, void* format);

        void FillHeap();
        void RegMaterial(MaterialSys::Material* material);
        void RemoveMaterial(MaterialSys::Material* material);


    private:
        bool isDirty;

        std::vector<MaterialSys::Material*> MaterialArray;

        _uint g_HeapOffset;
        _uint Offset;
        _uint propCount;
    };

}
#endif