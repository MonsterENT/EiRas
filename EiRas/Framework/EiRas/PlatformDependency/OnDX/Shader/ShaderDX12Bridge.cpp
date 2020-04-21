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

void ShaderDX12Bridge::AddVertexFuncToPass(LPCSTR vertexFuncName, _uint pass)
{
    ((ShaderDX12*)raw_obj)->AddVertexFuncToPass(vertexFuncName, pass);
}

void ShaderDX12Bridge::AddPixelFuncToPass(LPCSTR pixelFuncName, _uint pass)
{
    ((ShaderDX12*)raw_obj)->AddPixelFuncToPass(pixelFuncName, pass);
}

void ShaderDX12Bridge::SetVertexFuncToPass(_uint index, _uint pass)
{
    ((ShaderDX12*)raw_obj)->SetVertexFuncToPass(index, pass);
}

void ShaderDX12Bridge::SetPixelFuncToPass(_uint index, _uint pass)
{
    ((ShaderDX12*)raw_obj)->SetPixelFuncToPass(index, pass);
}

void ShaderDX12Bridge::InitRootSignature(ShaderLayout* shaderLayout)
{
    ShaderDX12* obj = (ShaderDX12*)raw_obj;
    obj->InitRootSignature(shaderLayout);
}

void ShaderDX12Bridge::InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* desc, _uint pass)
{
    ShaderDX12* obj = (ShaderDX12*)raw_obj;
    obj->InitVertexDescriptor(desc, pass);
}