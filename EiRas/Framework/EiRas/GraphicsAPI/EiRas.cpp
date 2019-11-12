//
//  EiRas.cpp
//  EiRas
//
//  Created by MonsterENT on 11/11/19.
//

#include "EiRas.hpp"

#include <Global/EiRasGlobalManager.hpp>
#include <GraphicsAPI/PlatformDependency/Metal/EiRasMetalBridge.hpp>

//Platform Dependency

using GraphicsAPI::EiRas;

static EiRas* g_instance = 0;

EiRas* EiRas::SharedInstance()
{
    return g_instance;
}

EiRas* EiRas::Create()
{
    g_instance = new EiRas();
    g_instance->PlatformBridge = new EiRasMetalBridge();
    
    //init device
    ((EiRasMetalBridge*)g_instance->PlatformBridge)->InitDevice();
    
    return g_instance;
}

void EiRas::OnUpdate()
{
    
}
