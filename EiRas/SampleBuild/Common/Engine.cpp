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

#include <FontSys/FontSys.hpp>
#include <FontSys/FontManager.hpp>

using namespace MaterialSys;
using namespace Graphics;
using namespace GraphicsAPI;
using namespace MeshSys;
using namespace ImageSys;
using namespace FontSys;

Image* imageObj = 0;

void Engine::m_initEngine()
{
    cmdBuffer = new CommandBuffer("main buffer");
    
    ShaderLayout* layout = new ShaderLayout(2);

    ShaderProp* commonCB0 = new ShaderProp("CommonCB0", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, sizeof(float4));
    commonCB0->InitRegisterSettings(0);

    ShaderPropRange commonSR1("CommonSR1", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT);
    commonSR1.PropNum = 1;
    commonSR1.InitBaseRegisterSettings(0);

    ShaderTable *table = new ShaderTable();
    table->AddRange(commonSR1);

    layout->Slots[0] = commonCB0;
    layout->Slots[1] = table;

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
    mat->SetProperty(&tmpCol, 0);
    mesh = 0;
    std::string resPath = FileSys::FileManager::shareInstance()->GetModelResourcePath("qumian", "obj");
    
    mesh = new Mesh("qumian");
    mesh->SubMeshCount = 1;
    SubMesh* subMesh = new SubMesh;
    subMesh->IndicesCount = 6;
    subMesh->VerticesCount = 4;
    subMesh->IndicesData = new _uint[6] {0, 1, 2, 2, 0, 3};
    subMesh->PositionData = new float3[4] {{-1, 1, 1}, {1, 1, 1}, {1, -1, 1}, {-1, -1, 1}};
    subMesh->UVData = new float2[4] {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    subMesh->NormalData = new float3[4] {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    mesh->SubMeshes = subMesh;
    //    mesh->LoadDataFromFile(resPath);
    mesh->BuildBuffer();

    std::string imagePath = FileSys::FileManager::shareInstance()->GetTextureResourcePath("ground512", "png");

    //imageObj = new Image("ground512");
    //imageObj->LoadFromFile(imagePath);

    std::string fontPath = FileSys::FileManager::shareInstance()->GetResourcePath("Font\\BELL", "TTF");
    FontSys::Font* font = new Font(fontPath);
    Text* text = font->GetText("A", 256);
    FontManager::SharedInstance()->fontDataList[0]->RefreshFontImage();

    mat->SetProperty(FontManager::SharedInstance()->fontDataList[0]->_FontImage, 1, 0);
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
    device = EiRas::Create(hWnd, 2560, 1440);
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
