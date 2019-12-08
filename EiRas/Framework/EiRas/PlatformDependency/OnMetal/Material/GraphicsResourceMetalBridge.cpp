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

GraphicsResourceMetalBridge::GraphicsResourceMetalBridge(GraphicsResourceType type, int bufferSize)
{
    if(type == GraphicsResourceType::CBV)
    {
        raw_obj = createConstantBufferMetal(bufferSize);
    }
}
