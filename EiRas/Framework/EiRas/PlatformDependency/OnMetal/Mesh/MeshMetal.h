//
//  MeshMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/15/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "BaseMetalObject.h"
#include <Global/GlobalDefine.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeshMetal : BaseMetalObject

-(instancetype)initWithVertexRes:(id)vertexRes indexRes:(id)indexRes vertexCount:(_uint)vertexCount indexCount:(_uint)indexCount vertexBufferIndex:(_uint)vertexBufferIndex indexBufferIndex:(_uint)indexBufferIndex;

@property(strong, readonly, nonatomic)id<MTLBuffer> vertexBuffer;
@property(strong, readonly, nonatomic)id<MTLBuffer> indexBuffer;

@property(assign, readonly, nonatomic)_uint vertexBufferIndex;
@property(assign, readonly, nonatomic)_uint indexBufferIndex;

@property(assign, readonly, nonatomic)_uint vertexCount;
@property(assign, readonly, nonatomic)_uint indexCount;

@end

NS_ASSUME_NONNULL_END
