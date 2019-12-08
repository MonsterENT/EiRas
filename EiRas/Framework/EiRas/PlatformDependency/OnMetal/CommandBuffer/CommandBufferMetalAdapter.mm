//
//  CommandBufferMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "CommandBufferMetalAdapter.hpp"
#import "CommandBufferMetal.h"
#include <PlatformDependency/OnMetal/MetalMacro.h>

void* Graphics::createCommandBufferMetal(std::string name)
{
    CommandBufferMetal* oc_obj = [CommandBufferMetal new];
    [oc_obj setLabel:[NSString stringWithUTF8String:name.c_str()]];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}

void Graphics::setMaterialMetal(void* ptr, void* material_raw_obj)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj setMaterial:(__bridge MaterialMetal*)material_raw_obj];
}

void Graphics::drawMeshMetal(void* ptr, void* meshData, int dataSize, int index)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj drawMesh:meshData dataSize:dataSize index:index];
}

void Graphics::beginFrameMetal(void* ptr)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj beginFrame];
}

void Graphics::presentMetal(void* ptr)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj present];
}

void Graphics::commitMetal(void* ptr)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj commit];
}

