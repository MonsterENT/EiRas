#ifndef Common_Blur_Hpp
#define Common_Blur_Hpp

#include <Global/GlobalDefine.h>
#include <Graphics/RenderTexture.hpp>

namespace Effect
{
    class CommonBlur
    {
    public:
        CommonBlur(_uint width, _uint height);

        _uint BlitTimes;
        float BlurCoef;

        _uint Width, Height;

        Graphics::RenderTexture* BluredRT;
    private:
        Graphics::RenderTexture* _TmpBluredRT;
    };
}

#endif