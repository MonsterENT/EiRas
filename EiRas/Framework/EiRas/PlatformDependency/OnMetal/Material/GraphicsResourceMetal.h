//
//  GraphicsResourceMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "BaseMetalObject.h"
#import <Global/GlobalDefine.h>

NS_ASSUME_NONNULL_BEGIN

@interface GraphicsResourceMetal : BaseMetalObject

-(instancetype)initWithBufferSize:(_uint)bufferSize initResource:(bool)initResource;

-(void)setResource:(void*)res;

@property(strong, nonatomic)id<MTLBuffer> rawBuffer;

@property(assign, readonly, nonatomic)_uint bufferSize;

@end

NS_ASSUME_NONNULL_END
