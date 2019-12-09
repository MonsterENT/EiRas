#pragma once
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <string>
#include <vector>

namespace MaterialSys
{
    class MaterialDX12;
    class MaterialTable;
    class MaterialProp;
}

namespace Graphics {
    
    class CommandBufferDX12
    {
    public:
        CommandBufferDX12(std::string name);
        ~CommandBufferDX12();

        void SetPipelineState(MaterialSys::MaterialDX12* mat, std::vector<MaterialSys::MaterialProp*> props, std::vector<MaterialSys::MaterialTable*> tables);

        ID3D12CommandAllocator* cmdAllocator = 0;
        ID3D12GraphicsCommandList* cmdList = 0;
    private:
        ID3D12DescriptorHeap** heapPool;
    };
}