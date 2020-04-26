#include "RuntimeUtilities.hpp"
#include <Graphics/GraphicsRenderState.hpp>

#include <FileSys/FileManager.hpp>

using namespace FileSys;
using namespace GUISys;

Material* RuntimeUtilities::_GUIDefaultMaterial = 0;
Shader* RuntimeUtilities::_GUIDefaultShader = 0;
Shader* RuntimeUtilities::_FontShader = 0;
GraphicsVertexDescriptor* RuntimeUtilities::_DefaultVertexDesc = 0;
ShaderLayout* RuntimeUtilities::_DefaultShaderLayout = 0;

ShaderLayout* RuntimeUtilities::GetDefaultShaderLayout()
{
    if (_DefaultShaderLayout == 0)
    {
        _DefaultShaderLayout = new ShaderLayout(2);

        ShaderPropRange commonCB("CommonCB", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_PIXEL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH);
        commonCB.AddProp(sizeof(float) * 4);
        commonCB.InitBaseRegisterSettings(0, 0);

        ShaderPropRange MainTexSlot("MainTexSlot", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_PIXEL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT);
        MainTexSlot.PropNum = 1;
        MainTexSlot.InitBaseRegisterSettings(0, 0);

        ShaderTable* table0 = new ShaderTable();
        table0->AddRange(commonCB);
        ShaderTable* table1 = new ShaderTable();
        table1->AddRange(MainTexSlot);
        _DefaultShaderLayout->Slots[0] = table0;
        _DefaultShaderLayout->Slots[1] = table1;
    }
    return _DefaultShaderLayout;
}
GraphicsVertexDescriptor* RuntimeUtilities::GetDefaultVertexDesc()
{
    if (_DefaultVertexDesc == 0)
    {
        _DefaultVertexDesc = new GraphicsVertexDescriptor();
        _DefaultVertexDesc->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
        _DefaultVertexDesc->AddBufferAttribute("TEXCOORD", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
        _DefaultVertexDesc->InitBufferLayout();
    }
    return _DefaultVertexDesc;
}

Material* RuntimeUtilities::GetGUIDefaultMaterial(CommandBuffer* cmdBuffer)
{
    if (_GUIDefaultMaterial == 0)
    {
        _GUIDefaultMaterial = new Material("UI Default", GetGUIDefaultShader(), cmdBuffer);
        _GUIDefaultMaterial->RenderState->_CullMode = CullMode::CullModeNone;
        _GUIDefaultMaterial->RenderState->_ZWrite = false;
        _GUIDefaultMaterial->RenderState->_ZTest = CompareFunction::CompareFunctionAlways;
    }
    return _GUIDefaultMaterial;
}

Shader* RuntimeUtilities::GetGUIDefaultShader()
{
    if (_GUIDefaultShader == 0)
    {
        std::string shaderFilePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\GUI\\GUIDefault", "hlsl");
        _GUIDefaultShader = new Shader(shaderFilePath, "VSMain", "PSMainBaseColor");
        #pragma region Pass1
            _GUIDefaultShader->AddVertexFuncToPass("VSMainSSUV", 1);
            _GUIDefaultShader->AddPixelFuncToPass("PSMainUseTex", 1);
        #pragma endregion
        _GUIDefaultShader->InitVertexDescriptor(GetDefaultVertexDesc());
        _GUIDefaultShader->InitLayout(GetDefaultShaderLayout());
    }
    return _GUIDefaultShader;
}

Material* RuntimeUtilities::CreateGUIDefaultMaterial(std::string name, CommandBuffer* cmdBuffer)
{
    Material* mat = new Material(name, GetGUIDefaultShader(), cmdBuffer);
    mat->RenderState->_CullMode = CullMode::CullModeNone;
    mat->RenderState->_ZWrite = false;
    mat->RenderState->_ZTest = CompareFunction::CompareFunctionAlways;
    return mat;
}

Shader* RuntimeUtilities::GetFontShader()
{
    if (_FontShader == 0)
    {
        std::string shaderFilePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\GUI\\GUIFont", "hlsl");
        _FontShader = new Shader(shaderFilePath, "VSMain", "PSMain");
        _FontShader->InitVertexDescriptor(GetDefaultVertexDesc());
        _FontShader->InitLayout(GetDefaultShaderLayout());
    }
    return _FontShader;
}

Material* RuntimeUtilities::CreateFontMaterial(std::string name, CommandBuffer* cmdBuffer)
{
    Material* mat = new Material(name, GetFontShader(), cmdBuffer);
    mat->RenderState->_CullMode = CullMode::CullModeNone;
    mat->RenderState->_ZWrite = false;
    mat->RenderState->_ZTest = CompareFunction::CompareFunctionAlways;
    mat->RenderState->_BlendSrcRGBFactor = BlendFactor::BlendRGBFactorSourceAlpha;
    mat->RenderState->_BlendDstRGBFactor = BlendFactor::BlendRGBFactorOneMinusSourceAlpha;
    return mat;
}