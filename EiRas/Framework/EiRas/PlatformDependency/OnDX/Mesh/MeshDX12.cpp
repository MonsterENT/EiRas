#include "MeshDX12.h"
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>

using namespace MeshSys;
using MaterialSys::GraphicsResourceDX12;
using GraphicsAPI::EiRasDX12;

MeshDX12::MeshDX12()
{
}

void MeshDX12::Reset()
{
    VertexBufferViews.clear();
    IndexBufferViews.clear();
}

void MeshDX12::BuildBufferView(void* rawVertexResObj, _uint vertexBufferSize, _uint vertexCount,
    void* rawIndexResObj, _uint indexBufferSize)
{
    GraphicsResourceDX12* _rawVertexResObj = (GraphicsResourceDX12*)rawVertexResObj;
    GraphicsResourceDX12* _rawIndexResObj = (GraphicsResourceDX12*)rawIndexResObj;

    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
    vertexBufferView.BufferLocation = _rawVertexResObj->Resource->GetGPUVirtualAddress();
    vertexBufferView.StrideInBytes = vertexBufferSize / vertexCount;
    vertexBufferView.SizeInBytes = vertexBufferSize;

    D3D12_INDEX_BUFFER_VIEW indexBufferView;
    indexBufferView.BufferLocation = _rawIndexResObj->Resource->GetGPUVirtualAddress();
    indexBufferView.SizeInBytes = indexBufferSize;
    indexBufferView.Format = DXGI_FORMAT_R32_UINT;

    VertexBufferViews.push_back(vertexBufferView);
    IndexBufferViews.push_back(indexBufferView);
}