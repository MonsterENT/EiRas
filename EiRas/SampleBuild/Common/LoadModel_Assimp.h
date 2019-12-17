#pragma once

#include <Importer.hpp>      // 导入器在该头文件中定义
#include <scene.h>           // 读取到的模型数据都放在scene中
#include <postprocess.h>     // 该头文件中包含后处理的标志位定义

#include<string.h>
#include<vector>
#include<types.h>

using std::string;

namespace MeshSys
{
    class Mesh;
    static void LoadMeshFromFile(string fileName)
    {
        //Assimp::Importer imp;
        //const aiScene* pscene = imp.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
        //if (pscene == 0)
        //{
        //    return 0;
        //}
        //EiRasMesh* mesh = new EiRasMesh();

        //EiRasMesh::SubMesh* combinedMesh = new EiRasMesh::SubMesh[pscene->mNumMeshes];
        //mesh->combinedMesh = combinedMesh;
        //mesh->subMeshCount = pscene->mNumMeshes;

        //int f = 0;
        //for (int i = 0; i < pscene->mNumMeshes; i++)
        //{
        //    aiMesh* pmesh = pscene->mMeshes[i];

        //    EiRasMesh::SubMesh* submesh = &combinedMesh[i];
        //    submesh->vertexCount = pmesh->mNumVertices;
        //    submesh->vertices = new EiRasConst_dx12::VertexDefault[submesh->vertexCount];
        //    for (int j = 0; j < pmesh->mNumVertices; j++)
        //    {
        //        EiRasConst_dx12::VertexDefault* vertex = &submesh->vertices[j];
        //        vertex->POSITION = XMFLOAT3(pmesh->mVertices[j].x, pmesh->mVertices[j].y, pmesh->mVertices[j].z);
        //        //char codes[100];
        //        //sprintf_s(codes, "%f %f %f\n", vertex->POSITION.x, vertex->POSITION.y, vertex->POSITION.z);
        //        //OutputDebugStringA(codes);
        //        vertex->NORMAL = XMFLOAT3(pmesh->mNormals[j].x, pmesh->mNormals[j].y, pmesh->mNormals[j].z);
        //    }

        //    submesh->indexCount = pmesh->mNumFaces * 3;
        //    submesh->indices = new UINT32[submesh->indexCount];
        //    UINT32 curIndex = 0;
        //    for (int k = 0; k < pmesh->mNumFaces; k++)
        //    {
        //        submesh->indices[curIndex++] = pmesh->mFaces[k].mIndices[0];
        //        submesh->indices[curIndex++] = pmesh->mFaces[k].mIndices[1];
        //        submesh->indices[curIndex++] = pmesh->mFaces[k].mIndices[2];
        //    }
        //}
        //return mesh;
    }
}
