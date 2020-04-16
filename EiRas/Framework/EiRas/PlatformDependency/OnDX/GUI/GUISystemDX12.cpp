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
        RECT windowRect;
        GetWindowRect(m_msg->hwnd, &windowRect);
        _MouseUVPos.x = (m_msg->pt.x - windowRect.left) / (float)(windowRect.right - windowRect.left);
        _MouseUVPos.y = (m_msg->pt.y - windowRect.top) / (float)(windowRect.bottom - windowRect.top);
    }
    break;
    default:
        break;
    }
}