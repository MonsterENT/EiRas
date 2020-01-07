//
//  LogManagerMacOS.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/7/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#import "LogManagerMacOS.h"

@implementation LogManagerMacOS

+(void)DebugPrint:(NSString*)str
{
    NSLog(@"%@", str);
}

@end
