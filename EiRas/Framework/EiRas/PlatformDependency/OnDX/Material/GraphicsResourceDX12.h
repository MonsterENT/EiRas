#pragma once
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Material/MaterialLayout.hpp>

namespace MaterialSys
{
    struct GraphicsResourceBehaviors;

    class GraphicsResourceDX12
    {
    public:
        GraphicsResourceDX12(int bufferSize, GraphicsResourceBehaviors* behaviors, bool initResource);
        virtual ~GraphicsResourceDX12();

        ID3D12Resource* Resource;

        GraphicsResourceBehaviors* Behaviors;

        virtual void SetResource(void* res, bool noMoreUpdate);

        int GetBufferSize();

    protected:
        UINT8* ResMappingDestPtr;

    private:
        int bufferSize;
    };
}

