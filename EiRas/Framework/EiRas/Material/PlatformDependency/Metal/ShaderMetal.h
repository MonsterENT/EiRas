//
//  ShaderMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OnMetal/BaseMetalObject.h>

@interface ShaderMetal : BaseMetalObject

-(instancetype)initWithFileName:(NSString*)fileName vertexFuncName:(NSString*)vertexFuncName pixelFuncName:(NSString*)pixelFuncName;

@end

