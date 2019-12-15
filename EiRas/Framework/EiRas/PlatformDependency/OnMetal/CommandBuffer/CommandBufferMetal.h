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

#import <PlatformDependency/OnMetal/Mesh/MeshMetal.h>

NS_ASSUME_NONNULL_BEGIN

@interface CommandBufferMetal : BaseMetalObject

@property(strong, nonatomic)id<MTLRenderCommandEncoder> renderCommandEncoder;

-(void)setLabel:(NSString*)name;

-(void)setMaterial:(MaterialMetal*)material props:(std::vector<MaterialSys::MaterialProp*>*)props tables:(std::vector<MaterialSys::MaterialTable*>*)tables;

-(void)drawMesh:(MeshMetal*)meshObj;

-(void)beginFrame;

-(void)reset;

-(void)commit:(bool)present;

@end

NS_ASSUME_NONNULL_END
