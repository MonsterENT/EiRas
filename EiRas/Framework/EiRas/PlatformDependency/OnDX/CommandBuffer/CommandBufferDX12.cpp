#include "CommandBufferDX12.h"
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <Material/Material.hpp>
#include <PlatformDependency/OnDX/Material/MaterialDX12.h>
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <Material/MaterialLayout.hpp>
#include <Material/ShaderLayout.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDescriptorHeapDX12.h>
#include <Mesh/Mesh.hpp>
#include <PlatformDependency/OnDX/Mesh/MeshDX12.h>
#include <Basic/Image.hpp>
#include <Graphics/RenderData.hpp>
#include <PlatformDependency/OnDX/Shader/ShaderLayoutDX12.hpp>
#include <PlatformDependency/OnDX/GPCompute/ComputeKernelDX12.hpp>

#include <PlatformDependency/OnDX/ResourceHeapManager/ResourceDescriptorHeapManager.hpp>

using namespace GPCompute;
using namespace Graphics;
using GraphicsAPI::EiRasDX12;
using namespace MaterialSys;
using namespace MeshSys;
using ImageSys::ImageSysBuildingList;

CommandBufferDX12::CommandBufferDX12(std::string Name)
{
    EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsActivedCmdBuffer = this;
    _CurrentRenderTexture = 0;
    GET_EIRAS_DX12(deviceObj);;
    HRESULT hr = deviceObj->device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));
    hr = deviceObj->device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, 0, IID_PPV_ARGS(&cmdList));

    wchar_t tmp_ws[16];
    swprintf(tmp_ws, 16, L"%hs", Name.c_str());
    cmdList->SetName(tmp_ws);
    CurrentUseingHeap = NULL;
    _CurrentWorldMatCB = 0;
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

    std::vector<ImageSys::Image*>::iterator it = ImageSysBuildingList.begin();
    while (it != ImageSysBuildingList.end())
    {
        if (!(*it)->isFinishBuild)
        {
            (*it)->Build(cmdList);
            it++;
        }
        else
        {
            (*it)->FinishBuild();
            it = ImageSysBuildingList.erase(it);
        }
    }

    deviceObj->_BeginFrame(cmdList);
}

void CommandBufferDX12::Reset()
{
    EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsActivedCmdBuffer = this;
    CurrentUseingHeap = (MaterialSys::GraphicsResourceDescriptorHeapDX12*)MaterialSys::ResourceDescriptorHeapManager::ShareInstance()->HeapPool[0];
    CurrentUseingHeap->FillHeap();
    cmdList->SetDescriptorHeaps(1, &CurrentUseingHeap->heap);
}

