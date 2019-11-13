//
//  EiRasMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OnMetal/BaseMetalObject.h>

@interface EiRasMetal : BaseMetalObject

+(void)SetMetalKitView:(nonnull MTKView*)mtkView;

-(void)InitDevice;

-(void)OnUpdate;

-(nullable id<MTLDevice>)getMetalDevice;
-(nullable id<MTLCommandQueue>)getMetalCommandQueue;

@end
