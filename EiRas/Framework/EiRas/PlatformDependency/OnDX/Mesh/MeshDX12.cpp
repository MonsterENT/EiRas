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

void MeshDX12::BuildBuffer(void* vertexRes, void* indexRes, _uint vertexCount, _uint indexCount)
{
    VertexCount = vertexCount;
    IndexCount = indexCount;

    GraphicsResourceDX12* rawVertexResObj = (GraphicsResourceDX12*)vertexRes;
    GraphicsResourceDX12* rawIndexResObj = (GraphicsResourceDX12*)indexRes;

    VertexBufferView.BufferLocation = rawVertexResObj->Resource->GetGPUVirtualAddress();
    VertexBufferView.StrideInBytes = rawVertexResObj->GetBufferSize() / VertexCount;
    VertexBufferView.SizeInBytes = rawVertexResObj->GetBufferSize();

    IndexBufferView.BufferLocation = rawIndexResObj->Resource->GetGPUVirtualAddress();
    IndexBufferView.SizeInBytes = rawIndexResObj->GetBufferSize();
    IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
}