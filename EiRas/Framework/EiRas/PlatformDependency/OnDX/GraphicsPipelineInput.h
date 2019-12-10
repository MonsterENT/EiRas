#pragma once

#include <d3d12.h>
#include <DirectXMath.h>

using DirectX::XMFLOAT4;
using DirectX::XMFLOAT3;
using DirectX::XMFLOAT2;

namespace Graphics
{
    const D3D12_INPUT_ELEMENT_DESC PipelineInput[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    struct VertexDefault
    {
        XMFLOAT3 POSITION;
        XMFLOAT2 TEXCOORD;
        XMFLOAT4 COLOR;
        XMFLOAT3 NORMAL;
    };
};