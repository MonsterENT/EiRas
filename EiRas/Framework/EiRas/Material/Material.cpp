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
#include <Graphics/CommandBuffer.hpp>

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/MaterialMetalBridge.hpp>
#endif

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/MaterialDX12Bridge.h>
#endif

using namespace Graphics;
using namespace MaterialSys;

Material::Material(std::string Name, Shader* shader, Graphics::CommandBuffer* commandBuffer)
{
    this->Name = Name;
    this->RenderState = new GraphicsRenderState();
    
#if GRAPHICS_METAL
    this->PlatformBridge = new MaterialMetalBridge(Name);
#endif
    
#if GRAPHICS_DX
    this->PlatformBridge = new MaterialDX12Bridge(Name, shader->PlatformBridge);
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
                tmpMatProp = new MaterialProp(tmpProp->PropName, tmpProp->PropType, tmpProp->Visibility, true, tmpProp->BufferSize);
                tmpMatProp->SlotID = i;
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
#if GRAPHICS_DX
                    tmpMatProp = new MaterialProp(tmpProp->PropName, tmpProp->PropType, tmpProp->Visibility, true, tmpProp->BufferSize);
#elif GRAPHICS_METAL
                    tmpMatProp = new MaterialProp(tmpProp->PropName, tmpProp->PropType, tmpProp->Visibility, false, tmpProp->BufferSize);
#endif
                    tmpMatProp->SlotID = -1;
                    Props.push_back(tmpMatProp);
                    tmpMatProps[propIndex] = tmpMatProp;
                    tmpResArray[propIndex] = tmpMatProp->Resource;
                }
                MaterialTable* matTable = new MaterialTable(shaderTable->PropNum, tmpMatProps);
                matTable->SlotID = i;
                LayoutTables.push_back(matTable);
                delete [] tmpResArray;
                delete [] tmpMatProps;
            }
        }
    }
    
    referenceCmdBuffer = commandBuffer;
    
    if (commandBuffer == 0)
    {
        commandBuffer->RegMaterial(this);
    }
    
    //init platform pso
    FinishStateChange();
}

void Material::SetProperty(int propertyId, void* res)
{
    if (propertyId >= Props.size())
    {
        return;
    }
#if GRAPHICS_DX
    ((MaterialDX12Bridge*)PlatformBridge)->SetProperty(Props[propertyId], res);
#endif
    
#if GRAPHICS_METAL
    ((MaterialMetalBridge*)PlatformBridge)->SetProperty(Props[propertyId], res);
#endif
}

void Material::FinishStateChange()
{
#if GRAPHICS_METAL
    ((MaterialMetalBridge*)this->PlatformBridge)->UpdateRenderState(RenderState, shader);
#endif
    
#if GRAPHICS_DX
    ((MaterialDX12Bridge*)this->PlatformBridge)->UpdateRenderState(RenderState, shader->PlatformBridge);
#endif
    
}

Material::~Material()
{
    if (referenceCmdBuffer)
    {
        referenceCmdBuffer->RemoveMaterial(this);
    }
}
