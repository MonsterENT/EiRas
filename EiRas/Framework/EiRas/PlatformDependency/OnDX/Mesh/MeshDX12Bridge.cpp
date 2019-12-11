#include "MeshDX12Bridge.h"
#include "MeshDX12.h"

using namespace MaterialSys;

MeshDX12Bridge::MeshDX12Bridge(EiRasPlatformBridgeProtocol* vertexResBridge, EiRasPlatformBridgeProtocol* indexResBridge)
{
    raw_obj = new MeshDX12(vertexResBridge->raw_obj, indexResBridge->raw_obj);
}