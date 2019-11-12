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

#import <GraphicsAPI/PlatformDependency/Metal/EiRasMetal.h>

@interface ShaderMetal()

@property(copy, nonatomic)NSString* fileName;
@property(copy, nonatomic)NSString* vertexFuncName;
@property(copy, nonatomic)NSString* pixelFuncName;

@property(strong, nonatomic)id<MTLFunction> vertexFunc;
@property(strong, nonatomic)id<MTLFunction> pixelFunc;

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
        EiRasMetal* deviceObj = (__bridge EiRasMetal*)EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsAPIDevice;
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

@end
