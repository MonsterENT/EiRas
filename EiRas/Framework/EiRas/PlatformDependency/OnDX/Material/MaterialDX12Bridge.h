#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>
#include <string>

namespace Graphics
{
    class GraphicsRenderState;
}

namespace MaterialSys
{
    class Shader;
    class MaterialDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        MaterialDX12Bridge(std::string name, Shader* shaderObj);

        void SetProperty(int propertyID, void* res);

        void UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj);
    };
}