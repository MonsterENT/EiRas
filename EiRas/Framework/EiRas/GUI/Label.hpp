#ifndef LABEL_HPP
#define LABEL_HPP

#include "View.hpp"
#include <Math/Math.hpp>
#include <FontSys/FontSys.hpp>
#include <Graphics/RenderData.hpp>

namespace GUISys
{
    class Label : public View
    {
    public:
        Label();

        virtual void NeedLayout();

        void SetText(FontSys::Text* text);
        void DrawView(Graphics::CommandBuffer* cmdBuffer);

        void SetTextColor(Math::float4 textColor)
        {
            _TextColor = textColor;
        }
    private:
        FontSys::Text* _Text;
        void _BuildTextMesh();
        MeshSys::Mesh* _TextMesh;

        Graphics::RenderData* _Render;
        Math::float4 _TextColor;
    };
}

#endif