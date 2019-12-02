//
//  CommandBufferMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "CommandBufferMetal.h"
#import <GraphicsAPI/PlatformDependency/Metal/EiRasMetal.h>
#include <OnMetal/MetalMacro.h>
#include <Global/EiRasGlobalManager.hpp>

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

-(void)setMaterial:(MaterialMetal*)material
{
    if(_renderCommandEncoder)
    {
        [_renderCommandEncoder endEncoding];
    }
    GET_EIRAS_METAL(deviceObj)
    _renderCommandEncoder = [_commandBuffer renderCommandEncoderWithDescriptor:[deviceObj getMTKView].currentRenderPassDescriptor];
    [_renderCommandEncoder setRenderPipelineState:material.pipelineState];
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
    [self getCmdBuffer];
}

-(void)present
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

-(void)commit
{
    [_commandBuffer commit];
    _commandBuffer = nullptr;
}
@end
