//
//  GraphicsResourceMetalBridge.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "GraphicsResourceMetalBridge.hpp"
#include "GraphicsResourceMetalAdapter.hpp"
#include <Material/GraphicsResource.hpp>

using namespace MaterialSys;

GraphicsResourceMetalBridge::GraphicsResourceMetalBridge(bool initResource)
{
    type = GraphicsResourceType::Default;
    shouldInitResource = initResource;
}

void GraphicsResourceMetalBridge::InitAsConstantBuffer(UINT bufferSize)
{
    type = GraphicsResourceType::CBV;
    raw_obj = createConstantBufferMetal(bufferSize, shouldInitResource);
}

void GraphicsResourceMetalBridge::InitAsDefault(UINT bufferSize)
{
    raw_obj = createDefaultBufferMetal(bufferSize, shouldInitResource);
}

void GraphicsResourceMetalBridge::SetResource(void* res, bool shouldUnmap)
{
    setResourceMetal(raw_obj, res, shouldUnmap);
}
