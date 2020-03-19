//
//  GraphicsResourceHeapMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "BaseMetalObject.h"
#include <Material/MaterialLayout.hpp>

using namespace MaterialSys;

@interface GraphicsResourceHeapMetal : BaseMetalObject

-(instancetype)initWithPropCount:(_uint)propCount;

@property(strong, nonatomic)id<MTLHeap> resourceHeap;

@end
