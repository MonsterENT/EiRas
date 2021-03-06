//
//  MeshMetalBridge.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/15/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "MeshMetalBridge.hpp"
#include "MeshMetalAdapter.hpp"
using namespace MeshSys;

MeshMetalBridge::MeshMetalBridge()
{
    raw_obj = createMeshMetal();
}


void MeshMetalBridge::BuildBuffer(EiRasPlatformBridgeProtocol* vertexResBridge, EiRasPlatformBridgeProtocol* indexResBridge, _uint vertexCount, _uint indexCount, _uint vertexBufferIndex, _uint indexBufferIndex)
{
    void* vertexResRawObj = 0;
    void* indexResRawObj = 0;
    
    if(vertexResBridge)
    {
        vertexResRawObj = vertexResBridge->raw_obj;
    }
    
    if(indexResBridge)
    {
        indexResRawObj = indexResBridge->raw_obj;
    }
    
    buildBufferMetal(raw_obj, vertexResRawObj, indexResRawObj, vertexCount, indexCount, vertexBufferIndex, indexBufferIndex);
}
