//
//  EiRasMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "EiRasMetalAdapter.hpp"
#import "EiRasMetal.h"
#include <PlatformDependency/OnMetal/MetalMacro.h>

void* GraphicsAPI::createMetal()
{
    EiRasMetal* oc_obj = [EiRasMetal new];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}

void GraphicsAPI::initMetalDevice(void* ptr)
{
    EiRasMetal* _ptr = (__bridge EiRasMetal*)ptr;
    [_ptr InitDevice];
}

void OnUpdateMetal(void* ptr)
{
    EiRasMetal* _ptr = (__bridge EiRasMetal*)ptr;
    [_ptr OnUpdate];
}
