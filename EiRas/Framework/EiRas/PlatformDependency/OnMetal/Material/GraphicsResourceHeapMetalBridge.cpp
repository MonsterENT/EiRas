//
//  GraphicsResourceHeapMetalBridge.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "GraphicsResourceHeapMetalBridge.hpp"
#include "GraphicsResourceHeapMetalAdapter.hpp"
using namespace MaterialSys;

GraphicsResourceHeapMetalBridge::GraphicsResourceHeapMetalBridge(_uint propCount, _uint tableCount, MaterialTable** tableArray)
{
    raw_obj = createResourceHeapMetal(propCount, tableCount, tableArray);
}