void CommandBufferDX12::Commit(bool present)
{
    if (EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsActivedCmdBuffer == this)
    {
        EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsActivedCmdBuffer = NULL;
    }
    GET_EIRAS_DX12(deviceObj);;
    if (present)
    {
        deviceObj->_Present(false, cmdList);
    }

    HRESULT tHR = cmdList->Close();
    assert(SUCCEEDED(tHR));
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

void CommandBufferDX12::SetTransformGraphics(MaterialSys::GraphicsResource* res)
{
    _CurrentWorldMatCB = res;
}

void CommandBufferDX12::DrawMesh(MeshSys::Mesh* mesh)
{
    cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    MeshDX12* rawMeshObj = (MeshDX12*)mesh->PlatformBridge->raw_obj;
    cmdList->IASetVertexBuffers(0, 1, &rawMeshObj->VertexBufferViews[0]);
    cmdList->IASetIndexBuffer(&rawMeshObj->IndexBufferViews[0]);
    for (_uint i = 0; i < mesh->SubMeshCount; i++)
    {
        cmdList->DrawIndexedInstanced(mesh->SubMeshes[i].IndexCount, 1, mesh->SubMeshes[i].IndexBufferStartIdx, 0, 0);
    }
}

void CommandBufferDX12::DrawRenderData(RenderData* render)
{
    if (render->_MaterialList.size() <= 0)
    {
        return;
    }
    cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    for (int meshIdx = 0; meshIdx < render->m_Meshes.size(); meshIdx++)
    {
        Mesh* meshObj = render->m_Meshes[meshIdx];
        MeshDX12* rawMeshObj = (MeshDX12*)meshObj->PlatformBridge->raw_obj;

        cmdList->IASetVertexBuffers(0, 1, &rawMeshObj->VertexBufferViews[0]);
        cmdList->IASetIndexBuffer(&rawMeshObj->IndexBufferViews[0]);

        for (_uint i = 0; i < meshObj->SubMeshCount; i++)
        {
            RenderMaterialPassData* mpd = 0;
            if (i >= render->_MaterialList.size())
            {
                mpd = &render->_MaterialList[0];
            }
            else
            {
                mpd = &render->_MaterialList[i];
            }
            if (mpd == 0)
            {
                continue;
            }
            Material* mat = mpd->m_Material;
            mat->FinishStateChange(mpd->Pass);
            SetMaterial((MaterialDX12*)mat->PlatformBridge->raw_obj, mat->materialLayout, mpd->Pass);
            cmdList->DrawIndexedInstanced(meshObj->SubMeshes[i].IndexCount, 1, meshObj->SubMeshes[i].IndexBufferStartIdx, 0, 0);
        }
    }
}

void SetComputeRootBufferView(ID3D12GraphicsCommandList* cmdList, MaterialSlot* slot, GraphicsResource* rootResource)
{
    GraphicsResourceType resType = rootResource->Behaviors.ResourceType;
    D3D12_GPU_VIRTUAL_ADDRESS ADDR = ((GraphicsResourceDX12*)rootResource->PlatformBridge->raw_obj)->Resource->GetGPUVirtualAddress();

    if (resType == GraphicsResourceType::CBV)
    {
        cmdList->SetComputeRootConstantBufferView(slot->SlotID, ADDR);
    }
    else if (resType == GraphicsResourceType::SRV)
    {
        cmdList->SetComputeRootShaderResourceView(slot->SlotID, ADDR);
    }
    else if (resType == GraphicsResourceType::UAV)
    {
        cmdList->SetComputeRootUnorderedAccessView(slot->SlotID, ADDR);
    }
}

void CommandBufferDX12::DispatchComputeKernel(GPCompute::ComputeKernelDX12* kernel, Math::int3 groupCount)
{
    cmdList->SetComputeRootSignature(kernel->GetRootSignature());
    cmdList->SetPipelineState(kernel->_ComputePipelineStateObject);
    GET_EIRAS_DX12(deviceObj);
    _uint offset = deviceObj->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    for (_uint i = 0; i < kernel->ResLayout->SlotNum; i++)
    {
        MaterialSlot* slot = kernel->ResLayout->Slots[i];
        if (slot->SlotType == MaterialSlotType::MaterialSlotType_Table)
        {
            MaterialTable* table = (MaterialTable*)slot;
            CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(CurrentUseingHeap->heap->GetGPUDescriptorHandleForHeapStart());
            gpuHandle.Offset(table->Props[0]->_heapOffset, offset);
            cmdList->SetComputeRootDescriptorTable(table->SlotID, gpuHandle);
        }
        else if (slot->SlotType == MaterialSlotType::MaterialSlotType_Prop)
        {
            MaterialProp* prop = (MaterialProp*)slot;
            if (prop->Resource == 0)
            {
                continue;
            }
            SetComputeRootBufferView(cmdList, slot, prop->Resource);
        }
        else if (slot->SlotType == MaterialSlotType::MaterialSlotType_Builtin_ViewProj)
        {
            SetComputeRootBufferView(cmdList, slot, EiRasGlobal::EiRasGlobalManager::SharedInstance()->CBViewProjRawRes);
        }
        else if (slot->SlotType == MaterialSlotType::MaterialSlotType_Ref_WorldMatrix && _CurrentWorldMatCB != 0)
        {
            SetComputeRootBufferView(cmdList, slot, _CurrentWorldMatCB);
        }
    }

    cmdList->Dispatch(groupCount.x, groupCount.y, groupCount.z);
}

void CommandBufferDX12::SetGraphicsRootBufferView(MaterialSlot* slot, GraphicsResource* ori, GraphicsResource* rootResource)
{
    GraphicsResourceType resType;
    if (ori != NULL)
    {
        resType = ori->Behaviors.ResourceType;
    }
    else if(rootResource != NULL)
    {
        resType = rootResource->Behaviors.ResourceType;
    }
    else
    {
        return;
    }
    GraphicsResourceDX12* rawObj = (GraphicsResourceDX12*)rootResource->PlatformBridge->raw_obj;
    D3D12_GPU_VIRTUAL_ADDRESS ADDR = rawObj->ResADDR;

    if (resType == GraphicsResourceType::CBV)
    {
        //rawObj->ChangeState(1, 0, 0, 0, cmdList);
        cmdList->SetGraphicsRootConstantBufferView(slot->SlotID, ADDR);
    }
    else if (resType == GraphicsResourceType::SRV)
    {
        //rawObj->ChangeState(0, 1, 0, 0, cmdList);
        cmdList->SetGraphicsRootShaderResourceView(slot->SlotID, ADDR);
    }
    else if (resType == GraphicsResourceType::UAV)
    {
        //rawObj->ChangeState(0, 0, 1, 0, cmdList);
        cmdList->SetGraphicsRootUnorderedAccessView(slot->SlotID, ADDR);
    }
}

void CommandBufferDX12::SetMaterial(MaterialSys::MaterialDX12* mat, MaterialSys::MaterialLayout* layout, _uint pass)
{
    cmdList->SetGraphicsRootSignature(mat->RawShaderObj->Layout->m_RootSignature);
    cmdList->SetPipelineState(mat->PassedPipelineState[pass]);

    GET_EIRAS_DX12(deviceObj);
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
        else if(slot->SlotType == MaterialSlotType::MaterialSlotType_Prop)
        {
            MaterialProp* prop = (MaterialProp*)slot;
            if (prop->Resource == 0)
            {
                continue;
            }

            SetGraphicsRootBufferView(slot, prop->_oriResource,  prop->Resource);
        }
        else if (slot->SlotType == MaterialSlotType::MaterialSlotType_Builtin_ViewProj)
        {
            SetGraphicsRootBufferView(slot, NULL, EiRasGlobal::EiRasGlobalManager::SharedInstance()->CBViewProjRawRes);
        }
        else if (slot->SlotType == MaterialSlotType::MaterialSlotType_Ref_WorldMatrix && _CurrentWorldMatCB != 0)
        {
            SetGraphicsRootBufferView(slot, NULL, _CurrentWorldMatCB);
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
        _CurrentRenderTexture->ChangeState(true, cmdList);
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
        _CurrentRenderTexture->ChangeState(false, cmdList);
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(_CurrentRenderTexture->RtvHeap->GetCPUDescriptorHandleForHeapStart());

        const float clearColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        if (_CurrentRenderTexture->DsvHeap)
        {
            CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(_CurrentRenderTexture->DsvHeap->GetCPUDescriptorHandleForHeapStart());
            cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);
            cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
            cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
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
