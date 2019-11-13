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

namespace Graphics {

class GraphicsRenderSate;
class Material;
class Mesh;

class CommandBuffer
{
public:
    CommandBuffer(std::string name);
    
    void SetGraphicsRenderState(GraphicsRenderSate* renderState);//render pass & pipleline state
    void SetMaterial(Material* material);//resources
    
    void DrawMesh(Mesh* mesh);
    
private:
    EiRasPlatformBridgeProtocol* PlatformBridge;
};

}

#endif /* CommandBuffer_hpp */
