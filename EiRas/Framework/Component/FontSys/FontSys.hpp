#ifndef Font_Sys_Hpp
#define Font_Sys_Hpp

#include <string>

namespace FontSys
{
    class FontManager;
    class FontMap;
    class Font
    {
        friend FontManager;
        friend FontMap;
    public:
        Font(std::string filePath);
        ~Font();
        void GetText(std::string text, int fontSizeInPixel = 16);

        int width, height;
        unsigned char* data;

    private:
        std::string filePath;
    };
}

#endif