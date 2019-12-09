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

NS_ASSUME_NONNULL_BEGIN

@interface CommandBufferMetal : BaseMetalObject

@property(strong, nonatomic)id<MTLRenderCommandEncoder> renderCommandEncoder;

-(void)setLabel:(NSString*)name;

-(void)setMaterial:(MaterialMetal*)material props:(std::vector<MaterialSys::MaterialProp*>*)props tables:(std::vector<MaterialSys::MaterialTable*>*)tables;

-(void)drawMesh:(void*)meshData dataSize:(int)dataSize index:(int)index;

-(void)beginFrame;

-(void)present;

-(void)commit;

@end

NS_ASSUME_NONNULL_END
