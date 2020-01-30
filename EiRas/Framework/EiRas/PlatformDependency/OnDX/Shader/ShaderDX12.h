#pragma once

#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <Global/GlobalDefine.h>

namespace Graphics
{
    class GraphicsVertexDescriptor;
}

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

        void InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* desc);

        ID3D12RootSignature* RootSignature;

        _uint VertexAttributesCount;
        D3D12_INPUT_ELEMENT_DESC* VertexDescriptor;
    };
}
