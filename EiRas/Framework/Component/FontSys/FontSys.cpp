#include "FontSys.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

#pragma comment( lib,"freetype.lib" )

using namespace FontSys;

void scanToBuffer(unsigned char* dstBuffer, int dstBufferWidth, int dstBufferHeight, FT_Bitmap bitmap, int x, int y)
{
    for (int row = y, src_row = 0; row < y + bitmap.rows; row++, src_row++)
    {
        for (int col = x, dst_col = 0; col < x + bitmap.width; col++, dst_col ++)
        {
            if (row > dstBufferHeight || col * 4 + 3 > dstBufferWidth || col * 4 + 2 > dstBufferWidth || col * 4 + 1 > dstBufferWidth || col * 4 > dstBufferWidth)
            {
                continue;
            }
            dstBuffer[row * dstBufferWidth * 4 + col * 4] = bitmap.buffer[src_row * bitmap.width + dst_col];
            dstBuffer[row * dstBufferWidth * 4 + col * 4 + 1] = bitmap.buffer[src_row * bitmap.width + dst_col];
            dstBuffer[row * dstBufferWidth * 4 + col * 4 + 2] = bitmap.buffer[src_row * bitmap.width + dst_col];
            dstBuffer[row * dstBufferWidth * 4 + col * 4 + 3] = bitmap.buffer[src_row * bitmap.width + dst_col];
        }
    }
}

Font::Font(std::string filePath)
{
    this->filePath = filePath;
}

Font::~Font()
{
}

void Font::GetText(std::string text, int fontSizeInPixel)
{
    FT_Library library;

    FT_Error ft_error;
    ft_error = FT_Init_FreeType(&library);

    if (ft_error)
    {
        return;
    }

    FT_Face face;
    ft_error = FT_New_Face(library, filePath.c_str(), 0, &face);

    if (ft_error == FT_Err_Cannot_Open_Resource)
    {
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSizeInPixel);

    const char* c_str_text = text.c_str();
    int lens = strlen(c_str_text);

    FT_Vector vector;
    vector.x = 0;
    vector.y = 0;

    int BufferWidth = 1024, BufferHeight = 1024, BufferSize = BufferWidth * BufferHeight * 4;
    
    data = new unsigned char[BufferSize];
    memset(data, 0, BufferSize);
    for (int i = 0; i < lens; i++)
    {
        FT_Set_Transform(face, 0, &vector);
        ft_error = FT_Load_Char(face, c_str_text[i], FT_LOAD_RENDER);

        scanToBuffer(data, BufferWidth, BufferHeight, face->glyph->bitmap, face->glyph->bitmap_left, face->glyph->bitmap_top);

        vector.x += face->glyph->advance.x;
        vector.y += face->glyph->advance.y;
    }

    width = BufferWidth;
    height = BufferHeight;

    //FT_Done_FreeType(library);
    //FT_Done_Face(face);
}

