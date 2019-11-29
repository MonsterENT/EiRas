#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys
{
    class ShaderDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        ShaderDX12Bridge(LPCWSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName);
    };
}
