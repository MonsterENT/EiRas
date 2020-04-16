#include "Label.hpp"
#include <Mesh/Mesh.hpp>

using namespace MeshSys;
using namespace GUISys;
using namespace FontSys;
using namespace Math;

Label::Label()
{
    _Text = 0;
}

void Label::SetText(FontSys::Text* text)
{
    _Text = text;
    _BuildTextMesh();
}

void Label::_BuildTextMesh()
{
    _uint charCount = _Text->_FontMapIndex.size();
    float subMeshWidth = _Frame.width / (float)charCount;
    float subMeshHeight = _Frame.height;
    float posTop = _Frame.top;
    float posLeft = _Frame.left;

    /*Mesh* mesh = (Mesh*)_Mesh;
    mesh->SubMeshCount = charCount;
    mesh->SubMeshes = new SubMesh[charCount];
    for (int i = 0; i < charCount; i++)
    {
        rect_float uvRect = _Text->_MappingRect[i];

        SubMesh* subMesh = &(mesh->SubMeshes[i]);
        subMesh->IndicesCount = 6;
        subMesh->VerticesCount = 4;
        subMesh->IndicesData = new _uint[6]{ 0, 1, 2, 1, 2, 3 };
        subMesh->PositionData = new float3[4]{ {posLeft, posTop, 1}, {posLeft + subMeshWidth, posTop, 1}, {posLeft, posTop - subMeshHeight, 1}, {posLeft + subMeshWidth, posTop - subMeshHeight, 1} };
        subMesh->UVData = new float2[4]{ {uvRect.left, uvRect.top}, {uvRect.left + uvRect.width, uvRect.top}, {uvRect.left, uvRect.top + uvRect.height}, {uvRect.left + uvRect.width, uvRect.top + uvRect.height} };
        subMesh->NormalData = new float3[4]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    }*/
}