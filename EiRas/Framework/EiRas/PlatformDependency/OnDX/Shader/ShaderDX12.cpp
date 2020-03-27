#include "ShaderDX12.h"
#include <PlatformDependency/OnDX/DX12Utils.h>
#include <Material/ShaderLayout.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <Graphics/GraphicsVertexDescriptor.hpp>
#include <Material/GraphicsResource.hpp>
#include <Graphics/GraphicsRenderState.hpp>

using namespace MaterialSys;
using namespace Graphics;
using GraphicsAPI::EiRasDX12;

ID3D12RootSignature* createRootSig(ShaderLayout* shaderLayout);

ShaderDX12::ShaderDX12(LPCSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName)
{
    this->VertexFunc = 0;
    this->PixelFunc = 0;
    DX12Utils::g_compileShader(fileName, vertexFuncName, "vs_5_1", this->VertexFunc);
    DX12Utils::g_compileShader(fileName, pixelFuncName, "ps_5_1", this->PixelFunc);
    RootSignature = 0;
    VertexDescriptor = 0;
    VertexAttributesCount = 0;
}       

void ShaderDX12::InitRootSignature(ShaderLayout* shaderLayout)
{
    this->RootSignature = createRootSig(shaderLayout);
}

void ShaderDX12::InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* desc)
{
    if (desc->_AttributeIndex < 1)
    {
        return;
    }
    VertexAttributesCount = desc->_AttributeIndex;
    VertexDescriptor = new D3D12_INPUT_ELEMENT_DESC[VertexAttributesCount];
    for (_uint i = 0; i < desc->_AttributeIndex; i++)
    {
        Graphics::GraphiceVertexAttribute& att = desc->Attributes[i];
        VertexDescriptor[i].SemanticName = att.SemanticName.c_str();
        VertexDescriptor[i].SemanticIndex = 0;
        VertexDescriptor[i].Format = (DXGI_FORMAT)Graphics::GraphicsVertexAttributeToDX12Format(att.AttributeFormat);
        VertexDescriptor[i].InputSlot = att.BufferIndex;
        VertexDescriptor[i].AlignedByteOffset = att.Offset;
        VertexDescriptor[i].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
        VertexDescriptor[i].InstanceDataStepRate = 0;
    }
}

ID3D12PipelineState* ShaderDX12::_GetPSO(Graphics::GraphicsRenderState* renderState)
{
    _uint hashCode = renderState->GetHashCode();
    PSOCache_MAP::iterator cachedObj = _PSOCache.find(hashCode);
    if (cachedObj != _PSOCache.end())
    {
        return cachedObj->second;
    }
    else
    {
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout = { this->VertexDescriptor, this->VertexAttributesCount };
        psoDesc.pRootSignature = this->RootSignature;
        psoDesc.VS = CD3DX12_SHADER_BYTECODE(this->VertexFunc);
        psoDesc.PS = CD3DX12_SHADER_BYTECODE(this->PixelFunc);

        CD3DX12_RASTERIZER_DESC rasterizerStateDesc(D3D12_DEFAULT);
        rasterizerStateDesc.CullMode = (D3D12_CULL_MODE)(4 - (int)renderState->_CullMode);
        rasterizerStateDesc.FillMode = (D3D12_FILL_MODE)renderState->_FillMode;
        psoDesc.RasterizerState = rasterizerStateDesc;

        D3D12_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        D3D12_RENDER_TARGET_BLEND_DESC rt_blend_desc;
        rt_blend_desc.LogicOpEnable = false;
        rt_blend_desc.LogicOp = D3D12_LOGIC_OP_NOOP;
        rt_blend_desc.BlendEnable = ((renderState->_BlendSrcRGBFactor == BlendFactor::BlendRGBFactorOne) && (renderState->_BlendDstRGBFactor == BlendFactor::BlendRGBFactorZero) &&
            (renderState->_BlendSrcAlphaFactor == BlendFactor::BlendRGBFactorOne) && (renderState->_BlendDstAlphaFactor == BlendFactor::BlendRGBFactorZero)) ? false : true;
        rt_blend_desc.BlendOp = (D3D12_BLEND_OP)renderState->_BlendOp_RGB;
        rt_blend_desc.BlendOpAlpha = (D3D12_BLEND_OP)renderState->_BlendOp_ALPHA;
        rt_blend_desc.SrcBlend = (D3D12_BLEND)Graphics::BlendFactorConvertDX12(renderState->_BlendSrcRGBFactor);
        rt_blend_desc.DestBlend = (D3D12_BLEND)Graphics::BlendFactorConvertDX12(renderState->_BlendDstRGBFactor);
        rt_blend_desc.SrcBlendAlpha = (D3D12_BLEND)Graphics::BlendFactorConvertDX12(renderState->_BlendSrcAlphaFactor);
        rt_blend_desc.DestBlendAlpha = (D3D12_BLEND)Graphics::BlendFactorConvertDX12(renderState->_BlendDstAlphaFactor);
        rt_blend_desc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
        for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
            blendDesc.RenderTarget[i] = rt_blend_desc;
        psoDesc.BlendState = blendDesc;

        psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
        psoDesc.DepthStencilState.DepthEnable = true;

        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
        psoDesc.SampleDesc.Count = 1;
        psoDesc.SampleDesc.Quality = 0;

        ID3D12PipelineState* pso = 0;
        GET_EIRAS_DX12(deviceObj)
            deviceObj->device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pso));

        if (pso)
        {
            _PSOCache.insert(PSOCache_PAIR(hashCode, pso));
        }
        return pso;
    }
}

