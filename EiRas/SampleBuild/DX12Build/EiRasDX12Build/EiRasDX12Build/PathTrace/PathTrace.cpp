#include "PathTrace.hpp"
#include "GraphicsData.hpp"

#include <GraphicsAPI/EiRas.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Material/Shader.hpp>
#include <Material/ShaderLayout.h>
#include <GPCompute/ComputeKernel.hpp>
#include <FileSys/FileManager.hpp>
#include <Material/GraphicsResource.hpp>

#include <PlatformDependency/OnDX/ResourceHeapManager/ResourceDescriptorHeapManager.hpp>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>
#include <PlatformDependency/OnDX/CommandBuffer/CommandBufferDX12.h>

using namespace GraphicsAPI;
using namespace Math;
using namespace Graphics;
using namespace MaterialSys;
using namespace GPCompute;

ID3D12Resource* TargetRes;

GraphicsResource* Target;

CommandBuffer* Cmd;
ComputeKernel* PtKernel;

PathTrace::PathTrace()
{
    SceneManager = new SceneSearchManager(float3(0, 0, 0), float3(10, 10, 10), 1);

    Cmd = new CommandBuffer("PathTrace");

    ShaderLayout* ptLayout = new ShaderLayout(1);
    ShaderTable* table = new ShaderTable();
    table->AddProp(-1, "_Target", GraphicsResourceType::UAV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW);
    ptLayout->Slots[0] = table;
    ptLayout->BuildOnDX12();

    std::string path = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\PathTrace\\Pt", "hlsl");
    PtKernel = new ComputeKernel();
    PtKernel->SetLayout(ptLayout);
    PtKernel->AddKernel(path, "pt_kernel");
    PtKernel->Build();

    Target = new GraphicsResource("_PtTarget", GraphicsResourceType::UAV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, false);
    Target->InitAsCustom(1920, 1080, GraphicsResourceFormat::R16G16B16A16_FLOAT, GraphicsResourceDimension::GraphicsResourceDimension_Tex2D);

    GraphicsResourceFormat format = GraphicsResourceFormat::R16G16B16A16_FLOAT;
    TargetRes = ((GraphicsResourceDX12*)Target->PlatformBridge->raw_obj)->Resource;
    _uint heapOffset = ResourceDescriptorHeapManager::ShareInstance()->HeapPool[0]->DynamicFillHeapGlobal(TargetRes, &format, false, true);
    PtKernel->SetPropertyObject(Target, 0, 0, heapOffset);
}

PathTrace::~PathTrace()
{
    if (SceneManager)
    {
        delete SceneManager;
        SceneManager = 0;
    }
}

void PathTrace::OnUpdate()
{
    Cmd->BeginFrame();
    Cmd->Reset();

    ((CommandBufferDX12*)Cmd->PlatformBridge->raw_obj)->cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(TargetRes, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));
    Cmd->DispatchComputeKernel(PtKernel, int3(1920 / 8, 1080 / 8, 1));
    ((CommandBufferDX12*)Cmd->PlatformBridge->raw_obj)->cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(TargetRes, D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    Cmd->Commit(true);
}
