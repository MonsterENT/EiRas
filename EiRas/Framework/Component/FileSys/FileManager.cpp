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

#define COMMON_PATH_STR_LEN 150

static FileManager* _instance = 0;

static char* g_ResPath = 0;

#if GRAPHICS_METAL
inline void GetPathOnMac(std::string resName, std::string type)
{
    const char* tSource = getResourcePathMacOs(resName, type);
    size_t len = strlen(tSource) + 1;
    memcpy(g_ResPath, tSource, sizeof(char) * len);
}
#endif

FileManager* FileManager::shareInstance()
{
    if(_instance == 0)
    {
        _instance = new FileManager();
        g_ResPath = new char[COMMON_PATH_STR_LEN];
    }
    return _instance;
}

const char * FileManager::GetResourcePath(std::string resName, std::string type)
{
#if GRAPHICS_METAL
    GetPathOnMac(resName, type);
#endif
    
#if GRAPHICS_DX
    std::string tmpPath = "";
    tmpPath += FileManagerWin::GetProjectBasePath();
    tmpPath += "Common\\Resource\\";
    tmpPath += resName + "." + type;
    memcpy(g_ResPath, tmpPath.c_str(), COMMON_PATH_STR_LEN * sizeof(char));
#endif
    return g_ResPath;
}

const char * FileManager::GetTextureResourcePath(std::string resName, std::string type)
{
#if GRAPHICS_METAL
    GetPathOnMac(resName, type);
#endif
    
#if GRAPHICS_DX
    std::string tmpPath = "";
    tmpPath += FileManagerWin::GetProjectBasePath();
    tmpPath += "Common\\Resource\\Texture\\";
    tmpPath += resName + "." + type;
    memcpy(g_ResPath, tmpPath.c_str(), COMMON_PATH_STR_LEN * sizeof(char));
#endif
    return g_ResPath;
}

const char * FileManager::GetModelResourcePath(std::string resName, std::string type)
{
#if GRAPHICS_METAL
    GetPathOnMac(resName, type);
#endif
    
#if GRAPHICS_DX
    std::string tmpPath = "";
    tmpPath += FileManagerWin::GetProjectBasePath();
    tmpPath += "Common\\Resource\\Model\\";
    tmpPath += resName + "." + type;
    memcpy(g_ResPath, tmpPath.c_str(), COMMON_PATH_STR_LEN * sizeof(char));
#endif
    return g_ResPath;
}
