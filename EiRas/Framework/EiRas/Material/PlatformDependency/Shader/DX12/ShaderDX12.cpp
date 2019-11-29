#include "ShaderDX12.h"
#include <OnDX/DX12Utils.h>

using MaterialSys::ShaderDX12;

ShaderDX12::ShaderDX12(LPCWSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName)
{
    this->vertexFunc = 0;
    this->pixelFunc = 0;
    DX12Utils::g_compileShader(fileName, vertexFuncName, "vs_5_1", this->vertexFunc);
    DX12Utils::g_compileShader(fileName, vertexFuncName, "ps_5_1", this->pixelFunc);
}       