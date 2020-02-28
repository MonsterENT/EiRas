//
//  ShaderMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "ShaderMetal.h"
#import <Global/EiRasGlobalManager.hpp>
#import <MetalKit/MetalKit.h>
#import <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetal.h>
#include <PlatformDependency/OnMetal/MetalMacro.h>
#include <Graphics/GraphicsVertexDescriptor.hpp>

@interface ShaderMetal()
@end

@implementation ShaderMetal

-(instancetype)initWithFileName:(NSString*)fileName vertexFuncName:(NSString*)vertexFuncName pixelFuncName:(NSString*)pixelFuncName
{
    if(self)
    {
        self = [super init];
        _fileName = fileName;
        _vertexFuncName = vertexFuncName;
        _pixelFuncName = pixelFuncName;
        GET_EIRAS_METAL(deviceObj)
        if(deviceObj)
        {
            id<MTLDevice> device = [deviceObj getMetalDevice];
            if(device)
            {
                id<MTLLibrary> defaultLibrary = [device newDefaultLibrary];
                _vertexFunc = [defaultLibrary newFunctionWithName:vertexFuncName];
                _pixelFunc = [defaultLibrary newFunctionWithName:pixelFuncName];
            }
        }
    }
    return self;
}

-(void)initVertexDescriptor:(void*)desc
{
    Graphics::GraphicsVertexDescriptor* _desc = (Graphics::GraphicsVertexDescriptor*)desc;
    _vertexDesc = [MTLVertexDescriptor vertexDescriptor];
    
    for(int i = 0; i < _desc->_AttributeIndex; i++)
    {
        _vertexDesc.attributes[i].offset = _desc->Attributes[i].Offset;
        _vertexDesc.attributes[i].format = (MTLVertexFormat)_desc->Attributes[i].AttributeFormat;
        _vertexDesc.attributes[i].bufferIndex = _desc->Attributes[i].BufferIndex;
    }
    
    for(int i = 0; i < _desc->_LayoutIndex; i++)
    {
        _vertexDesc.layouts[i].stepFunction = MTLVertexStepFunctionPerVertex;
        _vertexDesc.layouts[i].stepRate = 1;
        _vertexDesc.layouts[i].stride = _desc->Layouts[i].Stride;
    }
    
}

@end
