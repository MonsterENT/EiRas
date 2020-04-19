#include "View.hpp"
#include <Mesh/Mesh.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <GUI/GUISystem.hpp>
#include <Material/Material.hpp>

using namespace MeshSys;
using namespace GUISys;
using namespace Math;
using namespace Graphics;
using namespace MaterialSys;

View::View()
{
    _Mesh = new MeshSys::Mesh("GUI Mesh");
    _Material = GUISystem::SharedMaterial;
}

void View::SetFrame(Math::rect_float frame)
{
    GUIBase::SetFrame(frame);

    Mesh* mesh = (Mesh*)_Mesh;
    mesh->SubMeshCount = 1;
    mesh->SubMeshes = new SubMesh[1];

    SubMesh* subMesh = &(mesh->SubMeshes[0]);
    subMesh->IndicesCount = 6;
    subMesh->VerticesCount = 4;
    subMesh->IndicesData = new _uint[6]{ 0, 1, 2, 1, 2, 3 };
    subMesh->PositionData = new float3[4]{ {_NDC.left, _NDC.top, 1}, {_NDC.left + _NDC.width, _NDC.top, 1}, {_NDC.left, _NDC.top - _NDC.height, 1}, {_NDC.left + _NDC.width, _NDC.top - _NDC.height, 1} };
    subMesh->UVData = new float2[4]{ {0, 0}, {1, 0}, {0, 1}, {1, 1} };
    subMesh->NormalData = new float3[4]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    mesh->BuildBuffer(MeshType::VertexInput2D);
}

void View::DrawView(Graphics::CommandBuffer* cmdBuffer)
{
    _Material->FinishStateChange();
    cmdBuffer->SetMaterial(_Material);
    cmdBuffer->DrawMesh((Mesh*)_Mesh);
}