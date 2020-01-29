//
//  GraphicsResourceHeapMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "GraphicsResourceHeapMetalAdapter.hpp"
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnMetal/MetalMacro.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#import "GraphicsResourceHeapMetal.h"

using MaterialSys::GraphicsResource;

void* MaterialSys::createResourceHeapMetal(_uint propCount, _uint tableCount, MaterialTable** tableArray)
{
    GraphicsResourceHeapMetal* oc_obj = [[GraphicsResourceHeapMetal alloc] initWithPropCount:propCount tableCount:tableCount tableArray:tableArray];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    [oc_obj setLabel:@"GraphicsResourceHeap"];
    return bridgePtr;
}
