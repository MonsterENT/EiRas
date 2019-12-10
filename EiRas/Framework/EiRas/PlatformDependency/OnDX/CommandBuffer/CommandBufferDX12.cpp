#include "CommandBufferDX12.h"
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/Material/MaterialDX12.h>
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <Material/MaterialLayout.hpp>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceHeapDX12.h>

using Graphics::CommandBufferDX12;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;

CommandBufferDX12::CommandBufferDX12(std::string Name)
{
    GET_EIRAS_DX12(deviceObj)
    deviceObj->device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));
    deviceObj->device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, 0, IID_PPV_ARGS(&cmdList));
    wchar_t tmp_ws[16];
    swprintf(tmp_ws, 16, L"%hs", Name.c_str());
    cmdList->SetName(tmp_ws);
    CurrentUseingHeap = NULL;
}

CommandBufferDX12::~CommandBufferDX12()
{
    cmdList->Release();
    cmdAllocator->Release();
}

void CommandBufferDX12::BeginFrame(MaterialSys::GraphicsResourceHeapDX12* heapObj)
{
    cmdAllocator->Reset();
    cmdList->Reset(cmdAllocator, NULL);
    CurrentUseingHeap = heapObj;
    cmdList->SetDescriptorHeaps(1, &heapObj->heap);
}

void CommandBufferDX12::Commit()
{
    GET_EIRAS_DX12(deviceObj)
    ID3D12CommandList* ppCommandLists[] = { cmdList };
    deviceObj->cmdQueue->ExecuteCommandLists(1, ppCommandLists);
}

void CommandBufferDX12::Present()
{
    GET_EIRAS_DX12(deviceObj)
    deviceObj->swapChain3->Present(1, 0);
#pragma message("TOFIX")
    deviceObj->WaitForPreviousFrame();
}

void CommandBufferDX12::SetPipelineState(MaterialSys::MaterialDX12* mat, std::vector<MaterialSys::MaterialProp*>* props, std::vector<MaterialSys::MaterialTable*>* tables)
{
    cmdList->SetGraphicsRootSignature(mat->RawShaderObj->RootSignature);
    cmdList->SetPipelineState(mat->PipelineState);

    if (CurrentUseingHeap)
    {
        CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(CurrentUseingHeap->heap->GetGPUDescriptorHandleForHeapStart());
        for (int i = 0; i < tables->size(); i++)
        {
            cmdList->SetGraphicsRootDescriptorTable((*tables)[i]->SlotID, gpuHandle);
            gpuHandle.Offset((*tables)[i]->PropNum, CurrentUseingHeap->Offset);
        }
    }

    for (int i = 0; i < props->size(); i++)
    {
        MaterialProp* prop = (*props)[i];

        D3D12_GPU_VIRTUAL_ADDRESS ADDR = ((GraphicsResourceDX12*)prop->Resource->PlatformBridge->raw_obj)->Resource->GetGPUVirtualAddress();
        int rootParamIndex = prop->SlotID;
        if (prop->PropType == GraphicsResourceType::CBV)
        {
            cmdList->SetGraphicsRootConstantBufferView(rootParamIndex, ADDR);
        }
        else if (prop->PropType == GraphicsResourceType::SRV)
        {
            cmdList->SetGraphicsRootShaderResourceView(rootParamIndex, ADDR);
        }
        else if (prop->PropType == GraphicsResourceType::UAV)
        {
            cmdList->SetGraphicsRootUnorderedAccessView(rootParamIndex, ADDR);
        }
    }
}
