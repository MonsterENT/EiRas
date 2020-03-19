//
//  ShaderResourceMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 3/8/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#import "ShaderResourceMetal.h"
#include <Global/EiRasGlobalManager.hpp>
#import <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetal.h>
#include <PlatformDependency/OnMetal/MetalMacro.h>
#include <Global/GlobalDefine.h>

@implementation ShaderResourceMetal

-(instancetype)initResource:(_uint)width height:(_uint)height texData:(void*) texData buildStatusFlag:(bool*)buildStatusFlag
{
    self = [super init];
    
    MTLTextureDescriptor* texDesc = [[MTLTextureDescriptor alloc]init];
    texDesc.pixelFormat = MTLPixelFormatBGRA8Unorm;
    texDesc.width = width;
    texDesc.height = height;
//    texDesc.storageMode = MTLStorageModeShared; \
    In iOS and tvOS, the default value is MTLStorageModeShared. In macOS, the default value is MTLStorageModeManaged.
    
    GET_EIRAS_METAL(deviceObj)
    self.rawTexture = [[deviceObj getMetalDevice] newTextureWithDescriptor:texDesc];
    
    MTLRegion region = {
        { 0, 0, 0 },                   // MTLOrigin
        {width, height, 1} // MTLSize
    };
    
    
    [self.rawTexture replaceRegion:region mipmapLevel:0 withBytes:texData bytesPerRow:4 * width];
    
    return self;
}

@end
