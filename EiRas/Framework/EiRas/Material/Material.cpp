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
#include <Basic/Image.hpp>

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Material/MaterialMetalBridge.hpp>
#endif

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Material/MaterialDX12Bridge.h>
#endif

using namespace Graphics;
using namespace MaterialSys;
using namespace ImageSys;

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
        _uint slotNum = shader->Layout->SlotNum;
        materialLayout = new MaterialLayout(slotNum);
        for (int i = 0; i < slotNum; i++)
        {
            ShaderSlot* shaderSlot = shader->Layout->Slots[i];
            MaterialProp* tmpMatProp = 0;
            if (shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Prop)
            {
                ShaderProp* tmpProp = (ShaderProp*)shaderSlot;
                tmpMatProp = new MaterialProp(tmpProp->PropName, tmpProp->PropType, tmpProp->Visibility, tmpProp->UpdateFreq, true, tmpProp->BufferSize);
                tmpMatProp->SlotID = i;
                materialLayout->Slots[i] = tmpMatProp;
            }
            else if (shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Table)
            {
                ShaderTable* shaderTable = (ShaderTable*)shaderSlot;
                
                _uint ranegNum = shaderTable->Ranges.size();

                std::vector<MaterialProp*>* tmpMatProps = new std::vector<MaterialProp*>();
                for (_uint ranegIndex = 0; ranegIndex < ranegNum; ranegIndex++)
                {
                    ShaderPropRange* tmpRange = &shaderTable->Ranges[ranegIndex];

                    for (_uint propIndex = 0; propIndex < tmpRange->PropNum; propIndex++)
                    {
#if GRAPHICS_DX
                        if (tmpRange->PropType == GraphicsResourceType::SRV)
                        {
                            tmpMatProp = new MaterialProp(tmpRange->BasePropName, tmpRange->PropType, tmpRange->Visibility, tmpRange->UpdateFreq, false, -1);
                        }
                        else
                        {
#pragma message("TODO")
                            tmpMatProp = new MaterialProp(tmpRange->BasePropName, tmpRange->PropType, tmpRange->Visibility, tmpRange->UpdateFreq, true, tmpRange->BufferSizeList[propIndex]);
                        }
#elif GRAPHICS_METAL
                        tmpMatProp = new MaterialProp(tmpProp->BasePropName, tmpProp->PropType, tmpProp->Visibility, false, tmpProp->BufferSize);
#endif
                        tmpMatProp->SlotID = -1;
                        tmpMatProps->push_back(tmpMatProp);
                    }
                }
                MaterialTable* matTable = new MaterialTable(tmpMatProps->size(), (MaterialProp**)&tmpMatProps[0]);
                matTable->SlotID = i;
                materialLayout->Slots[i] = matTable;
            }
        }
    }
    
    //init platform pso
    FinishStateChange();

    referenceCmdBuffer = commandBuffer;

    if (commandBuffer == 0)
    {
        commandBuffer->RegMaterial(this);
    }
}

inline MaterialProp* getMaterialProp(Material* mat, _uint slotIndex, _uint propIndex, bool &fromTable)
{
    fromTable = false;
    if (!mat->materialLayout)
    {
        return 0;
    }

    if (slotIndex >= mat->materialLayout->SlotNum)
    {
        return 0;
    }

    MaterialProp* tProp = 0;
    MaterialSlot* tSlot = mat->materialLayout->Slots[slotIndex];
    if (tSlot->SlotType == MaterialSlotType::MaterialSlotType_Table)
    {
        MaterialTable* tTable = (MaterialTable*)tSlot;
        if (propIndex >= tTable->PropNum || propIndex < 0)
        {
            return 0;
        }

        tProp = tTable->Props[propIndex];
        fromTable = true;
    }
    else
    {
        tProp = (MaterialProp*)tSlot;
    }
    return tProp;
}

void Material::SetProperty(void* res, _uint slotIndex, int propIndex)
{
    bool fromTable = false;
    MaterialProp* tProp = getMaterialProp(this, slotIndex, propIndex, fromTable);
    if (tProp == 0)
    {
        return;
    }
#if GRAPHICS_DX
    ((MaterialDX12Bridge*)PlatformBridge)->SetProperty(tProp, res);
#endif
    
#if GRAPHICS_METAL
    ((MaterialMetalBridge*)PlatformBridge)->SetProperty(tProp, res);
#endif
}

void Material::SetProperty(ImageSys::Image* image, _uint slotIndex, int propIndex)
{
    bool fromTable = false;
    MaterialProp* tProp = getMaterialProp(this, slotIndex, propIndex, fromTable);
    if (tProp == 0)
    {
        return;
    }
    tProp->Resource = image->PipelineResource;
    if (fromTable)
    {
        referenceCmdBuffer->_DynamicFillHeap(tProp);
    }
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
