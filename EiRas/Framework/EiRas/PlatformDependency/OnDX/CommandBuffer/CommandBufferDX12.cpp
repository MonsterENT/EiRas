#include "CommandBufferDX12.h"
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/Material/MaterialDX12.h>
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <Material/MaterialLayout.hpp>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceHeapDX12.h>
#include <PlatformDependency/OnDX/Mesh/MeshDX12.h>
#include <Basic/Image.hpp>

using Graphics::CommandBufferDX12;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;
using ImageSys::ImageSysBuildingList;

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

void CommandBufferDX12::BeginFrame()
{
    GET_EIRAS_DX12(deviceObj)

    cmdAllocator->Reset();
    cmdList->Reset(cmdAllocator, NULL);
    for (int i = 0; i < ImageSysBuildingList.size(); i++)
    {
        if (!ImageSysBuildingList[i]->isFinishBuild)
        {
            ImageSysBuildingList[i]->Build(cmdList);
        }
        else
        {
            ImageSysBuildingList[i]->FinishBuild();
        }
    }

#pragma region tmp
    cmdList->RSSetViewports(1, &deviceObj->viewPort);
    cmdList->RSSetScissorRects(1, &deviceObj->scissorRect);

    // Indicate that the back buffer will be used as a render target.
    cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(deviceObj->renderTargets[deviceObj->curFrameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(deviceObj->rtvHeap->GetCPUDescriptorHandleForHeapStart(), deviceObj->curFrameIndex, deviceObj->rtvDescriptorSize);
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(deviceObj->dsvHeap->GetCPUDescriptorHandleForHeapStart());
    cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

    // Record commands.
    const float clearColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
#pragma endregion
}

void CommandBufferDX12::Reset(MaterialSys::GraphicsResourceHeapDX12* heapObj)
{
    if (heapObj)
    {
        CurrentUseingHeap = heapObj;
        cmdList->SetDescriptorHeaps(1, &heapObj->heap);
    }
}

void CommandBufferDX12::Commit(bool present)
{
    GET_EIRAS_DX12(deviceObj)
        if (present)
        {
            cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(deviceObj->renderTargets[deviceObj->curFrameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
        }
    assert(SUCCEEDED(cmdList->Close()));
    ID3D12CommandList* ppCommandLists[] = { cmdList };
    deviceObj->cmdQueue->ExecuteCommandLists(1, ppCommandLists);

    if (present)
    {
        assert(SUCCEEDED(deviceObj->swapChain3->Present(1, 0)));
#pragma message("TOFIX")
        deviceObj->WaitForPreviousFrame();
    }
}

void CommandBufferDX12::DrawMesh(MeshSys::MeshDX12* mesh)
{
    cmdList->IASetVertexBuffers(0, 1, &mesh->VertexBufferView);
    cmdList->DrawInstanced(mesh->VertexCount, 1, 0, 0);
}


void CommandBufferDX12::SetMaterial(MaterialSys::MaterialDX12* mat, MaterialSys::MaterialLayout* layout)
{
    cmdList->SetGraphicsRootSignature(mat->RawShaderObj->RootSignature);
    cmdList->SetPipelineState(mat->PipelineState);

    for (int i = 0; i < layout->SlotNum; i++)
    {
        MaterialSlot* slot = layout->Slots[i];
        if (slot->SlotType == MaterialSlotType::MaterialSlotType_Table)
        {
            MaterialTable* table = (MaterialTable*)slot;
            cmdList->SetGraphicsRootDescriptorTable(table->SlotID, ((GraphicsResourceDX12*)table->Props[0]->Resource->PlatformBridge->raw_obj)->GpuHandle);
        }
        else
        {
            MaterialProp* prop = (MaterialProp*)slot;

            D3D12_GPU_VIRTUAL_ADDRESS ADDR = ((GraphicsResourceDX12*)prop->Resource->PlatformBridge->raw_obj)->Resource->GetGPUVirtualAddress();
            int rootParamIndex = prop->SlotID;

            GraphicsResourceType resType = prop->Resource->Behaviors.ResourceType;

            if (resType == GraphicsResourceType::CBV)
            {
                cmdList->SetGraphicsRootConstantBufferView(rootParamIndex, ADDR);
            }
            else if (resType == GraphicsResourceType::SRV)
            {
                cmdList->SetGraphicsRootShaderResourceView(rootParamIndex, ADDR);
            }
            else if (resType == GraphicsResourceType::UAV)
            {
                cmdList->SetGraphicsRootUnorderedAccessView(rootParamIndex, ADDR);
            }
        }
    }
}
