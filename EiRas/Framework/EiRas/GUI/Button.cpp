#include "Button.hpp"
using namespace GUISys;

Button::Button()
{
    m_Response = NULL;
}

void Button::SetFrame(Math::rect_float frame)
{
    View::SetFrame(frame);
}

void Button::OnEvent(ResponseDataBase* data)
{
    View::OnEvent(data);
    if (m_Response)
    {
        m_Response->InvokeWithData((ResponseDataBase*)data);
    }
}