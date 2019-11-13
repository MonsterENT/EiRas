//
//  CommandBufferMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "CommandBufferMetal.h"
#import <GraphicsAPI/PlatformDependency/Metal/EiRasMetal.h>

#include <Global/EiRasGlobalManager.hpp>

@implementation CommandBufferMetal

-(instancetype)init
{
    if(self)
    {
        self = [super init];
        EiRasMetal* deviceObj = (__bridge EiRasMetal*)EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsAPIDevice;
        _commandBuffer = [[deviceObj getMetalCommandQueue] commandBuffer];
    }
    return self;
}

-(void)setLabel:(NSString*)name
{
    [_commandBuffer setLabel:name];
}

@end
