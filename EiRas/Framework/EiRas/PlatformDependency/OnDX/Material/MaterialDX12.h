#pragma once

#include <Windows.h>
#include <string>
#include <d3d12.h>
#include <vector>
#include <Global/GlobalDefine.h>

namespace Graphics
{
    class GraphicsRenderState;
}

namespace MaterialSys
{
    class ShaderDX12;
    class MaterialLayout;
    class MaterialProp;
    class MaterialTable;

    class MaterialDX12
    {
    public:
        std::string Name;
        MaterialDX12(std::string Name, ShaderDX12* shaderObj);

        void UpdateRenderState(Graphics::GraphicsRenderState* renderState, ShaderDX12* shaderObj, void* rawCmdBuffer, _uint pass = 0);

        ShaderDX12* RawShaderObj;

        std::vector<ID3D12PipelineState*> PassedPipelineState;
    };
}