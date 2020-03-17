#include "FontManager.hpp"
using namespace FontSys;

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

FontManager::FontManager()
{

}

Font* FontManager::GetFont(std::string filePath)
{
    return 0;
}

void FontManager::_StoreFontData(unsigned char* data, _uint width, _uint height, _uint offsetX, _uint offsetY)
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

    _ScanToBuffer(refFontMap->data, FONT_MAP_WIDTH, FONT_MAP_HEIGHT, refFontMap->_Left, refFontMap->_Top, data, width, height);
    refFontMap->_Left += offsetX;
    refFontMap->_Top = refFontMap->_Top > offsetY ? refFontMap->_Top : offsetY;
}