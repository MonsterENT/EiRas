#ifndef VIEW_HPP
#define VIEW_HPP

#include "GUIBase.hpp"

namespace GUISys
{
    class View : public GUIBase
    {
    public:
        View();

        virtual void SetFrame(Math::rect_float frame);
    private:
        void* _Mesh;
    };
}

#endif
