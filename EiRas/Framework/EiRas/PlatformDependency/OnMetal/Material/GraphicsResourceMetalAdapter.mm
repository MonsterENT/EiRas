//
//  GraphicsResourceMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "GraphicsResourceMetalAdapter.hpp"
#include <PlatformDependency/OnMetal/MetalMacro.h>
#import "ConstantBufferMetal.h"
#import "GraphicsResourceMetal.h"

void* MaterialSys::createConstantBufferMetal(std::string name, int bufferSize, bool initResource)
{
    ConstantBufferMetal* oc_obj = [[ConstantBufferMetal alloc]initWithBufferSize:bufferSize initResource:initResource];
    [oc_obj setLabel:[NSString stringWithUTF8String:name.c_str()]];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}

void* MaterialSys::createDefaultBufferMetal(std::string name, int bufferSize, bool initResource)
{
    GraphicsResourceMetal* oc_obj = [[GraphicsResourceMetal alloc]initWithBufferSize:bufferSize initResource:initResource];
    [oc_obj setLabel:[NSString stringWithUTF8String:name.c_str()]];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}

void MaterialSys::setResourceMetal(void* ptr, void* res)
{
    GraphicsResourceMetal* oc_obj = (__bridge GraphicsResourceMetal*)ptr;
    [oc_obj setResource:res];
}
