//
//  FileManager.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/5/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "FileManager.hpp"
#include <EiRas/Global/PlatformDefine.h>
#include <Component/PlatformDependency/macOS/FileSys/FileManagerMacOSAdapter.h>

using namespace FileSys;

static FileManager* _instance = 0;

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
    return getResourcePathMacOs(resName, type);
}
