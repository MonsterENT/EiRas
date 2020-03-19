//
//  CommandBufferMetalAdapter.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef CommandBufferMetalAdapter_hpp
#define CommandBufferMetalAdapter_hpp

#include <string>
#include <vector>

namespace MaterialSys {
class Material;
}

namespace Graphics {

void* createCommandBufferMetal(std::string name);

void setMaterialMetal(void* ptr, MaterialSys::Material* material);

void drawMeshMetal(void* ptr, void* meshObj);

void beginFrameMetal(void* ptr);

void resetCmdBufferMetal(void* ptr);

void commitMetal(void* ptr, bool present);

}

#endif /* CommandBufferMetalAdapter_hpp */
