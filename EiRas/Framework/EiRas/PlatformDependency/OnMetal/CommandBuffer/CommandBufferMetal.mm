//
//  CommandBufferMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "CommandBufferMetal.h"
#import <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetal.h>
#include <PlatformDependency/OnMetal/MetalMacro.h>
#include <Global/EiRasGlobalManager.hpp>
#include <Material/MaterialLayout.hpp>
#import "GraphicsResourceMetal.h"
#import <PlatformDependency/OnMetal/Mesh/MeshMetal.h>

using namespace MaterialSys;

@interface CommandBufferMetal()
@property(strong, nonatomic)id<MTLCommandBuffer> commandBuffer;
@end

@implementation CommandBufferMetal

-(instancetype)init
{
    if(self)
    {
        self = [super init];
    }
    return self;
}

-(void)setLabel:(NSString*)name
{
    _name = name;
}

-(id<MTLCommandBuffer>)getCmdBuffer
{
    GET_EIRAS_METAL(deviceObj)
    _commandBuffer = [[deviceObj getMetalCommandQueue] commandBuffer];
    [_commandBuffer setLabel:_name];
    return _commandBuffer;
}

-(void)_BindProp:(MaterialProp*)prop
{
    if(!prop)
    {
        return;
    }
    GraphicsResourceMetal* rawResourceObj = (__bridge GraphicsResourceMetal*)prop->Resource->PlatformBridge->raw_obj;
    if(prop->Resource->Behaviors.Visibility == GraphicsResourceVisibility::VISIBILITY_ALL || prop->Resource->Behaviors.Visibility == GraphicsResourceVisibility::VISIBILITY_VERTEX)
    {
        if(prop->Resource->Behaviors.ResourceType == GraphicsResourceType::CBV)
        {
            [_renderCommandEncoder setVertexBuffer:rawResourceObj.rawBuffer offset:0 atIndex:prop->SlotID];
        }
        else if(prop->Resource->Behaviors.ResourceType == GraphicsResourceType::SRV)
        {
            //for srv texture
            [_renderCommandEncoder setVertexTexture:rawResourceObj.rawTexture atIndex:prop->SlotID];
        }
        
    }
    if(prop->Resource->Behaviors.Visibility == GraphicsResourceVisibility::VISIBILITY_ALL || prop->Resource->Behaviors.Visibility == GraphicsResourceVisibility::VISIBILITY_PIXEL)
    {
        if(prop->Resource->Behaviors.ResourceType == GraphicsResourceType::CBV)
        {
            [_renderCommandEncoder setFragmentBuffer:rawResourceObj.rawBuffer offset:0 atIndex:prop->SlotID];
        }
        else if(prop->Resource->Behaviors.ResourceType == GraphicsResourceType::SRV)
        {
            [_renderCommandEncoder setFragmentTexture:rawResourceObj.rawTexture atIndex:prop->SlotID];
        }
    }
}

-(void)setMaterial:(MaterialSys::Material*)material
{
    if(_renderCommandEncoder)
    {
        [_renderCommandEncoder endEncoding];
    }
    GET_EIRAS_METAL(deviceObj)
    
    MaterialMetal* matRawObj = (__bridge MaterialMetal*)material->PlatformBridge->raw_obj;
    
    _renderCommandEncoder = [_commandBuffer renderCommandEncoderWithDescriptor:[deviceObj getMTKView].currentRenderPassDescriptor];
    [_renderCommandEncoder setLabel:[NSString stringWithFormat:@"Render Pass Set Material : %@", matRawObj.name]];
    [_renderCommandEncoder setRenderPipelineState:matRawObj.pipelineState];
    
    for(int i = 0; i < material->materialLayout->SlotNum; i++)
    {
        MaterialSlot* slot = material->materialLayout->Slots[i];
        if(slot->SlotType == MaterialSlotType::MaterialSlotType_Prop)
        {
            [self _BindProp:(MaterialProp*)slot];
        }
        else if(slot->SlotType == MaterialSlotType::MaterialSlotType_Table)
        {
            MaterialTable* table = (MaterialTable*)slot;
            for(int propIndex = 0; propIndex < table->PropNum; propIndex++)
            {
                [self _BindProp:table->Props[propIndex]];
            }
        }
    }
}

-(void)drawMesh:(MeshMetal*)meshObj
{
    [_renderCommandEncoder setVertexBuffer:meshObj.vertexBuffer offset:0 atIndex:meshObj.vertexBufferIndex];
    [_renderCommandEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangleStrip indexCount:meshObj.indexCount indexType:MTLIndexTypeUInt32 indexBuffer:meshObj.indexBuffer indexBufferOffset:0];
}

-(void)beginFrame
{
    
}

-(void)reset
{
    [self getCmdBuffer];
}

-(void)commit:(bool)present
{
    if(_renderCommandEncoder)
    {
        [_renderCommandEncoder setViewport:(MTLViewport){0.0, 0.0, 1600, 1200, 0.0, 1.0 }];
        [_renderCommandEncoder setCullMode:MTLCullModeBack];
        [_renderCommandEncoder endEncoding];
        _renderCommandEncoder = nullptr;
    }
    if(present)
    {
        GET_EIRAS_METAL(deviceObj)
        [_commandBuffer presentDrawable:[deviceObj getMTKView].currentDrawable];
    }
    [_commandBuffer commit];
    _commandBuffer = nullptr;
}
@end
