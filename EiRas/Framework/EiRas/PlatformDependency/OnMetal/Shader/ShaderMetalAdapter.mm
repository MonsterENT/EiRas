//
//  ShaderMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "ShaderMetalAdapter.hpp"
#include <PlatformDependency/OnMetal/MetalMacro.h>

#import "ShaderMetal.h"

void* MaterialSys::createShaderMetal(std::string fileName, std::string vertexFuncName, std::string pixelFuncName)
{
    ShaderMetal* oc_obj = [[ShaderMetal alloc]initWithFileName:[NSString stringWithUTF8String:fileName.c_str()] vertexFuncName:[NSString stringWithUTF8String:vertexFuncName.c_str()] pixelFuncName:[NSString stringWithUTF8String:pixelFuncName.c_str()]];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}
