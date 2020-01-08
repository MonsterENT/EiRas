//
//  LogManager.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/7/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "LogManager.hpp"
#if GRAPHICS_METAL
#include "LogManagerMacOSAdapter.hpp"
#endif


char logCache[150];

using LogSys::LogManager;

void _ClearLogCache()
{
    memset(logCache, '\0', sizeof(char) * 150);
}

void LogManager::DebugPrint(std::string str)
{
#if GRAPHICS_METAL
    DebugPrintMacOS(str);
#endif
}

void LogManager::DebugPrint(int i)
{
    _ClearLogCache();
    sprintf(logCache, "%d", i);
    DebugPrint(logCache);
}

void LogManager::DebugPrint(float f)
{
    _ClearLogCache();
    sprintf(logCache, "%f", f);
    DebugPrint(logCache);
}

void LogManager::DebugPrint(double d)
{
    _ClearLogCache();
    sprintf(logCache, "%lf", d);
    DebugPrint(logCache);
}

void LogManager::DebugPrint(_uint ui)
{
    _ClearLogCache();
    sprintf(logCache, "%d", ui);
    DebugPrint(logCache);
}
