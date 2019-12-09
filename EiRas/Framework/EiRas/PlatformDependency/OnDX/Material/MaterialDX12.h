#pragma once

#include <Windows.h>
#include <string>
#include <d3d12.h>

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
        MaterialDX12(std::string name, ShaderDX12* shaderObj);

        void SetProperty(MaterialProp* prop, void* res);

        void UpdateRenderState(Graphics::GraphicsRenderState* renderState, ShaderDX12* shaderObj);

        ShaderDX12* RawShaderObj;

        ID3D12PipelineState* PipelineState;
    };
}