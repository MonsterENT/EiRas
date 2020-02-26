#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <Global/GlobalDefine.h>
#include <vector>

namespace MaterialSys
{
    class GraphicsResource;
}

namespace ImageSys
{
    class Image;

    extern std::vector<Image*> ImageSysBuildingList;

    class Image
    {
    public:

        Image(std::string filePath);

        int Width, Height, Channels;

        MaterialSys::GraphicsResource* PipelineResource;

        bool isFinishBuild;

        void Build(void* cmdList);

        void FinishBuild();
    };


}

#endif