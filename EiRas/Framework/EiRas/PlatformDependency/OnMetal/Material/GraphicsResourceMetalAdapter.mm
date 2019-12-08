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

void* MaterialSys::createConstantBufferMetal(int bufferSize)
{
    ConstantBufferMetal* oc_obj = [ConstantBufferMetal new];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}
