#pragma once

#include <Windows.h>
#include <string>
#include <vector>

namespace Graphics
{
    class GraphicsRenderState;
}

namespace MaterialSys
{
    class Shader;
    class ShaderDX12;
    class MaterialLayout;
    class MaterialProp;
    class MaterialTable;

    class MaterialDX12
    {
    public:
        std::string Name;
        MaterialDX12(std::string name, Shader* shaderObj);

        void SetProperty(int propertyId, void* res);

        void UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj);

        ShaderDX12* RawShaderObj;

        std::vector<MaterialProp*> Props;
        std::vector<MaterialProp*> LayoutProps;
        std::vector<MaterialTable*> LayoutTables;
    };
}