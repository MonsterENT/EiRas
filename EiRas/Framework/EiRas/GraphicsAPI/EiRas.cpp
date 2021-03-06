//
//  EiRas.cpp
//  EiRas
//
//  Created by MonsterENT on 11/11/19.
//

#include "EiRas.hpp"

#include <Global/EiRasGlobalManager.hpp>

//Platform Dependency
#if GRAPHICS_DX
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12Bridge.h>
#endif

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/GraphicsAPI/EiRasMetalBridge.hpp>
#endif

#define PLATFORM_BRIDGE 

using GraphicsAPI::EiRas;

static EiRas* g_instance = 0;

EiRas* EiRas::SharedInstance()
{
    return g_instance;
}
#if GRAPHICS_DX
EiRas* EiRas::Create(HWND hwnd, int frameWidth, int frameHeight)
{
    g_instance = new EiRas();
    g_instance->PlatformBridge = new EiRasDX12Bridge(hwnd, frameWidth, frameHeight);
    //init device
    ((EiRasDX12Bridge*)g_instance->PlatformBridge)->InitDevice();
    return g_instance;
}
#endif

#if GRAPHICS_METAL
EiRas* EiRas::Create()
{
    g_instance = new EiRas();
    g_instance->PlatformBridge = new EiRasMetalBridge();
    //init device
    ((EiRasMetalBridge*)g_instance->PlatformBridge)->InitDevice();
    return g_instance;
}
#endif

void EiRas::OnUpdate()
{
    
}
