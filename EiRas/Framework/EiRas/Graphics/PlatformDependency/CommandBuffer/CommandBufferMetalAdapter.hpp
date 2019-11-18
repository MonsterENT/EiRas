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

namespace Graphics {

void* createCommandBufferMetal(std::string name);

void setMaterialMetal(void* ptr, void* material_raw_obj);

void drawMeshMetal(void* ptr, void* meshData, int dataSize, int index);

void beginFrameMetal(void* ptr);

void presentMetal(void* ptr);

void commitMetal(void* ptr);

}

#endif /* CommandBufferMetalAdapter_hpp */
