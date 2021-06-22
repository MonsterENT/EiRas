#include "View.hpp"
#include <Mesh/Mesh.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <GUI/GUISystem.hpp>
#include <Material/Material.hpp>
#include "RuntimeUtilities.hpp"
#include <Graphics/GraphicsRenderState.hpp>

using namespace MeshSys;
using namespace GUISys;
using namespace Math;
using namespace Graphics;
using namespace MaterialSys;

View::View()
{
    GUISystem::SharedInstance()->RegGUIComponent(this);
    _Mesh = new MeshSys::Mesh("GUI Mesh");
    _Material = RuntimeUtilities::CreateGUIDefaultMaterial("GUI View");
    SetBackgroundColor(float4(1, 1, 1, 1));
    _UseShaderPass = 0;
}

void View::SetBackgroundImage(Graphics::RenderTexture* rt)
{
    _Material->SetProperty(rt, 1, 0);
    _UseShaderPass = 1;
}

void View::SetBackgroundColor(Math::float4 color)
{
    _BackgroundColor = color;
}

void View::SetFrame(Math::rect_float frame)
{
    GUIBase::SetFrame(frame);
}

void View::NeedLayout()
{
    GUIBase::NeedLayout();
    Mesh* mesh = (Mesh*)_Mesh;
    mesh->SubMeshCount = 1;
    mesh->SubMeshes = new SubMesh[1];

    SubMesh* subMesh = &(mesh->SubMeshes[0]);
    subMesh->IndexCount = 6;
    subMesh->IndexBufferStartIdx = 0;
    mesh->SetVertexData(new float3[4]{ {_NDC.left, _NDC.top, 1}, {_NDC.left + _NDC.width, _NDC.top, 1}, {_NDC.left, _NDC.top - _NDC.height, 1}, {_NDC.left + _NDC.width, _NDC.top - _NDC.height, 1} },
        new float2[4]{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, 4);
    mesh->SetIndexData(new _uint[6]{ 0, 1, 2, 1, 2, 3 }, 6);
    mesh->BuildBuffer(MeshType::VertexInput2D);
}

void View::DrawView(Graphics::CommandBuffer* cmdBuffer)
{
    _Material->RenderState->EnableCommonBlend(_BackgroundColor.w - 0.999f < 0);
    _Material->SetProperty(&_BackgroundColor, 0, 0);
    _Material->FinishStateChange(_UseShaderPass);
    cmdBuffer->SetMaterial(_Material, _UseShaderPass);
    cmdBuffer->DrawMesh((Mesh*)_Mesh);
}