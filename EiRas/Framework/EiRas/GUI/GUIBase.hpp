#ifndef GUI_BASE_HPP
#define GUI_BASE_HPP

#include <string>

namespace GUISys
{
    class GUIBase
    {
    public:
        GUIBase();

        virtual ~GUIBase()
        {
        }
    protected:
        void* _Mesh;
    };
}

#endif