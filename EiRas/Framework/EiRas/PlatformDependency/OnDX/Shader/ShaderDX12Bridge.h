#pragma once

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Windows.h>
#include <Global/GlobalDefine.h>

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

        void AddVertexFuncToPass(LPCSTR vertexFuncName, _uint pass);
        void AddPixelFuncToPass(LPCSTR pixelFuncName, _uint pass);

        void SetVertexFuncToPass(_uint index, _uint pass);
        void SetPixelFuncToPass(_uint index, _uint pass);

        void InitRootSignature(ShaderLayout* shaderLayout);
        
        void InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* desc);

        virtual ~ShaderDX12Bridge()
        {

        }
    };
}
