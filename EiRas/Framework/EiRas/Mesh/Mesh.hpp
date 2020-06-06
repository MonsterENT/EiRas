//
//  Mesh.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/18/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp


#include <string>
#include <Material/GraphicsResource.hpp>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

#include <Global/GlobalDefine.h>
#include <vector>

namespace MaterialSys
{
    class GraphicsResource;
}

namespace Math {
    class float2;
    class float3;
    class float4;
}

namespace MeshSys {

    enum class MeshType
    {
        VertexInput3D = 0,
        VertexInput2D = 1,
    };
    
#pragma region TOFIX
    class MeshBuffer
    {
    public:
        MaterialSys::GraphicsResource* Buffer;
        _uint BufferStride;
        _uint BufferSize;
        _uint BufferUsed;

        bool IsValide(_uint size, _uint stride)
        {
            if (BufferStride == stride)
            {
                if (BufferSize - BufferUsed >= size)
                {
                    return true;
                }
            }

            return false;
        }
    };
    class MeshBufferManager
    {
    public:

        static MeshBufferManager* GetManager();
        std::vector<MeshBuffer> VertexBufferPool;
        std::vector<MeshBuffer> IndexBufferPool;

        MeshBuffer* GetValideVertexBufferWithSize(_uint size, _uint stride)
        {
            return GetValideBufferWithSize(&VertexBufferPool, size, stride);
        }

        MeshBuffer* GetValideIndexBufferWithSize(_uint size, _uint stride)
        {
            return GetValideBufferWithSize(&IndexBufferPool, size, stride);
        }

    private:
        MeshBuffer* GetValideBufferWithSize(std::vector<MeshBuffer>* pool, _uint size, _uint stride)
        {
            for (int i = 0; i < pool->size(); i++)
            {
                if ((*pool)[i].IsValide(size, stride))
                {
                    return &(*pool)[i];
                }
            }

            MeshBuffer t;
            t.BufferSize = size; // TO FIX
            t.BufferStride = stride;
            t.BufferUsed = size;
            pool->push_back(t);
            return &(pool->back());
        }
    };
#pragma endregion

    class Mesh;

    class SubMeshPackedData
    {
        friend Mesh;
    public:
        void* VertexData;
        _uint VertexDataSize;
        _uint VertexDataStride;

        _uint* IndexData;
        _uint IndexDataSize;
        _uint IndexDataStride;

        ~SubMeshPackedData()
        {
            delete[] VertexData;
            delete[] IndexData;
        }
    };

    class SubMesh
    {
        friend Mesh;
    public:
        _uint IndexCount;
        _uint VertexCount;
        Math::float3* PositionData;
        Math::float3* NormalData;
        Math::float2* UVData;
        Math::float4* ColorData;

        _uint VertexBufferRefIndex;
        _uint IndexBufferRefIndex;

        _uint IndexBufferStartLocation;


    private:
        SubMeshPackedData* _PackedData;

        void PackData(MeshType inputType)
        {
            if (_PackedData == 0)
            {
                _PackedData = new SubMeshPackedData();
                if (inputType == MeshType::VertexInput3D)
                {
                    _PackedData->VertexData = new VertexData3D[VertexCount];
                    _PackedData->VertexDataStride = sizeof(VertexData3D);
                }
                else
                {
                    _PackedData->VertexData = new VertexData2D[VertexCount];
                    _PackedData->VertexDataStride = sizeof(VertexData2D);
                }
                _PackedData->VertexDataSize = _PackedData->VertexDataStride * VertexCount;
                _PackedData->IndexDataStride = sizeof(_uint);
                _PackedData->IndexDataSize = sizeof(_uint) * IndexCount;
            }

            for (_uint i = 0; i < VertexCount; i++)
            {
                if (inputType == MeshType::VertexInput3D)
                {
                    VertexData3D* tmpData = (VertexData3D*)_PackedData->VertexData + i;
                    if (PositionData)
                        tmpData->Position = float3(PositionData[i].x, PositionData[i].y, PositionData[i].z);
                    if (UVData)
                        tmpData->UV = float2(UVData[i].x, UVData[i].y);
                    if (NormalData)
                        tmpData->Normal = float3(NormalData[i].x, NormalData[i].y, NormalData[i].z);
                }
                else
                {
                    VertexData2D* tmpData = (VertexData2D*)_PackedData->VertexData + i;
                    if (PositionData)
                        tmpData->Position = float2(PositionData[i].x, PositionData[i].y);
                    if (UVData)
                        tmpData->UV = float2(UVData[i].x, UVData[i].y);
                }
            }
        }
    };

    class Mesh
    {
    public:
        Mesh(std::string name);

        void LoadDataFromFile(std::string fileName);

        std::string Name;

        void BuildBuffer(MeshType inputType = MeshType::VertexInput3D);

        EiRasPlatformBridgeProtocol* PlatformBridge;

        _uint SubMeshCount;
        SubMesh* SubMeshes;

    private:
    };

}

#endif /* Mesh_hpp */
