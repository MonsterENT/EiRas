//
//  MaterialMetalAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/13/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "MaterialMetalAdapter.hpp"
#include "MaterialMetal.h"
#include <OnMetal/MetalMacro.h>
#include <Material/Shader.hpp>
//#include <Material/PlatformDependency/Shader/Metal/ShaderMetal.h>

void* MaterialSys::createMaterialMetal(std::string name)
{
    MaterialMetal* oc_obj = [[MaterialMetal alloc]initWithName:[NSString stringWithUTF8String:name.c_str()]];
    PROCESS_OC_OBJ(oc_obj, bridgePtr)
    return bridgePtr;
}

void MaterialSys::UpdateRenderStateMetal(void* ptr, Graphics::GraphicsRenderState* renderState, Shader* shaderObj)
{
    MaterialMetal* _ptr = (__bridge MaterialMetal*)ptr;
    ShaderMetal* oc_obj_shader_metal = (__bridge ShaderMetal*)shaderObj->GetRawObj();
    [_ptr UpdateRenderState:renderState Shader:oc_obj_shader_metal];
}