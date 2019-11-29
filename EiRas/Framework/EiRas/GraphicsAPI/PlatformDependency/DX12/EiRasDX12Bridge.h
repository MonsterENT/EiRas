#pragma once
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace GraphicsAPI {

    class EiRasDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        EiRasDX12Bridge(HWND hwnd, int frameWidth, int frameHeight);
        void InitDevice();
    };
}

