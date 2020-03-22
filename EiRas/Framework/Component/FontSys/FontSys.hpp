#ifndef Font_Sys_Hpp
#define Font_Sys_Hpp

#include <string>
#include <Math/Math.hpp>
#include <Global/GlobalDefine.h>
#include <vector>

namespace FontSys
{
    class FontManager;
    class FontMap;
    class Font;

    class Text
    {
        friend Font;
    public:
    private:
        void _AddFontData(_uint fontMapIndex, Math::rect_float uvRect)
        {
            _FontMapIndex.push_back(fontMapIndex);
            _MappingRect.push_back(uvRect);
        }
        std::vector<_uint> _FontMapIndex;
        std::vector<Math::rect_float> _MappingRect;
    };

    class Font
    {
        friend FontManager;
        friend FontMap;
    public:
        Font(std::string filePath);
        ~Font();
        Text* GetText(std::string text, int fontSizeInPixel = 16);

    private:
        std::string filePath;
    };
}

#endif