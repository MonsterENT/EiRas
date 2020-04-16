#ifndef GUI_SYSTEM_HPP
#define GUI_SYSTEM_HPP

#include <Global/GlobalDefine.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Math/Math.hpp>

namespace GUISys
{
    class GUIBase;
    class GUISystem
    {
        friend GUIBase;
    public:
        static GUISystem* CreateSystem(_uint width, _uint height);
        static GUISystem* SharedInstance();
        GUISystem(_uint width, _uint height);
        void RunLoopInvoke(void* msg);

        EiRasPlatformBridgeProtocol* PlatformBridge;

    protected:
        _uint _Height, _Width;
        void FrameToNDC(Math::rect_float frame, Math::rect_float& NDC);
        void RegGUIComponent(GUIBase* comp);
    };
}

#endif