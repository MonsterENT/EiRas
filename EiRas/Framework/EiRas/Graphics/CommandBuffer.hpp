//
//  CommandBuffer.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef CommandBuffer_hpp
#define CommandBuffer_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>


namespace MaterialSys {
class Material;
}

namespace MeshSys {
class Mesh;
}

namespace Graphics {

class GraphicsRenderSate;

class CommandBuffer
{
public:
    CommandBuffer(std::string name);
    
    void SetMaterial(MaterialSys::Material* material);
    
    void DrawMesh(MeshSys::Mesh* mesh);
    
    void BeginFrame();
    
    void Present();
    
    void Commit();
    
private:
    EiRasPlatformBridgeProtocol* PlatformBridge;
};

}

#endif /* CommandBuffer_hpp */
