#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>

namespace MaterialSys
{
    class ShaderLayout;

    class ShaderDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        ShaderDX12Bridge(LPCSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName);
        
        void InitRootSignature(ShaderLayout* shaderLayout);
        
        virtual ~ShaderDX12Bridge()
        {

        }
    };
}
