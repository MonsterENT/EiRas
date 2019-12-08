//
//  Mesh.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/18/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <Global/PlatformDefine.h>
#include <string>

#if GRAPHICS_METAL
#include <ShaderFile/Metal/MetalGraphicsPipelineInput.h>
#endif



namespace MeshSys {

class Mesh
{
public:
    Mesh(std::string name);
#if GRAPHICS_METAL
    AAPLVertex* GetVertices();
#endif

    int GetMeshDataSize();
};

}

#endif /* Mesh_hpp */
