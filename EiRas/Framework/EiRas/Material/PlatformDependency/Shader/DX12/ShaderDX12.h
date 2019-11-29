#pragma once

#include <GraphicsAPI/PlatformDependency/DX12/EiRasDX12.h>

namespace MaterialSys
{
    class ShaderDX12
    {
    public:
        ShaderDX12(LPCWSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName);
        ID3DBlob* vertexFunc;
        ID3DBlob* pixelFunc;
    private:
                
    };
}
