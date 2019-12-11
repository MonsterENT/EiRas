//
//  GraphicsResourceMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "BaseMetalObject.h"

NS_ASSUME_NONNULL_BEGIN

@interface GraphicsResourceMetal : BaseMetalObject

-(instancetype)initWithBufferSize:(unsigned int)bufferSize initResource:(bool)initResource;

-(void)setResource:(void*)res shouldUnmap:(bool)shouldUnmap;

@property(strong, nonatomic)id<MTLBuffer> rawBuffer;

@property(assign, readonly, nonatomic)int bufferSize;

@end

NS_ASSUME_NONNULL_END
