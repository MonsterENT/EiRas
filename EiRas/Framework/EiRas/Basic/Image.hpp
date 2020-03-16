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
        std::string Name;

        Image(std::string name);

        void LoadFromFile(std::string filePath);

        void LoadFromBuffer(void* buffer, int width, int height, int channels = 4);

        int Width, Height, Channels;

        MaterialSys::GraphicsResource* PipelineResource;

        bool isFinishBuild;

        void Build(void* cmdList);

        void FinishBuild();

    private:
        void buildResourceWithData(void* data);
    };


}

#endif