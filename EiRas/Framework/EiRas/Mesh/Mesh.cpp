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

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Mesh/MeshMetalBridge.hpp>
#endif

using namespace MaterialSys;
#if GRAPHICS_DX
using namespace Graphics;
#endif

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
    { { 0.5, -0.5, 0.5 }, { 0, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0 } },
    { { -0.5, -0.5, 0.5 }, { 0, 0 }, { 0, 1, 0, 1 }, { 1, 0, 0 } },
    { { 0, 0.5, 0.5 }, { 0, 0 }, { 0, 0, 1, 1 }, { 1, 0, 0 } }
};
#endif

Mesh::Mesh(std::string Name)
{
    VertexBuffer = new GraphicsResource(Name, GraphicsResourceType::Default, true, GetMeshDataSize());
    VertexBuffer->SetResource(GetVertices(), true);

#if GRAPHICS_DX
    PlatformBridge = new MeshDX12Bridge(VertexBuffer->PlatformBridge, NULL, 3, -1);
#endif
    
#if GRAPHICS_METAL
    PlatformBridge = new MeshMetalBridge(VertexBuffer->PlatformBridge, nullptr, 3, 0, 0, 0);
#endif
}

void* Mesh::GetVertices()
{
    return triangleVertices;
}

_uint Mesh::GetMeshDataSize()
{
    return sizeof(triangleVertices);
}
