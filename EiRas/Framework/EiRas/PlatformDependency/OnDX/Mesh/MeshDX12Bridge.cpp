#include "MeshDX12Bridge.h"
#include "MeshDX12.h"

using namespace MeshSys;

MeshDX12Bridge::MeshDX12Bridge()
{
    raw_obj = new MeshDX12();
}

void MeshDX12Bridge::BuildBuffer(EiRasPlatformBridgeProtocol* vertexResBridge, EiRasPlatformBridgeProtocol* indexResBridge, UINT vertexCount, UINT indexCount)
{
    void* indexRawObj = 0;
    if (indexResBridge)
    {
        indexRawObj = indexResBridge->raw_obj;
    }
    ((MeshDX12*)raw_obj)->BuildBuffer(vertexResBridge->raw_obj, indexRawObj, vertexCount, indexCount);
}