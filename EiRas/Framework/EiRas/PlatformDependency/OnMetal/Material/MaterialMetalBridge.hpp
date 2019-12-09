//
//  MaterialMetalBridge.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/13/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef MaterialMetalBridge_hpp
#define MaterialMetalBridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

#include <string>

namespace Graphics {
class GraphicsRenderState;
}

namespace MaterialSys {
class Shader;
class MaterialProp;
class MaterialMetalBridge : public EiRasPlatformBridgeProtocol
{
public:
    MaterialMetalBridge(std::string name);
    void SetProperty(MaterialProp* prop, void* res);
    void UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj);
};

}

#endif /* MaterialMetalBridge_hpp */
