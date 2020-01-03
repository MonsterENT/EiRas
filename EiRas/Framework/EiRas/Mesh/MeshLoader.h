#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

#include <string>

namespace MeshSys
{
    class Mesh;
    void LoadMeshFromFile(std::string fileName, Mesh* meshObj);
}
#endif
