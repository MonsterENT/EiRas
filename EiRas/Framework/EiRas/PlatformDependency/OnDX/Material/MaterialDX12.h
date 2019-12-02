#pragma once

#include <Windows.h>
#include <string>

namespace Graphics
{
    class GraphicsRenderState;
}

namespace MaterialSys
{
    class Shader;
    class ShaderDX12;
    class MaterialDX12
    {
    public:
        std::string Name;
        MaterialDX12(std::string name, Shader* shaderObj);

        void SetProperty(int propertyId, void* res);

        void UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj);

        ShaderDX12* RawShaderObj;
    };
}