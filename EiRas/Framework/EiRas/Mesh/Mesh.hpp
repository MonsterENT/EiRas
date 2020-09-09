//
//  Mesh.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/18/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <Common/CommonMacro.hpp>
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
    class VertexData3D;
    class VertexData2D;
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

        MeshBuffer()
        {
            Buffer = 0;
            BufferStride = 0;
            BufferSize = 0;
            BufferUsed = 0;
        }

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
        std::vector<MeshBuffer*> VertexBufferPool;
        std::vector<MeshBuffer*> IndexBufferPool;

        MeshBuffer* GetValideVertexBufferWithSize(_uint size, _uint stride)
        {
            return GetValideBufferWithSize(&VertexBufferPool, size, stride);
        }

        MeshBuffer* GetValideIndexBufferWithSize(_uint size, _uint stride)
        {
            return GetValideBufferWithSize(&IndexBufferPool, size, stride);
        }

    private:
        MeshBuffer* GetValideBufferWithSize(std::vector<MeshBuffer*>* pool, _uint size, _uint stride)
        {
            //for (int i = 0; i < pool->size(); i++)
            //{
            //    if ((*pool)[i].IsValide(size, stride))
            //    {
            //        return &(*pool)[i];
            //    }
            //}

            MeshBuffer* t = new MeshBuffer();
            t->BufferSize = size; // TO FIX
            t->BufferStride = stride;
            t->BufferUsed = size;
            pool->push_back(t);
            return (pool->back());
        }
    };
#pragma endregion

    class Mesh;

    class MeshPackedData
    {
        friend Mesh;
    public:
        void* VertexData;
        _uint VertexDataSize;
        _uint VertexDataStride;

        _uint* IndexData;
        _uint IndexDataSize;
        _uint IndexDataStride;

        MeshPackedData()
        {
            VertexData = 0;
            VertexDataSize = 0;
            VertexDataStride = 0;

            IndexData = 0;
            IndexDataSize = 0;
            IndexDataStride = 0;
        }

        ~MeshPackedData()
        {
            if (VertexData != 0)
            {
                delete[] VertexData;
            }
        }

        void Reset()
        {
            if (VertexData != 0)
            {
                delete[] VertexData;
            }
            VertexData = 0;
            IndexData = 0;
            VertexDataSize = 0;
            VertexDataStride = 0;
            IndexDataSize = 0;
            IndexDataStride = 0;
        }
    };

    class SubMesh
    {
    public:
        _uint IndexCount;
        _uint IndexBufferStartIdx;
    private:
    };

    class Mesh
    {
    public:
        Mesh(std::string name);

        void LoadDataFromFile(std::string fileName);

        std::string Name;

        void BuildBuffer(MeshType inputType = MeshType::VertexInput3D, bool noMoreUpdate = true);

        EiRasPlatformBridgeProtocol* PlatformBridge;

        _uint SubMeshCount;
        SubMesh* SubMeshes;

        void SetVertexData(Math::float3* position, _uint count);
        void SetVertexData(Math::float3* position, Math::float2* uv, _uint count);
        void SetIndexData(_uint* index, _uint count);

        void SetVertexData(std::vector<Math::float3> position, std::vector<Math::float2> uv);
        void SetVertexData(std::vector<Math::float3> position, std::vector<Math::float3> normal, std::vector<Math::float2> uv);
        void SetVertexData(std::vector<Math::float3> position, std::vector<Math::float3> normal, std::vector<Math::float2> uv, std::vector<Math::float4> color);
        void SetIndexData(std::vector<_uint> index);

        Math::float3* GetPositionData(int &count);

    protected:

        _uint VertexCount;
        _uint IndexCount;

        Math::float3* PositionData;
        Math::float3* NormalData;
        Math::float2* UVData;
        Math::float4* ColorData;
        _uint* IndexData;

        MeshBuffer* _VertexBuffer, * _IndexBuffer;
        MeshPackedData* _PackedData;
        void PackData(MeshType inputType);
    private:

    };

}

#endif /* Mesh_hpp */
