#pragma once
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <string>
#include <vector>

namespace MaterialSys
{
    class GraphicsResourceHeapDX12;
    class MaterialDX12;
    class MaterialLayout;
    
    class MeshDX12;
    class GraphicsResourceDX12;
}

namespace MeshSys
{
    class MeshDX12;
}

namespace Graphics {
    
    class CommandBufferDX12
    {
    public:
        CommandBufferDX12(std::string Name);
        ~CommandBufferDX12();

        void BeginFrame();

        void Reset(MaterialSys::GraphicsResourceHeapDX12* heapObj);
        void Commit(bool present);

        void DrawMesh(MeshSys::MeshDX12* mesh);

        void SetMaterial(MaterialSys::MaterialDX12* mat, MaterialSys::MaterialLayout* layout);

        ID3D12CommandAllocator* cmdAllocator = 0;
        ID3D12GraphicsCommandList* cmdList = 0;
        MaterialSys::GraphicsResourceHeapDX12* CurrentUseingHeap;
    private:
    };
}
