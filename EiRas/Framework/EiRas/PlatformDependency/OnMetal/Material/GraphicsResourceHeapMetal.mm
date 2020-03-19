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
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnMetal/Material/GraphicsResourceMetalBridge.hpp>
#include <PlatformDependency/OnMetal/Material/GraphicsResourceMetal.h>
#include "ConstantBufferMetal.h"

@implementation GraphicsResourceHeapMetal

-(instancetype)initWithPropCount:(_uint)propCount
{
    self = [super init];
    if(self)
    {
        GET_EIRAS_METAL(deviceObj)
        MTLHeapDescriptor* desc = [[MTLHeapDescriptor alloc] init];
        desc.storageMode = MTLStorageModeShared;
        desc.size = propCount;
        
        _resourceHeap = [[deviceObj getMetalDevice] newHeapWithDescriptor:desc];
        
//        int allocOffset = 0;
//        for(_uint i = 0; i < tableCount; i++)
//        {
//            MaterialTable* table = tableArray[i];
//            for(_uint propIndex = 0; propIndex < table->PropNum; propIndex++)
//            {
//                MaterialProp* prop = table->Props[propIndex];
//                id rawObj = (__bridge id)prop->Resource->PlatformBridge->raw_obj;
//                
//                if([rawObj isKindOfClass:[ConstantBufferMetal class]])
//                {
//                    ConstantBufferMetal* tmpCBObj = rawObj;
//                    if (@available(iOS 13.0, *)) {
//                        tmpCBObj.rawBuffer = [_resourceHeap newBufferWithLength:tmpCBObj.bufferSize options:MTLStorageModeShared offset:allocOffset];
//                    } else {
//                        [_resourceHeap newBufferWithLength:tmpCBObj.bufferSize options:MTLResourceStorageModeShared];
//                    }
//                    allocOffset += tmpCBObj.bufferSize;
//                }
//            }
//        }
    }
    return self;
}

-(void)setLabel:(NSString *)name
{
    [_resourceHeap setLabel:name];
}

@end
