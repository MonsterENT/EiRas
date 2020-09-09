#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>
#include <Global/GlobalDefine.h>

namespace MeshSys
{
    class MeshDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        MeshDX12Bridge();
        void Reset();
        void BuildBufferView(void* vertexResObjPB, _uint vertexBufferSize, _uint vertexCount,
            void* indexResObjPB, _uint indexBufferSize);
    };
}