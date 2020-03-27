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

    class Mesh;

class SubMesh
{
public:
    _uint IndicesCount;
    _uint* IndicesData;
    
    _uint VerticesCount;
    Math::float3* PositionData;
    Math::float3* NormalData;
    Math::float2* UVData;
    Math::float4* ColorData;

    MaterialSys::GraphicsResource* VertexBuffer;
    MaterialSys::GraphicsResource* IndexBuffer;

    void* TriangleData;
    _uint TriangleDataSize;

    _uint IndexDataSize;
};

class Mesh
{
public:
    Mesh(std::string name);
    
    void LoadDataFromFile(std::string fileName);

    std::string Name;

    void BuildBuffer();

    EiRasPlatformBridgeProtocol* PlatformBridge;

    _uint SubMeshCount;
    SubMesh* SubMeshes;
    
private:
   
};

}

#endif /* Mesh_hpp */
