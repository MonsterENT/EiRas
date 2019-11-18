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
#include <ShaderFile/Metal/MetalGraphicsPipelineInput.h>

namespace MeshSys {

class Mesh
{
public:
    Mesh(std::string name);
    
    AAPLVertex* GetVertices();
    
    int GetMeshDataSize();
};

}

#endif /* Mesh_hpp */
