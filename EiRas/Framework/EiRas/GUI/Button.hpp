#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "GUIBase.hpp"

namespace GUISys
{
    class Button: public GUIBase
    {
    public:
        Button();

        virtual void SetFrame(Math::rect_float frame);
    };
}

#endif