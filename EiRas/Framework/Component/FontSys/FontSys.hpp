#ifndef Font_Sys_Hpp
#define Font_Sys_Hpp

#include <string>
#include <Math/Math.hpp>
#include <Global/GlobalDefine.h>
#include <vector>
#include <map>

namespace FontSys
{
    class FontManager;
    class FontMap;
    class Font;

    typedef struct CharData
    {
        Math::rect_float MappingRect;
        _uint FontMapIndex;
        CharData()
        {
        }

        CharData(Math::rect_float rect, _uint mapIndex)
        {
            MappingRect = rect;
            FontMapIndex = mapIndex;
        }
    } CharData;

    class Text
    {
        friend Font;
    public:
        std::string RefTextStr;
        void _AddFontData(const CharData* data)
        {
            CharDataList.push_back(CharData(data->MappingRect, data->FontMapIndex));
        }
        std::vector<CharData> CharDataList;
    };

    class Font
    {
        friend FontManager;
        friend FontMap;
    public:
        Font(std::string filePath);
        ~Font();
        Text* GetText (std::string text, int fontSizeInPixel = 16);

    private:
        std::string filePath;

        std::map<char, CharData> _CachedCharData;
    };
}

#endif