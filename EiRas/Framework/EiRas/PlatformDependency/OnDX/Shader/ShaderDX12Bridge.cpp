#include "ShaderDX12Bridge.h"
#include "ShaderDX12.h"
#include <PlatformDependency/OnDX/Shader/ShaderLayout.h>

using MaterialSys::ShaderLayout;
using MaterialSys::ShaderDX12Bridge;

ShaderDX12Bridge::ShaderDX12Bridge(LPCSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName)
{
    raw_obj = new ShaderDX12(fileName, vertexFuncName, pixelFuncName);
}

void ShaderDX12Bridge::InitRootSignature(ShaderLayout* shaderLayout)
{
    ShaderDX12* obj = (ShaderDX12*)raw_obj;
    obj->InitRootSignature(shaderLayout);
}