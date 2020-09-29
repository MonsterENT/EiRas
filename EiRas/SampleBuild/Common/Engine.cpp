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
#include <Effect/CommonBlur/CommonBlur.hpp>
#include <Global/EiRasGlobalManager.hpp>

#pragma region GUI Include
#include <GUI/Button.hpp>
#include <GUI/GUISystem.hpp>
#include <GUI/Label.hpp>
#include <GUI/Ex/InspectorTransform.hpp>
#pragma endregion

#pragma message("TO FIX. TMP")
#include <DirectXMath.h>
using namespace DirectX;
using namespace Effect;
using namespace BasicComponent;
using namespace MaterialSys;
using namespace Graphics;
using namespace GraphicsAPI;
using namespace MeshSys;
using namespace ImageSys;
using namespace FontSys;
using namespace Math;
using namespace GUISys;

Image* imageObj = 0;

CommonBlur* _CommonBlur;

Camera _Camera;
TransformSys _Transform;

RenderTexture* _SceneRenderTexture;

Label* label;

InspectorTransform* inspector = NULL;

RenderData sf90RenderData;

#pragma region TestMeshUpdate

float CloseTo0Coef = 0;

#pragma endregion

void OnClick(void* data)
{

}

void Engine::m_initEngine()
{
    _SceneRenderTexture = new RenderTexture("Scene RT", RenderBufferFormat::R8G8B8A8_UNORM, true, 2560, 1440);

    _Camera.SetProjection(45, 2560.0 / 1440.0, 0.01, 1000);
    _Camera.Transform.Init(float3(0, 0, 1), float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 0));
    EiRasGlobal::EiRasGlobalManager::SharedInstance()->SetViewProj(*_Camera.GetViewMatrix(), *_Camera.GetProjectionMatrix());
    

    _Transform.Init(float3(0, 1, 0), float3(1, 0, 0), float3(0, 0, 1), float3(0, -1, 5));
    _Transform.LocalScale = float3(1, 1, 1);
    _Transform.UpdateToGraphics();
    
    cmdBuffer = new CommandBuffer("main buffer");
    
    _CommonBlur = new CommonBlur(2560 / 2, 1440 / 2, cmdBuffer);
    
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
        ShaderProp* customCB = new ShaderProp("CustomCB", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, sizeof(float4));

        ShaderPropRange commonSR1("_MainTex", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT);
        commonSR1.PropNum = 1;
        //commonSR1.InitBaseRegisterSettings(0);

        ShaderTable* table = new ShaderTable();
        table->AddRange(commonSR1);

        ShaderSlot* T0 = new ShaderSlot();
        T0->SlotType = ShaderSlotType::ShaderSlotType_Builtin_ViewProj;
        ShaderSlot* T1 = new ShaderSlot();
        T1->SlotType = ShaderSlotType::ShaderSlotType_Ref_WorldMatrix;
        defaultlayout->Slots[0] = T0;
        defaultlayout->Slots[1] = T1;
        defaultlayout->Slots[2] = customCB;
        defaultlayout->Slots[3] = table;
        defaultlayout->BuildOnDX12();
    }
#pragma endregion


#if GRAPHICS_METAL
    shader = new Shader("m_shader", "vertexShader", "fragmentShader");
#elif GRAPHICS_DX
    std::string shaderPath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\BasicBRDF", "hlsl");
    _BasicBRDFShader = new Shader(shaderPath, "VSMain", "PSMain");
