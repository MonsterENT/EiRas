//
//  Mesh.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/18/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Mesh.hpp"

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Mesh/MeshDX12Bridge.h>
#endif

using MaterialSys::Mesh;
using namespace Graphics;

#if GRAPHICS_METAL
static AAPLVertex triangleVertices[] =
{
    // 2D positions,    RGBA colors
    { {  250,  -250 }, { 1, 0, 0, 1 } },
    { { -250,  -250 }, { 0, 1, 0, 1 } },
    { {    0,   250 }, { 0, 0, 1, 1 } },
};
#endif

#if GRAPHICS_DX
static VertexDefault triangleVertices[] =
{
    { { 250, -250, 0.5 }, { 0, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0 } },
    { { -250, -250, 0.5 }, { 0, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0 } },
    { { 0, 250, 0.5 }, { 0, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0 } }
};
#endif

Mesh::Mesh(std::string Name)
{
    VertexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, GetMeshDataSize());
    VertexBuffer->SetResource(GetVertices(), true);

#if GRAPHICS_DX
    PlatformBridge = new MeshDX12Bridge(VertexBuffer->PlatformBridge, NULL);
#endif
}

void* Mesh::GetVertices()
{
    return triangleVertices;
}

int Mesh::GetMeshDataSize()
{
#if GRAPHICS_METAL
    return sizeof(triangleVertices);
#endif
    return 0;
}
