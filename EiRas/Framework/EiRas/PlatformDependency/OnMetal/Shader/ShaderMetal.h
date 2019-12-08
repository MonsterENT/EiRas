//
//  ShaderMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PlatformDependency/OnMetal/BaseMetalObject.h>

@interface ShaderMetal : BaseMetalObject

-(instancetype)initWithFileName:(NSString*)fileName vertexFuncName:(NSString*)vertexFuncName pixelFuncName:(NSString*)pixelFuncName;

@property(copy, nonatomic)NSString* fileName;
@property(copy, nonatomic)NSString* vertexFuncName;
@property(copy, nonatomic)NSString* pixelFuncName;

@property(strong, nonatomic)id<MTLFunction> vertexFunc;
@property(strong, nonatomic)id<MTLFunction> pixelFunc;

@end

