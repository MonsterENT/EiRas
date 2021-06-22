#include "CommonBlur.hpp"
#include <PlatformDependency/OnDX/DX12Utils.h>
#include <Material/Material.hpp>
#include <Material/Shader.hpp>
#include <Material/ShaderLayout.h>
#include <Component/FileSys/FileManager.hpp>
#include <Graphics/GraphicsVertexDescriptor.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Graphics/GraphicsRenderState.hpp>
#include <Math/Math.hpp>

using namespace Math;
using namespace MaterialSys;
using namespace Effect;
using namespace Graphics;
using namespace DX12Utils;

typedef struct CommonCB
{
    float4 BlurSettings;//x width, y height, z BlurCoef
} CommonCB;

static CommonCB g_tmpCB;

CommonBlur::CommonBlur(_uint width, _uint height, Graphics::CommandBuffer* refCmdBuffer)
{
    _RefCmdBuffer = refCmdBuffer;
#pragma region Init
    ShaderLayout* shaderLayout = new ShaderLayout(2);
    {
        //ShaderProp* commonCB0 = new ShaderProp("BlurCB", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, sizeof(CommonCB));
        //commonCB0->InitRegisterSettings(0);

        ShaderPropRange commonCB0("BlurCR", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH);
        commonCB0.AddProp(sizeof(CommonCB));

        ShaderPropRange commonSR0("BlurSR", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT);
        commonSR0.PropNum = 1;

        ShaderTable* table0 = new ShaderTable();
        table0->AddRange(commonSR0);

        ShaderTable* table1 = new ShaderTable();
        table1->AddRange(commonCB0);

        shaderLayout->Slots[0] = table0;
        shaderLayout->Slots[1] = table1;
        shaderLayout->BuildOnDX12();
    }

    GraphicsVertexDescriptor* m_vertexDesc = new GraphicsVertexDescriptor();

    m_vertexDesc->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
    m_vertexDesc->InitBufferLayout();

    std::string shaderFilePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\CommonBlur", "hlsl");
    _Shader = new Shader(shaderFilePath, "VSMain", "PSMainH");
    _Shader->AddPixelFuncToPass("PSMainV", 1);
    _Shader->SetVertexFuncToPass(0, 1);
    _Shader->InitVertexDescriptor(m_vertexDesc);
    _Shader->SetLayout(shaderLayout);

    _Material = new Material("Common Blur Material", _Shader);
    _Material->RenderState->_CullMode = CullMode::CullModeNone;
#pragma endregion

    Width = width;
    Height = height;

    BluredRT = new RenderTexture("Common Blur", MaterialSys::GraphicsResourceFormat::R8G8B8A8_UNORM, false, width, height);
    _TmpBluredRT = new RenderTexture("Common Blur Tmp", MaterialSys::GraphicsResourceFormat::R8G8B8A8_UNORM, false, width, height);
}

#define PROCESS \
{\
    BlitFullScreen(src, _TmpBluredRT, _RefCmdBuffer, _Material);\
    RenderTexture* t_src = _TmpBluredRT, * t_dest = BluredRT;\
    blitTimes += blitTimes % 2 > 0 ? 0 : 1;\
    for (int i = 0; i < blitTimes; i++)\
    {\
        BlitFullScreen(t_src, t_dest, _RefCmdBuffer, _Material);\
        RenderTexture* t = t_dest;\
        t_dest = t_src;\
        t_src = t;\
    }\
}

void CommonBlur::ProcessWithSource(Graphics::RenderTexture* src, _uint blitTimes, float blurCoef)
{
    g_tmpCB.BlurSettings.x = Width;
    g_tmpCB.BlurSettings.y = Height;
    g_tmpCB.BlurSettings.z = blurCoef;
    _Material->SetProperty(&g_tmpCB, 1, 0);

    BlitFullScreen(src, _TmpBluredRT, _RefCmdBuffer, _Material, 0);
    BlitFullScreen(_TmpBluredRT, BluredRT, _RefCmdBuffer, _Material, 1);
    RenderTexture* t_src = BluredRT, * t_dest = _TmpBluredRT;
    blitTimes += blitTimes % 2 > 0 ? 0 : 1;
    for (int i = 0; i < blitTimes; i++)
    {
        BlitFullScreen(t_src, t_dest, _RefCmdBuffer, _Material, 0);
        BlitFullScreen(t_dest, t_src, _RefCmdBuffer, _Material, 1);
        RenderTexture* t = t_dest;
        t_dest = t_src;
        t_src = t;
    }
}

void CommonBlur::ProcessWithSource(MaterialSys::GraphicsResource* src, _uint blitTimes, float blurCoef)
{
    //g_tmpCB.BlurSettings.x = Width;
    //g_tmpCB.BlurSettings.y = Height;
    //g_tmpCB.BlurSettings.z = blurCoef;
    //_Material->SetProperty(&g_tmpCB, 0, 1);
    //PROCESS
}