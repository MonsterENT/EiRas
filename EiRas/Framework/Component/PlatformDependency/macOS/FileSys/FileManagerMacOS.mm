//
//  FileManagerMacOS.m
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/5/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#import "FileManagerMacOS.h"

@implementation FileManagerMacOS

+(NSString*)getResourcePath:(NSString*)resName type:(NSString*)type
{
    return [[NSBundle mainBundle]pathForResource:resName ofType:type];
}

@end
