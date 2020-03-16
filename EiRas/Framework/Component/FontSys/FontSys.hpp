#ifndef Font_Sys_Hpp
#define Font_Sys_Hpp

#include <string>

namespace FontSys
{
    class Font
    {
    public:
        Font(std::string filePath);
        ~Font();
        void InitData(std::string text, int fontSizeInPixel = 16);

        int FontSizeInPixel;

        int width, height;
        unsigned char* data;

    private:
        std::string filePath;
    };
}

#endif