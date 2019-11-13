//
//  EiRasMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "EiRasMetal.h"

static MTKView* g_mtkView = 0;

@interface EiRasMetal()

@property(strong, nonatomic)id<MTLCommandQueue> cmdQueue;

@property(strong, nonatomic)id<MTLDevice> metalDevice;

@end

@implementation EiRasMetal

+(void)SetMetalKitView:(nonnull MTKView*)mtkView
{
    g_mtkView = mtkView;
}

-(void)InitDevice
{
    if(g_mtkView)
    {
        _metalDevice = g_mtkView.device;
        _cmdQueue = [_metalDevice newCommandQueue];
        _cmdQueue.label = @"EiRasDefalutCommandQueue";
    }
}

-(nullable id<MTLDevice>)getMetalDevice
{
    return _metalDevice;
}

-(nullable id<MTLCommandQueue>)getMetalCommandQueue
{
    return _cmdQueue;
}

-(void)OnUpdate
{
    
}
@end
