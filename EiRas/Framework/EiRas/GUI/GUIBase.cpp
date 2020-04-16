#include "GUIBase.hpp"
#include "GUISystem.hpp"
using namespace GUISys;

GUIBase::GUIBase()
{
}

void GUIBase::SetFrame(Math::rect_float frame)
{
    _Frame = frame;
    GUISystem::SharedInstance()->FrameToNDC(_Frame, _NDC);
}