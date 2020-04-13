#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>

namespace Graphics
{
    class GraphicsVertexDescriptor;
}

namespace MaterialSys
{
    class ShaderLayout;

    class ShaderDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        ShaderDX12Bridge(LPCSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName);
        ShaderDX12Bridge(LPCSTR fileName);

        void InitRootSignature(ShaderLayout* shaderLayout);
        
        void InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* desc);

        virtual ~ShaderDX12Bridge()
        {

        }
    };
}