ID3D12RootSignature* createRootSig(ShaderLayout* shaderLayout)
{
    _uint slotNum = shaderLayout->SlotNum;

    UINT _BASE_CB_REGISTER = 0;
    UINT _BASE_SR_REGISTER = 0;
    ID3D12RootSignature* rootSig = nullptr;
    CD3DX12_ROOT_PARAMETER1* rootParameters = new CD3DX12_ROOT_PARAMETER1[slotNum];
    for (_uint i = 0; i < slotNum; i++)
    {
        UINT _BASE_SPACE = 0;
        ShaderSlot* slot = shaderLayout->Slots[i];
        if (slot->SlotType == MaterialSys::ShaderSlotType::ShaderSlotType_Prop)
        {
            ShaderProp* prop = (ShaderProp*)slot;
            if (prop->PropType == GraphicsResourceType::CBV)
            {
                rootParameters[i].InitAsConstantBufferView(_BASE_CB_REGISTER++, _BASE_SPACE);
            }
            else if (prop->PropType == GraphicsResourceType::SRV)
            {
                rootParameters[i].InitAsShaderResourceView(_BASE_SR_REGISTER++, _BASE_SPACE);
            }
            else
            {
#pragma message("TOFIX")
            }
        }
        else if (slot->SlotType == MaterialSys::ShaderSlotType::ShaderSlotType_Table)
        {
            ShaderTable* table = (ShaderTable*)slot;
            
            _uint rangeNum = table->Ranges.size();

#pragma message("TOFIX")
            CD3DX12_DESCRIPTOR_RANGE1 ranges[100];
            for (_uint j = 0; j < rangeNum; j++)
            {
                ShaderPropRange* range = &table->Ranges[j];
                if (range->PropType == GraphicsResourceType::SRV)
                {
                    ranges[j].Init((D3D12_DESCRIPTOR_RANGE_TYPE)range->PropType, range->PropNum, _BASE_SR_REGISTER, _BASE_SPACE);
                    _BASE_SR_REGISTER += range->PropNum;
                }
                else if (range->PropType == GraphicsResourceType::CBV)
                {
                    ranges[j].Init((D3D12_DESCRIPTOR_RANGE_TYPE)range->PropType, range->PropNum, _BASE_CB_REGISTER, _BASE_SPACE);
                    _BASE_CB_REGISTER += range->PropNum;
                }
            }
            rootParameters[i].InitAsDescriptorTable(rangeNum, ranges, (D3D12_SHADER_VISIBILITY)MaterialSys::GraphicsResourceVisibilityToDX12(table->Ranges[0].Visibility));
        }
    }

    CD3DX12_STATIC_SAMPLER_DESC samplerDesc(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR);

    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init_1_1(slotNum, rootParameters, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;
    D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_1, &signature, &error);
    GET_EIRAS_DX12(deviceObj)
    deviceObj->device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSig));

    delete[] rootParameters;
    return rootSig;
}
