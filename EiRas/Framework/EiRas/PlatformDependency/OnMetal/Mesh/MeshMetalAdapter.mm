//
//  MeshMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/15/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "MeshMetalAdapter.hpp"
#import "MeshMetal.h"
#import "MetalMacro.h"
#import "GraphicsResourceMetal.h"

void* MaterialSys::createMeshMetal(void* vertexRes, void* indexRes, _uint vertexCount, _uint indexCount, _uint vertexBufferIndex, _uint indexBufferIndex)
{
    MeshMetal* oc_obj = [[MeshMetal alloc]initWithVertexRes:(__bridge id)vertexRes indexRes:(__bridge id)indexRes vertexCount:vertexCount indexCount:indexCount vertexBufferIndex:vertexBufferIndex indexBufferIndex:indexBufferIndex];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}
