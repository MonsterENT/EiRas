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
    CBViewProj = new GraphicsResource("CBViewProj", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, true);
    CBViewProj->InitAsConstantBuffer(32 * sizeof(float));

    _CB1 = 0;
}
