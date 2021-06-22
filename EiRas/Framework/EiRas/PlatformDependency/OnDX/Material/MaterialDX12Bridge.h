#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>
#include <string>
#include <Global/GlobalDefine.h>

namespace Graphics
{
    class GraphicsRenderState;
}

namespace MaterialSys
{
    class MaterialProp;
    class ShaderDX12Bridge;
    class Material;
    class MaterialDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        MaterialDX12Bridge(std::string Name, EiRasPlatformBridgeProtocol* shaderObj, Material* matObj);
        virtual ~MaterialDX12Bridge();
        void UpdateRenderState(Graphics::GraphicsRenderState* renderState, EiRasPlatformBridgeProtocol* shaderObj, _uint pass = 0);
    };
}