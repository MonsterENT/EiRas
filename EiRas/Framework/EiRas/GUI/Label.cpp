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
}

void Label::_BuildTextMesh()
{
    //Mesh* mesh = (Mesh*)_Mesh;
    //mesh->SubMeshCount = _Text->_FontMapIndex.size();
    //SubMesh** subMeshes = new SubMesh * [mesh->SubMeshCount];
    //for (int i = 0; i < _Text->_FontMapIndex.size(); i++)
    //{
    //    Math::rect_float uvRect = _Text->_MappingRect[i];
    //    SubMesh* subMesh = new SubMesh();
    //    subMesh->IndicesCount = 6;
    //    subMesh->VerticesCount = 4;
    //    subMesh->IndicesData = new _uint[6]{ 0, 1, 2, 2, 0, 3 };
    //    subMesh->PositionData = new float3[4]{ {-1, 1, 1}, {1, 1, 1}, {1, -1, 1}, {-1, -1, 1} };
    //    subMesh->UVData = new float2[4]{ {0, 0}, {1, 0}, {1, 1}, {0, 1} };
    //    subMesh->NormalData = new float3[4]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    //    mesh->SubMeshes = subMesh;
    //}
}