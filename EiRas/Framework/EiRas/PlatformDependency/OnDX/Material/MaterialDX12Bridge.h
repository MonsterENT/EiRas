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
    class MaterialDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        MaterialDX12Bridge(std::string Name, EiRasPlatformBridgeProtocol* shaderObj);
        void UpdateRenderState(Graphics::GraphicsRenderState* renderState, EiRasPlatformBridgeProtocol* shaderObj, EiRasPlatformBridgeProtocol* cmdBufferPB, _uint pass = 0);
    };
}