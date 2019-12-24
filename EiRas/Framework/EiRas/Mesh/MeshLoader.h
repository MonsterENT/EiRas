#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

#include<string.h>
#include<vector>
#include<types.h>

namespace MeshSys
{
    class Mesh;
    void LoadMeshFromFile(std::string fileName, Mesh* meshObj);
}
#endif
