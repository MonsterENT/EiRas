#include "GUISystemDX12Bridge.hpp"
#include "GUISystemDX12.hpp"
using namespace GUISys;

GUISystemDX12Bridge::GUISystemDX12Bridge()
{
    raw_obj = new GUISystemDX12();
}

void GUISystemDX12Bridge::RunLoopInvoke(void* msg)
{
    ((GUISystemDX12*)raw_obj)->RunLoopInvoke(msg);
}

void GUISystemDX12Bridge::SetEventResponse(Response* response)
{
    ((GUISystemDX12*)raw_obj)->SetEventResponse(response);
}