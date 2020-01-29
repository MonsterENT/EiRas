//
//  FileManagerMacOSAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/5/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "FileManagerMacOSAdapter.h"
#import "FileManagerMacOS.h"

const char* FileSys::getResourcePathMacOs(std::string resName, std::string type)
{
    NSString* tmp = [FileManagerMacOS getResourcePath:[NSString stringWithUTF8String:resName.c_str()] type:[NSString stringWithUTF8String:type.c_str()]];
    return [tmp UTF8String];
}
