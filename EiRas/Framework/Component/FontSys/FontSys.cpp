#include "FontSys.hpp"
#include "FontManager.hpp"
#include <ft2build.h>
#include <FileSys/FileManager.hpp>
#include FT_FREETYPE_H

#pragma comment( lib,"freetype.lib" )

using std::map;
using std::pair;
using namespace FontSys;

static Font* g_DefaultFont = 0;

Font* Font::GetDefaultFont()
{
    if (g_DefaultFont == 0)
    {
        g_DefaultFont = new Font(FileSys::FileManager::shareInstance()->GetResourcePath("Font\\BELL", "TTF"));
    }
    return g_DefaultFont;
}

Font::Font(std::string filePath)
{
    this->filePath = filePath;
}

Font::~Font()
{
}

bool Font::GetText(std::string text, Text* textObj, int fontSizeInPixel)
{
    textObj->RefTextStr = text;

    FT_Library library;

    FT_Error ft_error;
    ft_error = FT_Init_FreeType(&library);

    if (ft_error)
    {
        return false;
    }

    FT_Face face;
    ft_error = FT_New_Face(library, filePath.c_str(), 0, &face);

    if (ft_error == FT_Err_Cannot_Open_Resource)
    {
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSizeInPixel);

    const char* c_str_text = text.c_str();
    int lens = strlen(c_str_text);

    FT_Vector vector;
    vector.x = 0;
    vector.y = 0;

    for (int i = 0; i < lens; i++)
    {
        char t = c_str_text[i];

        map<char, CharData>::iterator charDataIt = _CachedCharData.find(t);
        if (charDataIt != _CachedCharData.end())
        {
            textObj->_AddFontData(&(charDataIt->second));
            continue;
        }

        FT_Set_Transform(face, 0, &vector);
        ft_error = FT_Load_Char(face, t, FT_LOAD_RENDER);
        FT_Bitmap bitmap = face->glyph->bitmap;

        Math::rect_float outUVRect;
        _uint fontMapIndex = FontManager::SharedInstance()->_StoreFontData(bitmap.buffer, bitmap.width, bitmap.rows, face->glyph->bitmap_left, face->glyph->bitmap_top, outUVRect);

        CharData data = CharData(outUVRect, fontMapIndex);
        _CachedCharData.insert(pair<char, CharData>(t, data));
        textObj->_AddFontData(&data);

        vector.x += face->glyph->advance.x;
        vector.y += face->glyph->advance.y;
    }

    return true;
    //FT_Done_FreeType(library);
    //FT_Done_Face(face);
}

