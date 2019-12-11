#pragma once
#include <Global/EiRasGlobalManager.hpp>

#define GET_EIRAS_DX12(device) EiRasDX12* device = (EiRasDX12*)EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsAPIDevice;
