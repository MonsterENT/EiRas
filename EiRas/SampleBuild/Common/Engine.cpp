#include "Engine.hpp"
#include <Material/ShaderLayout.h>
#include <GraphicsAPI/EiRas.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Graphics/GraphicsVertexDescriptor.hpp>
#include <Material/Material.hpp>
#include <Material/Shader.hpp>
#include <Mesh/Mesh.hpp>
#include <Graphics/VertexDataType.h>
#include <Graphics/GraphicsRenderState.hpp>
#include <Component/FileSys/FileManager.hpp>
#include <Basic/Image.hpp>
#include <FontSys/FontSys.hpp>
#include <FontSys/FontManager.hpp>
#include <Math/Math.hpp>

#include <Basic/Camera.hpp>
#include <Basic/TransformSys.hpp>
#include <Graphics/RenderTexture.hpp>

#pragma message("TO FIX. TMP")
#include <DirectXMath.h>
using namespace DirectX;

using namespace BasicComponent;
using namespace MaterialSys;
using namespace Graphics;
using namespace GraphicsAPI;
using namespace MeshSys;
using namespace ImageSys;
using namespace FontSys;
using namespace Math;

Image* imageObj = 0;

#define FILL_SUBMESH(submesh)\
submesh->IndicesCount = 6;\
submesh->VerticesCount = 4;\
submesh->IndicesData = new _uint[6]{ 0, 1, 2, 2, 0, 3 };\
submesh->UVData = new float2[4]{ {0, 0}, {1, 0}, {1, 1}, {0, 1} };\
submesh->NormalData = new float3[4]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };\

typedef struct CommonCB0
{
    Matrix4X4 WorldToViewMatrix;
    Matrix4X4 ProjectionMatrix;
}CommonCB0;

typedef struct CommonCB1
{
    Matrix4X4 LocalToWorldMatrix;
    Matrix4X4 WorldToLocalMatrix;
}CommonCB1;

CommonCB0 _CommonCB0;
CommonCB1 _CommonCB1;

Camera _Camera;
TransformSys _Transform;

RenderTexture* _SceneRenderTexture;

void Engine::m_initEngine()
{
    _SceneRenderTexture = new RenderTexture("Scene RT", RenderBufferFormat::R8G8B8A8_UNORM, true, 2560, 1440);

    _Camera.SetProjection(45, 2560.0 / 1440.0, 0.01, 1000);
    _Camera.Transform.Init(float3(0, 0, 1), float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 0));
    _CommonCB0.WorldToViewMatrix = *_Camera.GetViewMatrix();
    _CommonCB0.ProjectionMatrix = *_Camera.GetProjectionMatrix();

    _Transform.Init(float3(0, 1, 0), float3(1, 0, 0), float3(0, 0, 1), float3(0, -1, 5));
    _Transform.LocalScale = float3(1, 1, 1);
    _CommonCB1.LocalToWorldMatrix = *_Transform.GetLocalToWorldMatrix();
    _CommonCB1.WorldToLocalMatrix = *_Transform.GetWorldToLocalMatrix();
    
    cmdBuffer = new CommandBuffer("main buffer");

#pragma region CustomShaderLayout
    ShaderLayout* customLayout = new ShaderLayout(2);
    {
        ShaderProp* commonCB0 = new ShaderProp("CommonCB0", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, sizeof(float4));
        commonCB0->InitRegisterSettings(0);

        ShaderPropRange commonSR1("CommonSR1", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT);
        commonSR1.PropNum = 1;
        commonSR1.InitBaseRegisterSettings(0);

        ShaderTable* table = new ShaderTable();
        table->AddRange(commonSR1);

        customLayout->Slots[0] = commonCB0;
        customLayout->Slots[1] = table;
    }
#pragma endregion

#pragma region Default3DShaderLayout
    ShaderLayout* defaultlayout = new ShaderLayout(4);
    {
        ShaderProp* commonCB0 = new ShaderProp("CommonCB0", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, sizeof(Matrix4X4) * 2);
        commonCB0->InitRegisterSettings(0);
        ShaderProp* commonCB1 = new ShaderProp("CommonCB1", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, sizeof(Matrix4X4) * 2);
        commonCB1->InitRegisterSettings(1);
        ShaderProp* customCB = new ShaderProp("CustomCB", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, sizeof(float4));
        customCB->InitRegisterSettings(2);

        ShaderPropRange commonSR1("CommonSR1", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT);
        commonSR1.PropNum = 1;
        commonSR1.InitBaseRegisterSettings(0);

        ShaderTable* table = new ShaderTable();
        table->AddRange(commonSR1);

        defaultlayout->Slots[0] = commonCB0;
        defaultlayout->Slots[1] = commonCB1;
        defaultlayout->Slots[2] = customCB;
        defaultlayout->Slots[3] = table;
    }
