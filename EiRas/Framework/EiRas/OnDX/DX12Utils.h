#pragma once
#include <string>
#include <GraphicsAPI/PlatformDependency/DX12/EiRasDX12.h>
#pragma comment (lib, "D3DCompiler.lib")

namespace DX12Utils
{

    static inline void g_getAssetsPath(_Out_writes_(pathSize) WCHAR* path, UINT pathSize)
    {
        if (path == nullptr)
        {
            return;
        }

        DWORD size = GetModuleFileName(nullptr, path, pathSize);
        if (size == 0 || size == pathSize)
        {
            return;
        }

        WCHAR* lastSlash = wcsrchr(path, L'\\');
        if (lastSlash)
        {
            *(lastSlash + 1) = L'\0';
        }
    }

    static bool g_compileShader(LPCWSTR fileName, LPCSTR fnName, LPCSTR target, ID3DBlob*& shader)
    {
#pragma warning TOFIX
        WCHAR assetsPath[512];
        g_getAssetsPath(assetsPath, _countof(assetsPath));
        std::wstring m_assetsPath;
        m_assetsPath = assetsPath;
        m_assetsPath += fileName;
        //LPCSTR target = "ps_5_1";
        //if (VS)
        //{
            //target = "vs_5_1";
        //}
        return SUCCEEDED(D3DCompileFromFile(m_assetsPath.c_str(), 0, 0, fnName, target, 0, 0, &shader, 0));
    }

    //static bool g_createPSO(ID3DBlob* VS, ID3DBlob* PS, ID3D12PipelineState*& pso, ID3D12RootSignature* rootSignature)
    //{
    //    CD3DX12_RASTERIZER_DESC rasterizerStateDesc(D3D12_DEFAULT);
    //    rasterizerStateDesc.CullMode = D3D12_CULL_MODE_NONE;

    //    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    //    psoDesc.InputLayout = { EiRasConst_dx12::c_defaultInputDesc, _countof(EiRasConst_dx12::c_defaultInputDesc) };
    //    psoDesc.pRootSignature = rootSignature;
    //    psoDesc.VS = CD3DX12_SHADER_BYTECODE(VS);
    //    psoDesc.PS = CD3DX12_SHADER_BYTECODE(PS);
    //    psoDesc.RasterizerState = rasterizerStateDesc;
    //    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    //    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    //    //psoDesc.DepthStencilState.DepthEnable = false;
    //    //psoDesc.DepthStencilState.StencilEnable = false;
    //    psoDesc.SampleMask = UINT_MAX;
    //    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    //    psoDesc.NumRenderTargets = 1;
    //    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    //    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    //    psoDesc.SampleDesc.Count = 1;
    //    return G_DEVICE->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pso));
    //}
}