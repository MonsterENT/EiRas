#ifndef VIEW_HPP
#define VIEW_HPP

#include "GUIBase.hpp"
#include <Math/Math.hpp>
#include "Response.hpp"
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    class Material;
}

namespace Graphics
{
    class RenderTexture;
}

namespace GUISys
{
    class View : public GUIBase
    {
        friend GUISystem;
    public:
        View();

        virtual void SetBackgroundImage(Graphics::RenderTexture* rt);
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
        _uint _UseShaderPass;
    };
}

#endif