#pragma endregion


#if GRAPHICS_METAL
    shader = new Shader("m_shader", "vertexShader", "fragmentShader");
#elif GRAPHICS_DX
    std::string fontShaderFilePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\CommonFont", "hlsl");
    _CommonFontShader = new Shader(fontShaderFilePath, "VSMain", "PSMain");

    std::string texShaderFilePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\BasicBRDF", "hlsl");
    _CommonTexShader = new Shader(texShaderFilePath, "VSMain", "PSMain");
#endif
    _CommonFontShader->InitLayout(customLayout);
    _CommonTexShader->InitLayout(defaultlayout);
    
    GraphicsVertexDescriptor* m_vertexDesc = new GraphicsVertexDescriptor();
    
    m_vertexDesc->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->AddBufferAttribute("TEXCOORD", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
    m_vertexDesc->AddBufferAttribute("NORMAL", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->InitBufferLayout();
    
    _CommonFontShader->InitVertexDescriptor(m_vertexDesc);
    _CommonTexShader->InitVertexDescriptor(m_vertexDesc);

    _FontMat0 = new Material("_FontMat0", _CommonFontShader, cmdBuffer);
    _FontMat0->RenderState->_BlendSrcRGBFactor = BlendFactor::BlendRGBFactorSourceAlpha;
    _FontMat0->RenderState->_BlendDstRGBFactor = BlendFactor::BlendRGBFactorOneMinusSourceAlpha;
    _FontMat0->FinishStateChange();

    _FontMat1 = new Material("_FontMat1", _CommonFontShader, cmdBuffer);
    _FontMat1->RenderState->_BlendSrcRGBFactor = BlendFactor::BlendRGBFactorSourceAlpha;
    _FontMat1->RenderState->_BlendDstRGBFactor = BlendFactor::BlendRGBFactorOneMinusSourceAlpha;
    _FontMat1->FinishStateChange();

    _TexMat0 = new Material("_TexMat0", _CommonTexShader, cmdBuffer);


    static float4 tmpCol;
    tmpCol.x = 1;
    tmpCol.y = 1;
    tmpCol.z = 1;
    tmpCol.w = 1;
    _FontMat0->SetProperty(&tmpCol, 0);
    _FontMat1->SetProperty(&tmpCol, 0);    
    
    SubMesh* subMesh = new SubMesh;

    _FontMesh0 = new Mesh("_FontMesh0");
    _FontMesh0->SubMeshCount = 1;
    FILL_SUBMESH(subMesh)
    subMesh->PositionData = new float3[4]{ {-1, 1, 0.5}, {0, 1, 0.5}, {0, 0, 0.5}, {-1, 0, 0.5} };
    _FontMesh0->SubMeshes = subMesh;
    _FontMesh0->BuildBuffer();
    
    subMesh = new SubMesh;
    _FontMesh1 = new Mesh("_FontMesh1");
    _FontMesh1->SubMeshCount = 1;
    FILL_SUBMESH(subMesh)
    subMesh->PositionData = new float3[4]{ {0, 1, 0.5}, {1, 1, 0.5}, {1, 0, 0.5}, {0, 0, 0.5} };
    _FontMesh1->SubMeshes = subMesh;
    _FontMesh1->BuildBuffer();

    subMesh = new SubMesh;
    _TexMesh0 = new Mesh("_TexMesh0");
    _TexMesh0->SubMeshCount = 1;
    FILL_SUBMESH(subMesh)
    subMesh->PositionData = new float3[4]{ {-0.5, 0.5, 1}, {0.5, 0.5, 1}, {0.5, -0.5, 1}, {-0.5, -0.5, 1} };
    _TexMesh0->SubMeshes = subMesh;
    _TexMesh0->BuildBuffer();


    std::string fontPath = FileSys::FileManager::shareInstance()->GetResourcePath("Font\\BELL", "TTF");
    FontSys::Font* font = new Font(fontPath);
    Text* text = font->GetText("SF90", 900);
    FontManager::SharedInstance()->fontDataList[0]->RefreshFontImage();
    FontManager::SharedInstance()->fontDataList[1]->RefreshFontImage();

    _FontMat0->SetProperty(FontManager::SharedInstance()->fontDataList[0]->_FontImage, 1, 0);
    _FontMat1->SetProperty(FontManager::SharedInstance()->fontDataList[1]->_FontImage, 1, 0);

    std::string imagePath = FileSys::FileManager::shareInstance()->GetTextureResourcePath("ground512", "png");
    imageObj = new Image("ground512");
    imageObj->LoadFromFile(imagePath);
    _TexMat0->SetProperty(imageObj, 3, 0);


    std::string sf90ModelPath = FileSys::FileManager::shareInstance()->GetModelResourcePath("SF90_TMP", "FBX");
    _SF90Mesh = new Mesh("SF90");
    _SF90Mesh->LoadDataFromFile(sf90ModelPath);
    _SF90Mesh->BuildBuffer();
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
    cmdBuffer->SetViewPort(0, 0, 2560, 1440);
    cmdBuffer->SetRenderTexture(_SceneRenderTexture);

    _TexMat0->SetProperty(&_CommonCB0, 0);
    _TexMat0->SetProperty(&_CommonCB1, 1);
    static float4 tmpCol = float4(1, 1, 1, 1);
    _TexMat0->SetProperty(&tmpCol, 2);

    _TexMat0->RenderState->_CullMode = CullMode::CullModeNone;
    _TexMat0->FinishStateChange();
    cmdBuffer->SetMaterial(_TexMat0);
    cmdBuffer->DrawMesh(_SF90Mesh);

    cmdBuffer->SetRenderTexture(0);
    _FontMat0->RenderState->_CullMode = CullMode::CullModeNone;
    _FontMat0->FinishStateChange();
    cmdBuffer->SetMaterial(_FontMat0);
    cmdBuffer->DrawMesh(_FontMesh0);

    _FontMat1->RenderState->_CullMode = CullMode::CullModeNone;
    _FontMat1->FinishStateChange();
    cmdBuffer->SetMaterial(_FontMat1);
    cmdBuffer->DrawMesh(_FontMesh1);

    cmdBuffer->Commit(true);
}

void Engine::KeyPressed(_uint param)
{
    static float FOV = 45;

    static float3 postion = _Transform.Position;
    static float3 forward = _Transform.Forward;
    static float3 up = _Transform.Up;
    static float3 right = _Transform.Right;

    XMVECTOR _forward = XMVectorSet(forward.x, forward.y, forward.z, 1);
    XMVECTOR _up = XMVectorSet(up.x, up.y, up.z, 1);
    XMVECTOR _right = XMVectorSet(right.x, right.y, right.z, 1);
    if (param == 0x25)//VK_LEFT
    {
        XMMATRIX R = XMMatrixRotationAxis(_forward, 3.14 / 25);
        _right = XMVector3TransformNormal(_right, R);
        _up = XMVector3TransformNormal(_up, R);
    }
    else if (param == 0x26)//VK_UP
    {
        postion.y += 0.1;
    }
    else if (param == 0x27)//VK_RIGHT
    {
        XMMATRIX R = XMMatrixRotationAxis(_forward, -3.14 / 25);
        _right = XMVector3TransformNormal(_right, R);
        _up = XMVector3TransformNormal(_up, R);
    }
    else if (param == 0x28)//VK_DOWN
    {
        postion.y -= 0.1;
    }
    else if (param == 'N')
    {
        postion.z -= 0.1;
    }
    else if (param == 'F')
    {
        postion.z += 0.1;
    }
    else if (param == 'A')
    {
        postion.x -= 0.1;
    }
    else if (param == 'D')
    {
        postion.x += 0.1;
    }
    else if (param == 'W')
    {
        FOV += 0.1;
    }
    else if (param == 'S')
    {
        FOV -= 0.1;
    }
    forward.x = XMVectorGetX(_forward);
    forward.y = XMVectorGetY(_forward);
    forward.z = XMVectorGetZ(_forward);

    up.x = XMVectorGetX(_up);
    up.y = XMVectorGetY(_up);
    up.z = XMVectorGetZ(_up);

    right.x = XMVectorGetX(_right);
    right.y = XMVectorGetY(_right);
    right.z = XMVectorGetZ(_right);

    _Transform.Init(forward, right, up, postion);
    _Transform.LocalScale = float3(1, 1, 1);
    _CommonCB1.LocalToWorldMatrix = *_Transform.GetLocalToWorldMatrix();
    _CommonCB1.WorldToLocalMatrix = *_Transform.GetWorldToLocalMatrix();

    _Camera.SetProjection(FOV, 2560.0 / 1440.0, 0.01, 1000);
    _Camera.Transform.Init(float3(0, 0, 1), float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 0));
    _CommonCB0.WorldToViewMatrix = *_Camera.GetViewMatrix();
    _CommonCB0.ProjectionMatrix = *_Camera.GetProjectionMatrix();

}