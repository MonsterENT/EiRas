//
//  CommandBuffer.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef CommandBuffer_hpp
#define CommandBuffer_hpp

namespace Graphics {

class GraphicsRenderSate;
class Material;
class Mesh;

class CommandBuffer
{
public:
    CommandBuffer()
    {
        
    }
    
    void SetGraphicsRenderState(GraphicsRenderSate* renderState);//render pass & pipleline state
    void SetMaterial(Material* material);//resources
    
    void DrawMesh(Mesh* mesh);
};

}

#endif /* CommandBuffer_hpp */
