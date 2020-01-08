//
//  FileManager.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/5/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "FileManager.hpp"
#include <EiRas/Global/PlatformDefine.h>

#if GRAPHICS_METAL
#include <Component/PlatformDependency/macOS/FileSys/FileManagerMacOSAdapter.h>
#endif

#if GRAPHICS_DX
#include <Component/PlatformDependency/Windows/FileSys/FileManagerWin.hpp>

#endif

using namespace FileSys;

static FileManager* _instance = 0;

static char* g_ResPath = 0;

FileManager* FileManager::shareInstance()
{
    if(_instance == 0)
    {
        _instance = new FileManager();
         
    }
    return _instance;
}

const char * FileManager::GetResourcePath(std::string resName, std::string type)
{
    if (g_ResPath == 0)
    {
        g_ResPath = new char[150];
    }

#if GRAPHICS_METAL
    return getResourcePathMacOs(resName, type);
#endif

#if GRAPHICS_DX
    std::string tmpPath = "";
    tmpPath += FileManagerWin::GetResourcePath();
    tmpPath += resName + "." + type;
    memcpy(g_ResPath, tmpPath.c_str(), 150 * sizeof(char));
    return g_ResPath;
#endif
}
