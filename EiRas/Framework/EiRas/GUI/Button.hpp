#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "View.hpp"
#include "Response.hpp"

namespace GUISys
{
    class Button: public View
    {
    public:
        Button();
        Response* m_Response;
        virtual void SetFrame(Math::rect_float frame);

        virtual void OnEvent(ResponseDataBase* data);
    protected:
    };
}

#endif