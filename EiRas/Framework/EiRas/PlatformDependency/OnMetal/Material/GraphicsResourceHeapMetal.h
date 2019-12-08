//
//  GraphicsResourceHeapMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "BaseMetalObject.h"

NS_ASSUME_NONNULL_BEGIN

@interface GraphicsResourceHeapMetal : BaseMetalObject

-(instancetype)initWithGraphicsResource:(NSArray<id>*)resArray;

@property(strong, nonatomic)id<MTLHeap> resourceHeap;

@end

NS_ASSUME_NONNULL_END
