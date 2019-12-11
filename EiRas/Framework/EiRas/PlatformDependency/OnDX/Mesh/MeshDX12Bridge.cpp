#include "MeshDX12Bridge.h"
#include "MeshDX12.h"

using namespace MaterialSys;

MeshDX12Bridge::MeshDX12Bridge(EiRasPlatformBridgeProtocol* vertexResBridge, EiRasPlatformBridgeProtocol* indexResBridge, UINT vertexCount, UINT indexCount)
{
    raw_obj = new MeshDX12(vertexResBridge->raw_obj, indexResBridge->raw_obj, vertexCount, indexCount);
}