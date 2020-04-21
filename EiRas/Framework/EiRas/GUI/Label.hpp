#ifndef LABEL_HPP
#define LABEL_HPP

#include "View.hpp"
#include <FontSys/FontSys.hpp>

namespace GUISys
{
    class Label : public View
    {
    public:
        Label();

        void SetText(FontSys::Text* text);
    private:
        FontSys::Text* _Text;

        void _BuildTextMesh();
    };
}

#endif