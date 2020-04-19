#ifndef VIEW_HPP
#define VIEW_HPP

#include "GUIBase.hpp"

namespace MaterialSys
{
    class Material;
}

namespace GUISys
{
    class View : public GUIBase
    {
        friend GUISystem;
    public:
        View();

        virtual void SetFrame(Math::rect_float frame);

        virtual void DrawView(Graphics::CommandBuffer* cmdBuffer);
    private:
        void* _Mesh;
        MaterialSys::Material* _Material;
    };
}

#endif
