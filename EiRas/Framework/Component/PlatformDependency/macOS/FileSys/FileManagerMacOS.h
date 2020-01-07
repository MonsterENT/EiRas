//
//  FileManagerMacOS.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/5/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FileManagerMacOS : NSObject

+(NSString*)getResourcePath:(NSString*)resName type:(NSString*)type;

@end

NS_ASSUME_NONNULL_END
