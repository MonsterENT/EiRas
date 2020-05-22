#include "EventBase.hpp"
#include "GUISystem.hpp"
using namespace GUISys;

EventBase::EventBase()
{
    GUISystem::SharedInstance()->RegEventComponent(this);
}