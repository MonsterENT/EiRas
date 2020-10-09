#include "ShaderLayoutDX12.hpp"
#include <PlatformDependency/OnDX/DX12Utils.h>
#include <Material/ShaderLayout.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
using namespace MaterialSys;
using GraphicsAPI::EiRasDX12;

ID3D12RootSignature* createRootSig(ShaderLayout* shaderLayout);

ShaderLayoutDX12::ShaderLayoutDX12()
{
    m_RootSignature = NULL;
}

ShaderLayoutDX12::~ShaderLayoutDX12()
{
    if (m_RootSignature != NULL)
    {
        m_RootSignature->Release();
    }
}

void ShaderLayoutDX12::Build(ShaderLayout* layout)
{
    if (m_RootSignature != NULL)
    {
        m_RootSignature->Release();
    }
    m_RootSignature = createRootSig(layout);
    assert(m_RootSignature != NULL);
}

ID3D12RootSignature* createRootSig(ShaderLayout* shaderLayout)
{
#pragma message("TOFIX")
    CD3DX12_DESCRIPTOR_RANGE1 ranges[100];
    _uint rangeOffset = 0;

    _uint slotNum = shaderLayout->SlotNum;

    UINT _BASE_CB_REGISTER = 0;
    UINT _BASE_SR_REGISTER = 0;
    UINT _BASE_UA_REGISTER = 0;
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
            else if (prop->PropType == GraphicsResourceType::UAV)
            {
                rootParameters[i].InitAsUnorderedAccessView(_BASE_UA_REGISTER++, _BASE_SPACE);
            }
            else
            {
#pragma message("TOFIX")
            }
        }
        else if (slot->SlotType == MaterialSys::ShaderSlotType::ShaderSlotType_Builtin_ViewProj ||
            slot->SlotType == MaterialSys::ShaderSlotType::ShaderSlotType_Ref_WorldMatrix)
        {
            rootParameters[i].InitAsConstantBufferView(_BASE_CB_REGISTER++, _BASE_SPACE);
        }
        else if (slot->SlotType == MaterialSys::ShaderSlotType::ShaderSlotType_Table)
        {
            ShaderTable* table = (ShaderTable*)slot;

            _uint rangeNum = table->Ranges.size();
            for (_uint j = 0; j < rangeNum; j++)
            {
                ShaderPropRange* range = &table->Ranges[j];
                if (range->PropType == GraphicsResourceType::SRV)
                {
                    ranges[j + rangeOffset].Init((D3D12_DESCRIPTOR_RANGE_TYPE)range->PropType, range->PropNum, _BASE_SR_REGISTER, _BASE_SPACE);
                    _BASE_SR_REGISTER += range->PropNum;
                }
                else if (range->PropType == GraphicsResourceType::CBV)
                {
                    ranges[j + rangeOffset].Init((D3D12_DESCRIPTOR_RANGE_TYPE)range->PropType, range->PropNum, _BASE_CB_REGISTER, _BASE_SPACE);
                    _BASE_CB_REGISTER += range->PropNum;

                }
            }
            rootParameters[i].InitAsDescriptorTable(rangeNum, ranges + rangeOffset, (D3D12_SHADER_VISIBILITY)MaterialSys::GraphicsResourceVisibilityToDX12(table->Ranges[0].Visibility));
            rangeOffset += rangeNum;
        }
    }

    CD3DX12_STATIC_SAMPLER_DESC samplerDesc(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR);

    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init_1_1(slotNum, rootParameters, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;
    D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_1, &signature, &error);
    GET_EIRAS_DX12(deviceObj);
    deviceObj->device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSig));
    delete[] rootParameters;
    return rootSig;
}
