#include "FontManager.hpp"
#include <Basic/Image.hpp>

using namespace FontSys;
using namespace Math;
using namespace ImageSys;

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

FontMap::FontMap()
{
    isFull = false;
    _Left = 0;
    _Top = 0;
    _RC = 0;
    _UsedHeight = 0;
    data = new unsigned char[FONT_MAP_HEIGHT * FONT_MAP_WIDTH * 1];
    memset(data, 0, FONT_MAP_HEIGHT * FONT_MAP_WIDTH * 1);
    _FontImage = new Image("Common Font Map");
}

bool FontMap::StoreFontData(unsigned char* data, _uint width, _uint height, _uint offsetX, _uint offsetY, Math::rect_float &outUVRect)
{
    if (_Left + width < FONT_MAP_WIDTH)
    {
        if (_Top + height < FONT_MAP_HEIGHT)
        {
            _ScanToBuffer(this->data, FONT_MAP_WIDTH, FONT_MAP_HEIGHT, _Left, _Top, data, width, height);
            outUVRect.left = (float)_Left / (float)FONT_MAP_WIDTH;
            outUVRect.top = (float)_Top / (float)FONT_MAP_HEIGHT;
            outUVRect.height = (float)height / (float)FONT_MAP_HEIGHT;
            outUVRect.width = (float)width / (float)FONT_MAP_WIDTH;

            _Left += width;
            if (_UsedHeight < _Top + height)
            {
                _UsedHeight = _Top + height;
            }
            
            return true;
        }
    }
    else
    {
        if (width < FONT_MAP_WIDTH)
        {
            if (_UsedHeight + height < FONT_MAP_HEIGHT)
            {
                //WriteBuffer
                _Top = _UsedHeight;
                _UsedHeight = _Top + height;

                _ScanToBuffer(this->data, FONT_MAP_WIDTH, FONT_MAP_HEIGHT, 0, _Top, data, width, height);

                outUVRect.left = (float)_Left / (float)FONT_MAP_WIDTH;
                outUVRect.top = (float)_Top / (float)FONT_MAP_HEIGHT;
                outUVRect.height = (float)height / (float)FONT_MAP_HEIGHT;
                outUVRect.width = (float)width / (float)FONT_MAP_WIDTH;

                _Left += width;
                return true;
            }
        }
    }
    return false;
}
void FontMap::RefreshFontImage()
{
    _FontImage->LoadFromBuffer(data, FONT_MAP_WIDTH, FONT_MAP_HEIGHT, 1);
}

FontManager::FontManager()
{

}

_uint FontManager::_StoreFontData(unsigned char* data, _uint width, _uint height, _uint offsetX, _uint offsetY, Math::rect_float& outUVRect)
{
    _uint fontMapIndex = -1;
    FontMap* refFontMap = 0;
    if (fontDataList.size() > 0)
    {
        refFontMap = fontDataList[fontDataList.size() - 1];
        refFontMap = refFontMap->isFull ? 0 : refFontMap;
    }
    fontMapIndex = fontDataList.size() - 1;

    if (refFontMap == 0)
    {
        refFontMap = new FontMap();
        fontDataList.push_back(refFontMap);
        fontMapIndex++;
    }

    if (!refFontMap->StoreFontData(data, width, height, offsetX, offsetY, outUVRect))
    {
        refFontMap = new FontMap();
        refFontMap->StoreFontData(data, width, height, offsetX, offsetY, outUVRect);
        fontDataList.push_back(refFontMap);
    }
    return fontMapIndex;
}