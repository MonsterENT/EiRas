//
//  LogManagerMacOS.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/7/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LogManagerMacOS : NSObject

+(void)DebugPrint:(NSString*)str;

@end

NS_ASSUME_NONNULL_END
