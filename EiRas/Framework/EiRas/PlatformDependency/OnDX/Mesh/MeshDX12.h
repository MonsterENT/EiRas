#pragma once

#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <vector>
#include <Global/GlobalDefine.h>

namespace MeshSys
{
    class MeshDX12
    {
    public:
        MeshDX12();

        std::vector<D3D12_VERTEX_BUFFER_VIEW> VertexBufferViews;
        std::vector<D3D12_INDEX_BUFFER_VIEW> IndexBufferViews;

        void BuildBufferView(void* rawVertexResObj, _uint vertexBufferSize, _uint vertexCount,
            void* rawIndexResObj, _uint indexBufferSize);
    };
}