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
    size_t len = strlen([tmp UTF8String]);
    char* path = new char[len + 1];
    path[len] = '\0';
    memcpy(path, [tmp UTF8String], sizeof(char) * len);
    return path;
}
