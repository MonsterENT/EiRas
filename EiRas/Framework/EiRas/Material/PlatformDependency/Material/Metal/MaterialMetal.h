//
//  MaterialMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/13/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OnMetal/BaseMetalObject.h>
#include <Graphics/GraphicsRenderState.hpp>
#include <Material/PlatformDependency/Shader/Metal/ShaderMetal.h>

NS_ASSUME_NONNULL_BEGIN

@interface MaterialMetal : BaseMetalObject

-(instancetype)initWithName:(NSString*)name;

-(void)UpdateRenderState:(Graphics::GraphicsRenderState*)renderState Shader:(ShaderMetal*)shaderObj;

@property(copy, nonatomic)NSString* name;

@property(strong, nonatomic)id<MTLRenderPipelineState> pipelineState;

@end

NS_ASSUME_NONNULL_END
