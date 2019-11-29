#include "ShaderDX12Bridge.h"
#include "ShaderDX12.h"
using MaterialSys::ShaderDX12Bridge;

ShaderDX12Bridge::ShaderDX12Bridge(LPCWSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName)
{
    raw_obj = new ShaderDX12(fileName, vertexFuncName, pixelFuncName);
}