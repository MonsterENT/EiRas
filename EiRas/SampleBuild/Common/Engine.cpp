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

#define FILL_SUBMESH(submesh)\
submesh->IndicesCount = 6;\
submesh->VerticesCount = 4;\
submesh->IndicesData = new _uint[6]{ 0, 1, 2, 2, 0, 3 };\
submesh->UVData = new float2[4]{ {0, 0}, {1, 0}, {1, 1}, {0, 1} };\
submesh->NormalData = new float3[4]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };\



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
    std::string fontShaderFilePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\CommonFont", "hlsl");
    _CommonFontShader = new Shader(fontShaderFilePath, "VSMain", "PSMain");

    std::string texShaderFilePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\CommonTex", "hlsl");
    _CommonTexShader = new Shader(texShaderFilePath, "VSMain", "PSMain");
#endif
    _CommonFontShader->InitLayout(layout);
    _CommonTexShader->InitLayout(layout);
    
    GraphicsVertexDescriptor* m_vertexDesc = new GraphicsVertexDescriptor();
    
    m_vertexDesc->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->AddBufferAttribute("TEXCOORD", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
    m_vertexDesc->AddBufferAttribute("NORMAL", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->InitBufferLayout();
    
    _CommonFontShader->InitVertexDescriptor(m_vertexDesc);
    _CommonTexShader->InitVertexDescriptor(m_vertexDesc);

    _FontMat0 = new Material("_FontMat0", _CommonFontShader, cmdBuffer);
    _FontMat1 = new Material("_FontMat1", _CommonFontShader, cmdBuffer);
    _TexMat0 = new Material("_TexMat0", _CommonTexShader, cmdBuffer);


    static float4 tmpCol;
    tmpCol.x = 1;
    tmpCol.y = 1;
    tmpCol.z = 1;
    tmpCol.w = 1;
    _FontMat0->SetProperty(&tmpCol, 0);
    _FontMat1->SetProperty(&tmpCol, 0);    
    _TexMat0->SetProperty(&tmpCol, 0);

    //std::string resPath = FileSys::FileManager::shareInstance()->GetModelResourcePath("qumian", "obj");
    
    SubMesh* subMesh = new SubMesh;

    _FontMesh0 = new Mesh("_FontMesh0");
    _FontMesh0->SubMeshCount = 1;
    FILL_SUBMESH(subMesh)
    subMesh->PositionData = new float3[4]{ {-1, 1, 1}, {0, 1, 1}, {0, 0, 1}, {-1, 0, 1} };
    _FontMesh0->SubMeshes = subMesh;
    _FontMesh0->BuildBuffer();
    
    subMesh = new SubMesh;
    _FontMesh1 = new Mesh("_FontMesh1");
    _FontMesh1->SubMeshCount = 1;
    FILL_SUBMESH(subMesh)
    subMesh->PositionData = new float3[4]{ {0, 1, 1}, {1, 1, 1}, {1, 0, 1}, {0, 0, 1} };
    _FontMesh1->SubMeshes = subMesh;
    _FontMesh1->BuildBuffer();

    subMesh = new SubMesh;
    _TexMesh0 = new Mesh("_TexMesh0");
    _TexMesh0->SubMeshCount = 1;
    FILL_SUBMESH(subMesh)
    subMesh->PositionData = new float3[4]{ {0, 0, 1}, {1, 0, 1}, {1, -1, 1}, {0, -1, 1} };
    _TexMesh0->SubMeshes = subMesh;
    _TexMesh0->BuildBuffer();


    std::string fontPath = FileSys::FileManager::shareInstance()->GetResourcePath("Font\\BELL", "TTF");
    FontSys::Font* font = new Font(fontPath);
    Text* text = font->GetText("ABC", 1024);
    FontManager::SharedInstance()->fontDataList[0]->RefreshFontImage();
    FontManager::SharedInstance()->fontDataList[1]->RefreshFontImage();

    _FontMat0->SetProperty(FontManager::SharedInstance()->fontDataList[0]->_FontImage, 1, 0);
    _FontMat1->SetProperty(FontManager::SharedInstance()->fontDataList[1]->_FontImage, 1, 0);

    std::string imagePath = FileSys::FileManager::shareInstance()->GetTextureResourcePath("ground512", "png");
    imageObj = new Image("ground512");
    imageObj->LoadFromFile(imagePath);
    _TexMat0->SetProperty(imageObj, 1, 0);

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

    cmdBuffer->SetMaterial(_FontMat0);
    cmdBuffer->DrawMesh(_FontMesh0);

    cmdBuffer->SetMaterial(_FontMat1);
    cmdBuffer->DrawMesh(_FontMesh1);

    cmdBuffer->SetMaterial(_TexMat0);
    cmdBuffer->DrawMesh(_TexMesh0);
    cmdBuffer->Commit(true);
}
