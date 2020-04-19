#include "GUISystem.hpp"
#include "GUIBase.hpp"

#include <Material/Material.hpp>
#include <Material/Shader.hpp>
#include <Material/ShaderLayout.h>
#include <Graphics/GraphicsVertexDescriptor.hpp>
#include <FileSys/FileManager.hpp>
#include <Graphics/CommandBuffer.hpp>

#ifdef GRAPHICS_DX
#include <PlatformDependency/OnDX/GUI/GUISystemDX12Bridge.hpp>
#endif

using namespace FileSys;
using namespace GUISys;
using namespace MaterialSys;
using namespace Graphics;

static GUISystem* g_guiSystem = 0;

Material* GUISystem::SharedMaterial = NULL;
Shader* GUISystem::DefaultShader = NULL;

GUISystem* GUISystem::CreateSystem(_uint width, _uint height, Graphics::CommandBuffer* cmdBuffer)
{
#pragma region init Default Material
    GraphicsVertexDescriptor* vertexDesc = new GraphicsVertexDescriptor();
    vertexDesc->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
    vertexDesc->AddBufferAttribute("TEXCOORD", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
    vertexDesc->InitBufferLayout();

    ShaderLayout* shaderLayout = new ShaderLayout(1);

    ShaderPropRange commonCB("CommonCB", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_PIXEL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH);
    commonCB.AddProp(sizeof(float) * 4);
    commonCB.InitBaseRegisterSettings(0, 0);

    ShaderPropRange MainTexSlot("MainTexSlot", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_PIXEL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT);
    MainTexSlot.PropNum = 1;
    MainTexSlot.InitBaseRegisterSettings(0, 0);

    ShaderTable* table = new ShaderTable();
    table->AddRange(commonCB);
    table->AddRange(MainTexSlot);
    shaderLayout->Slots[0] = table;

    std::string shaderFilePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\GUI\\GUIDefault", "hlsl");
    DefaultShader = new Shader(shaderFilePath, "VSMain", "PSMain");
    DefaultShader->InitVertexDescriptor(vertexDesc);
    DefaultShader->InitLayout(shaderLayout);

    SharedMaterial = new Material("UI Default", DefaultShader, cmdBuffer);
#pragma endregion

    g_guiSystem = new GUISystem(width, height, cmdBuffer);
    return g_guiSystem;
}

GUISystem* GUISystem::SharedInstance()
{
    return g_guiSystem;
}

GUISystem::GUISystem(_uint width, _uint height, Graphics::CommandBuffer* cmdBuffer)
{
    _Width = width;
    _Height = height;
    _CmdBuffer = cmdBuffer;
#ifdef GRAPHICS_DX
    PlatformBridge = new GUISystemDX12Bridge();
#endif

}

void GUISystem::RunLoopInvoke(void* msg)
{
    if (!msg)
    {
        return;
    }
    ((GUISystemDX12Bridge*)PlatformBridge)->RunLoopInvoke(msg);

    for (int i = 0; i < _RegedGUIComp.size(); i++)
    {
        _RegedGUIComp[i]->DrawView(_CmdBuffer);
    }
}

void GUISystem::FrameToNDC(Math::rect_float frame, Math::rect_float& NDC)
{
    NDC.width = frame.width / (float)_Width * 2.0f;
    NDC.height = frame.height / (float)_Height * 2.0f;

    NDC.left = frame.left / (float)_Width * 2.0f - 1.0f;
    NDC.top = frame.top / (float)_Height * 2.0f - 1.0f;
}

void GUISystem::RegGUIComponent(GUIBase* comp)
{
    _RegedGUIComp.push_back(comp);
}