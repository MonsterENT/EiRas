#pragma once
#include <Global/EiRasGlobalManager.hpp>

#define GET_EIRAS_DX12(device) EiRasDX12* device = (EiRasDX12*)EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsAPIDevice

#define GET_ACTIVED_CMD(cmd) Graphics::CommandBufferDX12* cmd = (Graphics::CommandBufferDX12*)EiRasGlobal::EiRasGlobalManager::SharedInstance()->GraphicsActivedCmdBuffer