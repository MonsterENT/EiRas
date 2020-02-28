#pragma once
#include <string>
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#pragma comment (lib, "D3DCompiler.lib")

namespace DX12Utils
{
    static inline void g_getAssetsPath(_Out_writes_(pathSize) CHAR* path, UINT pathSize)
    {
        if (path == nullptr)
        {
            return;
        }

        DWORD size = GetModuleFileNameA(nullptr, path, pathSize);
        if (size == 0 || size == pathSize)
        {
            return;
        }

        char* lastSlash = strrchr(path, L'\\');
        if (lastSlash)
        {
            *(lastSlash + 1) = L'\0';
        }
    }

    static bool g_compileShader(LPCSTR fileName, LPCSTR fnName, LPCSTR target, ID3DBlob*& shader)
    {
#pragma message("TOFIX")
        CHAR assetsPath[128];
        g_getAssetsPath(assetsPath, _countof(assetsPath));
        std::string m_assetsPath;
        m_assetsPath = assetsPath;
        m_assetsPath += fileName;

        wchar_t tmp_ws[128];
        swprintf(tmp_ws, 128, L"%hs", m_assetsPath.c_str());
        return SUCCEEDED(D3DCompileFromFile(tmp_ws, 0, 0, fnName, target, 0, 0, &shader, 0));
    }

    static HRESULT g_createPSO(ID3D12Device* device, MaterialSys::ShaderDX12* shaderObj, ID3D12PipelineState*& pso)
    {
        CD3DX12_RASTERIZER_DESC rasterizerStateDesc(D3D12_DEFAULT);
        rasterizerStateDesc.CullMode = D3D12_CULL_MODE_NONE;

        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout = { shaderObj->VertexDescriptor, shaderObj->VertexAttributesCount };
        psoDesc.pRootSignature = shaderObj->RootSignature;
        psoDesc.VS = CD3DX12_SHADER_BYTECODE(shaderObj->VertexFunc);
        psoDesc.PS = CD3DX12_SHADER_BYTECODE(shaderObj->PixelFunc);
        psoDesc.RasterizerState = rasterizerStateDesc;
        psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState.DepthEnable = true;
        psoDesc.DepthStencilState.StencilEnable = true;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
        psoDesc.SampleDesc.Count = 1;
        psoDesc.SampleDesc.Quality = 0;
        return device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pso));
    }
}