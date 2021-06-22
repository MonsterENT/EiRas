#pragma once

#include <Windows.h>
#include <string>
#include <d3d12.h>
#include <vector>
#include <Global/GlobalDefine.h>
#include <Material/Material.hpp>

namespace Graphics
{
    class GraphicsRenderState;
}

namespace MaterialSys
{
    class ShaderDX12;
    class MaterialProp;
    class MaterialDX12
    {
    public:
        std::string Name;
        MaterialDX12(std::string Name, ShaderDX12* shaderObj, Material* matObj);

        void UpdateRenderState(Graphics::GraphicsRenderState* renderState, ShaderDX12* shaderObj, _uint pass = 0);

        void Release();

        ShaderDX12* RawShaderObj;
        Material* RawMatObj;
        std::vector<ID3D12PipelineState*> PassedPipelineState;
    };
}