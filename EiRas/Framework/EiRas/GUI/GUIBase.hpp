#ifndef GUI_BASE_HPP
#define GUI_BASE_HPP

#include <string>
#include <Math/Math.hpp>
#include "Response.hpp"

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
        
        Math::rect_float GetFrame()
        {
            return _Frame;
        }

        Math::rect_float GetNDC()
        {
            return _NDC;
        }

        bool CheckNDCRay(Math::float2 rayPoint)
        {
            if (rayPoint.x > _NDC.left && rayPoint.x < _NDC.width + _NDC.left
                && rayPoint.y < _NDC.top && rayPoint.y > _NDC.top - _NDC.height)
            {
                return true;
            }
            return false;
        }

        virtual void OnEvent(ResponseDataBase* data)
        {
        }

    protected:

        virtual void DrawView(Graphics::CommandBuffer* cmdBuffer)
        {
        }
        Math::rect_float _Frame;
        Math::rect_float _NDC;
    };
}

#endif