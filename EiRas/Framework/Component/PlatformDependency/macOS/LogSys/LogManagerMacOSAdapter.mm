//
//  LogManagerMacOSAdapter.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/7/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "LogManagerMacOSAdapter.hpp"

#import "LogManagerMacOS.h"

void LogSys::DebugPrintMacOS(std::string str)
{
    [LogManagerMacOS DebugPrint:[NSString stringWithUTF8String:str.c_str()]];
}
