#include "CommonBlur.hpp"
using namespace Effect;
using namespace Graphics;

CommonBlur::CommonBlur(_uint width, _uint height)
{
    Width = width;
    Height = height;
    BlitTimes = 8;
    BlurCoef = 1;

    BluredRT = new RenderTexture("Common Blur", RenderBufferFormat::R8G8B8A8_UNORM, false, width, height);
    _TmpBluredRT = new RenderTexture("Common Blur Tmp", RenderBufferFormat::R8G8B8A8_UNORM, false, width, height);
}