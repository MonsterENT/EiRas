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
class MaterialProp;
class MaterialTable;
}

namespace Graphics {

void* createCommandBufferMetal(std::string name);

void setMaterialMetal(void* ptr, void* material_raw_obj, std::vector<MaterialSys::MaterialProp*>* props, std::vector<MaterialSys::MaterialTable*>* tables);

void drawMeshMetal(void* ptr, void* meshData, int dataSize, int index);

void beginFrameMetal(void* ptr);

void presentMetal(void* ptr);

void commitMetal(void* ptr);

}

#endif /* CommandBufferMetalAdapter_hpp */
