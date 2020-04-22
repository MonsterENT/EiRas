#include "RenderData.hpp"
#include <Material/Material.hpp>
#include <Mesh/Mesh.hpp>

using namespace MaterialSys;
using namespace MeshSys;
using namespace Graphics;

void RenderData::ClearMesh(bool release)
{
    if (release)
    {
        delete m_Mesh;
    }
    m_Mesh = 0;
}

void RenderData::ClearMaterials(bool release)
{
    if (release)
    {
        for (int i = 0; i < _MaterialList.size(); i++)
        {
            delete _MaterialList[i].m_Material;
        }
    }
    _MaterialList.clear();
}