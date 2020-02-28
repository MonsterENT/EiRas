#include "ImageSys.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


unsigned char* ImageSys::LoadImageFromFile(std::string path, int* width, int* height, int* comp)
{
    return stbi_load(path.c_str(), width, height, comp, 0);
}

void ImageSys::FreeData(void* data)
{
    stbi_image_free(data);
}
