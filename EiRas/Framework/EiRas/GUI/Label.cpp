#include "Label.hpp"
#include <Mesh/Mesh.hpp>
#include <GUI/GUISystem.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Material/Material.hpp>
#include <FontSys/FontManager.hpp>
#include "RuntimeUtilities.hpp"

using namespace MaterialSys;
using namespace Graphics;
using namespace MeshSys;
using namespace GUISys;
using namespace FontSys;
using namespace Math;

Label::Label()
{
    _Text = 0;
    _Render = new RenderData;
    SetTextColor(float4(0, 0, 0, 1));
}

void Label::SetText(FontSys::Text* text)
{
    _Text = text;
    _BuildTextMesh();
}

void Label::DrawView(Graphics::CommandBuffer* cmdBuffer)
{
    View::DrawView(cmdBuffer);
    cmdBuffer->DrawRenderData(_Render);
}

void Label::_BuildTextMesh()
{
    _Render->ClearMesh(true);
    _Render->ClearMaterials(true);

    _uint charCount = _Text->_FontMapIndex.size();
    float subMeshWidth = _NDC.width / (float)charCount;
    float subMeshHeight = _NDC.height;
    float posTop = _NDC.top;
    float posLeft = _NDC.left;

    Mesh* textMesh = new Mesh("TextMesh");

    _Render->SetMesh(textMesh);
    textMesh->SubMeshCount = charCount;
    textMesh->SubMeshes = new SubMesh[charCount];

    std::string matKey = _Text->RefTextStr + " Font Mat";
    for (int i = 0; i < charCount; i++)
    {
        Material* mat = RuntimeUtilities::CreateFontMaterial(matKey + std::to_string(i), GUISystem::SharedInstance()->_CmdBuffer);
        mat->SetProperty(FontManager::SharedInstance()->fontDataList[_Text->_FontMapIndex[i]]->_FontImage, 1, 0);
        mat->SetProperty(&_TextColor, 0, 0);
        _Render->AddMaterial(mat, 0);

        rect_float uvRect = _Text->_MappingRect[i];
        SubMesh* subMesh = &(textMesh->SubMeshes[i]);
        subMesh->IndicesCount = 6;
        subMesh->VerticesCount = 4;
        subMesh->IndicesData = new _uint[6]{ 0, 1, 2, 1, 2, 3 };
        subMesh->PositionData = new float3[4]{ {posLeft, posTop, 1}, {posLeft + subMeshWidth, posTop, 1}, {posLeft, posTop - subMeshHeight, 1}, {posLeft + subMeshWidth, posTop - subMeshHeight, 1} };
        subMesh->UVData = new float2[4]{ {uvRect.left, uvRect.top}, {uvRect.left + uvRect.width, uvRect.top}, {uvRect.left, uvRect.top + uvRect.height}, {uvRect.left + uvRect.width, uvRect.top + uvRect.height} };
        subMesh->NormalData = new float3[4]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

        posLeft += subMeshWidth;
    }
    textMesh->BuildBuffer(MeshType::VertexInput2D);
}