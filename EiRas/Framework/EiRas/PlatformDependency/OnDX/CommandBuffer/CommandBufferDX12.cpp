#include "CommandBufferDX12.h"
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/Material/MaterialDX12.h>
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <Material/MaterialLayout.hpp>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceHeapDX12.h>
#include <Mesh/Mesh.hpp>
#include <PlatformDependency/OnDX/Mesh/MeshDX12.h>
#include <Basic/Image.hpp>

using Graphics::CommandBufferDX12;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;
using namespace MeshSys;
using ImageSys::ImageSysBuildingList;

CommandBufferDX12::CommandBufferDX12(std::string Name)
{
    _CurrentRenderTexture = 0;
    GET_EIRAS_DX12(deviceObj);;
    HRESULT hr = deviceObj->device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));
    hr = deviceObj->device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, 0, IID_PPV_ARGS(&cmdList));
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
    GET_EIRAS_DX12(deviceObj);;
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

    deviceObj->_BeginFrame(cmdList);
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
    GET_EIRAS_DX12(deviceObj);;
    if (present)
    {
        deviceObj->_Present(false, cmdList);
    }
    assert(SUCCEEDED(cmdList->Close()));
    ID3D12CommandList* ppCommandLists[] = { cmdList };
    deviceObj->cmdQueue->ExecuteCommandLists(1, ppCommandLists);

    if (present)
    {
        deviceObj->_Present(true, cmdList);
    }
}

void CommandBufferDX12::SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth, float maxDepth)
{
    CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(topLeftX, topLeftY, width, height, minDepth, maxDepth);
    CD3DX12_RECT scissorRect = CD3DX12_RECT((LONG)topLeftX, (LONG)topLeftY, (LONG)topLeftX + (LONG)width, (LONG)topLeftY + (LONG)height);
    cmdList->RSSetViewports(1, &viewPort);
    cmdList->RSSetScissorRects(1, &scissorRect);
}

void CommandBufferDX12::DrawMesh(MeshSys::Mesh* mesh)
{
    cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    for (_uint i = 0; i < mesh->SubMeshCount; i++)
    {
        MeshDX12* rawMeshObj = (MeshDX12*)mesh->PlatformBridge->raw_obj;

        cmdList->IASetVertexBuffers(0, 1, &rawMeshObj->VertexBufferViews[i]);
        cmdList->IASetIndexBuffer(&rawMeshObj->IndexBufferViews[i]);
        cmdList->DrawIndexedInstanced(mesh->SubMeshes[i].IndicesCount, 1, 0, 0, 0);
    }
}


void CommandBufferDX12::SetMaterial(MaterialSys::MaterialDX12* mat, MaterialSys::MaterialLayout* layout)
{
    cmdList->SetGraphicsRootSignature(mat->RawShaderObj->RootSignature);
    cmdList->SetPipelineState(mat->PipelineState);

    GET_EIRAS_DX12(deviceObj);;
    _uint offset = deviceObj->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    for (_uint i = 0; i < layout->SlotNum; i++)
    {
        MaterialSlot* slot = layout->Slots[i];
        if (slot->SlotType == MaterialSlotType::MaterialSlotType_Table)
        {
            MaterialTable* table = (MaterialTable*)slot;
            CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(CurrentUseingHeap->heap->GetGPUDescriptorHandleForHeapStart());
            gpuHandle.Offset(table->Props[0]->_heapOffset, offset);
            cmdList->SetGraphicsRootDescriptorTable(table->SlotID, gpuHandle);
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

void CommandBufferDX12::SetRenderTexture(void* rawRenderTexture)
{
    if (rawRenderTexture == 0 && _CurrentRenderTexture == 0)
    {
        return;
    }
#pragma message("TO DO")
    if (_CurrentRenderTexture)
    {
        cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_CurrentRenderTexture->ColorBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    }
    else
    {
        GET_EIRAS_DX12(deviceObj);;
        deviceObj->_SetBackBufferState(false, cmdList);
    }
    _CurrentRenderTexture = NULL;

    if (rawRenderTexture)
    {
        _CurrentRenderTexture = (Graphics::RenderTextureDX12*)rawRenderTexture;
        cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_CurrentRenderTexture->ColorBuffer, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET));
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(_CurrentRenderTexture->RtvHeap->GetCPUDescriptorHandleForHeapStart());

        const float clearColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        if (_CurrentRenderTexture->DsvHeap)
        {
            CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(_CurrentRenderTexture->DsvHeap->GetCPUDescriptorHandleForHeapStart());
            cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);
            cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
            cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
            cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
        }
        else
        {
            cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, NULL);
            cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
        }
    }
    else
    {
        GET_EIRAS_DX12(deviceObj);;
        deviceObj->_SetBackBufferState(true, cmdList);
    }
}


void CommandBufferDX12::GetCurrentRenderTextureInfo(_uint* numRT, DXGI_FORMAT* rtFormats, DXGI_FORMAT* depthFormat)
{
    if (_CurrentRenderTexture == NULL)
    {
        *numRT = 1;
        rtFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        *depthFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    }
    else
    {
        *numRT = 1;
        rtFormats[0] = (DXGI_FORMAT)_CurrentRenderTexture->ColorFormat;
        *depthFormat = (DXGI_FORMAT)_CurrentRenderTexture->DepthStencilFormat;
    }
}
