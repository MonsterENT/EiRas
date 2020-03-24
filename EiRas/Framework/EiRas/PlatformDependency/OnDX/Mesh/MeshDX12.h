#pragma once

#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>

#include <Global/GlobalDefine.h>

namespace MeshSys
{
    class MeshDX12
    {
    public:
        MeshDX12();

        void BuildBuffer(void* vertexRes, void* indexRes, _uint vertexCount, _uint indexCount);

        _uint VertexCount, IndexCount;

        D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
        D3D12_INDEX_BUFFER_VIEW IndexBufferView;
    };
}