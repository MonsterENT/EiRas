#include "GUIBase.hpp"
#include "GUISystem.hpp"
using namespace GUISys;

GUIBase::GUIBase()
{
    _ParentNode = 0;
}

void GUIBase::SetFrame(Math::rect_float frame)
{
    _RelativeFrame = frame; 
    NeedLayout();
    for (int i = 0; i < _SubNodes.size(); i++)
    {
        _SubNodes[i]->NeedLayout();
    }
}

void GUIBase::NeedLayout()
{
    _Frame = _RelativeFrame;
    if (_ParentNode != 0)
    {
        _Frame.top += _ParentNode->_Frame.top;
        _Frame.top += _ParentNode->_Frame.top;
    }
    GUISystem::SharedInstance()->FrameToNDC(_Frame, _NDC);
}