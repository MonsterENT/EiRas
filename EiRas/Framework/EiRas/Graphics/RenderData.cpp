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
        for (int i = 0; i < m_Meshes.size(); i++)
        {
            delete m_Meshes[i];
        }
    }
    m_Meshes.clear();
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