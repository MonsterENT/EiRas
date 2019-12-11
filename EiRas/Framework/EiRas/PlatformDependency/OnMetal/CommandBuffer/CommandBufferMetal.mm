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
#include <PlatformDependency/OnMetal/Material/ConstantBufferMetal.h>

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
    [_commandBuffer setLabel:name];
}

-(id<MTLCommandBuffer>)getCmdBuffer
{
    GET_EIRAS_METAL(deviceObj)
    _commandBuffer = [[deviceObj getMetalCommandQueue] commandBuffer];
    return _commandBuffer;
}

-(void)setMaterial:(MaterialMetal*)material props:(std::vector<MaterialSys::MaterialProp*>*)props tables:(std::vector<MaterialSys::MaterialTable*>*)tables
{
    if(_renderCommandEncoder)
    {
        [_renderCommandEncoder endEncoding];
    }
    GET_EIRAS_METAL(deviceObj)
    _renderCommandEncoder = [_commandBuffer renderCommandEncoderWithDescriptor:[deviceObj getMTKView].currentRenderPassDescriptor];
    [_renderCommandEncoder setRenderPipelineState:material.pipelineState];
    
    for(int i = 0; i < props->size(); i++)
    {
        if((*props)[i]->PropType == GraphicsResourceType::CBV)
        {
            ConstantBufferMetal* cbObj = (__bridge ConstantBufferMetal*)(*props)[i]->Resource->PlatformBridge->raw_obj;
            [_renderCommandEncoder setVertexBuffer:cbObj.rawBuffer offset:0 atIndex:(*props)[i]->SlotID];
            [_renderCommandEncoder setFragmentBuffer:cbObj.rawBuffer offset:0 atIndex:(*props)[i]->SlotID];
        }
    }
}

-(void)drawMesh:(void*)meshData dataSize:(int)dataSize index:(int)index
{
    [_renderCommandEncoder setVertexBytes:meshData length:dataSize atIndex:index];
    [_renderCommandEncoder drawPrimitives:MTLPrimitiveTypeTriangle
                              vertexStart:0
                              vertexCount:3];
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
    if(present)
    {
        if(_renderCommandEncoder)
        {
            [_renderCommandEncoder setViewport:(MTLViewport){0.0, 0.0, 1600, 1200, 0.0, 1.0 }];
            [_renderCommandEncoder setCullMode:MTLCullModeBack];
            [_renderCommandEncoder endEncoding];
            _renderCommandEncoder = nullptr;
        }
        GET_EIRAS_METAL(deviceObj)
        [_commandBuffer presentDrawable:[deviceObj getMTKView].currentDrawable];
    }
    [_commandBuffer commit];
    _commandBuffer = nullptr;
}
@end
