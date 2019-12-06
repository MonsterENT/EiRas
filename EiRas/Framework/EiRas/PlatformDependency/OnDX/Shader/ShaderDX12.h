#pragma once

#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>

namespace MaterialSys
{
    class ShaderLayout;

    class ShaderDX12
    {
    public:
        ShaderDX12(LPCSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName);
        ID3DBlob* VertexFunc;
        ID3DBlob* PixelFunc;

        void InitRootSignature(ShaderLayout* RefShaderLayout);

        ID3D12RootSignature* RootSignature;
    };
}
