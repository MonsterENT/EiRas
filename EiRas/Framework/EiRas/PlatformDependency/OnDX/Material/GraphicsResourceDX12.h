#pragma once
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Material/MaterialLayout.hpp>

namespace Graphics
{
    class CommandBufferDX12;
}

namespace MaterialSys
{
    struct GraphicsResourceBehaviors;
    enum class GraphicsResourceDimension;

    class GraphicsResourceDX12
    {
        friend Graphics::CommandBufferDX12;
    public:
        GraphicsResourceDX12(int bufferSize, GraphicsResourceBehaviors* behaviors);
        virtual ~GraphicsResourceDX12();

        void BuildResource(D3D12_HEAP_TYPE heapType, D3D12_RESOURCE_STATES resourceState, GraphicsResourceDimension type, int format = 0, int width = 0, int height = 0, int depth = 0);

        ID3D12Resource* Resource;

        GraphicsResourceBehaviors* Behaviors;

        virtual void SetResource(void* res, bool noMoreUpdate);
        virtual void GetResource(void* res);

        int GetBufferSize();

        D3D12_RESOURCE_STATES ResourceState;
        void ChangeState(bool cbv, bool srv, bool uav, bool target, ID3D12GraphicsCommandList* cmdList);
        void ChangeState(D3D12_RESOURCE_STATES state, ID3D12GraphicsCommandList* cmdList);

    protected:
        UINT8* ResMappingDestPtr;
        UINT64 ResADDR;

    private:
        int bufferSize;
    };
}

