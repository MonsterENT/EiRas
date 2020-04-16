#ifndef GUI_BASE_HPP
#define GUI_BASE_HPP

#include <string>
#include <Math/Math.hpp>

namespace GUISys
{
    class View;
    class GUIBase
    {
        friend View;
    public:
        GUIBase();
        virtual ~GUIBase()
        {
        }

        virtual void SetFrame(Math::rect_float frame);

    protected:
        Math::rect_float _Frame;
        Math::rect_float _NDC;
    };
}

#endif