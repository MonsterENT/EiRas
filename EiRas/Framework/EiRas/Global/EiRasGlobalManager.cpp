//
//  EiRasGlobalManager.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "EiRasGlobalManager.hpp"
using EiRasGlobal::EiRasGlobalManager;

static EiRasGlobalManager* g_globalManager = 0;

EiRasGlobalManager* EiRasGlobalManager::SharedInstance()
{
    if(g_globalManager == 0)
    {
        g_globalManager = new EiRasGlobalManager();
    }
    return g_globalManager;
}
