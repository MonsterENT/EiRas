//
//  Material.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Material.hpp"
#include "Shader.hpp"
#include "ShaderLayout.h"
#include <Graphics/GraphicsRenderState.hpp>

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/MaterialMetalBridge.hpp>
#endif

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/MaterialDX12Bridge.h>
#endif

using Graphics::GraphicsRenderState;

using MaterialSys::Material;
using MaterialSys::Shader;
using MaterialSys::ShaderLayout;

Material::Material(std::string name, Shader* shader)
{
    this->RenderState = new GraphicsRenderState();

#if GRAPHICS_METAL
    this->PlatformBridge = new MaterialMetalBridge(name);
#endif

#if GRAPHICS_DX
    this->PlatformBridge = new MaterialDX12Bridge(name, shader);
#endif

    this->shader = shader;

    if(shader->Layout != 0)
    {
        for (int i = 0; i < shader->Layout->SlotNum; i++)
         {
             ShaderSlot* shaderSlot = shader->Layout->Slots[i];
             MaterialProp* tmpMatProp = 0;
             if (shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Prop)
             {
                 ShaderProp* tmpProp = (ShaderProp*)shaderSlot;
                 tmpMatProp = new MaterialProp(tmpProp->PropType, tmpProp->BufferSize);
                 tmpMatProp->SlotID = tmpProp->PropID;
                 Props.push_back(tmpMatProp);
                 LayoutProps.push_back(tmpMatProp);
             }
             else if (shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Table)
             {
                 ShaderTable* shaderTable = (ShaderTable*)shaderSlot;

                 GraphicsResource** tmpResArray = new GraphicsResource * [shaderTable->PropNum];
                 MaterialProp** tmpMatProps = new MaterialProp*[shaderTable->PropNum];
                 for (int propIndex = 0; propIndex < shaderTable->PropNum; propIndex++)
                 {
                     ShaderProp* tmpProp = shaderTable->Props[propIndex];
                     tmpMatProp = new MaterialProp(tmpProp->PropType, tmpProp->BufferSize);
                     tmpMatProp->SlotID = tmpProp->PropID;
                     Props.push_back(tmpMatProp);
                     tmpMatProps[propIndex] = tmpMatProp;
                     tmpResArray[propIndex] = tmpMatProp->Resource;
                 }
                 MaterialTable* matTable = new MaterialTable(shaderTable->PropNum, tmpMatProps, tmpResArray);
                 LayoutTables.push_back(matTable);
                 delete [] tmpResArray;
                 delete [] tmpMatProps;
             }
         }
    }
    
    //init platform pso
    FinishStateChange();
}

void Material::SetProperty(int propertyId, void* res)
{
#if GRAPHICS_DX
    ((MaterialDX12Bridge*)PlatformBridge)->SetProperty(propertyId, res);
#endif
}

void Material::FinishStateChange()
{
#if GRAPHICS_METAL
    ((MaterialMetalBridge*)this->PlatformBridge)->UpdateRenderState(RenderState, shader);
#endif

}
