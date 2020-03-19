//
//  CommandBufferMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PlatformDependency/OnMetal/BaseMetalObject.h>

#import <Metal/Metal.h>

#import <PlatformDependency/OnMetal/Material/MaterialMetal.h>

#include <vector>

#include <Material.hpp>

#import "MeshMetal.h"

NS_ASSUME_NONNULL_BEGIN

@interface CommandBufferMetal : BaseMetalObject

@property(strong, nonatomic)id<MTLRenderCommandEncoder> renderCommandEncoder;

@property(copy, nonatomic)NSString* name;

-(void)setMaterial:(MaterialSys::Material*)material;

-(void)drawMesh:(MeshMetal*)meshObj;

-(void)beginFrame;

-(void)reset;

-(void)commit:(bool)present;

@end

NS_ASSUME_NONNULL_END
