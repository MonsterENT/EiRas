#include "GUISystemDX12.hpp"
#include <Windows.h>
#include <atltypes.h>
#include <string>
#include <GUI/GUIBase.hpp>

using std::string;
using namespace GUISys;

void GUISystemDX12::RunLoopInvoke(void* msg)
{
    MSG* m_msg = (MSG*)msg;

    switch (m_msg->message)
    {
    case WM_KEYDOWN:
        break;
    case WM_LBUTTONDOWN:
    {
        RECT clientRect;
        GetClientRect(m_msg->hwnd, &clientRect);
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(m_msg->hwnd, &pt);
        _EventCommonData.MouseClickNDCPos.x = pt.x / (float)(clientRect.right) * 2.0f - 1.0f;
        _EventCommonData.MouseClickNDCPos.y = 1.0f - pt.y / (float)(clientRect.bottom) * 2.0f;
        if (_EventResponse)
        {
            _EventResponse->InvokeWithData(&_EventCommonData);
        }
    }
    break;
    default:
        break;
    }
}