#endif
    _BasicBRDFShader->SetLayout(defaultlayout);

    GraphicsVertexDescriptor* m_vertexDesc = new GraphicsVertexDescriptor();
    m_vertexDesc->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->AddBufferAttribute("TEXCOORD", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
    m_vertexDesc->AddBufferAttribute("NORMAL", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->InitBufferLayout();

    _BasicBRDFShader->InitVertexDescriptor(m_vertexDesc);
    _Mat0 = new Material("SF90", _BasicBRDFShader, cmdBuffer);

    static float4 tmpCol;
    tmpCol.x = 1;
    tmpCol.y = 1;
    tmpCol.z = 1;
    tmpCol.w = 1;
    _Mat0->SetProperty(&tmpCol, 0);

    std::string sf90ModelPath = FileSys::FileManager::shareInstance()->GetModelResourcePath("SF90_TMP", "FBX");
    _SF90Mesh = new Mesh("SF90");
    _SF90Mesh->LoadDataFromFile(sf90ModelPath);
    _SF90Mesh->BuildBuffer(MeshType::VertexInput3D, false);

#pragma region BuildRenderData
    sf90RenderData.AddMesh(_SF90Mesh);
    sf90RenderData.AddMaterial(_Mat0);
#pragma endregion


    GUISys::GUISystem::CreateSystem(_ClientHW.x, _ClientHW.y, cmdBuffer);

    Button* btn = new Button();
    btn->SetFrame(rect_float(600, 0, 100, 100));
    btn->m_Response = new Response(OnClick, NULL);

    std::string fontPath = FileSys::FileManager::shareInstance()->GetResourcePath("Font\\BELL", "TTF");
    FontSys::Font* font = new Font(fontPath);
    
    Text* text = new Text();
    font->GetText("SF90GGWP", text, 512);

    label = new Label();
    label->SetFrame(rect_float(600, 600, 400, 100));
    label->SetTextColor(float4(1, 0, 0, 1));
    label->SetBackgroundColor(float4(1, 1, 1, 1));
    label->SetText(text);

    inspector = new InspectorTransform(&_Transform);
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
    _ClientHW.x = width;
    _ClientHW.y = height;
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

void Engine::Update(void* data)
{
    std::string texturePath = FileSys::FileManager::shareInstance()->GetTextureResourcePath("ground512", "png");

    if (imageObj == 0)
    {
        imageObj = new Image("Texture");
        imageObj->LoadFromFile(texturePath);
    }
    _Mat0->SetProperty(imageObj, 3, 0);

    int count = 0;
    //float3* posData = _SF90Mesh->GetPositionData(count);
    //for (int i = 0; i < count; i++)
    //{
    //    posData[i] -= posData[i] * CloseTo0Coef;
    //}
    ////UnSafe But Efficient
    //_SF90Mesh->BuildBuffer(MeshType::VertexInput3D, false);

    cmdBuffer->BeginFrame();
    cmdBuffer->Reset();
    cmdBuffer->SetViewPort(0, 0, 2560, 1440);
    cmdBuffer->SetRenderTexture(_SceneRenderTexture);

    cmdBuffer->SetTransform(&_Transform);

    static float4 tmpCol = float4(1, 1, 1, 1);
    _Mat0->SetProperty(&tmpCol, 2);

    _Mat0->RenderState->_CullMode = CullMode::CullModeNone;
    //_Mat0->FinishStateChange();
    //cmdBuffer->SetMaterial(_Mat0);
    //cmdBuffer->DrawMesh(_SF90Mesh);
    cmdBuffer->DrawRenderData(&sf90RenderData);

    _CommonBlur->ProcessWithSource(_SceneRenderTexture, 4, 1);
    cmdBuffer->SetRenderTexture(0);

    //cmdBuffer->SetMaterial(_Mat0);
    //cmdBuffer->DrawMesh(_SF90Mesh);
    cmdBuffer->DrawRenderData(&sf90RenderData);

    label->SetBackgroundImage(_CommonBlur->BluredRT);
    if (data != 0)
    {
        GUISys::GUISystem::SharedInstance()->RunLoopInvoke(data);
    }
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
        //CloseTo0Coef += 0.01;
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
        //CloseTo0Coef -= 0.01;
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
    _Transform.UpdateToGraphics();

    _Camera.SetProjection(FOV, 2560.0 / 1440.0, 0.01, 1000);
    _Camera.Transform.Init(float3(0, 0, 1), float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 0));
    EiRasGlobal::EiRasGlobalManager::SharedInstance()->SetViewProj(*_Camera.GetViewMatrix(), *_Camera.GetProjectionMatrix());
}