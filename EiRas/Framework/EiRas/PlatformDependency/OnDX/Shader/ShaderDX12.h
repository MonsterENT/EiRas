#pragma once

#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <Global/GlobalDefine.h>
#include <map>
#include <vector>

namespace Graphics
{
    class GraphicsVertexDescriptor;
    class GraphicsRenderState;
}

namespace MaterialSys
{
    class ShaderLayout;

    typedef struct ShaderPassData
    {
        _uint VertexFuncIndex;
        _uint PixelFuncIndex;
        ShaderPassData()
        {
            VertexFuncIndex = 0;
            PixelFuncIndex = 0;
        }
        ShaderPassData(_uint vIndex, _uint pIndex)
        {
            VertexFuncIndex = vIndex;
            PixelFuncIndex = pIndex;
        }
    } ShaderPassData;

    class ShaderDX12
    {
    public:
        std::string Name;
        ShaderDX12(LPCSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName);
        ShaderDX12(LPCSTR fileName);

        void AddVertexFuncToPass(LPCSTR vertexFuncName, _uint pass);
        void AddPixelFuncToPass(LPCSTR pixelFuncName, _uint pass);

        void SetVertexFuncToPass(_uint index, _uint pass);
        void SetPixelFuncToPass(_uint index, _uint pass);


        std::vector<ID3DBlob*> VertexFuncList;
        std::vector<ID3DBlob*> PixelFuncList;
        std::vector<ShaderPassData> m_ShaderPassData;

        void InitRootSignature(ShaderLayout* RefShaderLayout);

        void InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* desc, _uint pass);

        ID3D12RootSignature* RootSignature;

        std::vector<_uint> VertexAttributesCountList;
        std::vector<D3D12_INPUT_ELEMENT_DESC*> VertexDescriptorList;

        ID3D12PipelineState* _GetPSO(Graphics::GraphicsRenderState* renderState, _uint numRT, DXGI_FORMAT* rtFormats, DXGI_FORMAT depthFormat, _uint pass = 0);

    private:

        typedef std::map<_uint, ID3D12PipelineState*> PSOCache_MAP;
        typedef std::pair<_uint, ID3D12PipelineState*> PSOCache_PAIR;
        PSOCache_MAP _PSOCache;
    };
}
