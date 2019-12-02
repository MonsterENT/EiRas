//
//  EiRasMetalBridge.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "EiRasMetalBridge.hpp"
#include "EiRasMetalAdapter.hpp"
#include <Global/EiRasGlobalManager.hpp>

using GraphicsAPI::EiRasMetalBridge;

EiRasMetalBridge::EiRasMetalBridge()
{
    raw_obj = createMetal();
    EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsAPIDevice = raw_obj;
}

void EiRasMetalBridge::InitDevice()
{
    initMetalDevice(raw_obj);
}

void EiRasMetalBridge::OnUpdate()
{
    
}
