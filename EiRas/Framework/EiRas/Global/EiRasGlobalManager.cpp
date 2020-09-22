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
    CBViewProjRawRes = 0;
    _CB1 = 0;
}

GraphicsResource* EiRasGlobalManager::GetViewProjRawRes()
{
    if (CBViewProjRawRes == 0)
    {
        CBViewProjRawRes = new GraphicsResource("CBViewProj", GraphicsResourceType::CBV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_HIGH, true);
        CBViewProjRawRes->InitAsConstantBuffer(32 * sizeof(float));
    }
    return CBViewProjRawRes;
}

void EiRasGlobalManager::SetViewProj(const Math::Matrix4X4 WorldToViewMatrix, const Math::Matrix4X4 ProjectionMatrix)
{
    _CBViewProj.ProjectionMatrix = ProjectionMatrix;
    _CBViewProj.WorldToViewMatrix = WorldToViewMatrix;

    GetViewProjRawRes()->SetResource(&_CBViewProj, false);
}