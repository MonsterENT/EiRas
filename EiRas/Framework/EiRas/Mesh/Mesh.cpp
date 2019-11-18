//
//  Mesh.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/18/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Mesh.hpp"


using MeshSys::Mesh;

static AAPLVertex triangleVertices[] =
{
    // 2D positions,    RGBA colors
    { {  250,  -250 }, { 1, 0, 0, 1 } },
    { { -250,  -250 }, { 0, 1, 0, 1 } },
    { {    0,   250 }, { 0, 0, 1, 1 } },
};

Mesh::Mesh(std::string name)
{
    
}

AAPLVertex* Mesh::GetVertices()
{
    return triangleVertices;
}

int Mesh::GetMeshDataSize()
{
    return sizeof(triangleVertices);
}
