//
//  ShaderResourceMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 3/8/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#import "GraphicsResourceMetal.h"

NS_ASSUME_NONNULL_BEGIN

@interface ShaderResourceMetal : GraphicsResourceMetal

-(instancetype)initResource:(_uint)width height:(_uint)height texData:(void*) texData buildStatusFlag:(bool*)buildStatusFlag;

@end

NS_ASSUME_NONNULL_END
