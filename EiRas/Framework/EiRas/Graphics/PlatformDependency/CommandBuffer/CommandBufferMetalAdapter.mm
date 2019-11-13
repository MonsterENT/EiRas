//
//  CommandBufferMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "CommandBufferMetalAdapter.hpp"
#import "CommandBufferMetal.h"
#include <OnMetal/MetalMacro.h>

void* Graphics::createCommandBufferMetal(std::string name)
{
    CommandBufferMetal* oc_obj = [CommandBufferMetal new];
    [oc_obj setLabel:[NSString stringWithUTF8String:name.c_str()]];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}
