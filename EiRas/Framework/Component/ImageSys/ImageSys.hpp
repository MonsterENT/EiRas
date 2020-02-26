#ifndef IMAGE_SYS_HPP
#define IMAGE_SYS_HPP

#include <string>
#include <Global/GlobalDefine.h>

namespace ImageSys
{
    float* LoadImageFromFile(std::string path, int* width, int* height, int* comp);
    void FreeData(void* data);
}

#endif