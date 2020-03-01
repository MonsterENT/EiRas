//
#include "MeshLoader.h"
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <vector>
#include <types.h>
#include <Mesh/Mesh.hpp>
#include <Global/PlatformDefine.h>
#include <Math/Math.hpp>

#include <Component/LogSys/LogManager.hpp>

#if GRAPHICS_DX
#pragma comment( lib,"assimp-vc140-mt.lib" )
#pragma comment( lib,"zlibstatic.lib" )
#endif

using namespace MeshSys;
using namespace Math;

void MeshSys::LoadMeshFromFile(std::string fileName, Mesh* meshObj)
{
    Assimp::Importer imp;
    const aiScene* pscene = imp.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    std::string tmpStr = imp.GetErrorString();
    if (pscene == 0)
    {
        return;
    }
    
    meshObj->SubMeshCount = pscene->mNumMeshes;
    if(meshObj->SubMeshCount <= 0)
    {
        return;
    }
    meshObj->SubMeshes = new SubMesh[meshObj->SubMeshCount];

    for (_uint i = 0; i < pscene->mNumMeshes; i++)
    {
        aiMesh* pmesh = pscene->mMeshes[i];
        SubMesh* submesh = &meshObj->SubMeshes[i];
        submesh->VerticesCount = pmesh->mNumVertices;
        submesh->PositionData = new float3[submesh->VerticesCount];
        submesh->NormalData = new float3[submesh->VerticesCount];
        submesh->UVData = new float2[submesh->VerticesCount];
        submesh->ColorData = new float4[submesh->VerticesCount];
        
        for (_uint j = 0; j < pmesh->mNumVertices; j++)
        {
            submesh->PositionData[j] = float3(pmesh->mVertices[j].x, pmesh->mVertices[j].y, pmesh->mVertices[j].z);
            submesh->NormalData[j] = float3(pmesh->mNormals[j].x, pmesh->mNormals[j].y, pmesh->mNormals[j].z);
            if (pmesh->HasTextureCoords(0))
            {
                submesh->UVData[j] = float2(pmesh->mTextureCoords[0][j].x, pmesh->mTextureCoords[0][j].y);
            }
        }

        submesh->IndicesCount = pmesh->mNumFaces * 3;
        submesh->IndicesData = new _uint[submesh->IndicesCount];
        _uint curIndex = 0;
        for (_uint k = 0; k < pmesh->mNumFaces; k++)
        {
            submesh->IndicesData[curIndex++] = pmesh->mFaces[k].mIndices[0];
            submesh->IndicesData[curIndex++] = pmesh->mFaces[k].mIndices[1];
            submesh->IndicesData[curIndex++] = pmesh->mFaces[k].mIndices[2];
        }
    }
    imp.FreeScene();
}

