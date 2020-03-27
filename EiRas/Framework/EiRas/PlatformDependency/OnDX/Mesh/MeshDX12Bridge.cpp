#include "MeshDX12Bridge.h"
#include "MeshDX12.h"
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

using namespace MeshSys;

MeshDX12Bridge::MeshDX12Bridge()
{
    raw_obj = new MeshDX12();
}

void MeshDX12Bridge::BuildBufferView(void* vertexResObjPB, _uint vertexBufferSize, _uint vertexCount,
    void* indexResObjPB, _uint indexBufferSize)
{
    ((MeshDX12*)raw_obj)->BuildBufferView(((EiRasPlatformBridgeProtocol*)vertexResObjPB)->raw_obj, vertexBufferSize, vertexCount,
        ((EiRasPlatformBridgeProtocol*)indexResObjPB)->raw_obj, indexBufferSize);
}