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

#include <PlatformDependency/OnDX/DX12Utils.h>

#include "GraphicsData.hpp"

using namespace GraphicsAPI;
using namespace Math;
using namespace Graphics;
using namespace MaterialSys;
using namespace GPCompute;

ID3D12Resource* TargetRes;

GraphicsResource* Target;
int heapOffset;

CommandBuffer* Cmd;
ComputeKernel* PtKernel;

Material* CopyStd;

GraphicsResource* ObjectMaterialData;

#pragma region BuildSimpleScene

#define FILL_TRIANGLE(o, p0, p1, p2, n, matid) o->pos0 = p0; o->pos1 = p1; o->pos2 = p2; o->normal = n; o->materialId = matid;

void buildScene(SceneSearchManager* ssm, ComputeKernel* kernel)
{
    ObjectMaterialData = new GraphicsResource("ObjectMaterialData", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, false);
    ObjectMaterialData->InitAsShaderResource(sizeof(MaterialData) * 4);

    MaterialData matData[4];
    matData[0].color = mfloat4(0.5, 0.5, 0.5, 1);
    matData[1].color = mfloat4(1, 0, 0, 1);
    matData[2].color = mfloat4(0, 0, 1, 1);
    matData[3].color = mfloat4(0.1, 0.2, 0.0, 1);

    ObjectMaterialData->SetResource(&matData[0], false);
    kernel->SetPropertyObject(ObjectMaterialData, 1);

    float boxSize = 5;

    //Bottom
    TriangleData* b0 = new TriangleData();
    FILL_TRIANGLE(b0, mfloat3(-boxSize, 0, 0), mfloat3(-boxSize, 0, boxSize * 2), mfloat3(boxSize, 0, boxSize * 2), mfloat3(0, 1, 0), 0);
    TriangleData* b1 = new TriangleData();
    FILL_TRIANGLE(b1, mfloat3(-boxSize, 0, 0), mfloat3(boxSize, 0, boxSize * 2), mfloat3(boxSize, 0, 0), mfloat3(0, 1, 0), 0);

    //front
    TriangleData* b2 = new TriangleData();
    FILL_TRIANGLE(b2, mfloat3(-boxSize - 1, 0, boxSize * 2), mfloat3(-boxSize - 1, boxSize * 2, boxSize * 2), mfloat3(boxSize + 1, boxSize * 2, boxSize * 2), mfloat3(0, 0, -1), 3);
    TriangleData* b3 = new TriangleData();
    FILL_TRIANGLE(b3, mfloat3(-boxSize - 1, 0, boxSize * 2), mfloat3(boxSize + 1, boxSize * 2, boxSize * 2), mfloat3(boxSize + 1, 0, boxSize * 2), mfloat3(0, 0, -1), 3);

    //left
    TriangleData* b4 = new TriangleData();
    FILL_TRIANGLE(b4, mfloat3(-boxSize, 0, 0), mfloat3(-boxSize, boxSize * 2, 0), mfloat3(-boxSize, boxSize * 2, boxSize * 2), mfloat3(1, 0, 0), 2);
    TriangleData* b5 = new TriangleData();
    FILL_TRIANGLE(b5, mfloat3(-boxSize, 0, 0), mfloat3(-boxSize, boxSize * 2, boxSize * 2), mfloat3(-boxSize, 0, boxSize * 2), mfloat3(1, 0, 0), 2);

    //right
    TriangleData* b6 = new TriangleData();
    FILL_TRIANGLE(b6, mfloat3(boxSize, 0, 0), mfloat3(boxSize, boxSize * 2, 0), mfloat3(boxSize, boxSize * 2, boxSize * 2), mfloat3(-1, 0, 0), 1);
    TriangleData* b7 = new TriangleData();
    FILL_TRIANGLE(b7, mfloat3(boxSize, 0, 0), mfloat3(boxSize, boxSize * 2, boxSize * 2), mfloat3(boxSize, 0, boxSize * 2), mfloat3(-1, 0, 0), 1);

    //top
    TriangleData* b8 = new TriangleData();
    FILL_TRIANGLE(b8, mfloat3(-boxSize, boxSize * 2, 0), mfloat3(-boxSize, boxSize * 2, boxSize * 2), mfloat3(boxSize, boxSize * 2, boxSize * 2), mfloat3(0, -1, 0), 0);
    TriangleData* b9 = new TriangleData();
    FILL_TRIANGLE(b9, mfloat3(-boxSize, boxSize * 2, 0), mfloat3(boxSize, boxSize * 2, boxSize * 2), mfloat3(boxSize, boxSize * 2, 0), mfloat3(0, -1, 0), 0);


    ssm->AddSceneObject(b0, float3(), float3());
    ssm->AddSceneObject(b1, float3(), float3());
    ssm->AddSceneObject(b2, float3(), float3());
    ssm->AddSceneObject(b3, float3(), float3());
    ssm->AddSceneObject(b4, float3(), float3());
    ssm->AddSceneObject(b5, float3(), float3());
    ssm->AddSceneObject(b6, float3(), float3());
    ssm->AddSceneObject(b7, float3(), float3());
    ssm->AddSceneObject(b8, float3(), float3());
    ssm->AddSceneObject(b9, float3(), float3());
    ssm->BuildGraphics(kernel, 0, 0, 2);
}

#pragma endregion


PathTrace::PathTrace()
{
    SceneManager = new SceneSearchManager(float3(0, 0, 0), float3(10, 10, 10), 1);

    Cmd = new CommandBuffer("PathTrace");

    ShaderLayout* ptLayout = new ShaderLayout(3);
    ShaderTable* table = new ShaderTable();
    table->AddProp(-1, "_Target", GraphicsResourceType::UAV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW);
    
    ShaderProp* prop0 = new ShaderProp("_MaterialData", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, -1);
    ShaderProp* prop1 = new ShaderProp("_TriangleData", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, -1);

    ptLayout->Slots[0] = table;
    ptLayout->Slots[1] = prop0;
    ptLayout->Slots[2] = prop1;
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
    heapOffset = ResourceDescriptorHeapManager::ShareInstance()->HeapPool[0]->DynamicFillHeapGlobal(TargetRes, &format, false, true);
    PtKernel->SetPropertyObject(Target, 0, 0, heapOffset);

    buildScene(SceneManager, PtKernel);

    CopyStd = new Material("CopyStd", DX12Utils::CopyStd());
    CopyStd->RenderState->_CullMode = CullMode::CullModeNone;
    CopyStd->RenderState->_ZTest = CompareFunction::CompareFunctionAlways;
    CopyStd->FinishStateChange();
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
    Cmd->SetViewPort(0, 0, 2560, 1440);

    ((CommandBufferDX12*)Cmd->PlatformBridge->raw_obj)->cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(TargetRes, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));
    Cmd->DispatchComputeKernel(PtKernel, int3(1920 / 8, 1080 / 8, 1));
    ((CommandBufferDX12*)Cmd->PlatformBridge->raw_obj)->cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(TargetRes, D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    
    CopyStd->SetPropertyObject(Target, 0, 0, heapOffset);
    Cmd->SetMaterial(CopyStd);
    Cmd->DrawMesh(DX12Utils::FullScreenTriangle());
    Cmd->Commit(true);
}

void PathTrace::CommitData()
{
}