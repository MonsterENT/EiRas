//
//  Mesh.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/18/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Mesh.hpp"


using MeshSys::Mesh;

#if GRAPHICS_METAL
static AAPLVertex triangleVertices[] =
{
    // 2D positions,    RGBA colors
    { {  250,  -250 }, { 1, 0, 0, 1 } },
    { { -250,  -250 }, { 0, 1, 0, 1 } },
    { {    0,   250 }, { 0, 0, 1, 1 } },
};
#endif

Mesh::Mesh(std::string Name)
{
    
}

#if GRAPHICS_METAL
AAPLVertex* Mesh::GetVertices()
{
    return triangleVertices;
}
#endif
int Mesh::GetMeshDataSize()
{
#if GRAPHICS_METAL
    return sizeof(triangleVertices);
#endif
    return 0;
}
