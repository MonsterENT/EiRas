#ifndef GUI_SYSTEM_DX12_BRIDGE_HPP
#define GUI_SYSTEM_DX12_BRIDGE_HPP
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <GUI/Response.hpp>

namespace GUISys
{
    class GUISystemDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GUISystemDX12Bridge();
        void SetEventResponse(Response* response);

        void RunLoopInvoke(void* msg);
    };
}

#endif