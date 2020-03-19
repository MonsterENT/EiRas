//
//  CommandBufferMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "CommandBufferMetalAdapter.hpp"
#import "CommandBufferMetal.h"
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <PlatformDependency/OnMetal/MetalMacro.h>
#include <Material/Material.hpp>

using namespace MaterialSys;

void* Graphics::createCommandBufferMetal(std::string name)
{
    CommandBufferMetal* oc_obj = [CommandBufferMetal new];
    [oc_obj setLabel:[NSString stringWithUTF8String:name.c_str()]];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}

void Graphics::setMaterialMetal(void* ptr, Material* material)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj setMaterial:material];
}

void Graphics::drawMeshMetal(void* ptr, void* meshObj)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    
    id meshRawObj = nullptr;
    
    if(meshObj)
    {
        meshRawObj = (__bridge id)((EiRasPlatformBridgeProtocol*)meshObj)->raw_obj;
    }
    [oc_obj drawMesh:meshRawObj];
}

void Graphics::beginFrameMetal(void* ptr)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj beginFrame];
}

void Graphics::resetCmdBufferMetal(void* ptr)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj reset];
}

void Graphics::commitMetal(void* ptr, bool present)
{
    CommandBufferMetal* oc_obj = (__bridge CommandBufferMetal*)ptr;
    [oc_obj commit:present];
}

