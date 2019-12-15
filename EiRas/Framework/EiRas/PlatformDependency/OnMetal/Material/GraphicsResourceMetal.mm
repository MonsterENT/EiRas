//
//  GraphicsResourceMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "GraphicsResourceMetal.h"
#include <Global/EiRasGlobalManager.hpp>
#import <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetal.h>
#include <PlatformDependency/OnMetal/MetalMacro.h>

@implementation GraphicsResourceMetal

-(instancetype)initWithBufferSize:(_uint)bufferSize initResource:(bool)initResource
{
    self = [super init];
    if(self)
    {
        if(initResource)
        {
            GET_EIRAS_METAL(deviceObj)
            _rawBuffer = [[deviceObj getMetalDevice] newBufferWithLength:bufferSize options:MTLResourceStorageModeShared];
        }
        _bufferSize = bufferSize;
    }
    return self;
}

-(void)setResource:(void*)res
{
    memcpy(_rawBuffer.contents, res, _bufferSize);
}

@end
