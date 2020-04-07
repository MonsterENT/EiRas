#ifndef Common_Blur_Hpp
#define Common_Blur_Hpp

#include <Global/GlobalDefine.h>
#include <Graphics/RenderTexture.hpp>

namespace MaterialSys
{
    class Material;
    class Shader;
}

namespace Graphics
{
    class CommandBuffer;
}

namespace Effect
{
    class CommonBlur
    {
    public:
        CommonBlur(_uint width, _uint height, Graphics::CommandBuffer* refCmdBuffer);
        _uint Width, Height;

        void ProcessWithSource(Graphics::RenderTexture* src, _uint blitTimes, float blurCoef);
        void ProcessWithSource(MaterialSys::GraphicsResource* src, _uint blitTimes, float blurCoef);

        Graphics::RenderTexture* _TmpBluredRT;
        Graphics::RenderTexture* BluredRT;
    private:


        MaterialSys::Material* _Material;
        MaterialSys::Shader* _Shader;
        Graphics::CommandBuffer* _RefCmdBuffer;
    };
}

#endif