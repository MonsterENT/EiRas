#include "MeshDX12.h"
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/GraphicsPipelineInput.h>

using namespace MaterialSys;
using GraphicsAPI::EiRasDX12;

MeshDX12::MeshDX12(void* vertexRes, void* indexRes, UINT vertextCount, UINT indexCount)
{
    VertextCount = vertextCount;

    IndexCount = indexCount;

    GraphicsResourceDX12* rawVertexResObj = (GraphicsResourceDX12*)vertexRes;
    //GraphicsResourceDX12* rawIndexResObj = (GraphicsResourceDX12*)indexRes;

    VertexBufferView.BufferLocation = rawVertexResObj->Resource->GetGPUVirtualAddress();
    VertexBufferView.StrideInBytes = sizeof(Graphics::VertexDefault);
    VertexBufferView.StrideInBytes = rawVertexResObj->GetBufferSize();
}