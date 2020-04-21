#ifndef VIEW_HPP
#define VIEW_HPP

#include "GUIBase.hpp"
#include <Math/Math.hpp>
#include "Response.hpp"

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

        virtual void SetBackgroundColor(Math::float4 color);
        virtual void SetFrame(Math::rect_float frame);
        virtual void DrawView(Graphics::CommandBuffer* cmdBuffer);

        virtual void OnEvent(ResponseDataBase* data)
        {
            GUIBase::OnEvent(data);
        }
    protected:

    private:
        void* _Mesh;
        MaterialSys::Material* _Material;
        Math::float4 _BackgroundColor;
    };
}

#endif
