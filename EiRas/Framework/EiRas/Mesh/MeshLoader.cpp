//
#include "MeshLoader.h"
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <vector>
#include <types.h>
#include <Mesh/Mesh.hpp>

#include <Math/Math.hpp>

#include <Component/LogSys/LogManager.hpp>

#if GRAPHICS_DX
#pragma comment( lib,"assimp-vc140-mt.lib" )
#pragma comment( lib,"zlibstatic.lib" )
#endif

using namespace MeshSys;
using namespace Math;

#define COPYDATA(dst, src, type) if(src.size() > 0){ \
meshObj->dst = new type[src.size()]; \
memcpy(meshObj->dst, &src[0], sizeof(type) * src.size()); \
}

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

    meshObj->VertexCount = 0;
    meshObj->IndexCount = 0;

    std::vector<float3> positionData;
    std::vector<float3> normalData;
    std::vector<float2> uvData;
    std::vector<float4> colorData;
    std::vector<_uint> indexData;
    for (_uint i = 0; i < pscene->mNumMeshes; i++)
    {
        aiMesh* pmesh = pscene->mMeshes[i];
        meshObj->VertexCount += pmesh->mNumVertices;

        for (_uint j = 0; j < pmesh->mNumVertices; j++)
        {
            positionData.push_back(float3(pmesh->mVertices[j].x, pmesh->mVertices[j].y, pmesh->mVertices[j].z));
            normalData.push_back(float3(pmesh->mNormals[j].x, pmesh->mNormals[j].y, pmesh->mNormals[j].z));
            if (pmesh->HasTextureCoords(0))
            {
                uvData.push_back(float2(pmesh->mTextureCoords[0][j].x, pmesh->mTextureCoords[0][j].y));
            }
        }

        SubMesh* submesh = &meshObj->SubMeshes[i];
        submesh->IndexBufferStartIdx = indexData.size();
        _uint indexCount = 0;
        for (_uint k = 0; k < pmesh->mNumFaces; k++)
        {
            indexCount += 3;
            indexData.push_back(pmesh->mFaces[k].mIndices[0]);
            indexData.push_back(pmesh->mFaces[k].mIndices[1]);
            indexData.push_back(pmesh->mFaces[k].mIndices[2]);
        }

        meshObj->IndexCount += indexCount;
        submesh->IndexCount = indexCount;
    }

    COPYDATA(PositionData, positionData, float3);
    COPYDATA(NormalData, normalData, float3);
    COPYDATA(UVData, uvData, float2);
    COPYDATA(ColorData, colorData, float4);
    COPYDATA(IndexData, indexData, _uint);

    imp.FreeScene();
}

