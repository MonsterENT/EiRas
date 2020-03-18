#include "FontManager.hpp"
using namespace FontSys;
using namespace Math;

FontManager* FontManager::g_Instance = 0;

void _ScanToBuffer(unsigned char* dstBuffer, int dstBufferWidth, int dstBufferHeight, int dstLeft, int dstTop, unsigned char* srcBuffer, int srcBufferWidth, int srcBufferHeight)
{
    for (int row = dstTop, src_row = 0; row < dstTop + srcBufferWidth; row++, src_row++)
    {
        for (int col = dstLeft, dst_col = 0; col < dstLeft + srcBufferHeight; col++, dst_col++)
        {
            if (row > dstBufferHeight || col > dstBufferWidth)
            {
                continue;
            }
            dstBuffer[row * dstBufferWidth + col] = srcBuffer[src_row * srcBufferWidth + dst_col];
        }
    }
}

bool FontMap::StoreFontData(unsigned char* data, _uint width, _uint height, _uint offsetX, _uint offsetY, Math::rect_float &outUVRect)
{
    //check width
    if (_Left + width < FONT_MAP_WIDTH)
    {
        if (_Top + height < FONT_MAP_HEIGHT)
        {
            //WriteBuffer
            //_ScanToBuffer(refFontMap->data, FONT_MAP_WIDTH, FONT_MAP_HEIGHT, refFontMap->_Left, refFontMap->_Top, data, width, height);
            return true;
        }
        else
        {
        }
    }
    else
    {
        if (width < FONT_MAP_WIDTH)
        {
            if (_UsedHeight + height < FONT_MAP_HEIGHT)
            {
                //WriteBuffer
                return true;
            }
        }
        else
        {
        }
    }
    return false;
}


FontManager::FontManager()
{

}

Font* FontManager::GetFont(std::string filePath)
{
    return 0;
}

void FontManager::_StoreFontData(unsigned char* data, _uint width, _uint height, _uint offsetX, _uint offsetY, Math::rect_float& outUVRect)
{
    FontMap* refFontMap = 0;
    if (fontDataList.size() > 0)
    {
        refFontMap = fontDataList[fontDataList.size() - 1];
        refFontMap = refFontMap->isFull ? 0 : refFontMap;
    }

    if (refFontMap == 0)
    {
        refFontMap = new FontMap();
        fontDataList.push_back(refFontMap);
    }

    if (!refFontMap->StoreFontData(data, width, height, offsetX, offsetY, outUVRect))
    {
        refFontMap = new FontMap();
        refFontMap->StoreFontData(data, width, height, offsetX, offsetY, outUVRect);
        fontDataList.push_back(refFontMap);
    }
}