//
//  MeshMetalAdapter.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/15/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef MeshMetalAdapter_hpp
#define MeshMetalAdapter_hpp

#include <Global/GlobalDefine.h>

namespace MeshSys {

void* createMeshMetal();

void buildBufferMetal(void* ptr, void* vertexRes, void* indexRes, _uint vertexCount, _uint indexCount, _uint vertexBufferIndex, _uint indexBufferIndex);
}

#endif /* MeshMetalAdapter_hpp */
