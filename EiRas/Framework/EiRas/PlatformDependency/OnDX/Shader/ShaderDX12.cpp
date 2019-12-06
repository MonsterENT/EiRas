#include "ShaderDX12.h"
#include <PlatformDependency/OnDX/DX12Utils.h>
#include <Material/ShaderLayout.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>

using MaterialSys::ShaderDX12;
using MaterialSys::ShaderLayout;
using MaterialSys::ShaderSlot;
using MaterialSys::ShaderProp;
using MaterialSys::ShaderTable;
using GraphicsAPI::EiRasDX12;

ID3D12RootSignature* createRootSig(ShaderLayout* shaderLayout);

ShaderDX12::ShaderDX12(LPCSTR fileName, LPCSTR vertexFuncName, LPCSTR pixelFuncName)
{
    this->VertexFunc = 0;
    this->PixelFunc = 0;
    DX12Utils::g_compileShader(fileName, vertexFuncName, "vs_5_1", this->VertexFunc);
    DX12Utils::g_compileShader(fileName, vertexFuncName, "ps_5_1", this->PixelFunc);
    RootSignature = 0;
}       

void ShaderDX12::InitRootSignature(ShaderLayout* shaderLayout)
{
    this->RootSignature = createRootSig(shaderLayout);
}

ID3D12RootSignature* createRootSig(ShaderLayout* shaderLayout)
{
    UINT _BASE_CB_REGISTER = 0;
    ID3D12RootSignature* rootSig = nullptr;
    CD3DX12_ROOT_PARAMETER1* rootParameters = new CD3DX12_ROOT_PARAMETER1[shaderLayout->SlotNum];
    for (int i = 0; i < shaderLayout->SlotNum; i++)
    {
        UINT _BASE_SPACE = 0;
        ShaderSlot* slot = shaderLayout->Slots[i];
        if (slot->SlotType == MaterialSys::ShaderSlotType::ShaderSlotType_Prop)
        {
            ShaderProp* prop = (ShaderProp*)slot;
            rootParameters[i].InitAsConstantBufferView(_BASE_CB_REGISTER++, _BASE_SPACE);
        }
        else if (slot->SlotType == MaterialSys::ShaderSlotType::ShaderSlotType_Table)
        {
            ShaderTable* table = (ShaderTable*)slot;
            CD3DX12_DESCRIPTOR_RANGE1* ranges = new CD3DX12_DESCRIPTOR_RANGE1[table->PropNum];
            for (int j = 0; j < table->PropNum; j++)
            {
                ranges[j].Init((D3D12_DESCRIPTOR_RANGE_TYPE)table->Props[j]->PropType, 1, _BASE_CB_REGISTER++, _BASE_SPACE);
            }
            rootParameters[i].InitAsDescriptorTable(table->PropNum, ranges);
            delete[] ranges;
        }
    }

    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init_1_1(shaderLayout->SlotNum, rootParameters, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;
    D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_1, &signature, &error);
    GET_EIRAS_DX12(deviceObj)
    deviceObj->device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSig));
    delete[] rootParameters;
    return rootSig;
}