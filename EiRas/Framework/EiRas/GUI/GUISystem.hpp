#ifndef GUI_SYSTEM_HPP
#define GUI_SYSTEM_HPP

#include <Global/GlobalDefine.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Math/Math.hpp>
#include <vector>

namespace MaterialSys
{
    class Material;
    class Shader;
}

namespace Graphics
{
    class CommandBuffer;
}

namespace GUISys
{
    class GUIBase;
    class EventBase;
    class View;
    class Label;
    class GUISystem
    {
        friend GUIBase;
        friend EventBase;
        friend View;
        friend Label;
    public:
        static GUISystem* CreateSystem(_uint width, _uint height, Graphics::CommandBuffer* cmdBuffer);
        static GUISystem* SharedInstance();
        GUISystem(_uint width, _uint height, Graphics::CommandBuffer* cmdBuffer);
        void RunLoopInvoke(void* msg);

        EiRasPlatformBridgeProtocol* PlatformBridge;

        void GetFrameSize(_uint& width, _uint& height)
        {
            width = _Width;
            height = _Height;
        }

    protected:
        _uint _Height, _Width;

        Graphics::CommandBuffer* _CmdBuffer;
        void FrameToNDC(Math::rect_float frame, Math::rect_float& NDC);
        void RegGUIComponent(GUIBase* comp);
        void RegEventComponent(EventBase* comp);
        std::vector<GUIBase*> _RegedGUIComp;
        std::vector<EventBase*> _RegedEventComp;
    };
}

#endif