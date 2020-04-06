#ifndef GUI_BASE_HPP
#define GUI_BASE_HPP

#include <string>
#include <Math/Math.hpp>

namespace GUISys
{
    class GUIBase
    {
    public:
        GUIBase();

        virtual ~GUIBase()
        {
        }

        Math::rect_float frame;

    protected:
        void* _Mesh;
    };
}

#endif