//
//  MeshMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/15/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "MeshMetal.h"
#import <PlatformDependency/OnMetal/Material/GraphicsResourceMetal.h>

@implementation MeshMetal

-(instancetype)initWithVertexRes:(id)vertexRes indexRes:(id)indexRes vertexCount:(_uint)vertexCount indexCount:(_uint)indexCount vertexBufferIndex:(_uint)vertexBufferIndex indexBufferIndex:(_uint)indexBufferIndex
{
    self = [super init];
    if(self)
    {
        if([vertexRes isKindOfClass:[GraphicsResourceMetal class]])
        {
            GraphicsResourceMetal* obj = vertexRes;
            _vertexBuffer = obj.rawBuffer;
            _vertexCount = vertexCount;
            _vertexBufferIndex = vertexBufferIndex;
        }
        
        if([indexRes isKindOfClass:[GraphicsResourceMetal class]])
        {
            GraphicsResourceMetal* obj = indexRes;
            _indexBuffer = obj.rawBuffer;
            _indexCount = indexCount;
            _indexBufferIndex = indexBufferIndex;
        }
    }
    return self;
}

@end
