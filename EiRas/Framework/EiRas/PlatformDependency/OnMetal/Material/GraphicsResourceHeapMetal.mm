//
//  GraphicsResourceHeapMetal.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import "GraphicsResourceHeapMetal.h"
#include <Global/EiRasGlobalManager.hpp>
#import <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetal.h>
#include <PlatformDependency/OnMetal/MetalMacro.h>

#include "ConstantBufferMetal.h"

@implementation GraphicsResourceHeapMetal

-(instancetype)initWithGraphicsResource:(NSArray<id>*)resArray
{
    self = [super init];
    if(self)
    {
        GET_EIRAS_METAL(deviceObj)
        MTLHeapDescriptor* desc = [[MTLHeapDescriptor alloc] init];
        desc.storageMode = MTLStorageModeShared;
        desc.size = 0;
        
        _resourceHeap = [[deviceObj getMetalDevice] newHeapWithDescriptor:desc];
        
        int allocOffset = 0;
        for(id resMetalObj in resArray)
        {
            if([resMetalObj isKindOfClass:[ConstantBufferMetal class]])
            {
                ConstantBufferMetal* tmpCBObj = resMetalObj;
                tmpCBObj.rawBuffer = [_resourceHeap newBufferWithLength:tmpCBObj.bufferSize options:MTLStorageModeShared offset:allocOffset];
                allocOffset += tmpCBObj.bufferSize;
            }
        }
    }
    return self;
}

@end
