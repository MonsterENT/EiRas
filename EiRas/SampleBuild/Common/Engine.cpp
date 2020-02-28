#include "Engine.hpp"
#include <Material/ShaderLayout.h>
#include <GraphicsAPI/EiRas.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Graphics/GraphicsVertexDescriptor.hpp>
#include <Material/Material.hpp>
#include <Material/Shader.hpp>
#include <Mesh/Mesh.hpp>
#include <Graphics/VertexDataType.h>
#include <Component/FileSys/FileManager.hpp>

#include <Basic/Image.hpp>

using namespace MaterialSys;
using namespace Graphics;
using namespace GraphicsAPI;
using namespace MeshSys;
using namespace ImageSys;

Image* imageObj = 0;

float4* testDataArray;

void Engine::m_initEngine()
{
    testDataArray = new float4[1000];
    
    cmdBuffer = new CommandBuffer("main buffer");
    
    ShaderLayout* layout = new ShaderLayout();
    layout->SlotNum = 2;

    ShaderProp* commonCb0 = new ShaderProp();
    commonCb0->BufferSize = sizeof(float) * 4;
    commonCb0->PropName = "CommonCB0";
    commonCb0->PropType = GraphicsResourceType::CBV;
    commonCb0->Visibility = GraphicsResourceVisibility::VISIBILITY_PIXEL;
    commonCb0->SlotType = ShaderSlotType::ShaderSlotType_Prop;
    commonCb0->UpdateFreq = GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH;

    ShaderProp* commonSR1 = new ShaderProp();
    commonSR1->BufferSize = 0;
    commonSR1->PropName = "CommmonSR1";
    commonSR1->PropType = GraphicsResourceType::SRV;
    commonSR1->Visibility = GraphicsResourceVisibility::VISIBILITY_PIXEL;
    commonSR1->UpdateFreq = GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT;

    layout->Slots = new ShaderSlot*[2];
    layout->Slots[0] = commonCb0;
    layout->Slots[1] = commonSR1;

#if GRAPHICS_METAL
    shader = new Shader("m_shader", "vertexShader", "fragmentShader");
#elif GRAPHICS_DX
    shader = new Shader("shaders.hlsl", "VSMain", "PSMain");
#endif
    shader->InitLayout(layout);
    
    GraphicsVertexDescriptor* m_vertexDesc = new GraphicsVertexDescriptor();
    
    m_vertexDesc->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->AddBufferAttribute("TEXCOORD", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
    m_vertexDesc->AddBufferAttribute("NORMAL", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->InitBufferLayout();
    
    shader->InitVertexDescriptor(m_vertexDesc);
    
    mat = new Material("material", shader, cmdBuffer);
    static float4 tmpCol;
    tmpCol.x = 1;
    tmpCol.y = 1;
    tmpCol.z = 0;
    tmpCol.w = 1;
    mat->SetProperty(0, -1, &tmpCol);
    mesh = 0;
    std::string resPath = FileSys::FileManager::shareInstance()->GetResourcePath("qumian", "obj");
    
    mesh = new Mesh("qumian");
    mesh->SubMeshCount = 1;
    SubMesh* subMesh = new SubMesh;
    subMesh->IndicesCount = 6;
    subMesh->VerticesCount = 4;
    subMesh->IndicesData = new _uint[6] {0, 1, 3, 1, 2, 3};
    subMesh->PositionData = new float3[4] {{-1, 1, 0}, {1, 1, 0}, {1, -1, 0}, {-1, -1, 0}};
    subMesh->UVData = new float2[4] {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    subMesh->NormalData = new float3[4] {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    mesh->SubMeshes = subMesh;
    //    mesh->LoadDataFromFile(resPath);
    mesh->BuildBuffer();
    
    
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

#if GRAPHICS_DX
void Engine::InitEngine(HWND hWnd, _uint width, _uint height)
{
    device = EiRas::Create(hWnd, 1024, 1080);
    m_initEngine();
}
#endif

#if GRAPHICS_METAL
void Engine::InitEngine()
{
    device = EiRas::Create();
    m_initEngine();
}
#endif

void Engine::Update()
{
    cmdBuffer->BeginFrame();
    cmdBuffer->Reset();
    cmdBuffer->SetMaterial(mat);
    if(mesh)
        cmdBuffer->DrawMesh(mesh);
    cmdBuffer->Commit(true);
}
