#ifndef Render_Data_Hpp
#define Render_Data_Hpp

#include <string>
#include <vector>
#include <Global/GlobalDefine.h>

namespace MeshSys
{
    class Mesh;
}

namespace MaterialSys
{
    class Material;
}

namespace Graphics
{
    typedef struct RenderMaterialPassData
    {
        MaterialSys::Material* m_Material;
        _uint Pass;
        RenderMaterialPassData(MaterialSys::Material* mat, _uint pass = 0)
        {
            m_Material = mat;
            Pass = pass;
        }
    } RenderMaterialPassData;

    class RenderData
    {
    public:

        void AddMesh(MeshSys::Mesh* mesh)
        {
            m_Meshes.push_back(mesh);
        }

        void AddMaterial(MaterialSys::Material* mat, _uint pass = 0)
        {
            SetMaterial(mat, _MaterialList.size(), pass);
        }

        void SetMaterial(MaterialSys::Material* mat, _uint subIndex, _uint pass = 0)
        {
            if (subIndex < 0)
            {
                return;
            }
            if (subIndex >= _MaterialList.size())
            {
                _MaterialList.push_back(RenderMaterialPassData(mat, pass));
            }
            else
            {
                _MaterialList[subIndex] = RenderMaterialPassData(mat, pass);
            }
        }

        void ClearMesh(bool release);

        void ClearMaterials(bool release);

        std::vector<MeshSys::Mesh*> m_Meshes;
        std::vector<RenderMaterialPassData> _MaterialList;
    };
}

#endif