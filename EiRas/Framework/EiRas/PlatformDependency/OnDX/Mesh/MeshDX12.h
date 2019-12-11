#pragma once

#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>

namespace MaterialSys
{
    class MeshDX12
    {
    public:
        MeshDX12(void* vertexRes, void* indexRes);
        D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
        D3D12_INDEX_BUFFER_VIEW IndexBufferView;
    };
}