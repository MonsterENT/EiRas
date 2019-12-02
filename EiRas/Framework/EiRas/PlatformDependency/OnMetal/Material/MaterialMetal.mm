//
//  MaterialMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/13/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "MaterialMetal.h"
#include <Global/EiRasGlobalManager.hpp>
#include <OnMetal/MetalMacro.h>

@implementation MaterialMetal

-(instancetype)initWithName:(NSString*)name
{
    if(self)
    {
        self = [super init];
        _name = name;
    }
    return self;
}

-(void)UpdateRenderState:(Graphics::GraphicsRenderState*)renderState Shader:(ShaderMetal*)shaderObj
{
    NSError* errorCode = NULL;
    GET_EIRAS_METAL(deviceObj)
    
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = _name;
    pipelineStateDescriptor.vertexFunction = shaderObj.vertexFunc;
    pipelineStateDescriptor.fragmentFunction = shaderObj.pixelFunc;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
    pipelineStateDescriptor.colorAttachments[0].blendingEnabled = (renderState->_BlendSrcRGBFactor + renderState->_BlendDstRGBFactor) > 1 || (renderState->_BlendSrcAlphaFactor + renderState->_BlendDstAlphaFactor) > 1;
    pipelineStateDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactor(renderState->_BlendSrcRGBFactor);
    pipelineStateDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactor(renderState->_BlendDstRGBFactor);
    pipelineStateDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactor(renderState->_BlendSrcAlphaFactor);
        pipelineStateDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactor(renderState->_BlendDstAlphaFactor);
    _pipelineState = [[deviceObj getMetalDevice] newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
                                                                                error:&errorCode];
    
    _renderPassDescriptor = [deviceObj getMTKView].currentRenderPassDescriptor;
}

@end
