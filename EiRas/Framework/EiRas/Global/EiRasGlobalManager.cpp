//
//  EiRasGlobalManager.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "EiRasGlobalManager.hpp"
#include <Material/GraphicsResource.hpp>

using namespace MaterialSys;
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

EiRasGlobalManager::EiRasGlobalManager()
{
    //_CB0 = new GraphicsResource("CommonCB0", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, true, 0);
}
