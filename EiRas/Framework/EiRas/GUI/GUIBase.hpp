#ifndef GUI_BASE_HPP
#define GUI_BASE_HPP

#include <string>
#include <Math/Math.hpp>

namespace Graphics
{
    class CommandBuffer;
}

namespace GUISys
{
    class View;
    class GUISystem;
    class GUIBase
    {
        friend View;
        friend GUISystem;
    public:
        GUIBase();
        virtual ~GUIBase()
        {
        }

        virtual void SetFrame(Math::rect_float frame);

    protected:
        virtual void DrawView(Graphics::CommandBuffer* cmdBuffer)
        {
        }
        Math::rect_float _Frame;
        Math::rect_float _NDC;
    };
}

#endif