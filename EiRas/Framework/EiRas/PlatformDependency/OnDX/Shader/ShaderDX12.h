#pragma once

#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <Global/GlobalDefine.h>
#include <map>

namespace Graphics
{
    class GraphicsVertexDescriptor;
    class GraphicsRenderState;
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

        ID3D12PipelineState* _GetPSO(Graphics::GraphicsRenderState* renderState);

    private:

        typedef std::map<_uint, ID3D12PipelineState*> PSOCache_MAP;
        typedef std::pair<_uint, ID3D12PipelineState*> PSOCache_PAIR;
        PSOCache_MAP _PSOCache;
    };
}
