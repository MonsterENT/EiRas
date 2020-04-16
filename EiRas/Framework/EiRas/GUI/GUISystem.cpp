#include "GUISystem.hpp"
#include "GUIBase.hpp"

#ifdef GRAPHICS_DX
#include <PlatformDependency/OnDX/GUI/GUISystemDX12Bridge.hpp>
#endif

using namespace GUISys;

static GUISystem* g_guiSystem = 0;

GUISystem* GUISystem::CreateSystem(_uint width, _uint height)
{
    g_guiSystem = new GUISystem(width, height);
    return g_guiSystem;
}

GUISystem* GUISystem::SharedInstance()
{
    return g_guiSystem;
}

GUISystem::GUISystem(_uint width, _uint height)
{
    _Width = width;
    _Height = height;
#ifdef GRAPHICS_DX
    PlatformBridge = new GUISystemDX12Bridge();
#endif

}

void GUISystem::RunLoopInvoke(void* msg)
{
    if (!msg)
    {
        return;
    }
    ((GUISystemDX12Bridge*)PlatformBridge)->RunLoopInvoke(msg);
}

void GUISystem::FrameToNDC(Math::rect_float frame, Math::rect_float& NDC)
{
    NDC.width = frame.width / (float)_Width * 2.0f;
    NDC.height = frame.height / (float)_Height * 2.0f;

    NDC.left = frame.left / (float)_Width * 2.0f - 1.0f;
    NDC.top = frame.top / (float)_Height * 2.0f - 1.0f;
}

void GUISystem::RegGUIComponent(GUIBase* comp)
{
}