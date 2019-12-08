//
//  ConstantBufferMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "BaseMetalObject.h"

NS_ASSUME_NONNULL_BEGIN

@interface ConstantBufferMetal : BaseMetalObject

-(instancetype)initWithBufferSize:(int)bufferSize allocMemory:(bool)allocMemory;

@property(strong, nonatomic)id<MTLBuffer> rawBuffer;

@property(assign, readonly, nonatomic)int bufferSize;

@end

NS_ASSUME_NONNULL_END
