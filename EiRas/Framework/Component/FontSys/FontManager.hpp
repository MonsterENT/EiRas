#ifndef Font_Manager_Hpp
#define Font_Manager_Hpp

#include <vector>
#include <string>
#include <Global/GlobalDefine.h>
#include <Math/Math.hpp>
#define FONT_MAP_HEIGHT 1024
#define FONT_MAP_WIDTH 1024

namespace FontSys
{
    class FontManager;
    class Font;
    class FontMap
    {
        friend FontManager;
    public:
        bool isFull;
        unsigned char* data;
        FontMap()
        {
            isFull = false;
            _Left = 0;
            _Top = 0;
            _RC = 0;
            _UsedHeight = 0;
            data = new unsigned char[FONT_MAP_HEIGHT * FONT_MAP_WIDTH];
            memset(data, 0, FONT_MAP_HEIGHT * FONT_MAP_WIDTH);
        }

        bool StoreFontData(unsigned char* data, _uint width, _uint height, _uint offsetX, _uint offsetY, Math::rect_float &outUVRect);

    private:
        _uint _RC;
        _uint _Left;
        _uint _Top;
        _uint _UsedHeight;
    };
    class FontManager
    {
        friend Font;
    public:
        static FontManager* SharedInstance()
        {
            if (g_Instance == 0)
            {
                g_Instance = new FontManager();
            }
            return g_Instance;
        }

        FontManager();

        Font* GetFont(std::string filePath);

    private:
        static FontManager* g_Instance;
        std::vector<FontMap*> fontDataList;

        _uint _StoreFontData(unsigned char* data, _uint width, _uint height, _uint offsetX, _uint offsetY, Math::rect_float& outUVRect);
    };
}

#endif