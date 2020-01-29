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

GraphicsResourceMetalBridge::GraphicsResourceMetalBridge(std::string name, bool initResource)
{
    type = GraphicsResourceType::Default;
    this->name = name;
    shouldInitResource = initResource;
}

void GraphicsResourceMetalBridge::InitAsConstantBuffer(_uint bufferSize)
{
    type = GraphicsResourceType::CBV;
    raw_obj = createConstantBufferMetal(name, bufferSize, shouldInitResource);
}

void GraphicsResourceMetalBridge::InitAsDefault(_uint bufferSize)
{
    raw_obj = createDefaultBufferMetal(name, bufferSize, shouldInitResource);
}

void GraphicsResourceMetalBridge::SetResource(void* res)
{
    setResourceMetal(raw_obj, res);
}
