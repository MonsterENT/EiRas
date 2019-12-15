#include "EiRasDX12Bridge.h"
#include "EiRasDX12.h"
#include <Global/EiRasGlobalManager.hpp>

using GraphicsAPI::EiRasDX12Bridge;
using GraphicsAPI::EiRasDX12;
using EiRasGlobal::EiRasGlobalManager;

EiRasDX12Bridge::EiRasDX12Bridge(HWND hwnd, int frameWidth, int frameHeight)
{
    raw_obj = (void*)new EiRasDX12(hwnd, frameWidth, frameHeight);
    EiRasGlobalManager::SharedInstance()->GraphicsAPIDevice = raw_obj;
}

void EiRasDX12Bridge::InitDevice()
{
    ((EiRasDX12*)raw_obj)->InitDevice();
}