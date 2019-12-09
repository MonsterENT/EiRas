//
//  ConstantBufferMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "ConstantBufferMetal.h"
#include <Global/EiRasGlobalManager.hpp>
#import <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetal.h>
#include <PlatformDependency/OnMetal/MetalMacro.h>

@implementation ConstantBufferMetal

-(instancetype)initWithBufferSize:(int)bufferSize allocMemory:(bool)allocMemory
{
    self = [super init];
    if(self)
    {
        if(allocMemory)
        {
            GET_EIRAS_METAL(deviceObj)
            _rawBuffer = [[deviceObj getMetalDevice] newBufferWithLength:bufferSize options:MTLResourceStorageModeShared];
        }
        _bufferSize = bufferSize;
        
        
    }
    return self;
}

@end
