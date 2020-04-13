#include "ShaderDX12Bridge.h"
#include "ShaderDX12.h"
#include <Material/ShaderLayout.h>

using MaterialSys::ShaderLayout;
using MaterialSys::ShaderDX12Bridge;

ShaderDX12Bridge::ShaderDX12Bridge(LPCSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName)
{
    raw_obj = new ShaderDX12(fileName, vertexFuncName, pixelFuncName);
}

ShaderDX12Bridge::ShaderDX12Bridge(LPCSTR fileName)
{
    raw_obj = new ShaderDX12(fileName);
}

void ShaderDX12Bridge::InitRootSignature(ShaderLayout* shaderLayout)
{
    ShaderDX12* obj = (ShaderDX12*)raw_obj;
    obj->InitRootSignature(shaderLayout);
}

void ShaderDX12Bridge::InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* desc)
{
    ShaderDX12* obj = (ShaderDX12*)raw_obj;
    obj->InitVertexDescriptor(desc);
}