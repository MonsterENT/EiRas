//
//  MaterialMetalAdapter.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/13/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef MaterialMetalAdapter_hpp
#define MaterialMetalAdapter_hpp

#include <string>

namespace Graphics {
class GraphicsRenderState;
}

namespace MaterialSys {
class Shader;
class MaterialProp;
void* createMaterialMetal(std::string name);

void setPropertyMetal(void* ptr, MaterialProp* prop, void* res);

void UpdateRenderStateMetal(void* ptr, Graphics::GraphicsRenderState* renderState, Shader* shaderObj);

}

#endif /* MaterialMetalAdapter_hpp */
