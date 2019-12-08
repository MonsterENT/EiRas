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

void* MaterialSys::createResourceHeapMetal(int resCount, GraphicsResource** resArray)
{

    NSMutableArray* tmpArray = [NSMutableArray array];
    for(int i = 0; i < resCount; i++)
    {
        GraphicsResource* resObj = resArray[i];
        [tmpArray addObject:(__bridge id)resObj->PlatformBridge->raw_obj];
    }
    
    GraphicsResourceHeapMetal* oc_obj = [[GraphicsResourceHeapMetal alloc]initWithGraphicsResource:tmpArray];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}
