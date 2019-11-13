//
//  CommandBufferMetal.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OnMetal/BaseMetalObject.h>

#import <Metal/Metal.h>

NS_ASSUME_NONNULL_BEGIN

@interface CommandBufferMetal : BaseMetalObject

@property(strong, nonatomic)id<MTLCommandBuffer> commandBuffer;

-(void)setLabel:(NSString*)name;

@end

NS_ASSUME_NONNULL_END
