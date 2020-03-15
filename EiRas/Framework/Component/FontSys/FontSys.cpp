#include "FontSys.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

#pragma comment( lib,"freetype.lib" )

using namespace FontSys;

unsigned char BUFFER[512][512];

Font::Font(std::string filePath)
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

    FT_Set_Pixel_Sizes(face, 0, 512);

    ft_error = FT_Load_Char(face, 'C', FT_LOAD_RENDER);

    FT_Bitmap bitmap = face->glyph->bitmap;
    for (int row = 0; row < bitmap.rows; row++)
    {
        for (int col = 0; col < bitmap.pitch; col++)
        {
            BUFFER[row][col] = bitmap.buffer[row * bitmap.pitch + col];
        }
    }
}

//    //BELL.TTF