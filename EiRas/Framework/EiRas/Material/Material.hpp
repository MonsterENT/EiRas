//
//  Material.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "Shader.hpp"
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>

namespace Graphics {
class GraphicsRenderState;
}

namespace MaterialSys {

class Material
{
public:
    Material(std::string name, Shader* shader);
    Graphics::GraphicsRenderState* RenderState;
    
    void FinishStateChange();
private:
    Shader* shader;
    EiRasPlatformBridgeProtocol* PlatformBridge;
};

};//namespace Material

#endif /* Material_hpp */
